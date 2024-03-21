#pragma once

#include "Coordinate.hpp"

namespace hgui::kernel
{
	class Image;

	struct GIFData
	{
		using pointer = std::unique_ptr<stbi_uc, void(*)(stbi_uc*)>;
		using delay = std::chrono::milliseconds;
		using frame = std::pair<stbi_uc*, delay>;
		using data = std::vector<frame>;

		Size<unsigned> size;
		unsigned int framesCount;
		channels channel = channels::UNKNOW;
		data pixels;

		pointer ptr = {nullptr, [](unsigned char*) {}};
	};

	class GIF
	{
	public:
		using Frame = std::pair<std::shared_ptr<Image>, GIFData::delay>;

		explicit GIF(const std::string& gifPath);
		explicit GIF(GIFData&& data);
		GIF(const GIF& gif) = delete;
		GIF(GIF&& gif) noexcept = default;

		~GIF() = default;

		GIF& operator=(const GIF& gif) = delete;
		GIF& operator=(GIF&& gif) noexcept = default;
		GIF& operator=(GIFData&& data) noexcept;

		[[nodiscard]] GIFData& get_data();
		[[nodiscard]] size get_size() const;
		[[nodiscard]] Frame get_frame(unsigned int frameNumber) const;
		[[nodiscard]] unsigned int get_frames_count() const;

		void set_data(GIFData&& newData);
		void set_delay(const GIFData::delay& delay, unsigned int frameNumber);
		void set_delay(const std::vector<GIFData::delay>& delays);

	private:
		GIFData m_data;

		static std::vector<stbi_uc> read_binary_file(const std::string& filePath);
		void load_gif(const std::string& gifPath);
	};
}
