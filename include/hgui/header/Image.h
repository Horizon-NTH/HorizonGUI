#pragma once

#include "Coordinate.hpp"

namespace hgui::kernel
{
	struct ImageData
	{
		using pointer = std::unique_ptr<unsigned char[], void(*)(unsigned char*)>;
		Size<unsigned> size;
		channels channel = channels::UNKNOW;
		pointer pixels = {nullptr, [](unsigned char*) {}};
	};

	class Image
	{
	public:
		explicit Image(const std::string& imagePath);
		explicit Image(ImageData&& data);
		Image(const Image& image) = delete;
		Image(Image&& image) noexcept = default;

		~Image() = default;

		Image& operator=(const Image& image) = delete;
		Image& operator=(Image&& image) noexcept = default;
		Image& operator=(ImageData&& image) noexcept;

		[[nodiscard]] const ImageData& get_data() const;
		[[nodiscard]] size get_size() const;

		void set_data(ImageData&& newData);

		void save_image(const std::string& filePath) const;

	private:
		ImageData m_data;

		void load_image(const std::string& filePath);
	};
}
