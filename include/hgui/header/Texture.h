#pragma once

#include "Include.h"
#include "Image.h"

namespace hgui
{
	namespace kernel
	{
		class Texture
		{
		public:
			Texture(const std::shared_ptr<Image>& image);
			~Texture();

			void bind() const;
			GLuint get_id() const;
			const std::shared_ptr<Image>& get_image() const;

		private:
			GLuint m_id;
			std::shared_ptr<Image> m_image;

			void generate();
		};
	}
}

