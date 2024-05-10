#include "../include/hgui/header/TextInput.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"
#include "../include/hgui/header/Shader.h"
#include "../include/hgui/header/Label.h"
#include "../include/hgui/header/Font.h"
#include "../include/hgui/header/Drawer.h"
#include "../include/hgui/header/TaskManager.h"

hgui::kernel::TextInput::TextInput(const std::shared_ptr<Shader>& shader, const size& size, const point& position, const std::shared_ptr<Label>& text, const std::pair<color, color>& colors, const std::pair<std::string, color>& placeHolder, const std::pair<color, std::chrono::milliseconds>& caret, Function onChange, const HGUI_PRECISION cornerRadius, const unsigned borderWidth) :
	Widget(shader, size, position),
	m_text(text),
	m_colors(colors),
	m_placeHolder(placeHolder),
	m_onChange(std::move(onChange)),
	m_cornerRadius(std::clamp(cornerRadius, 0.f, 1.f)),
	m_cornerAngularRadius(std::min(m_size.width, m_size.height) * 0.5f * m_cornerRadius),
	m_borderWidth(borderWidth),
	m_inlineRectanglePosition(m_position + point(m_borderWidth)),
	m_inlineRectangleSize(m_size - point(2 * m_borderWidth)),
	m_inlineCornerRadius(std::min(m_inlineRectangleSize.width, m_inlineRectangleSize.height) * 0.5f * m_cornerRadius),
	m_textColor(m_text ? m_text->get_color() : color()),
	m_caret(caret),
	m_caretPosition(0u),
	m_textDisplayedIndex(0u),
	m_drawer(std::make_unique<Drawer>(m_inlineRectanglePosition, m_inlineRectangleSize))
{
	TextInput::set_position(position);
	init_data();
	if (m_text)
	{
		assert_is_displayable(m_placeHolder.first, m_text->get_font());
		m_text->set_alignement(true);
		set_text_placment_and_height();
		update_text();
	}
}

hgui::kernel::TextInput::~TextInput() = default;

void hgui::kernel::TextInput::draw() const
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	m_shader->use().set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f))
	        .set_mat4("modelMatrix", m_modelMatrix.first)
	        .set_vec4("color", m_colors.second);
	m_VAO->bind();
	glDrawArrays(GL_TRIANGLES, 0, 138);
	m_shader->set_mat4("modelMatrix", m_modelMatrix.second)
	        .set_vec4("color", m_colors.first);
	glDrawArrays(GL_TRIANGLES, 138, 138);
	m_VAO->unbind();
	m_drawer->draw();
}

bool hgui::kernel::TextInput::is_inside(const point& point) const
{
	const hgui::point center = m_position + m_size / 2.f;
	const auto A = m_position,
			a = hgui::point(m_position.x + m_cornerAngularRadius, m_position.y + m_cornerAngularRadius),
			ap = hgui::point(m_position.x + m_cornerAngularRadius, m_position.y),
			B = hgui::point(m_position.x + m_size.width, m_position.y),
			b = hgui::point(m_position.x + m_size.width - m_cornerAngularRadius, m_position.y + m_cornerAngularRadius),
			bp = hgui::point(m_position.x + m_size.width - m_cornerAngularRadius, m_position.y),
			C = hgui::point(m_position.x + m_size.width, m_position.y + m_size.height),
			c = hgui::point(m_position.x + m_size.width - m_cornerAngularRadius, m_position.y + m_size.height - m_cornerAngularRadius),
			cp = hgui::point(m_position.x + m_size.width, m_position.y + m_size.height - m_cornerAngularRadius),
			D = hgui::point(m_position.x, m_position.y + m_size.height),
			d = hgui::point(m_position.x + m_cornerAngularRadius, m_position.y + m_size.height - m_cornerAngularRadius),
			dp = hgui::point(m_position.x, m_position.y + m_size.height - m_cornerAngularRadius);

	return point::is_in_rectangle(A, B, D, point) && !((point::is_in_rectangle(ap, a, A, point) && point::distance(point, a) >= m_cornerAngularRadius)
	                                                   || (point::is_in_rectangle(bp, B, b, point) && point::distance(point, b) >= m_cornerAngularRadius)
	                                                   || (point::is_in_rectangle(cp, C, c, point) && point::distance(point, c) >= m_cornerAngularRadius)
	                                                   || (point::is_in_rectangle(dp, d, D, point) && point::distance(point, d) >= m_cornerAngularRadius));
}

unsigned hgui::kernel::TextInput::get_caret_position_from_point(const point& point) const
{
	if (not m_text)
		throw std::runtime_error("TEXT INPUT REQUIRES A LABEL");
	if (not is_inside(point))
		throw std::runtime_error("POINT IS NOT INSIDE THE TEXT INPUT");
	unsigned index = m_textDisplayedIndex;
	const auto text = m_text->get_text();
	const auto font = m_text->get_font();
	float advance = static_cast<float>(font->get_char(text[index], m_text->get_font_size()).advance >> 6) / 2.f;
	while (point.x > m_text->get_position().x + advance && index < text.size())
	{
		advance += static_cast<float>(font->get_char(text[index], m_text->get_font_size()).advance >> 6) / 2.f;
		index++;
		advance += static_cast<float>(font->get_char(text[index], m_text->get_font_size()).advance >> 6) / 2.f;
	}
	return index;
}

void hgui::kernel::TextInput::focus()
{
	const auto focused = m_focused.lock();
	if (focused == shared_from_this())
		throw std::runtime_error("ALREADY FOCUSED");
	if (!m_text)
		throw std::runtime_error("TEXT INPUT REQUIRES A LABEL");
	if (focused)
		focused->unfocus();
	m_text->set_color(m_textColor);
	glfwSetCharCallback(glfwGetCurrentContext(), text_input);
	m_focused = std::dynamic_pointer_cast<TextInput>(shared_from_this());
	update_text();
	display_caret();
}

void hgui::kernel::TextInput::unfocus()
{
	if (m_focused.lock() != shared_from_this())
		throw std::runtime_error("ALREADY UNFOCUSED");
	if (not m_text)
		throw std::runtime_error("TEXT INPUT REQUIRES A LABEL");
	m_textColor = m_text->get_color();
	m_focused.reset();
	update_text();
	if (TaskManager::is_program(m_taskID))
	{
		TaskManager::deprogram(m_taskID);
	}
	m_drawer->get_shapes()->clear();
}

const std::string& hgui::kernel::TextInput::get_value() const
{
	return m_value;
}

const std::pair<hgui::color, hgui::color>& hgui::kernel::TextInput::get_colors() const
{
	return m_colors;
}

const std::pair<std::string, hgui::color>& hgui::kernel::TextInput::get_place_holder() const
{
	return m_placeHolder;
}

const hgui::kernel::TextInput::Function& hgui::kernel::TextInput::get_on_change_function() const
{
	return m_onChange;
}

bool hgui::kernel::TextInput::is_focused() const
{
	return m_focused.lock() == shared_from_this();
}

unsigned hgui::kernel::TextInput::get_caret_position() const
{
	return m_caretPosition;
}

const std::shared_ptr<hgui::kernel::Font>& hgui::kernel::TextInput::get_font() const
{
	if (!m_text)
		throw std::runtime_error("TEXT INPUT REQUIRES A LABEL");
	return m_text->get_font();
}

const hgui::color& hgui::kernel::TextInput::get_text_color() const
{
	return m_textColor;
}

const std::pair<hgui::color, std::chrono::milliseconds>& hgui::kernel::TextInput::get_caret() const
{
	return m_caret;
}

void hgui::kernel::TextInput::set_position(const point& newPosition)
{
	Widget::set_position(newPosition);
	m_inlineRectanglePosition = m_position + point(m_borderWidth);
	m_modelMatrix = std::make_pair(glm::mat4(1.0), glm::mat4(1.0));
	m_modelMatrix = std::make_pair(translate(m_modelMatrix.first, glm::vec3(m_position.x, m_position.y, 0.0f)),
		translate(m_modelMatrix.second, glm::vec3(m_inlineRectanglePosition.x, m_inlineRectanglePosition.y, 0.0f)));
	m_modelMatrix = std::make_pair(scale(m_modelMatrix.first, glm::vec3(m_size.width, m_size.height, 1.0f)),
		scale(m_modelMatrix.second, glm::vec3(m_inlineRectangleSize.width, m_inlineRectangleSize.height, 1.0f)));
	if (m_text)
		set_text_placment_and_height();
}

void hgui::kernel::TextInput::set_size(const size& newSize)
{
	Widget::set_size(newSize);
	m_cornerAngularRadius = std::min(m_size.width, m_size.height) * 0.5f * m_cornerRadius;
	m_inlineRectangleSize = m_size - point(2 * m_borderWidth);
	m_inlineCornerRadius = std::min(m_inlineRectangleSize.width, m_inlineRectangleSize.height) * 0.5f * m_cornerRadius;
	m_drawer->set_placement(m_inlineRectanglePosition, m_inlineRectangleSize);
	set_position(m_position);
	init_data();
	set_text_placment_and_height();
	update_text();
}

void hgui::kernel::TextInput::set_label(const std::shared_ptr<Label>& newText)
{
	if (not newText)
		throw std::runtime_error("TEXT INPUT REQUIRES A LABEL");
	m_text = newText;
	m_textColor = m_text->get_color();
	m_text->set_alignement(true);
	set_text_placment_and_height();
	update_text();
	assert_is_displayable(m_placeHolder.first, m_text->get_font());
	assert_is_displayable(m_value, m_text->get_font());
}

void hgui::kernel::TextInput::set_value(const std::string& value)
{
	m_value = value;
	assert_is_displayable(value, m_text->get_font());
	set_caret_position(0u);
	update_text();
}

void hgui::kernel::TextInput::set_colors(const std::pair<color, color>& colors)
{
	m_colors = colors;
}

void hgui::kernel::TextInput::set_place_holder(const std::pair<std::string, color>& placeHolder)
{
	m_placeHolder = placeHolder;
	assert_is_displayable(placeHolder.first, m_text->get_font());
	update_text();
}

void hgui::kernel::TextInput::set_on_change_function(const Function& onChange)
{
	m_onChange = onChange;
}

void hgui::kernel::TextInput::set_caret_position(unsigned caretPosition)
{
	caretPosition = std::clamp(caretPosition, 0u, static_cast<unsigned>(m_value.size()));
	if (TaskManager::is_program(m_taskID))
	{
		TaskManager::deprogram(m_taskID);
	}
	while (caretPosition > m_caretPosition)
	{
		increase_caret_position();
	}
	while (caretPosition < m_caretPosition)
	{
		decrease_caret_position();
	}
	m_drawer->get_shapes()->clear();
	display_caret();
}

void hgui::kernel::TextInput::set_font(const std::shared_ptr<Font>& font) const
{
	m_text->set_font(font);
	set_text_placment_and_height();
	update_text();
	assert_is_displayable(m_placeHolder.first, font);
	assert_is_displayable(m_value, font);
}

void hgui::kernel::TextInput::set_text_color(const color& textColor)
{
	m_textColor = textColor;
	if (m_text)
		m_text->set_color(textColor);
}

void hgui::kernel::TextInput::set_caret(const std::pair<color, std::chrono::milliseconds>& caret)
{
	m_caret = caret;
	display_caret();
}

void hgui::kernel::TextInput::init_data()
{
	std::vector<glm::vec2> vertices = {
				{m_cornerAngularRadius, 0.0f},
				{m_cornerAngularRadius, m_cornerAngularRadius},
				{m_size.width - m_cornerAngularRadius, m_cornerAngularRadius},

				{m_cornerAngularRadius, 0.0f},
				{m_size.width - m_cornerAngularRadius, 0.0f},
				{m_size.width - m_cornerAngularRadius, m_cornerAngularRadius},

				{0.0f, m_cornerAngularRadius},
				{0.0f, m_size.height - m_cornerAngularRadius},
				{m_size.width, m_size.height - m_cornerAngularRadius},

				{0.0f, m_cornerAngularRadius},
				{m_size.width, m_cornerAngularRadius},
				{m_size.width, m_size.height - m_cornerAngularRadius},

				{m_cornerAngularRadius, m_size.height - m_cornerAngularRadius},
				{m_cornerAngularRadius, m_size.height},
				{m_size.width - m_cornerAngularRadius, m_size.height},

				{m_cornerAngularRadius, m_size.height - m_cornerAngularRadius},
				{m_size.width - m_cornerAngularRadius, m_size.height - m_cornerAngularRadius},
				{m_size.width - m_cornerAngularRadius, m_size.height},
			};
	constexpr int numSegments = 10;
	float angle;
	for (int i = 0; i < numSegments; i++)
	{
		angle = static_cast<float>(i) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_cornerAngularRadius - m_cornerAngularRadius * std::cos(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::sin(angle));
		angle = static_cast<float>(i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_cornerAngularRadius - m_cornerAngularRadius * std::cos(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::sin(angle));
		vertices.emplace_back(0.f + m_cornerAngularRadius, 0.0f + m_cornerAngularRadius);
	}
	for (int i = 0; i < numSegments; i++)
	{
		angle = static_cast<float>(i) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * std::cos(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::sin(angle));
		angle = static_cast<float>(i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * std::cos(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::sin(angle));
		vertices.emplace_back(m_size.width - m_cornerAngularRadius, 0.0f + m_cornerAngularRadius);
	}
	for (int i = 0; i < numSegments; i++)
	{
		angle = static_cast<float>(i) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * std::cos(angle),
			m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * std::sin(angle));
		angle = static_cast<float>(i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * std::cos(angle),
			m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * std::sin(angle));
		vertices.emplace_back(m_size.width - m_cornerAngularRadius, m_size.height - m_cornerAngularRadius);
	}
	for (int i = 0; i < numSegments; i++)
	{
		angle = static_cast<float>(i) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_cornerAngularRadius - m_cornerAngularRadius * std::cos(angle),
			m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * std::sin(angle));
		angle = static_cast<float>(i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_cornerAngularRadius - m_cornerAngularRadius * std::cos(angle),
			m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * std::sin(angle));
		vertices.emplace_back(0.0f + m_cornerAngularRadius, m_size.height - m_cornerAngularRadius);
	}
	glm::mat2 normalize = {
				1.f / m_size.width, 0.f,
				0.f, 1.f / m_size.height
			};
	for (auto& vertice : vertices)
	{
		vertice = normalize * vertice;
	}
	vertices.insert(vertices.end(), {
			{m_inlineCornerRadius, 0.0f},
			{m_inlineCornerRadius, m_inlineCornerRadius},
			{m_inlineRectangleSize.width - m_inlineCornerRadius, m_inlineCornerRadius},

			{m_inlineCornerRadius, 0.0f},
			{m_inlineRectangleSize.width - m_inlineCornerRadius, 0.0f},
			{m_inlineRectangleSize.width - m_inlineCornerRadius, m_inlineCornerRadius},

			{0.0f, m_inlineCornerRadius},
			{0.0f, m_inlineRectangleSize.height - m_inlineCornerRadius},
			{m_inlineRectangleSize.width, m_inlineRectangleSize.height - m_inlineCornerRadius},

			{0.0f, m_inlineCornerRadius},
			{m_inlineRectangleSize.width, m_inlineCornerRadius},
			{m_inlineRectangleSize.width, m_inlineRectangleSize.height - m_inlineCornerRadius},

			{m_inlineCornerRadius, m_inlineRectangleSize.height - m_inlineCornerRadius},
			{m_inlineCornerRadius, m_inlineRectangleSize.height},
			{m_inlineRectangleSize.width - m_inlineCornerRadius, m_inlineRectangleSize.height},

			{m_inlineCornerRadius, m_inlineRectangleSize.height - m_inlineCornerRadius},
			{m_inlineRectangleSize.width - m_inlineCornerRadius, m_inlineRectangleSize.height - m_inlineCornerRadius},
			{m_inlineRectangleSize.width - m_inlineCornerRadius, m_inlineRectangleSize.height},
		});
	for (int i = 0; i < numSegments; i++)
	{
		angle = static_cast<float>(i) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_inlineCornerRadius - m_inlineCornerRadius * std::cos(angle),
			m_inlineCornerRadius - m_inlineCornerRadius * std::sin(angle));
		angle = static_cast<float>(i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_inlineCornerRadius - m_inlineCornerRadius * std::cos(angle),
			m_inlineCornerRadius - m_inlineCornerRadius * std::sin(angle));
		vertices.emplace_back(0.f + m_inlineCornerRadius, 0.0f + m_inlineCornerRadius);
	}
	for (int i = 0; i < numSegments; i++)
	{
		angle = static_cast<float>(i) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_inlineRectangleSize.width - m_inlineCornerRadius + m_inlineCornerRadius * std::cos(angle),
			m_inlineCornerRadius - m_inlineCornerRadius * std::sin(angle));
		angle = static_cast<float>(i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_inlineRectangleSize.width - m_inlineCornerRadius + m_inlineCornerRadius * std::cos(angle),
			m_inlineCornerRadius - m_inlineCornerRadius * std::sin(angle));
		vertices.emplace_back(m_inlineRectangleSize.width - m_inlineCornerRadius, 0.0f + m_inlineCornerRadius);
	}
	for (int i = 0; i < numSegments; i++)
	{
		angle = static_cast<float>(i) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_inlineRectangleSize.width - m_inlineCornerRadius + m_inlineCornerRadius * std::cos(angle),
			m_inlineRectangleSize.height - m_inlineCornerRadius + m_inlineCornerRadius * std::sin(angle));
		angle = static_cast<float>(i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_inlineRectangleSize.width - m_inlineCornerRadius + m_inlineCornerRadius * std::cos(angle),
			m_inlineRectangleSize.height - m_inlineCornerRadius + m_inlineCornerRadius * std::sin(angle));
		vertices.emplace_back(m_inlineRectangleSize.width - m_inlineCornerRadius, m_inlineRectangleSize.height - m_inlineCornerRadius);
	}
	for (int i = 0; i < numSegments; i++)
	{
		angle = static_cast<float>(i) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_inlineCornerRadius - m_inlineCornerRadius * std::cos(angle),
			m_inlineRectangleSize.height - m_inlineCornerRadius + m_inlineCornerRadius * std::sin(angle));
		angle = static_cast<float>(i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_inlineCornerRadius - m_inlineCornerRadius * std::cos(angle),
			m_inlineRectangleSize.height - m_inlineCornerRadius + m_inlineCornerRadius * std::sin(angle));
		vertices.emplace_back(0.0f + m_inlineCornerRadius, m_inlineRectangleSize.height - m_inlineCornerRadius);
	}
	normalize = glm::mat4({
			1.f / m_inlineRectangleSize.width, 0.f,
			0.f, 1.f / m_inlineRectangleSize.height
		});
	for (std::size_t i = 138; i < vertices.size(); i++)
	{
		vertices[i] = normalize * vertices[i];
	}
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices.data(), static_cast<int>(vertices.size()) * static_cast<int>(sizeof(glm::vec2)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), static_cast<void*>(nullptr));
	m_VAO->unbind();
}

void hgui::kernel::TextInput::set_text_placment_and_height() const
{
	if (not m_text)
		throw std::runtime_error("TEXT INPUT REQUIRES A LABEL");
	// We get all the printable characters of the font
	const std::string printableChars = get_font()->get_printable_characters(m_text->get_font_size());
	// We set the text height
	const auto temp = m_text->get_text();
	m_text->set_text(printableChars);
	m_text->set_height(static_cast<unsigned>(0.6f * m_inlineRectangleSize.height));
	m_text->set_text(temp);
	// We then set the text placement
	const auto offset = point(std::max(0.2f * m_inlineRectangleSize.height, 0.5f * m_cornerAngularRadius), 0.2f * m_inlineRectangleSize.height);
	m_text->set_position(m_inlineRectanglePosition + offset);
	m_drawer->set_placement(m_inlineRectanglePosition + offset, m_inlineRectangleSize - offset);
}

void hgui::kernel::TextInput::update_text() const
{
	std::string textToDisplay = m_value;
	unsigned index = m_textDisplayedIndex;
	if (!is_focused() && m_value.empty())
	{
		textToDisplay = m_placeHolder.first;
		index = 0u;
		m_text->set_color(m_placeHolder.second);
	}
	const auto& font = get_font();
	unsigned totalAdvance = 0u;
	const auto maxWidth = static_cast<unsigned>(m_inlineRectangleSize.width - std::max(0.4f * m_inlineRectangleSize.height, m_cornerAngularRadius));
	while (totalAdvance < maxWidth && index < textToDisplay.size())
	{
		totalAdvance += font->get_char(textToDisplay[index], m_text->get_font_size()).advance >> 6;
		index++;
	}
	if (totalAdvance > maxWidth)
		index--;
	m_text->set_text(textToDisplay.substr(m_textDisplayedIndex, index - m_textDisplayedIndex));
}

void hgui::kernel::TextInput::draw_caret() const
{
	const auto offset = get_advance(m_value.substr(m_textDisplayedIndex, m_caretPosition - m_textDisplayedIndex), m_text->get_font(), m_text->get_font_size());
	const auto& height = 0.6f * m_inlineRectangleSize.height;
	m_drawer->draw_rectangle(point(offset, 0.1f * height), point(static_cast<float>(offset) + 0.1f * height, 0.9f * height), m_caret.first);
}

void hgui::kernel::TextInput::display_caret() const
{
	if (m_drawer->get_shapes()->empty())
		draw_caret();
	else
		m_drawer->get_shapes()->clear();
	m_taskID = TaskManager::program(m_caret.second, [this] { display_caret(); });
}

void hgui::kernel::TextInput::increase_caret_position()
{
	if (m_caretPosition == m_value.size())
		return;
	m_caretPosition++;
	const auto maxWidth = static_cast<unsigned>(m_inlineRectangleSize.width - std::max(0.4f * m_inlineRectangleSize.height, m_cornerAngularRadius));
	while (get_advance(m_value.substr(m_textDisplayedIndex, m_caretPosition - m_textDisplayedIndex), m_text->get_font(), m_text->get_font_size()) > maxWidth)
	{
		m_textDisplayedIndex++;
	}
	update_text();
	if (TaskManager::is_program(m_taskID))
	{
		TaskManager::deprogram(m_taskID);
		m_drawer->get_shapes()->clear();
		display_caret();
	}
}

void hgui::kernel::TextInput::decrease_caret_position()
{
	if (!m_caretPosition)
		return;
	m_caretPosition--;
	if (m_caretPosition < m_textDisplayedIndex)
	{
		m_textDisplayedIndex--;
		update_text();
	}
	if (TaskManager::is_program(m_taskID))
	{
		TaskManager::deprogram(m_taskID);
		m_drawer->get_shapes()->clear();
		display_caret();
	}
}

void hgui::kernel::TextInput::delete_char()
{
	if (!m_caretPosition)
		return;
	m_value.erase(m_caretPosition - 1, 1);
	if (!m_textDisplayedIndex)
		decrease_caret_position();
	else
	{
		if (const auto maxWidth = static_cast<unsigned>(m_inlineRectangleSize.width - std::max(0.4f * m_inlineRectangleSize.height, m_cornerAngularRadius)); get_advance(m_value.substr(m_textDisplayedIndex - 1, m_caretPosition - m_textDisplayedIndex + 1), m_text->get_font(), m_text->get_font_size()) > maxWidth)
			decrease_caret_position();
		else
			m_textDisplayedIndex--;
	}
	update_text();
}

void hgui::kernel::TextInput::suppress_char()
{
	if (m_caretPosition == m_value.size())
		return;
	m_value.erase(m_caretPosition, 1);
	update_text();
}

void hgui::kernel::TextInput::assert_is_displayable(const std::string& text, const std::shared_ptr<Font>& font)
{
	for (const char c : text)
	{
		try
		{
			// We test if the character is printable with the current font
			[[maybe_unused]] const auto test = font->get_char(c, 12u);
		}
		catch (...)
		{
			throw std::runtime_error("CHARACTER NOT DISPLAYABLE");
		}
	}
}

unsigned hgui::kernel::TextInput::get_advance(const std::string& text, const std::shared_ptr<Font>& font, const unsigned size)
{
	unsigned advance = 0u;
	for (const char c : text)
	{
		advance += font->get_char(c, size).advance >> 6;
	}
	return advance;
}

void hgui::kernel::TextInput::text_input([[maybe_unused]] GLFWwindow* window, const unsigned int codepoint)
{
	if (const auto focused = m_focused.lock())
	{
		try
		{
			assert_is_displayable(std::string({static_cast<char>(codepoint)}), focused->get_font());
			focused->m_value.insert(focused->m_caretPosition, 1, static_cast<char>(codepoint));
			focused->increase_caret_position();
		}
		catch (...) {}
		if (const auto onChangeWithoutWidget = std::get_if<std::function<void()>>(&focused->m_onChange); onChangeWithoutWidget && *onChangeWithoutWidget)
			(*onChangeWithoutWidget)();
		else if (const auto onChangeWithWidget = std::get_if<std::function<void(const std::shared_ptr<TextInput>&)>>(&focused->m_onChange); onChangeWithWidget && *onChangeWithWidget)
			(*onChangeWithWidget)(focused);
		focused->update_text();
	}
}
