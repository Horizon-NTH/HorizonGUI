#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Shader.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "TagManager.h"
#include "Timer.h"

namespace hgui
{
	namespace kernel
	{
		void resources_cleaner();

		template<typename T>
		struct WeakPTRComparator
		{
			bool operator()(const std::weak_ptr<T>& lhs, const std::weak_ptr<T>& rhs) const
			{
				const auto lhsShared = lhs.lock();
				const auto rhsShared = rhs.lock();

				if (!lhsShared && !rhsShared)
				{
					return false;
				}
				else if (!lhsShared)
				{
					return true;
				}
				else if (!rhsShared)
				{
					return false;
				}

				return lhsShared < rhsShared;
			}
		};
	}

	class Widget : public std::enable_shared_from_this<Widget>
	{
		friend class Renderer;
		friend class MouseManager;
		friend class SpriteManager;
		friend class LabelManager;
		friend class ButtonManager;
		friend class CanvasManager;
		friend class SliderManager;

	public:
		Widget(const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color, const HGUI_PRECISION angularRotation);
		Widget(const Widget& widget) = default;
		Widget(Widget&& widget) = default;

		virtual ~Widget();

		Widget& operator=(const Widget& widget) = default;
		Widget& operator=(Widget&& widget) = default;

		[[nodiscard]] const point& get_position() const;
		[[nodiscard]] const size& get_size() const;
		[[nodiscard]] HGUI_PRECISION get_rotation() const;

		virtual void set_position(const point& newPosition);
		virtual void set_rotation(const HGUI_PRECISION newAngularRotation);

		void bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action, const std::function<void()>& function);
		[[nodiscard]] bool is_bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action);
		void unbind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action);

		virtual void draw() const = 0;
		[[nodiscard]] virtual bool is_inside(const point& point) const = 0;

		static void bind(const std::variant<std::shared_ptr<Widget>, std::string, std::vector<std::string>>& widgets, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action, const std::function<void()>& function);
		[[nodiscard]] static bool is_bind(const std::shared_ptr<Widget>& widget, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action);
		static void unbind(const std::variant<std::shared_ptr<Widget>, std::string, std::vector<std::string>>& widgets, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action);

		static void active(const std::vector<std::string>& tags = {});

	protected:
		std::shared_ptr<kernel::Shader> m_shader;
		std::shared_ptr<kernel::VertexArrayObject> m_VAO;
		std::shared_ptr<kernel::VertexBufferObject> m_VBO;
		size m_size;
		point m_position;
		color m_color;
		HGUI_PRECISION m_angularRotation;

	private:
		static std::vector<std::string> m_bindedTags;
		static std::map<std::weak_ptr<Widget>, std::vector<std::pair<std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>, std::pair<std::shared_ptr<Timer>, std::function<void()>>>>, kernel::WeakPTRComparator<Widget>> m_binds;
		static std::map<std::string, std::vector<std::weak_ptr<Widget>>> m_widgets;

		[[nodiscard]] static const std::vector<std::weak_ptr<Widget>>& get_widgets(const std::string& tag);

		friend void kernel::resources_cleaner();
	};
}
