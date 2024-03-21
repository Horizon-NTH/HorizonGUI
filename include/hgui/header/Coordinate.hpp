#pragma once

#include "Include.h"
#include "Define.h"
#include "Maths.hpp"

namespace hgui::kernel
{
	class Window;

	enum class operations
	{
		ADDITION,
		SUBTRACTION,
		MULTIPLICATION,
		DIVISION
	};

	template<typename T>
	class EM
	{
		friend class Window;
		template<typename U>
		friend class EM;

	public:
		// Basic constructor

		EM() noexcept;
		explicit EM(T value) noexcept;
		EM(const EM& em) noexcept = default;
		EM(EM&& em) noexcept = default;

		~EM() noexcept = default;

		EM& operator=(const EM& em) noexcept = default;
		EM& operator=(EM&& em) noexcept = default;

		// Basic constructor with conversion

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit EM(U value) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit EM(const EM<U>& em) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit EM(EM<U>&& em) noexcept;

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		EM& operator=(const EM<U>& em) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		EM& operator=(EM<U>&& em) noexcept;

		// Basic operator

		EM& operator+=(T element) noexcept;
		EM& operator-=(T element) noexcept;
		EM& operator*=(T element) noexcept;
		EM& operator/=(T element) noexcept;

		EM operator-() const noexcept;

		EM& operator+=(const EM& em) noexcept;
		EM& operator-=(const EM& em) noexcept;
		EM& operator*=(const EM& em) noexcept;
		EM& operator/=(const EM& em) noexcept;

		// Basic operator with conversion

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		EM& operator+=(U element) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		EM& operator-=(U element) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		EM& operator*=(U element) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		EM& operator/=(U element) noexcept;

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		EM& operator+=(const EM<U>& em) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		EM& operator-=(const EM<U>& em) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		EM& operator*=(const EM<U>& em) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		EM& operator/=(const EM<U>& em) noexcept;

		// EM Calcul Operator

		/// Between EM and scalar

		friend EM operator+(T value, const EM& em)
		{
			EM copy = em;
			return copy += value;
		}

		friend EM operator+(const EM& em, T value)
		{
			EM copy = em;
			return copy += value;
		}

		friend EM operator-(T value, const EM& em)
		{
			EM copy = -em;
			return copy += value;
		}

		friend EM operator-(const EM& em, T value)
		{
			EM copy = em;
			return copy -= value;
		}

		friend EM operator*(T value, const EM& em)
		{
			EM copy = em;
			return copy *= value;
		}

		friend EM operator*(const EM& em, T value)
		{
			EM copy = em;
			return copy *= value;
		}

		friend EM operator/(const EM& em, T value)
		{
			EM copy = em;
			return copy /= value;
		}

		friend EM operator/(T value, const EM& em)
		{
			EM copy = EM{} + value;
			return copy /= em;
		}

		/// Between EM and scalar with conversion

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend EM operator+(U value, const EM& em)
		{
			EM copy = em;
			return copy += value;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend EM operator+(const EM& em, U value)
		{
			EM copy = em;
			return copy += value;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend EM operator-(U value, const EM& em)
		{
			EM copy = -em;
			return copy += value;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend EM operator-(const EM& em, U value)
		{
			EM copy = em;
			return copy -= value;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend EM operator*(U value, const EM& em)
		{
			EM copy = em;
			return copy *= value;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend EM operator*(const EM& em, U value)
		{
			EM copy = em;
			return copy *= value;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend EM operator/(const EM& em, U value)
		{
			EM copy = em;
			return copy /= value;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend EM operator/(U value, const EM& em)
		{
			EM copy = EM{} + value;
			return copy /= em;
		}

		/// Between EMs

		friend EM operator+(const EM& em1, const EM& em2)
		{
			EM copy = em1;
			return copy += em2;
		}

		friend EM operator-(const EM& em1, const EM& em2)
		{
			EM copy = em1;
			return copy -= em2;
		}

		friend EM operator*(const EM& em1, const EM& em2)
		{
			EM copy = em1;
			return copy *= em2;
		}

		friend EM operator/(const EM& em1, const EM& em2)
		{
			EM copy = em1;
			return copy /= em2;
		}

		/// Between EMs with conversion

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend EM operator+(const EM& em1, const EM<U>& em2)
		{
			EM copy = em1;
			return copy += em2;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend EM operator-(const EM& em1, const EM<U>& em2)
		{
			EM copy = em1;
			return copy -= em2;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend EM operator*(const EM& em1, const EM<U>& em2)
		{
			EM copy = em1;
			return copy *= em2;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend EM operator/(const EM& em1, const EM<U>& em2)
		{
			EM copy = em1;
			return copy /= em2;
		}

		friend std::ostream& operator<<(std::ostream& stream, const EM& coords)
		{
			return stream << "Value based on window width : " << coords.get_width_value() << std::endl
			       << "Value based on window height : " << coords.get_height_value() << std::endl;
		}

		// Conversion operator
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit operator EM<U>() const noexcept;

		[[nodiscard]] T get_width_value() const;
		[[nodiscard]] T get_height_value() const;

		void set_reference(const reference& ref) noexcept;
		[[nodiscard]] const reference& get_reference() const noexcept;

		void set_base_value(T baseValue) noexcept;
		[[nodiscard]] T get_base_value() const noexcept;

	private:
		T m_value;
		reference m_reference{reference::BOTH};
		std::vector<std::pair<operations, std::variant<T, EM>>> m_operations;
		inline static std::pair<T, T> referenceSize{};

		[[nodiscard]] static T calcul(T sum, std::pair<operations, std::variant<T, EM>> element, T referenceSize) noexcept;
	};

	template<typename T>
	class Coordinate
	{
	public:
		// Basic constructor

		Coordinate() noexcept = default;
		Coordinate(const Coordinate& coords) noexcept = default;
		Coordinate(Coordinate&& coords) noexcept = default;

		explicit Coordinate(T bothCoord) noexcept;
		explicit Coordinate(const EM<T>& bothCoord) noexcept;
		Coordinate(T x, T y) noexcept;
		Coordinate(const EM<T>& x, T y) noexcept;
		Coordinate(T x, const EM<T>& y) noexcept;
		Coordinate(const EM<T>& x, const EM<T>& y) noexcept;
		explicit Coordinate(const std::pair<EM<T>, EM<T>>& coords) noexcept;
		explicit Coordinate(std::pair<EM<T>, EM<T>>&& coords) noexcept;
		explicit Coordinate(const std::array<EM<T>, 2>& coords) noexcept;
		explicit Coordinate(std::array<EM<T>, 2>&& coords) noexcept;
		explicit Coordinate(const Vector<T, 2>& coords) noexcept;
		explicit Coordinate(const GLSLvec2<T>& coords) noexcept;
		explicit Coordinate(const glm::vec<2, T>& coords) noexcept;

		virtual ~Coordinate() = default;

		Coordinate& operator=(const Coordinate& coords) noexcept;
		Coordinate& operator=(Coordinate&& coords) noexcept;

		// Basic constructor with conversion

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(const Coordinate<U>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(Coordinate<U>&& coords) noexcept;

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(U bothCoord) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(const EM<U>& bothCoord) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate(U x, T y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate(T x, U y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate(U x, U y) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Coordinate(U x, V y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate(const EM<T>& x, U y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate(const EM<U>& x, T y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate(const EM<U>& x, U y) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Coordinate(const EM<U>& x, V y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate(U x, const EM<T>& y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate(T x, const EM<U>& y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate(U x, const EM<U>& y) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Coordinate(U x, const EM<V>& y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate(const EM<U>& x, const EM<T>& y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate(const EM<T>& x, const EM<U>& y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate(const EM<U>& x, const EM<U>& y) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Coordinate(const EM<U>& x, const EM<V>& y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(const std::pair<EM<U>, EM<T>>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(const std::pair<EM<T>, EM<U>>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(const std::pair<EM<U>, EM<U>>& coords) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		explicit Coordinate(const std::pair<EM<U>, EM<V>>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(std::pair<EM<U>, EM<T>>&& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(std::pair<EM<T>, EM<U>>&& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(std::pair<EM<U>, EM<U>>&& coords) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		explicit Coordinate(std::pair<EM<U>, EM<V>>&& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(const std::array<EM<U>, 2>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(std::array<EM<U>, 2>&& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(const Vector<U, 2>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(const GLSLvec2<U>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Coordinate(const glm::vec<2, U>& coords) noexcept;

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator=(const Coordinate<U>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator=(Coordinate<U>&& coords) noexcept;

		// Basic operator

		Coordinate& operator=(const Vector<T, 2>& coords) noexcept;
		Coordinate& operator=(const std::pair<EM<T>, EM<T>>& coords) noexcept;
		Coordinate& operator=(const GLSLvec2<T>& coords) noexcept;
		Coordinate& operator=(const glm::vec<2, T>& coords) noexcept;

		Coordinate& operator+=(const Coordinate& coords) noexcept;
		Coordinate& operator-=(const Coordinate& coords) noexcept;
		Coordinate& operator+=(const GLSLvec2<T>& coords) noexcept;
		Coordinate& operator-=(const GLSLvec2<T>& coords) noexcept;
		Coordinate& operator*=(T value) noexcept;
		Coordinate& operator/=(T value) noexcept;

		Coordinate operator-() const noexcept;

		// Basic operator with conversion

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator=(const Vector<U, 2>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator=(const std::pair<EM<U>, EM<T>>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator=(const std::pair<EM<T>, EM<U>>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator=(const std::pair<EM<U>, EM<U>>& coords) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Coordinate& operator=(const std::pair<EM<U>, EM<V>>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator=(const GLSLvec2<U>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator=(const glm::vec<2, U>& coords) noexcept;

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator+=(const Coordinate<U>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator-=(const Coordinate<U>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator+=(const GLSLvec2<U>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator-=(const GLSLvec2<U>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator*=(U value) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Coordinate& operator/=(U value) noexcept;

		// Coordinate Operator

		friend Coordinate operator+(const Coordinate& coords1, const Coordinate& coords2)
		{
			auto coords = coords1;
			return coords += coords2;
		}

		friend Coordinate operator+(const GLSLvec2<T>& coords1, const Coordinate& coords2)
		{
			auto coords = coords2;
			return coords += coords1;
		}

		friend Coordinate operator+(const Coordinate& coords1, const GLSLvec2<T>& coords2)
		{
			auto coords = coords1;
			return coords += coords2;
		}

		friend Coordinate operator-(const Coordinate& coords1, const Coordinate& coords2)
		{
			auto coords = coords1;
			return coords -= coords2;
		}

		friend Coordinate operator-(const GLSLvec2<T>& coords1, const Coordinate& coords2)
		{
			auto coords = coords2;
			return coords -= coords1;
		}

		friend Coordinate operator-(const Coordinate& coords1, const GLSLvec2<T>& coords2)
		{
			auto coords = coords1;
			return coords -= coords2;
		}

		friend Coordinate operator*(T value, const Coordinate& coords)
		{
			auto coord = coords;
			return coord *= value;
		}

		friend Coordinate operator*(const Coordinate& coords, T value)
		{
			auto coord = coords;
			return coord *= value;
		}

		friend Coordinate operator/(const Coordinate& coords, T value)
		{
			auto coord = coords;
			return coord /= value;
		}

		// Coordinate Operator with conversion

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend Coordinate operator+(const Coordinate<U>& coords1, const Coordinate& coords2)
		{
			Coordinate coords = coords1;
			return coords += coords2;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend Coordinate operator+(const Coordinate& coords1, const Coordinate<U>& coords2)
		{
			Coordinate coords = coords1;
			return coords += coords2;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend Coordinate operator+(const GLSLvec2<U>& coords1, const Coordinate& coords2)
		{
			Coordinate coords = coords2;
			return coords += coords1;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend Coordinate operator+(const Coordinate& coords1, const GLSLvec2<U>& coords2)
		{
			Coordinate coords = coords1;
			return coords += coords2;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend Coordinate operator-(const Coordinate<U>& coords1, const Coordinate& coords2)
		{
			Coordinate coords = coords1;
			return coords -= coords2;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend Coordinate operator-(const Coordinate& coords1, const Coordinate<U>& coords2)
		{
			Coordinate coords = coords1;
			return coords -= coords2;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend Coordinate operator-(const GLSLvec2<U>& coords1, const Coordinate& coords2)
		{
			Coordinate coords = coords2;
			return coords -= coords1;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend Coordinate operator-(const Coordinate& coords1, const GLSLvec2<U>& coords2)
		{
			Coordinate coords = coords1;
			return coords -= coords2;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend Coordinate operator*(U value, const Coordinate& coords)
		{
			Coordinate coord = coords;
			return coord *= value;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend Coordinate operator*(const Coordinate& coords, U value)
		{
			Coordinate coord = coords;
			return coord *= value;
		}

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		friend Coordinate operator/(const Coordinate& coords, U value)
		{
			Coordinate coord = coords;
			return coord /= value;
		}

		friend std::ostream& operator<<(std::ostream& stream, const Coordinate& coords)
		{
			return stream << '(' << coords.m_coords.first.get_width_value() << ", " << coords.m_coords.second.get_height_value() << ')';
		}

		// Conversion operator
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit operator Coordinate<U>() const noexcept;
		explicit operator Vector<T, 2>() const noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit operator Vector<U, 2>() const noexcept;
		explicit operator glm::vec<2, T>() const noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit operator glm::vec<2, U>() const noexcept;

		virtual void update();

		Coordinate& set_reference(const reference& newReference) noexcept;
		Coordinate& undo_responsivness() noexcept;

		[[nodiscard]] const EM<T>& get_first_coord() const noexcept;
		void set_first_coord(const EM<T>& em) noexcept;

		[[nodiscard]] const EM<T>& get_second_coord() const noexcept;
		void set_second_coord(const EM<T>& em) noexcept;

	protected:
		std::pair<EM<T>, EM<T>> m_coords;
	};

	template<typename T>
	class Point final : public Coordinate<T>
	{
		T m_x;
		T m_y;

	public:
		// Basic constructor

		Point() noexcept;
		Point(const Point& point) noexcept;
		Point(Point&& point) noexcept;
		Point(const Coordinate<T>& point) noexcept;
		Point(Coordinate<T>&& point) noexcept;

		explicit Point(T xy) noexcept;
		explicit Point(const EM<T>& xy) noexcept;
		Point(T x, T y) noexcept;
		Point(const EM<T>& x, T y) noexcept;
		Point(T x, const EM<T>& y) noexcept;
		Point(const EM<T>& x, const EM<T>& y) noexcept;
		explicit Point(const Vector<T, 2>& point) noexcept;
		explicit Point(const GLSLvec2<T>& point) noexcept;
		explicit Point(const glm::vec<2, T>& point) noexcept;

		~Point() override = default;

		Point& operator=(const Point& point) noexcept;
		Point& operator=(Point&& point) noexcept;

		// Basic constructor with conversion

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Point(const Point<U>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Point(Point<U>&& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Point(const Coordinate<U>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Point(Coordinate<U>&& coords) noexcept;

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Point(U bothCoord) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Point(const EM<U>& bothCoord) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point(U x, T y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point(T x, U y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point(U x, U y) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Point(U x, V y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point(const EM<T>& x, U y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point(const EM<U>& x, T y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point(const EM<U>& x, U y) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Point(const EM<U>& x, V y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point(U x, const EM<T>& y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point(T x, const EM<U>& y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point(U x, const EM<U>& y) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Point(U x, const EM<V>& y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point(const EM<U>& x, const EM<T>& y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point(const EM<T>& x, const EM<U>& y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point(const EM<U>& x, const EM<U>& y) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Point(const EM<U>& x, const EM<V>& y) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Point(const Vector<U, 2>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Point(const GLSLvec2<U>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Point(const glm::vec<2, U>& coords) noexcept;

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point& operator=(const Point<U>& coords) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Point& operator=(Point<U>&& coords) noexcept;

		static bool is_in_rectangle(const Point& A, const Point& B, const Point& D, const Point& point);
		static Point rotate(const Point& point, const Point& center, T theta);
		static Point normalize(const Point& point);
		static T distance(const Point& point1, const Point& point2);
		static T dot(const Point& point1, const Point& point2);

		// Conversion operator
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit operator Point<U>() const noexcept;
		explicit operator Vector<T, 2>() const noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit operator Vector<U, 2>() const noexcept;
		explicit operator glm::vec<2, T>() const noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit operator glm::vec<2, U>() const noexcept;
		explicit operator GLSLvec2<T>() const noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit operator GLSLvec2<U>() const noexcept;

		const T& x;
		const T& y;
		EM<T>& em_x;
		EM<T>& em_y;

		void update() override;
	};

	template<typename T>
	class Size final : public Coordinate<T>
	{
		T m_width;
		T m_height;

	public:
		// Basic constructor

		Size() noexcept;
		Size(const Size& size) noexcept;
		Size(Size&& size) noexcept;
		Size(const Coordinate<T>& size) noexcept;
		Size(Coordinate<T>&& size) noexcept;

		explicit Size(T widthAndHeight) noexcept;
		explicit Size(const EM<T>& widthAndHeight) noexcept;
		Size(T width, T height) noexcept;
		Size(const EM<T>& width, T height) noexcept;
		Size(T width, const EM<T>& height) noexcept;
		Size(const EM<T>& width, const EM<T>& height) noexcept;
		explicit Size(const Vector<T, 2>& size) noexcept;
		explicit Size(const GLSLvec2<T>& size) noexcept;
		explicit Size(const glm::vec<2, T>& size) noexcept;

		~Size() override = default;

		Size& operator=(const Size& size) noexcept;
		Size& operator=(Size&& size) noexcept;

		// Basic constructor with conversion

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Size(const Size<U>& size) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Size(Size<U>&& size) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Size(const Coordinate<U>& size) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Size(Coordinate<U>&& size) noexcept;

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Size(U widthAndHeight) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Size(const EM<U>& widthAndHeight) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size(U width, T height) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size(T width, U height) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size(U width, U height) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Size(U width, V height) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size(const EM<T>& width, U height) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size(const EM<U>& width, T height) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size(const EM<U>& width, U height) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Size(const EM<U>& width, V height) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size(U width, const EM<T>& height) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size(T width, const EM<U>& height) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size(U width, const EM<U>& height) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Size(U width, const EM<V>& height) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size(const EM<U>& width, const EM<T>& height) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size(const EM<T>& width, const EM<U>& height) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size(const EM<U>& width, const EM<U>& height) noexcept;
		template<typename U, typename V, typename = std::enable_if_t<std::is_convertible_v<U, T>>, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
		Size(const EM<U>& width, const EM<V>& height) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Size(const Vector<U, 2>& size) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Size(const GLSLvec2<U>& size) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit Size(const glm::vec<2, U>& size) noexcept;

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size& operator=(const Size<U>& size) noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		Size& operator=(Size<U>&& size) noexcept;

		// Conversion operator
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit operator Size<U>() const noexcept;
		explicit operator Vector<T, 2>() const noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit operator Vector<U, 2>() const noexcept;
		explicit operator glm::vec<2, T>() const noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit operator glm::vec<2, U>() const noexcept;
		explicit operator GLSLvec2<T>() const noexcept;
		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
		explicit operator GLSLvec2<U>() const noexcept;

		const T& width;
		const T& height;
		EM<T>& em_width;
		EM<T>& em_height;

		void update() override;
	};
}

namespace hgui
{
	typedef hgui::kernel::Point<HGUI_PRECISION> point;
	typedef hgui::kernel::Size<HGUI_PRECISION> size;
}

// Literal Operator

inline hgui::kernel::EM<HGUI_PRECISION> operator""_em(const unsigned long long value) noexcept
{
	return hgui::kernel::EM(static_cast<HGUI_PRECISION>(static_cast<double>(value) / 100.));
}

inline hgui::kernel::EM<HGUI_PRECISION> operator""_em(const long double value) noexcept
{
	return hgui::kernel::EM(static_cast<HGUI_PRECISION>(value / 100.));
}

template<typename T>
hgui::kernel::EM<T>::EM() noexcept :
	m_value{},
	m_operations()
{
}

template<typename T>
hgui::kernel::EM<T>::EM(T value) noexcept :
	m_value(value),
	m_operations()
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>::EM(U value) noexcept :
	m_value(static_cast<T>(value)),
	m_operations()
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>::EM(const EM<U>& em) noexcept :
	EM(em.operator EM())
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>::EM(EM<U>&& em) noexcept :
	EM(std::move(em.operator EM()))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator=(const EM<U>& em) noexcept
{
	operator=(em.operator EM());
	return *this;
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator=(EM<U>&& em) noexcept
{
	operator=(std::move(em.operator EM()));
	return *this;
}

template<typename T>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator+=(T element) noexcept
{
	m_operations.push_back(std::make_pair(operations::ADDITION, element));
	return *this;
}

template<typename T>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator-=(T element) noexcept
{
	m_operations.push_back(std::make_pair(operations::SUBTRACTION, element));
	return *this;
}

template<typename T>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator*=(T element) noexcept
{
	m_operations.push_back(std::make_pair(operations::MULTIPLICATION, element));
	return *this;
}

template<typename T>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator/=(T element) noexcept
{
	m_operations.push_back(std::make_pair(operations::DIVISION, element));
	return *this;
}

template<typename T>
hgui::kernel::EM<T> hgui::kernel::EM<T>::operator-() const noexcept
{
	EM em(*this);
	em.m_operations.push_back(std::make_pair(operations::MULTIPLICATION, static_cast<T>(-1)));
	return em;
}

template<typename T>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator+=(const EM& em) noexcept
{
	m_operations.push_back(std::make_pair(operations::ADDITION, em));
	return *this;
}

template<typename T>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator-=(const EM& em) noexcept
{
	m_operations.push_back(std::make_pair(operations::SUBTRACTION, em));
	return *this;
}

template<typename T>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator*=(const EM& em) noexcept
{
	m_operations.push_back(std::make_pair(operations::MULTIPLICATION, em));
	return *this;
}

template<typename T>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator/=(const EM& em) noexcept
{
	m_operations.push_back(std::make_pair(operations::DIVISION, em));
	return *this;
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator+=(U element) noexcept
{
	return operator+=(static_cast<T>(element));
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator-=(U element) noexcept
{
	return operator-=(static_cast<T>(element));
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator*=(U element) noexcept
{
	return operator*=(static_cast<T>(element));
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator/=(U element) noexcept
{
	return operator/=(static_cast<T>(element));
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator+=(const EM<U>& em) noexcept
{
	return operator+=(em.operator EM());
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator-=(const EM<U>& em) noexcept
{
	return operator-=(em.operator EM());
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator*=(const EM<U>& em) noexcept
{
	return operator*=(em.operator EM());
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>& hgui::kernel::EM<T>::operator/=(const EM<U>& em) noexcept
{
	return operator/=(em.operator EM());
}

template<typename T>
template<typename U, typename>
hgui::kernel::EM<T>::operator EM<U>() const noexcept
{
	EM<U> em(static_cast<U>(this->m_value));
	em.m_reference = this->m_reference;
	for (const auto& operation : this->m_operations)
	{
		if (operation.second.index() == 0)
			em.m_operations.emplace_back(operation.first, static_cast<U>(std::get<0>(operation.second)));
		else if (operation.second.index() == 1)
			em.m_operations.emplace_back(operation.first, static_cast<EM<U>>(std::get<1>(operation.second)));
	}
	return em;
}

template<typename T>
T hgui::kernel::EM<T>::get_width_value() const
{
	T ref;
	switch (m_reference)
	{
		case reference::WIDTH:
			ref = static_cast<T>(EM<HGUI_PRECISION>::referenceSize.first);
			break;
		case reference::HEIGHT:
			ref = static_cast<T>(EM<HGUI_PRECISION>::referenceSize.second);
			break;
		case reference::BOTH:
			ref = static_cast<T>(EM<HGUI_PRECISION>::referenceSize.first);
			break;
	}
	auto function = [&](T sum, std::pair<operations, std::variant<T, EM>> element) { return calcul(sum, element, static_cast<T>(EM<HGUI_PRECISION>::referenceSize.first)); };
	return static_cast<T>(std::accumulate(m_operations.begin(), m_operations.end(), m_value * ref, function));
}

template<typename T>
T hgui::kernel::EM<T>::get_height_value() const
{
	T ref;
	switch (m_reference)
	{
		case reference::WIDTH:
			ref = static_cast<T>(EM<HGUI_PRECISION>::referenceSize.first);
			break;
		case reference::HEIGHT:
			ref = static_cast<T>(EM<HGUI_PRECISION>::referenceSize.second);
			break;
		case reference::BOTH:
			ref = static_cast<T>(EM<HGUI_PRECISION>::referenceSize.second);
			break;
	}
	auto function = [&](T sum, std::pair<operations, std::variant<T, EM>> element) { return calcul(sum, element, static_cast<T>(EM<HGUI_PRECISION>::referenceSize.second)); };
	return static_cast<T>(std::accumulate(m_operations.begin(), m_operations.end(), m_value * ref, function));
}

template<typename T>
void hgui::kernel::EM<T>::set_reference(const reference& ref) noexcept
{
	m_reference = ref;
}

template<typename T>
const hgui::reference& hgui::kernel::EM<T>::get_reference() const noexcept
{
	return m_reference;
}

template<typename T>
void hgui::kernel::EM<T>::set_base_value(T baseValue) noexcept
{
	m_value = baseValue;
}

template<typename T>
T hgui::kernel::EM<T>::get_base_value() const noexcept
{
	return m_value;
}

template<typename T>
T hgui::kernel::EM<T>::calcul(T sum, std::pair<operations, std::variant<T, EM>> element, T referenceSize) noexcept
{
	if (auto value = std::get_if<T>(&element.second))
	{
		switch (element.first)
		{
			case operations::ADDITION:
				return sum + *value;
			case operations::SUBTRACTION:
				return sum - *value;
			case operations::MULTIPLICATION:
				return sum * *value;
			case operations::DIVISION:
				return sum / *value;
			default:
				return {};
		}
	}
	if (auto em = std::get_if<EM>(&element.second))
	{
		T ref;
		switch (em->m_reference)
		{
			case reference::WIDTH:
				ref = static_cast<T>(EM<HGUI_PRECISION>::referenceSize.first);
				break;
			case reference::HEIGHT:
				ref = static_cast<T>(EM<HGUI_PRECISION>::referenceSize.second);
				break;
			case reference::BOTH:
				ref = referenceSize;
				break;
			default:
				ref = referenceSize;;
		}
		auto function = [&](T s, std::pair<operations, std::variant<T, EM>> el) { return calcul(s, el, referenceSize); };
		switch (element.first)
		{
			case operations::ADDITION:
				return sum + std::accumulate(em->m_operations.begin(), em->m_operations.end(), em->m_value * ref, function);
			case operations::SUBTRACTION:
				return sum - std::accumulate(em->m_operations.begin(), em->m_operations.end(), em->m_value * ref, function);
			case operations::MULTIPLICATION:
				return sum * std::accumulate(em->m_operations.begin(), em->m_operations.end(), em->m_value * ref, function);
			case operations::DIVISION:
				return sum / std::accumulate(em->m_operations.begin(), em->m_operations.end(), em->m_value * ref, function);
			default:
				return {};
		}
	}
	return {};
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(T bothCoord) noexcept :
	m_coords(EM<T>{} + bothCoord, EM<T>{} + bothCoord)
{
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(const EM<T>& bothCoord) noexcept :
	m_coords(bothCoord, bothCoord)
{
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(T x, T y) noexcept :
	m_coords(EM<T>{} + x, EM<T>{} + y)
{
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(const EM<T>& x, T y) noexcept :
	m_coords(x, EM<T>{} + y)
{
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(T x, const EM<T>& y) noexcept :
	m_coords(EM<T>{} + x, y)
{
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(const EM<T>& x, const EM<T>& y) noexcept :
	m_coords(x, y)
{
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(const std::pair<EM<T>, EM<T>>& coords) noexcept :
	m_coords(coords)
{
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(std::pair<EM<T>, EM<T>>&& coords) noexcept :
	m_coords(std::move(coords))
{
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(const std::array<EM<T>, 2>& coords) noexcept :
	m_coords(coords[0], coords[1])
{
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(std::array<EM<T>, 2>&& coords) noexcept :
	m_coords(std::move(coords[0]), std::move(coords[1]))
{
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(const GLSLvec2<T>& coords) noexcept :
	m_coords(EM<T>{} + coords.x, EM<T>{} + coords.y)
{
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(const Vector<T, 2>& coords) noexcept :
	m_coords(EM<T>{} + coords[0], EM<T>{} + coords[1])
{
}

template<typename T>
hgui::kernel::Coordinate<T>::Coordinate(const glm::vec<2, T>& coords) noexcept :
	m_coords(EM<T>{} + coords.x, EM<T>{} + coords.y)
{
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const Coordinate& coords) noexcept
{
	m_coords.first = coords.m_coords.first;
	m_coords.second = coords.m_coords.second;
	update();
	return *this;
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(Coordinate&& coords) noexcept
{
	m_coords.first = std::move(coords.m_coords.first);
	m_coords.second = std::move(coords.m_coords.second);
	update();
	return *this;
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const Coordinate<U>& coords) noexcept :
	Coordinate(coords.operator Coordinate())
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(Coordinate<U>&& coords) noexcept :
	Coordinate(std::move(coords.operator Coordinate()))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(U bothCoord) noexcept :
	Coordinate(static_cast<T>(bothCoord))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const EM<U>& bothCoord) noexcept :
	Coordinate(static_cast<EM<T>>(bothCoord))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(U x, T y) noexcept :
	Coordinate(static_cast<T>(x), y)
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(T x, U y) noexcept :
	Coordinate(x, static_cast<T>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(U x, U y) noexcept :
	Coordinate(static_cast<T>(x), static_cast<T>(y))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Coordinate<T>::Coordinate(U x, V y) noexcept :
	Coordinate(static_cast<T>(x), static_cast<T>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const EM<T>& x, U y) noexcept :
	Coordinate(x, static_cast<T>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const EM<U>& x, T y) noexcept :
	Coordinate(static_cast<EM<T>>(x), y)
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const EM<U>& x, U y) noexcept :
	Coordinate(static_cast<EM<T>>(x), static_cast<T>(y))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Coordinate<T>::Coordinate(const EM<U>& x, V y) noexcept :
	Coordinate(static_cast<EM<T>>(x), static_cast<T>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(U x, const EM<T>& y) noexcept :
	Coordinate(static_cast<T>(x), y)
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(T x, const EM<U>& y) noexcept :
	Coordinate(x, static_cast<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(U x, const EM<U>& y) noexcept :
	Coordinate(static_cast<T>(x), static_cast<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Coordinate<T>::Coordinate(U x, const EM<V>& y) noexcept :
	Coordinate(static_cast<T>(x), static_cast<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const EM<U>& x, const EM<T>& y) noexcept :
	Coordinate(static_cast<EM<T>>(x), y)
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const EM<T>& x, const EM<U>& y) noexcept :
	Coordinate(x, static_cast<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const EM<U>& x, const EM<U>& y) noexcept :
	Coordinate(static_cast<EM<T>>(x), static_cast<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Coordinate<T>::Coordinate(const EM<U>& x, const EM<V>& y) noexcept :
	Coordinate(static_cast<EM<T>>(x), static_cast<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const std::pair<EM<U>, EM<T>>& coords) noexcept :
	Coordinate(std::make_pair(static_cast<EM<T>>(coords.first), coords.second))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const std::pair<EM<T>, EM<U>>& coords) noexcept :
	Coordinate(std::make_pair(coords.first, static_cast<EM<T>>(coords.second)))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const std::pair<EM<U>, EM<U>>& coords) noexcept :
	Coordinate(std::make_pair(static_cast<EM<T>>(coords.first), static_cast<EM<T>>(coords.second)))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Coordinate<T>::Coordinate(const std::pair<EM<U>, EM<V>>& coords) noexcept :
	Coordinate(std::make_pair(static_cast<EM<T>>(coords.first), static_cast<EM<T>>(coords.second)))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(std::pair<EM<U>, EM<T>>&& coords) noexcept :
	Coordinate(std::move(std::make_pair(static_cast<EM<T>>(coords.first), coords.second)))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(std::pair<EM<T>, EM<U>>&& coords) noexcept :
	Coordinate(std::move(std::make_pair(coords.first, static_cast<EM<T>>(coords.second))))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(std::pair<EM<U>, EM<U>>&& coords) noexcept :
	Coordinate(std::move(std::make_pair(static_cast<EM<T>>(coords.first), static_cast<EM<T>>(coords.second))))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Coordinate<T>::Coordinate(std::pair<EM<U>, EM<V>>&& coords) noexcept :
	Coordinate(std::move(std::make_pair(static_cast<EM<T>>(coords.first), static_cast<EM<T>>(coords.second))))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const std::array<EM<U>, 2>& coords) noexcept :
	Coordinate(std::array{static_cast<EM<T>>(coords[0]), static_cast<EM<T>>(coords[1])})
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(std::array<EM<U>, 2>&& coords) noexcept :
	Coordinate(std::move(std::array{static_cast<EM<T>>(coords[0]), static_cast<EM<T>>(coords[1])}))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const Vector<U, 2>& coords) noexcept :
	Coordinate(Vector<T, 2>(std::valarray<T>{static_cast<T>(coords[0]), static_cast<T>(coords[1])}))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const GLSLvec2<U>& coords) noexcept :
	Coordinate(GLSLvec2<T>(coords))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::Coordinate(const glm::vec<2, U>& coords) noexcept :
	Coordinate(glm::vec<2, T>(coords))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const Coordinate<U>& coords) noexcept
{
	return operator=(coords.operator Coordinate());
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(Coordinate<U>&& coords) noexcept
{
	return operator=(std::move(coords.operator Coordinate()));
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const Vector<T, 2>& coords) noexcept
{
	m_coords.first = EM<T>{} + coords[0];
	m_coords.second = EM<T>{} + coords[1];
	update();
	return *this;
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const std::pair<EM<T>, EM<T>>& coords) noexcept
{
	m_coords.first = coords.first;
	m_coords.second = coords.second;
	update();
	return *this;
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const GLSLvec2<T>& coords) noexcept
{
	m_coords.first = EM<T>{} + coords.x;
	m_coords.second = EM<T>{} + coords.y;
	update();
	return *this;
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const glm::vec<2, T>& coords) noexcept
{
	m_coords.first = EM<T>{} + coords.x;
	m_coords.second = EM<T>{} + coords.y;
	update();
	return *this;
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator+=(const Coordinate& coords) noexcept
{
	m_coords.first += coords.m_coords.first;
	m_coords.second += coords.m_coords.second;
	update();
	return *this;
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator-=(const Coordinate& coords) noexcept
{
	m_coords.first -= coords.m_coords.first;
	m_coords.second -= coords.m_coords.second;
	update();
	return *this;
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator+=(const GLSLvec2<T>& coords) noexcept
{
	m_coords.first += coords.x;
	m_coords.second += coords.y;
	update();
	return *this;
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator-=(const GLSLvec2<T>& coords) noexcept
{
	m_coords.first -= coords.x;
	m_coords.second -= coords.y;
	update();
	return *this;
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator*=(T value) noexcept
{
	m_coords.first *= value;
	m_coords.second *= value;
	update();
	return *this;
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator/=(T value) noexcept
{
	m_coords.first /= value;
	m_coords.second /= value;
	update();
	return *this;
}

template<typename T>
hgui::kernel::Coordinate<T> hgui::kernel::Coordinate<T>::operator-() const noexcept
{
	return Coordinate(std::make_pair(-m_coords.first, -m_coords.second));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const Vector<U, 2>& coords) noexcept
{
	return operator=(Coordinate(coords));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const std::pair<EM<U>, EM<T>>& coords) noexcept
{
	return operator=(Coordinate(coords));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const std::pair<EM<T>, EM<U>>& coords) noexcept
{
	return operator=(Coordinate(coords));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const std::pair<EM<U>, EM<U>>& coords) noexcept
{
	return operator=(Coordinate(coords));
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const std::pair<EM<U>, EM<V>>& coords) noexcept
{
	return operator=(Coordinate(coords));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const GLSLvec2<U>& coords) noexcept
{
	return operator=(Coordinate(coords));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator=(const glm::vec<2, U>& coords) noexcept
{
	return operator=(Coordinate(coords));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator+=(const Coordinate<U>& coords) noexcept
{
	return operator+=(coords.operator Coordinate());
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator-=(const Coordinate<U>& coords) noexcept
{
	return operator-=(coords.operator Coordinate());
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator+=(const GLSLvec2<U>& coords) noexcept
{
	return operator+=(GLSLvec2<T>(coords));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator-=(const GLSLvec2<U>& coords) noexcept
{
	return operator-=(GLSLvec2<T>(coords));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator*=(U value) noexcept
{
	return operator*=(static_cast<T>(value));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::operator/=(U value) noexcept
{
	return operator/=(static_cast<T>(value));
}

template<typename T>
hgui::kernel::Coordinate<T>::operator hgui::kernel::Vector<T, 2>() const noexcept
{
	return Vector<T, 2>(std::valarray<T>{this->m_coords.first.get_width_value(), this->m_coords.second.get_height_value()});
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::operator hgui::kernel::Vector<U, 2>() const noexcept
{
	return Vector<U, 2>(std::valarray<U>{static_cast<U>(this->m_coords.first.get_width_value()), static_cast<U>(this->m_coords.second.get_height_value())});
}

template<typename T>
hgui::kernel::Coordinate<T>::operator glm::vec<2, T>() const noexcept
{
	return glm::vec<2, T>(m_coords.first.get_width_value(), m_coords.second.get_height_value());
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::operator glm::vec<2, U>() const noexcept
{
	return glm::vec<2, U>(static_cast<U>(this->m_coords.first.get_width_value()), static_cast<U>(this->m_coords.second.get_height_value()));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Coordinate<T>::operator Coordinate<U>() const noexcept
{
	return Coordinate<U>(std::make_pair(static_cast<EM<U>>(this->m_coords.first), static_cast<EM<U>>(this->m_coords.first)));
}

template<typename T>
void hgui::kernel::Coordinate<T>::update()
{
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::set_reference(const reference& newReference) noexcept
{
	m_coords.first.set_reference(newReference);
	m_coords.second.set_reference(newReference);
	update();
	return *this;
}

template<typename T>
hgui::kernel::Coordinate<T>& hgui::kernel::Coordinate<T>::undo_responsivness() noexcept
{
	m_coords = std::pair(EM<T>{} + m_coords.first.get_width_value(), EM<T>{} + m_coords.second.get_height_value());
	return *this;
}

template<typename T>
const hgui::kernel::EM<T>& hgui::kernel::Coordinate<T>::get_first_coord() const noexcept
{
	return m_coords.first;
}

template<typename T>
void hgui::kernel::Coordinate<T>::set_first_coord(const EM<T>& em) noexcept
{
	m_coords.first = em;
}

template<typename T>
const hgui::kernel::EM<T>& hgui::kernel::Coordinate<T>::get_second_coord() const noexcept
{
	return m_coords.second;
}

template<typename T>
void hgui::kernel::Coordinate<T>::set_second_coord(const EM<T>& em) noexcept
{
	m_coords.second = em;
}

template<typename T>
hgui::kernel::Point<T>::Point() noexcept :
	Coordinate<T>(),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(const Point& point) noexcept :
	Coordinate<T>(point),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(Point&& point) noexcept :
	Coordinate<T>(std::move(point)),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(const Coordinate<T>& point) noexcept :
	Coordinate<T>(point),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(Coordinate<T>&& point) noexcept :
	Coordinate<T>(std::move(point)),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(T xy) noexcept :
	Coordinate<T>(xy),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(const EM<T>& xy) noexcept :
	Coordinate<T>(xy),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(T x, T y) noexcept :
	Coordinate<T>(x, y),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(const EM<T>& x, T y) noexcept :
	Coordinate<T>(x, y),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(T x, const EM<T>& y) noexcept :
	Coordinate<T>(x, y),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(const EM<T>& x, const EM<T>& y) noexcept :
	Coordinate<T>(x, y),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(const Vector<T, 2>& point) noexcept :
	Coordinate<T>(point),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(const GLSLvec2<T>& point) noexcept :
	Coordinate<T>(point),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>::Point(const glm::vec<2, T>& point) noexcept :
	Coordinate<T>(point),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Point<T>& hgui::kernel::Point<T>::operator=(const Point& point) noexcept
{
	Coordinate<T>::operator=(point);
	return *this;
}

template<typename T>
hgui::kernel::Point<T>& hgui::kernel::Point<T>::operator=(Point&& point) noexcept
{
	Coordinate<T>::operator=(std::move(point));
	return *this;
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(const Point<U>& coords) noexcept :
	Point(coords.operator Point())
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(Point<U>&& coords) noexcept :
	Point(std::move(coords.operator Point()))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(const Coordinate<U>& coords) noexcept :
	Point(static_cast<Coordinate<T>>(coords))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(Coordinate<U>&& coords) noexcept :
	Point(std::move(static_cast<Coordinate<T>>(coords)))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(U bothCoord) noexcept :
	Point(static_cast<T>(bothCoord))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(const EM<U>& bothCoord) noexcept :
	Point(static_cast<EM<T>>(bothCoord))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(U x, T y) noexcept :
	Point(static_cast<T>(x), y)
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(T x, U y) noexcept :
	Point(x, static_cast<T>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(U x, U y) noexcept :
	Point(static_cast<T>(x), static_cast<T>(y))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Point<T>::Point(U x, V y) noexcept :
	Point(static_cast<T>(x), static_cast<T>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(const EM<T>& x, U y) noexcept :
	Point(x, static_cast<T>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(const EM<U>& x, T y) noexcept :
	Point(static_cast<EM<T>>(x), y)
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(const EM<U>& x, U y) noexcept :
	Point(static_cast<EM<T>>(x), static_cast<T>(y))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Point<T>::Point(const EM<U>& x, V y) noexcept :
	Point(static_cast<EM<T>>(x), static_cast<T>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(U x, const EM<T>& y) noexcept :
	Point(static_cast<T>(x), y)
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(T x, const EM<U>& y) noexcept :
	Point(x, static_cast<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(U x, const EM<U>& y) noexcept :
	Point(static_cast<T>(x), static_cast<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Point<T>::Point(U x, const EM<V>& y) noexcept :
	Point(static_cast<T>(x), static_cast<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(const EM<U>& x, const EM<T>& y) noexcept :
	Point(static_cast<EM<T>>(x), y)
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(const EM<T>& x, const EM<U>& y) noexcept :
	Point(x, static_cast<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(const EM<U>& x, const EM<U>& y) noexcept :
	Point(static_cast<EM<T>>(x), static_cast<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Point<T>::Point(const EM<U>& x, const EM<V>& y) noexcept :
	Point(static_cast<EM<T>>(x), static_cast<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(const Vector<U, 2>& coords) noexcept :
	Coordinate<T>(coords),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(const GLSLvec2<U>& coords) noexcept :
	Coordinate<T>(coords),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::Point(const glm::vec<2, U>& coords) noexcept :
	Coordinate<T>(coords),
	m_x(),
	m_y(),
	x(m_x),
	y(m_y),
	em_x(this->m_coords.first),
	em_y(this->m_coords.second)
{
	update();
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>& hgui::kernel::Point<T>::operator=(const Point<U>& coords) noexcept
{
	return operator=(coords.operator Point());
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>& hgui::kernel::Point<T>::operator=(Point<U>&& coords) noexcept
{
	return operator=(std::move(coords.operator Point()));
}

template<typename T>
bool hgui::kernel::Point<T>::is_in_rectangle(const Point& A, const Point& B, const Point& D, const Point& point)
{
	const auto dotAMAB = point::dot(point - A, B - A), dotAMAD = point::dot(point - A, D - A);
	return (0 < dotAMAB && dotAMAB < point::dot(B - A, B - A)) && (0 < dotAMAD && dotAMAD < point::dot(D - A, D - A));
}

template<typename T>
hgui::kernel::Point<T> hgui::kernel::Point<T>::rotate(const Point& point, const Point& center, const T theta)
{
	const Point translated = point - center;

	const float angleRadians = glm::radians(theta);
	const float cosTheta = std::cos(angleRadians);
	const float sinTheta = std::sin(angleRadians);

	const Point rotated(translated.x * cosTheta - translated.y * sinTheta, translated.x * sinTheta + translated.y * cosTheta);

	return rotated + center;
}

template<typename T>
hgui::kernel::Point<T> hgui::kernel::Point<T>::normalize(const Point& point)
{
	try
	{
		auto vec = static_cast<Vector<T, 2>>(point);
		vec.normalize();
		return Point(vec);
	}
	catch (...)
	{
		return {};
	}
}

template<typename T>
T hgui::kernel::Point<T>::distance(const Point& point1, const Point& point2)
{
	return kernel::distance(static_cast<Vector<T, 2>>(point1), static_cast<Vector<T, 2>>(point2));
}

template<typename T>
T hgui::kernel::Point<T>::dot(const Point& point1, const Point& point2)
{
	return kernel::dot(static_cast<Vector<T, 2>>(point1), static_cast<Vector<T, 2>>(point2));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::operator Point<U>() const noexcept
{
	return Point<U>(this->em_x, this->em_y);
}

template<typename T>
hgui::kernel::Point<T>::operator hgui::kernel::Vector<T, 2>() const noexcept
{
	return Vector<T, 2>(std::valarray<T>{this->x, this->y});
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::operator hgui::kernel::Vector<U, 2>() const noexcept
{
	return Vector<U, 2>(std::valarray<U>{static_cast<U>(this->x), static_cast<U>(this->y)});
}

template<typename T>
hgui::kernel::Point<T>::operator glm::vec<2, T>() const noexcept
{
	return glm::vec<2, T>(x, y);
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::operator glm::vec<2, U>() const noexcept
{
	return glm::vec<2, U>(static_cast<U>(this->x), static_cast<U>(this->y));
}

template<typename T>
hgui::kernel::Point<T>::operator hgui::kernel::GLSLvec2<T>() const noexcept
{
	return glm::vec<2, T>(x, y);
}

template<typename T>
template<typename U, typename>
hgui::kernel::Point<T>::operator hgui::kernel::GLSLvec2<U>() const noexcept
{
	return glm::vec<2, T>(x, y);
}

template<typename T>
void hgui::kernel::Point<T>::update()
{
	m_x = this->m_coords.first.get_width_value();
	m_y = this->m_coords.second.get_height_value();
}

template<typename T>
hgui::kernel::Size<T>::Size() noexcept :
	Coordinate<T>(),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(const Size& size) noexcept :
	Coordinate<T>(size),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(Size&& size) noexcept :
	Coordinate<T>(std::move(size)),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(const Coordinate<T>& size) noexcept :
	Coordinate<T>(size),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(Coordinate<T>&& size) noexcept :
	Coordinate<T>(std::move(size)),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(T widthAndHeight) noexcept :
	Coordinate<T>(widthAndHeight),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(const EM<T>& widthAndHeight) noexcept :
	Coordinate<T>(widthAndHeight),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(T width, T height) noexcept :
	Coordinate<T>(width, height),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(const EM<T>& width, T height) noexcept :
	Coordinate<T>(width, height),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(T width, const EM<T>& height) noexcept :
	Coordinate<T>(width, height),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(const EM<T>& width, const EM<T>& height) noexcept :
	Coordinate<T>(width, height),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(const Vector<T, 2>& size) noexcept :
	Coordinate<T>(size),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(const GLSLvec2<T>& size) noexcept :
	Coordinate<T>(size),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>::Size(const glm::vec<2, T>& size) noexcept :
	Coordinate<T>(size),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
hgui::kernel::Size<T>& hgui::kernel::Size<T>::operator=(const Size& size) noexcept
{
	Coordinate<T>::operator=(size);
	return *this;
}

template<typename T>
hgui::kernel::Size<T>& hgui::kernel::Size<T>::operator=(Size&& size) noexcept
{
	Coordinate<T>::operator=(std::move(size));
	return *this;
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(const Size<U>& size) noexcept :
	Size(size.operator Size())
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(Size<U>&& size) noexcept :
	Size(std::move(size.operator Size()))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(const Coordinate<U>& size) noexcept :
	Size(static_cast<Coordinate<T>>(size))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(Coordinate<U>&& size) noexcept :
	Size(std::move(static_cast<Coordinate<T>>(size)))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(U widthAndHeight) noexcept :
	Size(static_cast<T>(widthAndHeight))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(const EM<U>& widthAndHeight) noexcept :
	Size(static_cast<EM<T>>(widthAndHeight))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(U width, T height) noexcept :
	Size(static_cast<T>(width), height)
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(T width, U height) noexcept :
	Size(width, static_cast<T>(height))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(U width, U height) noexcept :
	Size(static_cast<T>(width), static_cast<T>(height))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Size<T>::Size(U width, V height) noexcept :
	Size(static_cast<T>(width), static_cast<T>(height))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(const EM<T>& width, U height) noexcept :
	Size(width, static_cast<T>(height))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(const EM<U>& width, T height) noexcept :
	Size(static_cast<EM<T>>(width), height)
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(const EM<U>& width, U height) noexcept :
	Size(static_cast<EM<T>>(width), static_cast<T>(height))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Size<T>::Size(const EM<U>& width, V height) noexcept :
	Size(static_cast<EM<T>>(width), static_cast<T>(height))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(U width, const EM<T>& height) noexcept :
	Size(static_cast<T>(width), height)
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(T width, const EM<U>& height) noexcept :
	Size(width, static_cast<EM<T>>(height))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(U width, const EM<U>& height) noexcept :
	Size(static_cast<T>(width), static_cast<EM<T>>(height))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Size<T>::Size(U width, const EM<V>& height) noexcept :
	Size(static_cast<T>(width), static_cast<EM<T>>(height))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(const EM<U>& width, const EM<T>& height) noexcept :
	Size(static_cast<EM<T>>(width), height)
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(const EM<T>& width, const EM<U>& height) noexcept :
	Size(width, static_cast<EM<T>>(height))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(const EM<U>& width, const EM<U>& height) noexcept :
	Size(static_cast<EM<T>>(width), static_cast<EM<T>>(height))
{
}

template<typename T>
template<typename U, typename V, typename, typename>
hgui::kernel::Size<T>::Size(const EM<U>& width, const EM<V>& height) noexcept :
	Size(static_cast<EM<T>>(width), static_cast<EM<T>>(height))
{
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(const Vector<U, 2>& size) noexcept :
	Coordinate<T>(size),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(const GLSLvec2<U>& size) noexcept :
	Coordinate<T>(size),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::Size(const glm::vec<2, U>& size) noexcept :
	Coordinate<T>(size),
	m_width(),
	m_height(),
	width(m_width),
	height(m_height),
	em_width(this->m_coords.first),
	em_height(this->m_coords.second)
{
	update();
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>& hgui::kernel::Size<T>::operator=(const Size<U>& size) noexcept
{
	return operator=(size.operator Size());
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>& hgui::kernel::Size<T>::operator=(Size<U>&& size) noexcept
{
	return operator=(std::move(size.operator Size()));
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::operator Size<U>() const noexcept
{
	return Size<U>(this->em_width, this->em_height);
}

template<typename T>
hgui::kernel::Size<T>::operator hgui::kernel::Vector<T, 2>() const noexcept
{
	return Vector<T, 2>(width, height);
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::operator hgui::kernel::Vector<U, 2>() const noexcept
{
	return Vector<U, 2>(std::valarray<U>{static_cast<U>(this->x), static_cast<U>(this->y)});
}

template<typename T>
hgui::kernel::Size<T>::operator glm::vec<2, T>() const noexcept
{
	return glm::vec<2, T>(width, height);
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::operator glm::vec<2, U>() const noexcept
{
	return glm::vec<2, U>(static_cast<U>(this->x), static_cast<U>(this->y));
}

template<typename T>
hgui::kernel::Size<T>::operator hgui::kernel::GLSLvec2<T>() const noexcept
{
	return glm::vec<2, T>(width, height);
}

template<typename T>
template<typename U, typename>
hgui::kernel::Size<T>::operator hgui::kernel::GLSLvec2<U>() const noexcept
{
	return glm::vec<2, U>(static_cast<U>(this->x), static_cast<U>(this->y));
}

template<typename T>
void hgui::kernel::Size<T>::update()
{
	m_width = this->m_coords.first.get_width_value();
	m_height = this->m_coords.second.get_height_value();
}
