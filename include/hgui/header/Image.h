#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"

namespace hgui::kernel
{
	struct ImageData
	{
		int width;
		int height;
		channels channel;
		unsigned char* pixels;
	};

	class Image
	{
	public:
		explicit Image(const std::string& imagePath);
		Image(const std::string& imagePath, const ImageData& data);
		~Image();

		[[nodiscard]] const ImageData& get_data() const;
		void set_data(const ImageData& newData);
		[[nodiscard]] size get_size() const;

		void load_image();
		void save_image();

	private:
		std::string m_path;
		ImageData m_data;
	};
}
