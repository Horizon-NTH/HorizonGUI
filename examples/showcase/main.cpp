#include <hgui/HorizonGUI.h>

#if __has_include(<sndfile.h>)
#include <sndfile.h>
#elif __has_include(<snd/sndfile.h>)
#include <snd/sndfile.h>
#else
#error "libsndfile headers not found."
#endif

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <array>
#include <chrono>
#include <cmath>
#include <numbers>
#include <algorithm>
#include <functional>
#include <variant>
#include <utility>

namespace fs = std::filesystem;
using namespace std::chrono_literals;

namespace demo
{
	namespace
	{
		[[nodiscard]] fs::path locate_asset_root(const fs::path& start)
		{
			fs::path current = fs::weakly_canonical(start);
			while (!current.empty())
			{
				if (const auto candidate = current / "examples" / "assets"; fs::exists(candidate))
				{
					return candidate;
				}
				const auto parent = current.parent_path();
				if (parent == current)
				{
					break;
				}
				current = parent;
			}
			throw std::runtime_error(
				"Unable to locate the examples/assets directory relative to the current working directory.");
		}

		[[nodiscard]] fs::path find_font_path(const fs::path& assetRoot)
		{
			static const std::array candidates =
			{
				assetRoot / "fonts" / "Roboto-Regular.ttf",
				assetRoot / "fonts" / "Inter-Regular.ttf",
				fs::path("/System/Library/Fonts/SFNSDisplay.ttf"),
				fs::path("/System/Library/Fonts/Supplemental/Arial.ttf"),
				fs::path("/Library/Fonts/Arial.ttf"),
				fs::path("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"),
				fs::path("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf"),
				fs::path("C:/Windows/Fonts/arial.ttf")
			};
			for (const auto& candidate : candidates)
			{
				if (!candidate.empty() && fs::exists(candidate))
				{
					return fs::canonical(candidate);
				}
			}
			std::ostringstream oss;
			oss << "No usable font found. Place a .ttf file in " << (assetRoot / "fonts");
			throw std::runtime_error(oss.str());
		}

		[[nodiscard]] fs::path ensure_tone_file()
		{
			const auto path = fs::temp_directory_path() / "horizongui_showcase_sine.wav";
			if (fs::exists(path))
			{
				return path;
			}

			SF_INFO info{};
			info.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
			info.channels = 1;
			info.samplerate = 44100;

			if (SNDFILE* file = sf_open(path.string().c_str(), SFM_WRITE, &info); file != nullptr)
			{
				constexpr double durationSeconds = 2.5;
				const auto sampleCount = static_cast<std::size_t>(info.samplerate * durationSeconds);
				std::vector<float> samples(sampleCount);
				for (std::size_t i = 0; i < sampleCount; ++i)
				{
					constexpr double frequency = 440.0;
					samples[i] = static_cast<float>(0.35 * std::sin(
						2.0 * std::numbers::pi_v<double> * frequency * static_cast<double>(i) / static_cast<double>(info
							.samplerate)));
				}
				const sf_count_t written =
					sf_write_float(file, samples.data(), static_cast<sf_count_t>(samples.size()));
				sf_close(file);
				if (written != static_cast<sf_count_t>(samples.size()))
				{
					throw std::runtime_error("Failed to write generated tone to temporary file.");
				}
				return path;
			}
			throw std::runtime_error("Failed to open temporary file for generated audio tone.");
		}

		[[nodiscard]] std::shared_ptr<hgui::kernel::Image> make_checkerboard_image(
			unsigned side, const hgui::color& accent)
		{
			constexpr unsigned channels = 4;
			const std::size_t stride = static_cast<std::size_t>(side) * static_cast<std::size_t>(side) * channels;
			auto* buffer = new unsigned char[stride];
			for (unsigned y = 0; y < side; ++y)
			{
				for (unsigned x = 0; x < side; ++x)
				{
					const bool highlight = ((x / 8) + (y / 8)) % 2 == 0;
					const std::size_t index = (static_cast<std::size_t>(y) * side + x) * channels;
					buffer[index + 0] = highlight ? static_cast<unsigned char>(accent.r * 255.f) : 32u;
					buffer[index + 1] = highlight ? static_cast<unsigned char>(accent.g * 255.f) : 32u;
					buffer[index + 2] = highlight ? static_cast<unsigned char>(accent.b * 255.f) : 160u;
					buffer[index + 3] = 255u;
				}
			}
			hgui::kernel::ImageData data
			{
				.size = hgui::kernel::Size(side, side),
				.channel = hgui::channels::RGBA,
				.pixels = hgui::kernel::ImageData::pointer(buffer, [](unsigned char* ptr) { delete[] ptr; })
			};
			return std::make_shared<hgui::kernel::Image>(std::move(data));
		}

		[[nodiscard]] hgui::kernel::GIFData make_color_cycling_gif(const unsigned side, const unsigned frames)
		{
			constexpr unsigned channels = 4;
			const std::size_t frameStride = static_cast<std::size_t>(side) * static_cast<std::size_t>(side) * channels;
			auto* buffer = new stbi_uc[frameStride * frames];
			for (unsigned frame = 0; frame < frames; ++frame)
			{
				const float t = static_cast<float>(frame) / static_cast<float>(std::max(1u, frames - 1));
				for (unsigned y = 0; y < side; ++y)
				{
					for (unsigned x = 0; x < side; ++x)
					{
						const std::size_t index = static_cast<std::size_t>(frame) * frameStride + (static_cast<
							std::size_t>(y) * side + x) * channels;
						buffer[index + 0] = static_cast<stbi_uc>(255.f * (1.f - t));
						buffer[index + 1] = static_cast<stbi_uc>(255.f * t);
						buffer[index + 2] = static_cast<stbi_uc>(128.f + 127.f * std::sin(
							2.f * std::numbers::pi_v<float> * static_cast<float>(x) / static_cast<float>(side)));
						buffer[index + 3] = 255u;
					}
				}
			}
			hgui::kernel::GIFData data;
			data.size = hgui::kernel::Size(side, side);
			data.framesCount = frames;
			data.channel = hgui::channels::RGBA;
			data.ptr = hgui::kernel::GIFData::pointer(buffer, [](stbi_uc* ptr) { delete[] ptr; });
			for (unsigned frame = 0; frame < frames; ++frame)
			{
				data.pixels.emplace_back(buffer + frame * frameStride, std::chrono::milliseconds(120));
			}
			return data;
		}
	}
}

int main()
{
	try
	{
		auto iconImage = demo::make_checkerboard_image(64, hgui::color("#38bdf8"));

		hgui::init();

		auto window = hgui::WindowManager::create(
			"HorizonGUI Showcase",
			hgui::size(1280, 720),
			hgui::point(120.f, 80.f),
			iconImage);

		hgui::Renderer::set_background_color(hgui::color("#0f172a"));

		const auto assetRoot = demo::locate_asset_root(fs::current_path());
		const auto fontPath = demo::find_font_path(assetRoot);
		auto baseFont = hgui::FontManager::create(fontPath.string());

		const auto tonePath = demo::ensure_tone_file();
		auto tone = std::make_shared<hgui::kernel::Audio>(tonePath.string());
		auto soundPlayer = hgui::SoundPlayerManager::create(tone);
		soundPlayer->set_volume(0.5f);

		const auto uiTag = hgui::TagManager::create_tag("SHOWCASE_UI");
		const auto artTag = hgui::TagManager::create_tag("SHOWCASE_ART");
		const auto overlayTag = hgui::TagManager::create_tag("SHOWCASE_OVERLAY");

		hgui::kernel::Widget::active({uiTag, artTag, overlayTag, HGUI_TAG_MAIN});

		// --- UI section ------------------------------------------------------
		hgui::TagManager::set_current_tag(uiTag);

		auto title = hgui::LabelManager::create(
			"HorizonGUI Showcase",
			hgui::point(4_em, 14_em),
			baseFont,
			false,
			std::tuple{36u, hgui::color("#f8fafc"), 1.f});

		auto subtitle = hgui::LabelManager::create(
			"Every widget, input manager and helper in a single demo window.",
			hgui::point(4_em, 20_em),
			baseFont,
			false,
			std::tuple{18u, hgui::color("#94a3b8"), 1.f});

		(void)title;
		(void)subtitle;

		auto volumeLabel = hgui::LabelManager::create(
			"Volume: 0.50",
			hgui::point(4_em, 30_em),
			baseFont,
			false,
			std::tuple{16u, hgui::color("#e2e8f0"), 1.f});

		hgui::kernel::Ranges sliderRange{0.f, 1.f, 0u, 2u};
		auto slider = hgui::SliderManager::create(
			sliderRange,
			hgui::size(30_em, 4_em),
			hgui::point(4_em, 34_em),
			std::tuple{hgui::color("#f8fafc"), hgui::color("#323f4b"), hgui::color("#38bdf8")},
			std::function<void(float, float, std::shared_ptr<hgui::kernel::Slider>)>(
				[volumeLabel, weakPlayer = std::weak_ptr(soundPlayer)](const float value, float,
				                                                       const std::shared_ptr<hgui::kernel::Slider>&)
				{
					std::ostringstream oss;
					oss << "Volume: " << std::fixed << std::setprecision(2) << value;
					volumeLabel->set_text(oss.str());
					if (const auto player = weakPlayer.lock())
					{
						player->set_volume(value);
					}
				}));
		slider->set_value(0.5f);

		auto audioStatus = hgui::LabelManager::create(
			"Click the button to play a generated sine wave.",
			hgui::point(4_em, 42_em),
			baseFont,
			false,
			std::tuple{16u, hgui::color("#cbd5f5"), 1.f});

		auto playButton = hgui::ButtonManager::create(
			[audioStatus, weakPlayer = std::weak_ptr(soundPlayer)]
			{
				if (const auto player = weakPlayer.lock())
				{
					if (player->is_playing())
					{
						player->stop();
						audioStatus->set_text("Tone stopped. Press play to hear it again.");
					}
					else
					{
						player->play();
						audioStatus->set_text("Tone playing... press the button to stop it.");
					}
				}
			},
			hgui::size(16_em, 8_em),
			hgui::point(4_em, 46_em),
			nullptr,
			std::tuple{hgui::color("#1f2937"), hgui::color("#1e293b"), hgui::color("#38bdf8")},
			30.f,
			true,
			"Play tone",
			baseFont,
			hgui::color("#f8fafc"));

		auto inputPrompt = hgui::LabelManager::create(
			"TextInput widget",
			hgui::point(4_em, 58_em),
			baseFont,
			false,
			std::tuple{16u, hgui::color("#e2e8f0"), 1.f});

		auto lastMessage = hgui::LabelManager::create(
			"You have not typed anything yet.",
			hgui::point(4_em, 70_em),
			baseFont,
			false,
			std::tuple{16u, hgui::color("#38bdf8"), 1.f});

		(void)inputPrompt;

		auto textInput = hgui::TextInputManager::create(
			hgui::size(30_em, 6_em),
			hgui::point(4_em, 62_em),
			std::pair{baseFont, hgui::color("#f8fafc")},
			std::pair{hgui::color("#1f2933"), hgui::color("#38bdf8")},
			std::pair{std::string("Write a note"), hgui::color("#64748b")},
			std::pair{hgui::color("#38bdf8"), std::chrono::milliseconds(450)},
			std::make_tuple(
				std::variant<std::function<void()>, std::function<void
					             (const std::shared_ptr<hgui::kernel::TextInput>&)>>(
					[lastMessage](const std::shared_ptr<hgui::kernel::TextInput>& input)
					{
						lastMessage->set_text("You typed: " + input->get_value());
					}),
				std::variant<std::function<void()>, std::function<void
					             (const std::shared_ptr<hgui::kernel::TextInput>&)>>(
					[lastMessage]
					{
						lastMessage->set_text("Input focused. Start typing!");
					}),
				std::variant<std::function<void()>, std::function<void
					             (const std::shared_ptr<hgui::kernel::TextInput>&)>>(
					[lastMessage]
					{
						hgui::after(150ms, [lastMessage]
						{
							lastMessage->set_text("Input idle. Click to edit again.");
						});
					})),
			120u, {}, 50, 2);

		(void)playButton;
		(void)textInput;

		// --- Artistic widgets (canvas / sprites) -----------------------------
		hgui::TagManager::set_current_tag(artTag);

		auto canvas = hgui::CanvasManager::create(nullptr, hgui::size(44_em, 44_em), hgui::point(48_em, 16_em),
		                                          hgui::color("#111826"));
		const auto drawer = canvas->get_drawer();
		drawer->draw_rectangle(hgui::point(24.f, 24.f), hgui::point(200.f, 160.f), hgui::color("#1d4ed8"), true);
		drawer->draw_triangle(hgui::point(80.f, 220.f), hgui::point(200.f, 220.f), hgui::point(140.f, 120.f),
		                      hgui::color("#22d3ee"), true);
		drawer->draw_circle(hgui::point(260.f, 120.f), 56.f, hgui::color("#f97316"), true);
		drawer->draw_line(hgui::point(20.f, 20.f), hgui::point(300.f, 220.f), hgui::color("#94a3b8"), 6.f);

		auto spriteImage = demo::make_checkerboard_image(96, hgui::color("#22d3ee"));
		auto sprite = hgui::SpriteManager::create(spriteImage, hgui::size(12_em, 12_em), hgui::point(52_em, 20_em),
		                                          hgui::color("#f8fafc"));

		auto gifData = demo::make_color_cycling_gif(96, 12);
		auto gif = std::make_shared<hgui::kernel::GIF>(std::move(gifData));
		auto animatedSprite = hgui::SpriteManager::create(gif, hgui::size(12_em, 12_em), hgui::point(68_em, 20_em),
		                                                  hgui::color("#ffffff"));
		animatedSprite->loop();

		(void)spriteImage;
		(void)gif;

		// --- Overlay ---------------------------------------------------------
		hgui::TagManager::set_current_tag(overlayTag);

		auto canvasStatus = hgui::LabelManager::create(
			"Mouse over canvas to sample coordinates.",
			hgui::point(48_em, 62_em),
			baseFont,
			false,
			std::tuple{15u, hgui::color("#cbd5f5"), 1.f});

		auto mouseHint = hgui::LabelManager::create(
			"",
			hgui::point(48_em, 67_em),
			baseFont,
			false,
			std::tuple{14u, hgui::color("#38bdf8"), 1.f});

		canvas->bind(hgui::inputs::OVER, [mouseHint]
		{
			const auto position = hgui::MouseManager::get_position();
			std::ostringstream oss;
			oss << "Cursor position: (" << static_cast<int>(position.x) << ", " << static_cast<int>(position.y) << ")";
			mouseHint->set_text(oss.str());
		});

		canvas->bind(hgui::inputs::NOVER, [mouseHint]
		{
			mouseHint->set_text("Cursor outside canvas.");
		});

		auto fpsLabel = hgui::LabelManager::create(
			"FPS: --",
			hgui::point(4_em, 4_em),
			baseFont,
			false,
			std::tuple<unsigned int, hgui::color, float>{14u, hgui::color("#38bdf8"), 1.f});

		auto helpLabel = hgui::LabelManager::create(
			"Esc: quit | Space: pause animation",
			hgui::point(4_em, 8_em),
			baseFont,
			false,
			std::tuple{14u, hgui::color("#94a3b8"), 1.f});

		// --- Global binds ----------------------------------------------------
		hgui::KeyBoardManager::bind(hgui::KeyBoardAction{hgui::keys::ESCAPE, hgui::actions::PRESS}, []
		{
			hgui::end();
		});

		auto animationPlaying = std::make_shared<bool>(true);
		hgui::KeyBoardManager::bind(hgui::KeyBoardAction{hgui::keys::SPACE, hgui::actions::PRESS},
		                            [weakAnim = std::weak_ptr(animatedSprite), animationPlaying, helpLabel]
		                            {
			                            if (const auto spritePtr = weakAnim.lock())
			                            {
				                            if (*animationPlaying)
				                            {
					                            spritePtr->pause();
					                            helpLabel->set_text("Esc: quit | Space: resume animation");
				                            }
				                            else
				                            {
					                            spritePtr->play();
					                            helpLabel->set_text("Esc: quit | Space: pause animation");
				                            }
				                            *animationPlaying = !*animationPlaying;
			                            }
		                            });

		hgui::MouseManager::bind(std::make_pair(hgui::buttons::RIGHT, hgui::actions::PRESS), [canvasStatus]
		{
			canvasStatus->set_text("Right click detected - widgets react to mouse actions, too!");
		});

		hgui::Renderer::draw({uiTag, overlayTag}, hgui::effects::CLASSIC);
		hgui::Renderer::draw({artTag}, hgui::effects::BLURRED);

		hgui::Renderer::set_draw_callback([fpsLabel, sprite]
		{
			const double dt = hgui::get_delta_time();
			if (dt > 0.0)
			{
				std::ostringstream oss;
				oss << "FPS: " << std::fixed << std::setprecision(1) << (1.0 / dt);
				fpsLabel->set_text(oss.str());
			}
			static float rotation = 0.f;
			rotation += static_cast<float>(45.0 * dt);
			sprite->set_rotation(rotation);
		});

		hgui::Renderer::loop();
	}
	catch (const std::exception& exception)
	{
		std::cerr << "HorizonGUI showcase failed: " << exception.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
