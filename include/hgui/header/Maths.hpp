#pragma once

#include "Include.h"
#include "Define.h"
#include "Vector.hpp"

namespace hgui
{
	namespace kernel
	{
		template<typename T>
		class Size;
		template<typename T>
		class Point;

		enum class operation
		{
			ADDITION,
			SUBTRACTION,
			MULTIPLICATION,
			DIVISION
		};

		template<typename T>
		class EM
		{
			friend class Size<T>;
			friend class Point<T>;

		public:
			EM() noexcept;
			explicit EM(T value) noexcept;
			EM(const EM& em) noexcept = default;
			EM(EM&& em) noexcept = default;

			~EM() noexcept = default;

			EM& operator=(const EM& em) noexcept = default;
			EM& operator=(EM&& em) noexcept = default;

			friend EM operator+(EM em, T element) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::ADDITION, element));
				return em;
			}

			template<typename U>
			friend EM operator+(EM em, U element) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::ADDITION, static_cast<T>(element)));
				return em;
			}

			friend EM operator+(T element, EM em) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::ADDITION, element));
				return em;
			}

			template<typename U>
			friend EM operator+(U element, EM em) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::ADDITION, static_cast<T>(element)));
				return em;
			}

			friend EM operator-(EM em, T element) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::SUBTRACTION, element));
				return em;
			}

			template<typename U>
			friend EM operator-(EM em, U element) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::SUBTRACTION, static_cast<T>(element)));
				return em;
			}

			friend EM operator-(T element, EM em) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::SUBTRACTION, element));
				return em;
			}

			template<typename U>
			friend EM operator-(U element, EM em) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::SUBTRACTION, static_cast<T>(element)));
				return em;
			}

			friend EM operator*(EM em, T element) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::MULTIPLICATION, element));
				return em;
			}

			template<typename U>
			friend EM operator*(EM em, U element) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::MULTIPLICATION, static_cast<T>(element)));
				return em;
			}

			friend EM operator*(T element, EM em) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::MULTIPLICATION, element));
				return em;
			}

			template<typename U>
			friend EM operator*(U element, EM em) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::MULTIPLICATION, static_cast<T>(element)));
				return em;
			}

			friend EM operator/(EM em, T element) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::DIVISION, element));
				return em;
			}

			template<typename U>
			friend EM operator/(EM em, U element) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::DIVISION, static_cast<T>(element)));
				return em;
			}

			friend EM operator/(T element, EM em) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::DIVISION, element));
				return em;
			}

			template<typename U>
			friend EM operator/(U element, EM em) noexcept
			{
				em.m_operations.push_back(std::make_pair(operation::DIVISION, static_cast<T>(element)));
				return em;
			}

			T value;
			static Size<T> referenceSize;

		private:
			std::vector<std::pair<operation, T>> m_operations;

			static T calcul(T sum, std::pair<operation, T> element) noexcept;
		};

		template<typename T>
		class GLSLvec2 final : public Vector<T, 2>
		{
		public:
			GLSLvec2() noexcept;
			explicit GLSLvec2(T initializationValue) noexcept;
			GLSLvec2(T x, T y) noexcept;
			GLSLvec2(const GLSLvec2& vector) noexcept;
			GLSLvec2(const Vector<T, 2>& vector) noexcept;

			template<typename U, typename V>
			GLSLvec2(U x, V y) noexcept;
			template<typename U>
			GLSLvec2(const GLSLvec2<U>& vector) noexcept;
			template<typename U>
			GLSLvec2(const glm::vec<2, U>& vector) noexcept;

			GLSLvec2& operator=(const GLSLvec2& vector) noexcept;
			template<typename U>
			GLSLvec2& operator=(const GLSLvec2<U>& vector) noexcept;
			GLSLvec2& operator=(const glm::vec2& vector) noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const GLSLvec2<T>& vec2)
			{
				return stream << '(' << vec2.x << ", " << vec2.y << ')';
			}

			T& x;
			T& y;
		};

		template<typename T>
		class GLSLvec3 final : public Vector<T, 3>
		{
		public:
			GLSLvec3() noexcept;
			explicit GLSLvec3(T initializationValue) noexcept;
			GLSLvec3(T x, T y, T z) noexcept;
			GLSLvec3(const GLSLvec3& vector) noexcept;
			GLSLvec3(const Vector<T, 3>& vector) noexcept;

			template<typename U, typename V, typename W>
			GLSLvec3(U x, V y, W z) noexcept;
			template<typename U>
			GLSLvec3(const GLSLvec3<U>& vector) noexcept;
			template<typename U, typename V>
			GLSLvec3(const glm::vec<2, U>& vector, V z) noexcept;
			template<typename U>
			GLSLvec3(const glm::vec<3, U>& vector) noexcept;

			GLSLvec3& operator=(const GLSLvec3& vector) noexcept;
			template<typename U>
			GLSLvec3& operator=(const GLSLvec3<U>& vector) noexcept;
			GLSLvec3& operator=(const glm::vec2& vector) noexcept;
			GLSLvec3& operator=(const glm::vec3& vector) noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const GLSLvec3<T>& vec3)
			{
				return stream << '(' << vec3.x << ", " << vec3.y << ", " << vec3.z << ')';
			}

			T& x;
			T& y;
			T& z;
		};

		template<typename T>
		class GLSLvec4 final : public Vector<T, 4>
		{
		public:
			GLSLvec4() noexcept;
			explicit GLSLvec4(T initializationValue) noexcept;
			GLSLvec4(T x, T y, T z, T w) noexcept;
			GLSLvec4(const GLSLvec4& vector) noexcept;
			GLSLvec4(const Vector<T, 4>& vector) noexcept;

			template<typename U, typename V, typename W, typename X>
			GLSLvec4(U x, V y, W z, X w) noexcept;
			template<typename U>
			GLSLvec4(const GLSLvec4<U>& vector) noexcept;
			template<typename U, typename V, typename W>
			GLSLvec4(const glm::vec<2, U>& vector, V z, W w) noexcept;
			template<typename U, typename V>
			GLSLvec4(const glm::vec<3, U>& vector, V w) noexcept;
			template<typename U>
			GLSLvec4(const glm::vec<4, U>& vector) noexcept;

			GLSLvec4& operator=(const GLSLvec4& vector) noexcept;
			template<typename U>
			GLSLvec4& operator=(const GLSLvec4<U>& vector) noexcept;
			GLSLvec4& operator=(const glm::vec2& vector) noexcept;
			GLSLvec4& operator=(const glm::vec3& vector) noexcept;
			GLSLvec4& operator=(const glm::vec4& vector) noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const GLSLvec4<T>& vec4)
			{
				return stream << '(' << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << ')';
			}

			T& x;
			T& y;
			T& z;
			T& w;
		};

		template<typename T>
		class Point final : public Vector<T, 2>
		{
		public:
			Point() noexcept;
			explicit Point(T xy) noexcept;
			explicit Point(EM<T> xy) noexcept;
			Point(T x, T y) noexcept;
			Point(EM<T> x, T y) noexcept;
			Point(T x, EM<T> y) noexcept;
			Point(EM<T> x, EM<T> y) noexcept;
			Point(const Point& point) noexcept;
			Point(const GLSLvec2<T>& point) noexcept;
			Point(const Vector<T, 2>& point) noexcept;
			Point(const glm::vec2& point) noexcept;

			template<typename U>
			explicit Point(EM<U> xy) noexcept;
			template<typename U, typename V>
			Point(EM<U> x, V y) noexcept;
			template<typename U, typename V>
			Point(U x, EM<V> y) noexcept;
			template<typename U, typename V>
			Point(EM<U> x, EM<V> y) noexcept;
			template<typename U, typename V>
			Point(U x, V y) noexcept;
			template<typename U>
			Point(const Point<U>& point) noexcept;
			template<typename U>
			Point(const GLSLvec2<U>& point) noexcept;

			Point& operator=(const Point& point) noexcept;
			template<typename U>
			Point& operator=(const Point<U>& point) noexcept;
			Point& operator=(const glm::vec2& point) noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const Point& point)
			{
				return stream << '(' << point.x << ", " << point.y << ')';
			}

			static bool is_in_rectangle(const Point& A, const Point& B, const Point& D, const Point& point);
			static Point rotate(const Point& point, const Point& center, T theta);

			T& x;
			T& y;

			void update();

		private:
			std::pair<std::unique_ptr<EM<T>>, std::unique_ptr<EM<T>>> m_em;
		};

		template<typename T>
		class Size final : public Vector<T, 2>
		{
		public:
			Size() noexcept;
			explicit Size(T widthAndHeight) noexcept;
			explicit Size(EM<T> widthAndHeight) noexcept;
			Size(T width, T height) noexcept;
			Size(EM<T> width, T height) noexcept;
			Size(T width, EM<T> height) noexcept;
			Size(EM<T> width, EM<T> height) noexcept;
			Size(const Size& size) noexcept;
			Size(const Vector<T, 2>& size) noexcept;
			Size(const glm::vec2& size) noexcept;

			template<typename U>
			explicit Size(EM<U> widthAndHeight) noexcept;
			template<typename U, typename V>
			Size(EM<U> width, V height) noexcept;
			template<typename U, typename V>
			Size(U width, EM<V> height) noexcept;
			template<typename U, typename V>
			Size(EM<U> width, EM<V> height) noexcept;
			template<typename U, typename V>
			Size(U width, V height) noexcept;
			template<typename U>
			Size(const Size<U>& size) noexcept;

			Size& operator=(const Size& size) noexcept;
			template<typename U>
			Size& operator=(const Size<U>& size) noexcept;
			Size& operator=(const glm::vec2& size) noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const Size& size)
			{
				return stream << '(' << size.width << ", " << size.height << ')';
			}

			T& width;
			T& height;

			void update() const;

		private:
			std::pair<std::unique_ptr<EM<T>>, std::unique_ptr<EM<T>>> m_em;
		};

		template<typename T>
		class Color final : public Vector<T, 4>
		{
		public:
			Color() noexcept;
			explicit Color(T rgb, T a = static_cast<T>(1)) noexcept;
			Color(T r, T g, T b, T a = static_cast<T>(1)) noexcept;
			template<typename U>
			Color(U r, U g, U b, U a = static_cast<U>(1)) noexcept;
			Color(const Color& color) noexcept;
			Color(const Vector<T, 3>& color) noexcept;
			Color(const Vector<T, 4>& color) noexcept;
			Color(const glm::vec3& color) noexcept;
			Color(const glm::vec4& color) noexcept;

			template<typename U, typename V, typename W, typename X>
			Color(U r, V g, W b, X a = static_cast<X>(1)) noexcept;
			template<typename U>
			Color(const Color<U>& color) noexcept;

			Color& operator=(const Color& color) noexcept;
			template<typename U>
			Color& operator=(const Color<U>& color) noexcept;
			Color& operator=(const glm::vec3& color) noexcept;
			Color& operator=(const glm::vec4& color) noexcept;

			explicit operator Vector<T, 3>() const noexcept;
			template<typename U>
			explicit operator Vector<U, 3>() const noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const Color& color)
			{
				return stream << '(' << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ')';
			}

			T& r;
			T& g;
			T& b;
			T& a;
		};
	}

	typedef kernel::GLSLvec2<float> vec2;
	typedef kernel::GLSLvec3<float> vec3;
	typedef kernel::GLSLvec4<float> vec4;
	typedef kernel::GLSLvec2<double> dvec2;
	typedef kernel::GLSLvec3<double> dvec3;
	typedef kernel::GLSLvec4<double> dvec4;
	typedef kernel::GLSLvec2<int> ivec2;
	typedef kernel::GLSLvec3<int> ivec3;
	typedef kernel::GLSLvec4<int> ivec4;
	typedef kernel::GLSLvec2<unsigned int> uvec2;
	typedef kernel::GLSLvec3<unsigned int> uvec3;
	typedef kernel::GLSLvec4<unsigned int> uvec4;
	typedef kernel::Point<HGUI_PRECISION> point;
	typedef kernel::Color<HGUI_PRECISION> color;
	typedef kernel::Size<HGUI_PRECISION> size;
}

inline hgui::kernel::EM<HGUI_PRECISION> operator""_em(const unsigned long long value) noexcept
{
	return hgui::kernel::EM(static_cast<HGUI_PRECISION>(value));
}

inline hgui::kernel::EM<HGUI_PRECISION> operator""_em(const long double value) noexcept
{
	return hgui::kernel::EM(static_cast<HGUI_PRECISION>(value));
}

template<typename T>
hgui::kernel::Size<T> hgui::kernel::EM<T>::referenceSize;

template<typename T>
hgui::kernel::EM<T>::EM() noexcept :
	value{},
	m_operations()
{
}

template<typename T>
hgui::kernel::EM<T>::EM(T value) noexcept :
	value(static_cast<T>(value / 100)),
	m_operations()
{
}

template<typename T>
T hgui::kernel::EM<T>::calcul(T sum, std::pair<operation, T> element) noexcept
{
	switch (element.first)
	{
		case operation::ADDITION:
			return sum + element.second;
		case operation::SUBTRACTION:
			return sum - element.second;
		case operation::MULTIPLICATION:
			return sum * element.second;
		case operation::DIVISION:
			return sum / element.second;
		default:
			return {};
	}
}

template<typename T>
hgui::kernel::GLSLvec2<T>::GLSLvec2() noexcept :
	Vector<T, 2>(),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
hgui::kernel::GLSLvec2<T>::GLSLvec2(T initializationValue) noexcept :
	Vector<T, 2>(initializationValue),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
hgui::kernel::GLSLvec2<T>::GLSLvec2(T x, T y) noexcept :
	Vector<T, 2>({x, y}),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
template<typename U, typename V>
hgui::kernel::GLSLvec2<T>::GLSLvec2(U x, V y) noexcept :
	Vector<T, 2>({static_cast<T>(x), static_cast<T>(y)}),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
hgui::kernel::GLSLvec2<T>::GLSLvec2(const GLSLvec2& vector) noexcept :
	Vector<T, 2>({vector.x, vector.y}),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
template<typename U>
hgui::kernel::GLSLvec2<T>::GLSLvec2(const GLSLvec2<U>& vector) noexcept :
	Vector<T, 2>({
			static_cast<T>(vector.x), static_cast<T>(vector.y)
		}),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
hgui::kernel::GLSLvec2<T>::GLSLvec2(const Vector<T, 2>& vector) noexcept :
	Vector<T, 2>({vector[0], vector[1]}),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
template<typename U>
hgui::kernel::GLSLvec2<T>::GLSLvec2(const glm::vec<2, U>& vector) noexcept :
	Vector<T, 2>({
			static_cast<T>(vector.x),
			static_cast<T>(vector.y)
		}),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
hgui::kernel::GLSLvec2<T>& hgui::kernel::GLSLvec2<T>::operator=(const GLSLvec2& vector) noexcept
{
	x = vector.x;
	y = vector.y;
	return *this;
}

template<typename T>
template<typename U>
hgui::kernel::GLSLvec2<T>& hgui::kernel::GLSLvec2<T>::operator=(const GLSLvec2<U>& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	return *this;
}

template<typename T>
hgui::kernel::GLSLvec2<T>& hgui::kernel::GLSLvec2<T>::operator=(const glm::vec2& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	return *this;
}

template<typename T>
hgui::kernel::GLSLvec3<T>::GLSLvec3() noexcept :
	Vector<T, 3>(),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2])
{
}

template<typename T>
hgui::kernel::GLSLvec3<T>::GLSLvec3(T initializationValue) noexcept :
	Vector<T, 3>(initializationValue),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2])
{
}

template<typename T>
hgui::kernel::GLSLvec3<T>::GLSLvec3(T x, T y, T z) noexcept :
	Vector<T, 3>({x, y, z}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2])
{
}

template<typename T>
hgui::kernel::GLSLvec3<T>::GLSLvec3(const GLSLvec3& vector) noexcept :
	Vector<T, 3>({vector.x, vector.y, vector.z}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2])
{
}

template<typename T>
hgui::kernel::GLSLvec3<T>::GLSLvec3(const Vector<T, 3>& vector) noexcept :
	Vector<T, 3>({vector[0], vector[1], vector[2]}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2])
{
}

template<typename T>
template<typename U, typename V, typename W>
hgui::kernel::GLSLvec3<
	T>::GLSLvec3(U x, V y, W z) noexcept :
	Vector<T, 3>({static_cast<T>(x), static_cast<T>(y), static_cast<T>(z)}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2])
{
}

template<typename T>
template<typename U>
hgui::kernel::GLSLvec3<T>::GLSLvec3(const GLSLvec3<U>& vector) noexcept :
	Vector<T, 3>({
			static_cast<T>(vector.x), static_cast<T>(vector.y),
			static_cast<T>(vector.z)
		}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2])
{
}

template<typename T>
template<typename U, typename V>
hgui::kernel::GLSLvec3<T>::GLSLvec3(const glm::vec<2, U>& vector, V z) noexcept :
	Vector<T, 3>({
			static_cast<T>(vector.x),
			static_cast<T>(vector.y), static_cast<T>(z)
		}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2])
{
}

template<typename T>
template<typename U>
hgui::kernel::GLSLvec3<T>::GLSLvec3(const glm::vec<3, U>& vector) noexcept :
	Vector<T, 3>({
			static_cast<T>(vector.x),
			static_cast<T>(vector.y),
			static_cast<T>(vector.z)
		}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2])
{
}

template<typename T>
hgui::kernel::GLSLvec3<T>& hgui::kernel::GLSLvec3<T>::operator=(const GLSLvec3& vector) noexcept
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	return *this;
}

template<typename T>
template<typename U>
hgui::kernel::GLSLvec3<T>& hgui::kernel::GLSLvec3<T>::operator=(const GLSLvec3<U>& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	z = static_cast<T>(vector.z);
	return *this;
}

template<typename T>
hgui::kernel::GLSLvec3<T>& hgui::kernel::GLSLvec3<T>::operator=(const glm::vec2& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	return *this;
}

template<typename T>
hgui::kernel::GLSLvec3<T>& hgui::kernel::GLSLvec3<T>::operator=(const glm::vec3& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	z = static_cast<T>(vector.z);
	return *this;
}

template<typename T>
hgui::kernel::GLSLvec4<T>::GLSLvec4() noexcept :
	Vector<T, 4>(),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2]),
	w((*this)[3])
{
}

template<typename T>
hgui::kernel::GLSLvec4<T>::GLSLvec4(T initializationValue) noexcept :
	Vector<T, 4>(initializationValue),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2]),
	w((*this)[3])
{
}

template<typename T>
hgui::kernel::GLSLvec4<T>::GLSLvec4(T x, T y, T z, T w) noexcept :
	Vector<T, 4>({x, y, z, w}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2]),
	w((*this)[3])
{
}

template<typename T>
hgui::kernel::GLSLvec4<T>::GLSLvec4(const GLSLvec4& vector) noexcept :
	Vector<T, 4>({vector.x, vector.y, vector.z, vector.w}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2]),
	w((*this)[3])
{
}

template<typename T>
hgui::kernel::GLSLvec4<T>::GLSLvec4(const Vector<T, 4>& vector) noexcept :
	Vector<T, 4>({
			vector[0], vector[1], vector[2], vector[3]
		}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2]),
	w((*this)[3])
{
}

template<typename T>
template<typename U, typename V, typename W, typename X>
hgui::kernel::GLSLvec4<T>::GLSLvec4(U x, V y, W z, X w) noexcept :
	Vector<T, 4>({
			static_cast<T>(x), static_cast<T>(y), static_cast<T>(z),
			static_cast<T>(w)
		}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2]),
	w((*this)[3])
{
}

template<typename T>
template<typename U>
hgui::kernel::GLSLvec4<T>::GLSLvec4(const GLSLvec4<U>& vector) noexcept :
	Vector<T, 4>({
			static_cast<T>(vector.x), static_cast<T>(vector.y),
			static_cast<T>(vector.z), static_cast<T>(vector.w)
		}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2]),
	w((*this)[3])
{
}

template<typename T>
template<typename U, typename V, typename W>
hgui::kernel::GLSLvec4<T>::GLSLvec4(const glm::vec<2, U>& vector, V z, W w) noexcept :
	Vector<T, 4>({
			static_cast<T>(vector.x), static_cast<T>(vector.y), static_cast<T>(z), static_cast<T>(w)
		}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2]),
	w((*this)[3])
{
}

template<typename T>
template<typename U, typename V>
hgui::kernel::GLSLvec4<T>::GLSLvec4(const glm::vec<3, U>& vector, V w) noexcept :
	Vector<T, 4>({
			static_cast<T>(vector.x),
			static_cast<T>(vector.y),
			static_cast<T>(vector.z), static_cast<T>(w)
		}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2]),
	w((*this)[3])
{
}

template<typename T>
template<typename U>
hgui::kernel::GLSLvec4<T>::GLSLvec4(const glm::vec<4, U>& vector) noexcept :
	Vector<T, 4>({
			static_cast<T>(vector.x),
			static_cast<T>(vector.y),
			static_cast<T>(vector.z),
			static_cast<T>(vector.w)
		}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2]),
	w((*this)[3])
{
}

template<typename T>
hgui::kernel::GLSLvec4<T>& hgui::kernel::GLSLvec4<T>::operator=(const GLSLvec4& vector) noexcept
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
	return *this;
}

template<typename T>
template<typename U>
hgui::kernel::GLSLvec4<T>& hgui::kernel::GLSLvec4<T>::operator=(const GLSLvec4<U>& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	z = static_cast<T>(vector.z);
	w = static_cast<T>(vector.w);
	return *this;
}

template<typename T>
hgui::kernel::GLSLvec4<T>& hgui::kernel::GLSLvec4<T>::operator=(const glm::vec2& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	return *this;
}

template<typename T>
hgui::kernel::GLSLvec4<T>& hgui::kernel::GLSLvec4<T>::operator=(const glm::vec3& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	z = static_cast<T>(vector.z);
	return *this;
}

template<typename T>
hgui::kernel::GLSLvec4<T>& hgui::kernel::GLSLvec4<T>::operator=(const glm::vec4& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	z = static_cast<T>(vector.z);
	w = static_cast<T>(vector.w);
	return *this;
}

template<typename T>
hgui::kernel::Point<T>::Point() noexcept :
	Vector<T, 2>(),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
hgui::kernel::Point<T>::Point(T xy) noexcept :
	Vector<T, 2>(xy),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
hgui::kernel::Point<T>::Point(EM<T> xy) noexcept :
	Vector<T, 2>({
			static_cast<T>(std::accumulate(xy.m_operations.begin(), xy.m_operations.end(), xy.value * xy.referenceSize.width, EM<T>::calcul)),
			static_cast<T>(std::accumulate(xy.m_operations.begin(), xy.m_operations.end(), xy.value * xy.referenceSize.height, EM<T>::calcul))
		}),
	x((*this)[0]),
	y((*this)[1]),
	m_em(std::make_unique<EM<T>>(xy), std::make_unique<EM<T>>(xy))
{
}

template<typename T>
template<typename U>
hgui::kernel::Point<T>::Point(EM<U> xy) noexcept :
	Vector<T, 2>({
			static_cast<T>(std::accumulate(xy.m_operations.begin(), xy.m_operations.end(), xy.value * xy.referenceSize.width, EM<T>::calcul)),
			static_cast<T>(std::accumulate(xy.m_operations.begin(), xy.m_operations.end(), xy.value * xy.referenceSize.height, EM<T>::calcul))
		}),
	x((*this)[0]),
	y((*this)[1]),
	m_em(std::make_unique<EM<T>>(xy), std::make_unique<EM<T>>(xy))
{
}

template<typename T>
template<typename U, typename V>
hgui::kernel::Point<T>::Point(EM<U> x, V y) noexcept :
	Vector<T, 2>({
			static_cast<T>(std::accumulate(x.m_operations.begin(), x.m_operations.end(), x.value * x.referenceSize.width, EM<T>::calcul)),
			static_cast<T>(y)
		}),
	x((*this)[0]),
	y((*this)[1]),
	m_em(std::make_unique<EM<T>>(x), nullptr)
{
}

template<typename T>
template<typename U, typename V>
hgui::kernel::Point<T>::Point(U x, EM<V> y) noexcept :
	Vector<T, 2>({
			static_cast<T>(x),
			static_cast<T>(std::accumulate(y.m_operations.begin(), y.m_operations.end(), y.value * y.referenceSize.height, EM<T>::calcul))
		}),
	x((*this)[0]),
	y((*this)[1]),
	m_em(nullptr, std::make_unique<EM<T>>(y))
{
}

template<typename T>
hgui::kernel::Point<T>::Point(T x, T y) noexcept :
	Vector<T, 2>({x, y}),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
hgui::kernel::Point<T>::Point(EM<T> x, T y) noexcept :
	Vector<T, 2>({
			static_cast<T>(std::accumulate(x.m_operations.begin(), x.m_operations.end(), x.value * x.referenceSize.width, EM<T>::calcul)),
			y
		}),
	x((*this)[0]),
	y((*this)[1]),
	m_em(std::make_unique<EM<T>>(x), y)
{
}

template<typename T>
hgui::kernel::Point<T>::Point(T x, EM<T> y) noexcept :
	Vector<T, 2>({
			x,
			static_cast<T>(std::accumulate(y.m_operations.begin(), y.m_operations.end(), y.value * y.referenceSize.height, EM<T>::calcul))
		}),
	x((*this)[0]),
	y((*this)[1]),
	m_em(nullptr, std::make_unique<EM<T>>(y))
{
}

template<typename T>
hgui::kernel::Point<T>::Point(EM<T> x, EM<T> y) noexcept :
	Vector<T, 2>({
			static_cast<T>(std::accumulate(x.m_operations.begin(), x.m_operations.end(), x.value * x.referenceSize.width, EM<T>::calcul)),
			static_cast<T>(std::accumulate(y.m_operations.begin(), y.m_operations.end(), y.value * y.referenceSize.height, EM<T>::calcul))
		}),
	x((*this)[0]),
	y((*this)[1]),
	m_em(std::make_unique<EM<T>>(x), std::make_unique<EM<T>>(y))
{
}

template<typename T>
template<typename U, typename V>
hgui::kernel::Point<T>::Point(EM<U> x, EM<V> y) noexcept :
	Vector<T, 2>({
			static_cast<T>(std::accumulate(x.m_operations.begin(), x.m_operations.end(), x.value * x.referenceSize.width, EM<T>::calcul)),
			static_cast<T>(std::accumulate(y.m_operations.begin(), y.m_operations.end(), y.value * y.referenceSize.height, EM<T>::calcul))
		}),
	x((*this)[0]),
	y((*this)[1]),
	m_em(std::make_unique<EM<T>>(x), std::make_unique<EM<T>>(y))
{
}

template<typename T>
hgui::kernel::Point<T>::Point(const Point& point) noexcept :
	Vector<T, 2>({point.x, point.y}),
	x((*this)[0]),
	y((*this)[1]),
	m_em(point.m_em.first ? std::make_unique<EM<T>>(*point.m_em.first) : nullptr, point.m_em.second ? std::make_unique<EM<T>>(*point.m_em.second) : nullptr)
{
}

template<typename T>
hgui::kernel::Point<T>::Point(const GLSLvec2<T>& point) noexcept :
	Vector<T, 2>({point.x, point.y}),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
hgui::kernel::Point<T>::Point(const Vector<T, 2>& point) noexcept :
	Vector<T, 2>({point[0], point[1]}),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
template<typename U, typename V>
hgui::kernel::Point<T>::Point(U x, V y) noexcept :
	Vector<T, 2>({static_cast<T>(x), static_cast<T>(y)}),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
template<typename U>
hgui::kernel::Point<T>::Point(const Point<U>& point) noexcept :
	Vector<T, 2>({static_cast<T>(point.x), static_cast<T>(point.y)}),
	x((*this)[0]),
	y((*this)[1]),
	m_em(point.m_em.first ? std::make_unique<EM<T>>(*point.m_em.first) : nullptr, point.m_em.second ? std::make_unique<EM<T>>(*point.m_em.second) : nullptr)
{
}

template<typename T>
template<typename U>
hgui::kernel::Point<T>::Point(const GLSLvec2<U>& point) noexcept :
	Vector<T, 2>({static_cast<T>(point.x), static_cast<T>(point.y)}),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
hgui::kernel::Point<T>::Point(const glm::vec2& point) noexcept :
	Vector<T, 2>({static_cast<T>(point.x), static_cast<T>(point.y)}),
	x((*this)[0]),
	y((*this)[1])
{
}

template<typename T>
hgui::kernel::Point<T>& hgui::kernel::Point<T>::operator=(const Point& point) noexcept
{
	x = point.x;
	y = point.y;
	m_em = std::make_pair(point.m_em.first ? std::make_unique<EM<T>>(*point.m_em.first) : nullptr, point.m_em.second ? std::make_unique<EM<T>>(*point.m_em.second) : nullptr);
	return *this;
}

template<typename T>
template<typename U>
hgui::kernel::Point<T>& hgui::kernel::Point<T>::operator=(const Point<U>& point) noexcept
{
	x = static_cast<T>(point.x);
	y = static_cast<T>(point.y);
	m_em = std::make_pair(point.m_em.first ? std::make_unique<EM<T>>(*point.m_em.first) : nullptr, point.m_em.second ? std::make_unique<EM<T>>(*point.m_em.second) : nullptr);
	return *this;
}

template<typename T>
hgui::kernel::Point<T>& hgui::kernel::Point<T>::operator=(const glm::vec2& point) noexcept
{
	x = static_cast<T>(point.x);
	y = static_cast<T>(point.y);
	return *this;
}

template<typename T>
bool hgui::kernel::Point<T>::is_in_rectangle(const Point& A, const Point& B, const Point& D, const Point& point)
{
	const auto dotAMAB = kernel::dot(point - A, B - A), dotAMAD = kernel::dot(point - A, D - A);
	return (0 < dotAMAB && dotAMAB < kernel::dot(B - A, B - A)) && (0 < dotAMAD && dotAMAD < kernel::dot(D - A, D - A));
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
void hgui::kernel::Point<T>::update()
{
	if (m_em.first)
		x = static_cast<T>(std::accumulate(m_em.first->m_operations.begin(), m_em.first->m_operations.end(), m_em.first->value * m_em.first->referenceSize.width, EM<T>::calcul));
	if (m_em.second)
		y = static_cast<T>(std::accumulate(m_em.second->m_operations.begin(), m_em.second->m_operations.end(), m_em.second->value * m_em.second->referenceSize.height, EM<T>::calcul));
}

template<typename T>
hgui::kernel::Size<T>::Size() noexcept :
	Vector<T, 2>(),
	width((*this)[0]),
	height((*this)[1])
{
}

template<typename T>
hgui::kernel::Size<T>::Size(T widthAndHeight) noexcept :
	Vector<T, 2>(widthAndHeight),
	width((*this)[0]),
	height((*this)[1])
{
}

template<typename T>
hgui::kernel::Size<T>::Size(EM<T> widthAndHeight) noexcept :
	Vector<T, 2>({
			static_cast<T>(std::accumulate(widthAndHeight.m_operations.begin(), widthAndHeight.m_operations.end(), widthAndHeight.value * widthAndHeight.referenceSize.width, EM<T>::calcul)),
			static_cast<T>(std::accumulate(widthAndHeight.m_operations.begin(), widthAndHeight.m_operations.end(), widthAndHeight.value * widthAndHeight.referenceSize.height, EM<T>::calcul))
		}),
	width((*this)[0]),
	height((*this)[1]),
	m_em(std::make_unique<EM<T>>(widthAndHeight), std::make_unique<EM<T>>(widthAndHeight))
{
}

template<typename T>
template<typename U>
hgui::kernel::Size<T>::Size(EM<U> widthAndHeight) noexcept :
	Vector<T, 2>({
			static_cast<T>(std::accumulate(widthAndHeight.m_operations.begin(), widthAndHeight.m_operations.end(), widthAndHeight.value * widthAndHeight.referenceSize.width, EM<T>::calcul)),
			static_cast<T>(std::accumulate(widthAndHeight.m_operations.begin(), widthAndHeight.m_operations.end(), widthAndHeight.value * widthAndHeight.referenceSize.height, EM<T>::calcul))
		}),
	width((*this)[0]),
	height((*this)[1]),
	m_em(std::make_unique<EM<T>>(widthAndHeight), std::make_unique<EM<T>>(widthAndHeight))
{
}

template<typename T>
template<typename U, typename V>
hgui::kernel::Size<T>::Size(EM<U> width, V height) noexcept :
	Vector<T, 2>({
			static_cast<T>(std::accumulate(width.m_operations.begin(), width.m_operations.end(), width.value * width.referenceSize.width, EM<T>::calcul)),
			static_cast<T>(height)
		}),
	width((*this)[0]),
	height((*this)[1]),
	m_em(std::make_unique<EM<T>>(width), nullptr)
{
}

template<typename T>
template<typename U, typename V>
hgui::kernel::Size<T>::Size(U width, EM<V> height) noexcept :
	Vector<T, 2>({
			static_cast<T>(width),
			static_cast<T>(std::accumulate(height.m_operations.begin(), height.m_operations.end(), height.value * height.referenceSize.height, EM<T>::calcul))
		}),
	width((*this)[0]),
	height((*this)[1]),
	m_em(nullptr, std::make_unique<EM<T>>(height))
{
}

template<typename T>
hgui::kernel::Size<T>::Size(T width, T height) noexcept :
	Vector<T, 2>({width, height}),
	width((*this)[0]),
	height((*this)[1])
{
}

template<typename T>
hgui::kernel::Size<T>::Size(EM<T> width, T height) noexcept :
	Vector<T, 2>({
			static_cast<T>(std::accumulate(width.m_operations.begin(), width.m_operations.end(), width.value * width.referenceSize.width, EM<T>::calcul)),
			height
		}),
	width((*this)[0]),
	height((*this)[1]),
	m_em(std::make_unique<EM<T>>(width), nullptr)
{
}

template<typename T>
hgui::kernel::Size<T>::Size(T width, EM<T> height) noexcept :
	Vector<T, 2>({
			width,
			static_cast<T>(std::accumulate(height.m_operations.begin(), height.m_operations.end(), height.value * height.referenceSize.height, EM<T>::calcul))
		}),
	width((*this)[0]),
	height((*this)[1]),
	m_em(nullptr, std::make_unique<EM<T>>(height))
{
}

template<typename T>
hgui::kernel::Size<T>::Size(EM<T> width, EM<T> height) noexcept :
	Vector<T, 2>({
			static_cast<T>(std::accumulate(width.m_operations.begin(), width.m_operations.end(), width.value * width.referenceSize.width, EM<T>::calcul)),
			static_cast<T>(std::accumulate(height.m_operations.begin(), height.m_operations.end(), height.value * height.referenceSize.height, EM<T>::calcul))
		}),
	width((*this)[0]),
	height((*this)[1]),
	m_em(std::make_unique<EM<T>>(width), std::make_unique<EM<T>>(height))
{
}

template<typename T>
template<typename U, typename V>
hgui::kernel::Size<T>::Size(EM<U> width, EM<V> height) noexcept :
	Vector<T, 2>({
			static_cast<T>(std::accumulate(width.m_operations.begin(), width.m_operations.end(), width.value * width.referenceSize.width, EM<T>::calcul)),
			static_cast<T>(std::accumulate(height.m_operations.begin(), height.m_operations.end(), height.value * height.referenceSize.height, EM<T>::calcul))
		}),
	width((*this)[0]),
	height((*this)[1]),
	m_em(std::make_unique<EM<T>>(width), std::make_unique<EM<T>>(height))
{
}

template<typename T>
hgui::kernel::Size<T>::Size(const Size& size) noexcept :
	Vector<T, 2>({size.width, size.height}),
	width((*this)[0]),
	height((*this)[1]),
	m_em(size.m_em.first ? std::make_unique<EM<T>>(*size.m_em.first) : nullptr, size.m_em.second ? std::make_unique<EM<T>>(*size.m_em.second) : nullptr)
{
}

template<typename T>
hgui::kernel::Size<T>::Size(const Vector<T, 2>& size) noexcept :
	Vector<T, 2>({size[0], size[1]}),
	width((*this)[0]),
	height((*this)[1])
{
}

template<typename T>
template<typename U, typename V>
hgui::kernel::Size<T>::Size(U width, V height) noexcept :
	Vector<T, 2>({static_cast<T>(width), static_cast<T>(height)}),
	width((*this)[0]),
	height((*this)[1])
{
}

template<typename T>
template<typename U>
hgui::kernel::Size<T>::Size(const Size<U>& size) noexcept :
	Vector<T, 2>({static_cast<T>(size.width), static_cast<T>(size.height)}),
	width((*this)[0]),
	height((*this)[1]),
	m_em(size.m_em.first ? std::make_unique<EM<T>>(*size.m_em.first) : nullptr, size.m_em.second ? std::make_unique<EM<T>>(*size.m_em.second) : nullptr)
{
}

template<typename T>
hgui::kernel::Size<T>::Size(const glm::vec2& size) noexcept :
	Vector<T, 2>({static_cast<T>(size.x), static_cast<T>(size.y)}),
	width((*this)[0]),
	height((*this)[1])
{
}

template<typename T>
hgui::kernel::Size<T>& hgui::kernel::Size<T>::operator=(const Size& size) noexcept
{
	width = size.width;
	height = size.height;
	m_em = std::make_pair(size.m_em.first ? std::make_unique<EM<T>>(*size.m_em.first) : nullptr, size.m_em.second ? std::make_unique<EM<T>>(*size.m_em.second) : nullptr);
	return *this;
}

template<typename T>
template<typename U>
hgui::kernel::Size<T>& hgui::kernel::Size<T>::operator=(const Size<U>& size) noexcept
{
	width = static_cast<T>(size.width);
	height = static_cast<T>(size.height);
	m_em = std::make_pair(size.m_em.first ? std::make_unique<EM<T>>(*size.m_em.first) : nullptr, size.m_em.second ? std::make_unique<EM<T>>(*size.m_em.second) : nullptr);
	return *this;
}

template<typename T>
hgui::kernel::Size<T>& hgui::kernel::Size<T>::operator=(const glm::vec2& size) noexcept
{
	width = static_cast<T>(size.x);
	height = static_cast<T>(size.y);
	return *this;
}

template<typename T>
void hgui::kernel::Size<T>::update() const
{
	if (m_em.first)
		width = static_cast<T>(std::accumulate(m_em.first->m_operations.begin(), m_em.first->m_operations.end(), m_em.first->value * m_em.first->referenceSize.width, EM<T>::calcul));
	if (m_em.second)
		height = static_cast<T>(std::accumulate(m_em.second->m_operations.begin(), m_em.second->m_operations.end(), m_em.second->value * m_em.second->referenceSize.height, EM<T>::calcul));
}

template<typename T>
hgui::kernel::Color<T>::Color() noexcept :
	Vector<T, 4>(),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
}

template<typename T>
hgui::kernel::Color<T>::Color(T rgb, T a) noexcept :
	Vector<T, 4>(rgb),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
	this->a = a;
}

template<typename T>
hgui::kernel::Color<T>::Color(T r, T g, T b, T a) noexcept :
	Vector<T, 4>({r, g, b, a}),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
}

template<typename T>
template<typename U>
hgui::kernel::Color<T>::Color(U r, U g, U b, U a) noexcept :
	Vector<T, 4>({static_cast<T>(r), static_cast<T>(g), static_cast<T>(b), static_cast<T>(a)}),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
}

template<typename T>
hgui::kernel::Color<T>::Color(const Color& color) noexcept :
	Vector<T, 4>({color.r, color.g, color.b, color.a}),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
}

template<typename T>
hgui::kernel::Color<T>::Color(const Vector<T, 3>& color) noexcept :
	Vector<T, 4>({
			color[0], color[1], color[2], static_cast<T>(1)
		}),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
}

template<typename T>
hgui::kernel::Color<T>::Color(const Vector<T, 4>& color) noexcept :
	Vector<T, 4>({color[0], color[1], color[2], color[3]}),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
}

template<typename T>
template<typename U, typename V, typename W, typename X>
hgui::kernel::Color<T>::Color(U r, V g, W b, X a) noexcept :
	Vector<T, 4>({
			static_cast<T>(r), static_cast<T>(g), static_cast<T>(b),
			static_cast<T>(a)
		}),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
}

template<typename T>
template<typename U>
hgui::kernel::Color<T>::Color(const Color<U>& color) noexcept :
	Vector<T, 4>({
			static_cast<T>(color.r), static_cast<T>(color.g),
			static_cast<T>(color.b), static_cast<T>(color.a)
		}),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
}

template<typename T>
hgui::kernel::Color<T>::Color(const glm::vec3& color) noexcept :
	Vector<T, 4>({
			static_cast<T>(color.r), static_cast<T>(color.g),
			static_cast<T>(color.b), static_cast<T>(1)
		}),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
}

template<typename T>
hgui::kernel::Color<T>::Color(const glm::vec4& color) noexcept :
	Vector<T, 4>({
			static_cast<T>(color.r), static_cast<T>(color.g),
			static_cast<T>(color.b), static_cast<T>(color.a)
		}),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
}

template<typename T>
hgui::kernel::Color<T>& hgui::kernel::Color<T>::operator=(const Color& color) noexcept
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
	return *this;
}

template<typename T>
template<typename U>
hgui::kernel::Color<T>& hgui::kernel::Color<T>::operator=(const Color<U>& color) noexcept
{
	r = static_cast<T>(color.r);
	g = static_cast<T>(color.g);
	b = static_cast<T>(color.b);
	a = static_cast<T>(color.a);
	return *this;
}

template<typename T>
hgui::kernel::Color<T>& hgui::kernel::Color<T>::operator=(const glm::vec3& color) noexcept
{
	r = static_cast<T>(color.r);
	g = static_cast<T>(color.g);
	b = static_cast<T>(color.b);
	a = static_cast<T>(1);
	return *this;
}

template<typename T>
hgui::kernel::Color<T>& hgui::kernel::Color<T>::operator=(const glm::vec4& color) noexcept
{
	r = static_cast<T>(color.r);
	g = static_cast<T>(color.g);
	b = static_cast<T>(color.b);
	a = static_cast<T>(color.a);
	return *this;
}

template<typename T>
hgui::kernel::Color<T>::operator Vector<T, 3>() const noexcept
{
	return Vector<T, 3>({r, g, b});
}

template<typename T>
template<typename U>
hgui::kernel::Color<T>::operator Vector<U, 3>() const noexcept
{
	return Vector<U, 3>({static_cast<U>(r), static_cast<U>(g), static_cast<U>(b)});
}
