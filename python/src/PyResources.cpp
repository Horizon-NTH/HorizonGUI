#include "../include/Include.h"

void init_resources(const py::module& hgui, const py::module& kernel)
{
	using shader = hgui::kernel::Shader;
	py::class_<shader, std::shared_ptr<shader>>(hgui, "Shader",
				"The Shader class facilitates the creation, management, and utilization of shader programs.")
			.def(py::init<const std::string&, const std::string&, const std::string&>(), "vertex_shader"_a, "fragment_shader"_a, "geometry_shader"_a = "",
				"Constructs a Shader object by specifying the source code for the vertex, fragment, and geometry shaders. This constructor compiles and links the shaders to create a shader program.")
			.def("use", &shader::use, py::return_value_policy::reference_internal,
				"Sets the shader program as the current one for rendering.")
			.def_property_readonly("id", &shader::get_id,
				"Retrieves the ID of the shader program.")
			.def("set_int", &shader::set_int, py::return_value_policy::reference_internal, "uniform_name"_a, "integer"_a,
				"Sets an integer uniform variable in the shader.")
			.def("set_float", &shader::set_float, py::return_value_policy::reference_internal, "uniform_name"_a, "float"_a,
				"Sets an floating-point uniform variable in the shader.")
			.def("set_vec2", py::overload_cast<const std::string&, const hgui::vec2&>(&shader::set_vec2), py::return_value_policy::reference_internal, "uniform_name"_a, "vec2"_a,
				"Sets an vec2 uniform variable in the shader.")
			.def("set_vec2", py::overload_cast<const std::string&, const hgui::point&>(&shader::set_vec2), py::return_value_policy::reference_internal, "uniform_name"_a, "point"_a,
				"Sets an point uniform variable in the shader.")
			.def("set_vec2", py::overload_cast<const std::string&, const hgui::size&>(&shader::set_vec2), py::return_value_policy::reference_internal, "uniform_name"_a, "size"_a,
				"Sets an size uniform variable in the shader.")
			.def("set_vec3", py::overload_cast<const std::string&, const hgui::vec3&>(&shader::set_vec3), py::return_value_policy::reference_internal, "uniform_name"_a, "vec3"_a,
				"Sets an vec3 uniform variable in the shader.")
			.def("set_vec3", py::overload_cast<const std::string&, const hgui::color&>(&shader::set_vec3), py::return_value_policy::reference_internal, "uniform_name"_a, "color"_a,
				"Sets an color uniform variable in the shader.")
			.def("set_vec4", py::overload_cast<const std::string&, const hgui::vec4&>(&shader::set_vec4), py::return_value_policy::reference_internal, "uniform_name"_a, "vec4"_a,
				"Sets an vec4 uniform variable in the shader.")
			.def("set_vec4", py::overload_cast<const std::string&, const hgui::color&>(&shader::set_vec4), py::return_value_policy::reference_internal, "uniform_name"_a, "color"_a,
				"Sets an color with alpha value uniform variable in the shader.")
			.def("set_double", &shader::set_double, py::return_value_policy::reference_internal, "uniform_name"_a, "double"_a,
				"Sets an double uniform variable in the shader.")
			.def("set_dvec2", py::overload_cast<const std::string&, const hgui::dvec2&>(&shader::set_dvec2), py::return_value_policy::reference_internal, "uniform_name"_a, "dvec2"_a,
				"Sets an dvec2 uniform variable in the shader.")
			.def("set_dvec3", py::overload_cast<const std::string&, const hgui::dvec3&>(&shader::set_dvec3), py::return_value_policy::reference_internal, "uniform_name"_a, "dvec3"_a,
				"Sets an dvec3 uniform variable in the shader.")
			.def("set_dvec4", py::overload_cast<const std::string&, const hgui::dvec4&>(&shader::set_dvec4), py::return_value_policy::reference_internal, "uniform_name"_a, "dvec4"_a,
				"Sets an dvec4 uniform variable in the shader.")
			.def("set_mat4", [](shader& self, const std::string& uniform_name, const std::array<float, 16>& mat4) { self.set_mat4(uniform_name, glm::make_mat4(mat4.data())); }, py::return_value_policy::reference_internal, "uniform_name"_a, "mat4"_a,
				"Sets an mat4 uniform variable in the shader.");

	using option = hgui::kernel::TextureOption;
	py::class_<option>(kernel, "TextureOption",
				"The TextureOption structure allow the user to choose it's desired wrapping, filtering options for the texture he is creating.")
			.def(py::init<GLint, GLint, GLint, GLint>(), "wrap_s"_a = GL_CLAMP_TO_EDGE, "wrap_t"_a = GL_CLAMP_TO_EDGE, "min_filter"_a = GL_LINEAR, "mag_filter"_a = GL_LINEAR,
				"Default constructor")
			.def_readwrite("wrap_s", &option::wrap_s,
				"Texture wrapping on s-axis.")
			.def_readwrite("wrap_t", &option::wrap_t,
				"Texture wrapping on t-axis.")
			.def_readwrite("min_filter", &option::min_filter,
				"Texture minifying filter.")
			.def_readwrite("mag_filter", &option::mag_filter,
				"Texture magnifying filter.");

	using texture = hgui::kernel::Texture;
	py::class_<texture, std::shared_ptr<texture>>(hgui, "Texture")
			.def(py::init<const std::shared_ptr<hgui::kernel::Image>&, option>(), "image"_a, "options"_a = option{},
				"Constructs a Texture object using a shared pointer to an image and an optional options.")
			.def("bind", &texture::bind,
				"Binds the texture, making it active for rendering.")
			.def_property_readonly("id", &texture::get_id, py::return_value_policy::reference_internal,
				"Retrieves the ID of the texture.")
			.def_property_readonly("image", &texture::get_image, py::return_value_policy::reference_internal,
				"Retrieves the associated image.");

	using vao = hgui::kernel::VertexArrayObject;
	py::class_<vao, std::shared_ptr<vao>>(kernel, "VertexArrayObject",
				"The VertexArrayObject class provides a mechanism for creating and managing OpenGL Vertex Array Objects (VAOs).")
			.def(py::init(),
				"Constructs a VertexArrayObject by generating a new VAO ID.")
			.def("bind", &vao::bind,
				"Binds the VAO to the current OpenGL context, making it the active VAO for subsequent rendering operations.")
			.def("unbind", &vao::unbind,
				"Unbinds the currently bound VAO, restoring the default state for rendering.");

	using vbo = hgui::kernel::VertexBufferObject;
	py::class_<vbo, std::shared_ptr<vbo>>(kernel, "VertexBufferObject",
				"The VertexBufferObject provides a mechanism for creating and managing OpenGL Vertex Buffer Objects (VBOs).")
			.def(py::init(),
				"Constructs a VertexBufferObject by generating a new VBO ID.")
			.def("bind", &vbo::bind,
				"Binds the VBO to the current OpenGL context, making it the active VBO for subsequent data operations.")
			.def("unbind", &vbo::unbind,
				"Unbinds the currently bound VBO, restoring the default state for data operations.")
			.def("set_data", &vbo::set_data, "data"_a, "size"_a, "dynamic"_a = false,
				"Allocates and sets the VBO's data with the given data and size. The dynamic flag specifies whether the data is expected to change frequently.")
			.def("set_sub_data", &vbo::set_sub_data, "data"_a, "size"_a, "offset"_a,
				"Updates a portion of the VBO's data with the provided data and size, starting from the specified offset.");

	using renderbuffer = hgui::kernel::RenderBuffer;
	py::class_<renderbuffer, std::shared_ptr<renderbuffer>>(kernel, "RenderBuffer",
				"The RenderBuffer class provides a mechanism for creating and managing OpenGL Render Buffers.")
			.def(py::init(),
				"Constructs a RenderBuffer by generating a new Render Buffer ID.")
			.def("bind", &renderbuffer::bind,
				"Binds the Render Buffer to the current OpenGL context, making it the active Render Buffer for subsequent operations.")
			.def("unbind", &renderbuffer::unbind,
				"Unbinds the currently bound Render Buffer, restoring the default state for operations.")
			.def("create_depth_stencil", &renderbuffer::create_depth_stencil,
				"Creates a depth and stencil attachment for the Render Buffer, making it suitable for depth and stencil information storage.")
			.def_property_readonly("id", &renderbuffer::get_id,
				"Retrieves the ID of the Render Buffer.");

	using framebuffer = hgui::kernel::FrameBuffer;
	py::class_<framebuffer, std::shared_ptr<framebuffer>>(kernel, "FrameBuffer",
				"The FrameBuffer class provides a means to work with OpenGL Frame buffers.")
			.def(py::init(),
				"Constructs a FrameBuffer object, generating a new Framebuffer ID.")
			.def("bind", &framebuffer::bind,
				"Binds the Framebuffer to the current OpenGL context, making it the active Framebuffer for rendering operations.")
			.def("unbind", &framebuffer::unbind,
				"Unbinds the currently bound Framebuffer, restoring the default state for rendering operations.")
			.def("clear", &framebuffer::clear,
				"Clears the contents of the Framebuffer, typically used to clear the color, depth, and stencil attachments.")
			.def("is_complete", &framebuffer::is_complete,
				"Checks if the Framebuffer is complete and ready for rendering.")
			.def("attach_texture", &framebuffer::attach_texture, "texture"_a,
				"Attaches a texture to the Framebuffer, enabling rendering into the provided texture.")
			.def("attach_render_buffer", &framebuffer::attach_render_buffer, "render_buffer"_a,
				"Attaches a Render Buffer to the Framebuffer, allowing depth and stencil information storage.")
			.def_property_readonly("id", &framebuffer::get_id,
				"Retrieves the ID of the Framebuffer.");

	using buffer = hgui::kernel::Buffer;
	py::class_<buffer, std::shared_ptr<buffer>>(hgui, "Buffer",
				"The Buffer class serves as a powerful tool for encapsulating render buffers and frame buffers.")
			.def(py::init<const std::shared_ptr<shader>&, const std::shared_ptr<texture>&>(), "shader"_a, "texture"_a,
				"Constructs a Buffer object with the specified shader and texture.")
			.def(py::init([](const std::shared_ptr<shader>& bufferShader, const hgui::size& bufferSize)
					{
						return hgui::BufferManager::create(bufferShader, bufferSize);
					}), "shader"_a, "buffer_size"_a,
				"Creates a buffer with the specified shader and buffer size")
			.def("bind", &buffer::bind,
				"Binds the frame buffers, allowing you to render in it.")
			.def("unbind", &buffer::unbind,
				"Unbinds the frame buffers.")
			.def("show", &buffer::show,
				"Displays the content of the frame buffers on the screen, enabling you to visualize the rendered output")
			.def("clear", &buffer::clear,
				"Clears the contents of the frame buffers, making it ready for subsequent rendering.");
}
