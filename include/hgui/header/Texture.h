#pragma once

#include "Include.h"

namespace hgui::kernel
{
	class Image;

	struct TextureOption
	{
		GLint wrap_s = GL_CLAMP_TO_EDGE;
		GLint wrap_t = GL_CLAMP_TO_EDGE;
		GLint min_filter = GL_LINEAR;
		GLint mag_filter = GL_LINEAR;
	};

	class Texture
	{
	public:
		explicit Texture(const std::shared_ptr<Image>& image, TextureOption options = {});
		Texture(const Texture& texture) noexcept = delete;
		Texture(Texture&& texture) noexcept = delete;

		~Texture() noexcept;

		Texture& operator=(const Texture& texture) noexcept = delete;
		Texture& operator=(Texture&& texture) noexcept = delete;

		void bind() const noexcept;

		[[nodiscard]] GLuint get_id() const noexcept;
		[[nodiscard]] const std::shared_ptr<Image>& get_image() const noexcept;

	private:
		GLuint m_id;
		std::shared_ptr<Image> m_image;
		TextureOption m_options;

		void generate() const;
	};
}
