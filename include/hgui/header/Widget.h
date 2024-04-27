#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	class Timer;
	class MouseManager;
}

namespace hgui::kernel
{
	class VertexBufferObject;
	class VertexArrayObject;
	class Shader;

	template<typename T>
	struct WeakPTRComparator
	{
		bool operator()(const std::weak_ptr<T>& lhs, const std::weak_ptr<T>& rhs) const
		{
			const auto lhsShared = lhs.lock();
			const auto rhsShared = rhs.lock();

			if (!lhsShared && !rhsShared)
				return false;
			if (!lhsShared)
				return true;
			if (!rhsShared)
				return false;
			return lhsShared < rhsShared;
		}
	};

	class Window;

	class Widget : public std::enable_shared_from_this<Widget>
	{
		friend class Window;
		friend class hgui::MouseManager;

	public:
		Widget(const std::shared_ptr<Shader>& shader, size size, point position);
		Widget(const Widget& widget) = default;
		Widget(Widget&& widget) = default;

		virtual ~Widget();

		Widget& operator=(const Widget& widget) = default;
		Widget& operator=(Widget&& widget) = default;

		[[nodiscard]] const point& get_position() const;
		[[nodiscard]] const size& get_size() const;

		virtual void set_position(const point& newPosition);
		virtual void set_size(const size& newSize);

		void bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action, const std::function<void()>& function);
		[[nodiscard]] bool is_bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action);
		void unbind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action);

		virtual void draw() const = 0;
		[[nodiscard]] virtual bool is_inside(const point& point) const = 0;

		static void bind(const std::variant<std::shared_ptr<Widget>, std::string, std::vector<std::string>>& widgets, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action, const std::function<void()>& function);
		[[nodiscard]] static bool is_bind(const std::shared_ptr<Widget>& widget, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action);
		static void unbind(const std::variant<std::shared_ptr<Widget>, std::string, std::vector<std::string>>& widgets, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action);

		static void active(const std::vector<std::string>& tags = {});
		[[nodiscard]] static const std::vector<std::string>& get_active_tag();
		[[nodiscard]] static const std::vector<std::weak_ptr<Widget>>& get_widgets(const std::string& tag);

	protected:
		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<VertexArrayObject> m_VAO;
		std::shared_ptr<VertexBufferObject> m_VBO;
		size m_size;
		point m_position;

	private:
		std::string m_taskID;

		static inline std::vector<std::string> m_bindedTags;
		static inline std::map<std::weak_ptr<Widget>, std::vector<std::pair<std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>, std::pair<std::shared_ptr<Timer>, std::function<void()>>>>, WeakPTRComparator<Widget>> m_binds;
		static inline std::map<std::string, std::vector<std::weak_ptr<Widget>>> m_widgets;

		static void update();

		friend void kernel::resources_cleaner();
	};
}
