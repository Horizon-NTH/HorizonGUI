#pragma once

#include "Include.h"
#include "Image.h"

namespace hgui::kernel
{
	class Texture
	{
	public:
		explicit Texture(const std::shared_ptr<Image>& image);

		~Texture();

		void bind() const;

		[[nodiscard]] GLuint get_id() const;

		[[nodiscard]] const std::shared_ptr<Image>& get_image() const;

	private:
		GLuint m_id;
		std::shared_ptr<Image> m_image;

		void generate() const;
	};
}
