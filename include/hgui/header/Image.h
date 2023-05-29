#pragma once

#include "Include.h"
#include "MonitorManager.h"

namespace hgui
{
	namespace kernel
	{
		enum ImageChannel
		{
			GRAYSCALE = 0x1903,
			GRAYSCALE_ALPHA = 0x8227,
			RGB = 0x1907,
			RGBA = 0x1908
		};

		struct ImageData
		{
			int width;
			int height;
			ImageChannel channel;
			unsigned char* pixels;
		};

		class Image
		{
		public:
			Image(const std::string& imagePath);
			Image(const std::string& imagePath, const ImageData& data);
			~Image();

			const ImageData& get_data() const;
			void set_data(const ImageData& newData);

			void load_image();
			void save_image();

		private:
			std::string m_path;
			ImageData m_data;
		};
	}
	const std::shared_ptr<kernel::Image> image_loader(const std::string& imagePath);
}

