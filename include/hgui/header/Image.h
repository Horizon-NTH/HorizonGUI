#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"

namespace hgui::kernel
{
	struct ImageData
	{
		unsigned int width;
		unsigned int height;
		channels channel;
		unsigned char* pixels;
	};

	class Image
	{
	public:
		explicit Image(std::string  imagePath);
		Image(std::string  imagePath, const ImageData& data);
		Image(const Image& image) = default;
		Image(Image&& image) = default;

		~Image();

		Image& operator=(const Image& image) = default;
		Image& operator=(Image&& image) = default;

		[[nodiscard]] const ImageData& get_data() const;
		[[nodiscard]] size get_size() const;

		void set_data(const ImageData& newData);

		void load_image();
		void save_image();

	private:
		std::string m_path;
		ImageData m_data;
		bool m_autoLoaded;
	};
}