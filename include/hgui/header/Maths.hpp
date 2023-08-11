#pragma once

#include "Include.h"
#include "Vector.hpp"

namespace hgui
{
	namespace kernel
	{
		template<typename T>
		class Size;

		template<typename T>
		class EM
		{
		public:
			EM();
			EM(T value);
			EM(const EM<T>& EM);

			template<typename U>
			friend EM<T> operator*(T value, const EM<U>& EM)
			{
				return kernel::EM<U>(value);
			}

			T value;

			static Size<T> referenceSize;
		};

		template<typename T>
		class GLSLvec2 : public Vector<T, 2>
		{
		public:
			GLSLvec2() noexcept;
			explicit GLSLvec2(T initializationValue) noexcept;
			GLSLvec2(T x, T y) noexcept;
			GLSLvec2(const GLSLvec2<T>& vector) noexcept;
			GLSLvec2(const kernel::Vector<T, 2>& vector) noexcept;

			template<typename U, typename V>
			GLSLvec2(U x, V y) noexcept;
			template<typename U>
			GLSLvec2(const GLSLvec2<U>& vector) noexcept;
			template<typename U>
			GLSLvec2(const glm::vec<2, U>& vector) noexcept;


			GLSLvec2<T>& operator=(const GLSLvec2<T>& vector) noexcept;
			template<typename U>
			GLSLvec2<T>& operator=(const GLSLvec2<U>& vector) noexcept;
			GLSLvec2<T>& operator=(const glm::vec2& vector) noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const hgui::kernel::GLSLvec2<T>& vec2)
			{
				return stream << '(' << vec2.x << ", " << vec2.y << ')';
			}

			T& x;
			T& y;
		};

		template<typename T>
		class GLSLvec3 : public Vector<T, 3>
		{
		public:
			GLSLvec3() noexcept;
			explicit GLSLvec3(T initializationValue) noexcept;
			GLSLvec3(T x, T y, T z) noexcept;
			GLSLvec3(const GLSLvec3<T>& vector) noexcept;
			GLSLvec3(const kernel::Vector<T, 3>& vector) noexcept;

			template<typename U, typename V, typename W>
			GLSLvec3(U x, V y, W z) noexcept;
			template<typename U>
			GLSLvec3(const GLSLvec3<U>& vector) noexcept;
			template<typename U, typename V>
			GLSLvec3(const glm::vec<2, U>& vector, V z) noexcept;
			template<typename U>
			GLSLvec3(const glm::vec<3, U>& vector) noexcept;

			GLSLvec3<T>& operator=(const GLSLvec3<T>& vector) noexcept;
			template<typename U>
			GLSLvec3<T>& operator=(const GLSLvec3<U>& vector) noexcept;
			GLSLvec3<T>& operator=(const glm::vec2& vector) noexcept;
			GLSLvec3<T>& operator=(const glm::vec3& vector) noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const hgui::kernel::GLSLvec3<T>& vec3)
			{
				return stream << '(' << vec3.x << ", " << vec3.y << ", " << vec3.z << ')';
			}

			T& x;
			T& y;
			T& z;
		};

		template<typename T>
		class GLSLvec4 : public Vector<T, 4>
		{
		public:
			GLSLvec4() noexcept;
			explicit GLSLvec4(T initializationValue) noexcept;
			GLSLvec4(T x, T y, T z, T w) noexcept;
			GLSLvec4(const GLSLvec4<T>& vector) noexcept;
			GLSLvec4(const kernel::Vector<T, 4>& vector) noexcept;

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

			GLSLvec4<T>& operator=(const GLSLvec4<T>& vector) noexcept;
			template<typename U>
			GLSLvec4<T>& operator=(const GLSLvec4<U>& vector) noexcept;
			GLSLvec4<T>& operator=(const glm::vec2& vector) noexcept;
			GLSLvec4<T>& operator=(const glm::vec3& vector) noexcept;
			GLSLvec4<T>& operator=(const glm::vec4& vector) noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const hgui::kernel::GLSLvec4<T>& vec4)
			{
				return stream << '(' << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << ')';
			}

			T& x;
			T& y;
			T& z;
			T& w;
		};

		template<typename T>
		class Point : public Vector<T, 2>
		{
		public:
			Point() noexcept;
			explicit Point(T xy) noexcept;
			explicit Point(EM<T> xy) noexcept;
			Point(T x, T y) noexcept;
			Point(EM<T> x, T y) noexcept;
			Point(T x, EM<T> y) noexcept;
			Point(EM<T> x, EM<T> y) noexcept;
			Point(const Point<T>& point) noexcept;
			Point(const kernel::Vector<T, 2>& point) noexcept;
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

			Point<T>& operator=(const Point<T>& point) noexcept;
			template<typename U>
			Point<T>& operator=(const Point<U>& point) noexcept;
			Point<T>& operator=(const glm::vec2& point) noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const hgui::kernel::Point<T>& point)
			{
				return stream << '(' << point.x << ", " << point.y << ')';
			}

			T& x;
			T& y;
		};

		template<typename T>
		class Size : public Vector<T, 2>
		{
		public:
			Size() noexcept;
			explicit Size(T widthANDheight) noexcept;
			explicit Size(EM<T> widthANDheight) noexcept;
			Size(T width, T height) noexcept;
			Size(EM<T> width, T height) noexcept;
			Size(T width, EM<T> height) noexcept;
			Size(EM<T> width, EM<T> height) noexcept;
			Size(const Size<T>& size) noexcept;
			Size(const kernel::Vector<T, 2>& size) noexcept;
			Size(const glm::vec2& size) noexcept;

			template<typename U>
			explicit Size(EM<U> widthANDheight) noexcept;
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

			Size<T>& operator=(const Size<T>& size) noexcept;
			template<typename U>
			Size<T>& operator=(const Size<U>& size) noexcept;
			Size<T>& operator=(const glm::vec2& size) noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const hgui::kernel::Size<T>& size)
			{
				return stream << '(' << size.width << ", " << size.height << ')';
			}

			T& width;
			T& height;
		};

		template<typename T>
		class Color : public Vector<T, 3>
		{
		public:
			Color() noexcept;
			explicit Color(T rgb) noexcept;
			Color(T r, T g, T b) noexcept;
			Color(const Color<T>& color) noexcept;
			Color(const kernel::Vector<T, 3>& color) noexcept;
			Color(const glm::vec3& color) noexcept;

			template<typename U, typename V, typename W>
			Color(U r, V g, W b) noexcept;
			template<typename U>
			Color(const Color<U>& color) noexcept;


			Color<T>& operator=(const Color<T>& color) noexcept;
			template<typename U>
			Color<T>& operator=(const Color<U>& color) noexcept;
			Color<T>& operator=(const glm::vec3& color) noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const hgui::kernel::Color<T>& color)
			{
				return stream << '(' << color.r << ", " << color.g << ", " << color.b << ')';
			}

			T& r;
			T& g;
			T& b;
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
	typedef kernel::Point<float> point;
	typedef kernel::Color<float> color;
	typedef kernel::Size<float> size;
}

inline hgui::kernel::EM<float> operator""_em(unsigned long long value)
{
	return hgui::kernel::EM<float>(static_cast<float>(value));
}

template<typename T>
hgui::kernel::Size<T> hgui::kernel::EM<T>::referenceSize;

template<typename T>
inline hgui::kernel::EM<T>::EM() :
	value{}
{
}

template<typename T>
inline hgui::kernel::EM<T>::EM(T value) :
	value(static_cast<T>(value / 100))
{
}

template<typename T>
inline hgui::kernel::EM<T>::EM(const EM<T>& EM) :
	value(EM.value)
{
}

template<typename T>
inline hgui::kernel::GLSLvec2<T>::GLSLvec2() noexcept :
	Vector<T, 2>(), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::GLSLvec2<T>::GLSLvec2(T initializationValue) noexcept :
	Vector<T, 2>(initializationValue), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::GLSLvec2<T>::GLSLvec2(T x, T y) noexcept :
	Vector<T, 2>({ x, y }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
template<typename U, typename V>
inline hgui::kernel::GLSLvec2<T>::GLSLvec2(U x, V y) noexcept :
	Vector<T, 2>({ static_cast<T>(x), static_cast<T>(y) }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::GLSLvec2<T>::GLSLvec2(const GLSLvec2<T>& vector) noexcept :
	Vector<T, 2>({ vector.x, vector.y }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::GLSLvec2<T>::GLSLvec2(const kernel::Vector<T, 2>& vector) noexcept :
	Vector<T, 2>({ vector[0], vector[1] }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
template<typename U>
inline hgui::kernel::GLSLvec2<T>::GLSLvec2(const glm::vec<2, U>& vector) noexcept :
	Vector<T, 2>({ static_cast<T>(vector.x), static_cast<T>(vector.y) }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::GLSLvec2<T>& hgui::kernel::GLSLvec2<T>::operator=(const GLSLvec2<T>& vector) noexcept
{
	x = vector.x;
	y = vector.y;
	return *this;
}

template<typename T>
template<typename U>
inline hgui::kernel::GLSLvec2<T>& hgui::kernel::GLSLvec2<T>::operator=(const GLSLvec2<U>& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	return *this;
}

template<typename T>
inline hgui::kernel::GLSLvec2<T>& hgui::kernel::GLSLvec2<T>::operator=(const glm::vec2& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	return *this;
}

template<typename T>
inline hgui::kernel::GLSLvec3<T>::GLSLvec3() noexcept :
	Vector<T, 3>(), x((*this)[0]), y((*this)[1]), z((*this)[2])
{
}

template<typename T>
inline hgui::kernel::GLSLvec3<T>::GLSLvec3(T initializationValue) noexcept :
	Vector<T, 3>(initializationValue), x((*this)[0]), y((*this)[1]), z((*this)[2])
{
}

template<typename T>
inline hgui::kernel::GLSLvec3<T>::GLSLvec3(T x, T y, T z) noexcept :
	Vector<T, 3>({ x, y, z }), x((*this)[0]), y((*this)[1]), z((*this)[2])
{
}

template<typename T>
inline hgui::kernel::GLSLvec3<T>::GLSLvec3(const GLSLvec3<T>& vector) noexcept :
	Vector<T, 3>({ vector.x, vector.y, vector.z }), x((*this)[0]), y((*this)[1]), z((*this)[2])
{
}

template<typename T>
inline hgui::kernel::GLSLvec3<T>::GLSLvec3(const kernel::Vector<T, 3>& vector) noexcept :
	Vector<T, 3>({ vector[0], vector[1], vector[2] }), x((*this)[0]), y((*this)[1]), z((*this)[2])
{
}

template<typename T>
template<typename U, typename V, typename W>
inline hgui::kernel::GLSLvec3<T>::GLSLvec3(U x, V y, W z) noexcept :
	Vector<T, 3>({ static_cast<T>(x), static_cast<T>(y), static_cast<T>(z) }), x((*this)[0]), y((*this)[1]), z((*this)[2])
{
}

template<typename T>
template<typename U>
inline hgui::kernel::GLSLvec3<T>::GLSLvec3(const GLSLvec3<U>& vector) noexcept :
	Vector<T, 3>({ static_cast<T>(vector.x), static_cast<T>(vector.y), static_cast<T>(vector.z) }), x((*this)[0]), y((*this)[1]), z((*this)[2])
{
}

template<typename T>
template<typename U, typename V>
inline hgui::kernel::GLSLvec3<T>::GLSLvec3(const glm::vec<2, U>& vector, V z) noexcept :
	Vector<T, 3>({ static_cast<T>(vector.x), static_cast<T>(vector.y), static_cast<T>(z) }), x((*this)[0]), y((*this)[1]), z((*this)[2])
{
}

template<typename T>
template<typename U>
inline hgui::kernel::GLSLvec3<T>::GLSLvec3(const glm::vec<3, U>& vector) noexcept :
	Vector<T, 3>({ static_cast<T>(vector.x), static_cast<T>(vector.y), static_cast<T>(vector.z) }), x((*this)[0]), y((*this)[1]), z((*this)[2])
{
}

template<typename T>
inline hgui::kernel::GLSLvec3<T>& hgui::kernel::GLSLvec3<T>::operator=(const GLSLvec3<T>& vector) noexcept
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	return *this;
}

template<typename T>
template<typename U>
inline hgui::kernel::GLSLvec3<T>& hgui::kernel::GLSLvec3<T>::operator=(const GLSLvec3<U>& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	z = static_cast<T>(vector.z);
	return *this;
}

template<typename T>
inline hgui::kernel::GLSLvec3<T>& hgui::kernel::GLSLvec3<T>::operator=(const glm::vec2& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	return *this;
}

template<typename T>
inline hgui::kernel::GLSLvec3<T>& hgui::kernel::GLSLvec3<T>::operator=(const glm::vec3& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	z = static_cast<T>(vector.z);
	return *this;
}

template<typename T>
inline hgui::kernel::GLSLvec4<T>::GLSLvec4() noexcept :
	Vector<T, 4>(), x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3])
{
}

template<typename T>
inline hgui::kernel::GLSLvec4<T>::GLSLvec4(T initializationValue) noexcept :
	Vector<T, 4>(initializationValue), x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3])
{
}

template<typename T>
inline hgui::kernel::GLSLvec4<T>::GLSLvec4(T x, T y, T z, T w) noexcept :
	Vector<T, 4>({ x, y, z, w }), x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3])
{
}

template<typename T>
inline hgui::kernel::GLSLvec4<T>::GLSLvec4(const GLSLvec4<T>& vector) noexcept :
	Vector<T, 4>({ vector.x, vector.y, vector.z, vector.w }), x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3])
{
}

template<typename T>
inline hgui::kernel::GLSLvec4<T>::GLSLvec4(const kernel::Vector<T, 4>& vector) noexcept :
	Vector<T, 4>({ vector[0], vector[1], vector[2], vector[3] }), x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3])
{
}

template<typename T>
template<typename U, typename V, typename W, typename X>
inline hgui::kernel::GLSLvec4<T>::GLSLvec4(U x, V y, W z, X w) noexcept :
	Vector<T, 4>({ static_cast<T>(x), static_cast<T>(y), static_cast<T>(z), static_cast<T>(w) }), x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3])
{
}

template<typename T>
template<typename U>
inline hgui::kernel::GLSLvec4<T>::GLSLvec4(const GLSLvec4<U>& vector) noexcept :
	Vector<T, 4>({ static_cast<T>(vector.x), static_cast<T>(vector.y), static_cast<T>(vector.z), static_cast<T>(vector.w) }), x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3])
{
}

template<typename T>
template<typename U, typename V, typename W>
inline hgui::kernel::GLSLvec4<T>::GLSLvec4(const glm::vec<2, U>& vector, V z, W w) noexcept :
	Vector<T, 4>({ static_cast<T>(vector.x), static_cast<T>(vector.y), static_cast<T>(z), static_cast<T>(w) }), x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3])
{
}

template<typename T>
template<typename U, typename V>
inline hgui::kernel::GLSLvec4<T>::GLSLvec4(const glm::vec<3, U>& vector, V w) noexcept :
	Vector<T, 4>({ static_cast<T>(vector.x), static_cast<T>(vector.y), static_cast<T>(vector.z), static_cast<T>(w) }), x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3])
{
}

template<typename T>
template<typename U>
inline hgui::kernel::GLSLvec4<T>::GLSLvec4(const glm::vec<4, U>& vector) noexcept :
	Vector<T, 4>({ static_cast<T>(vector.x), static_cast<T>(vector.y), static_cast<T>(vector.z), static_cast<T>(vector.w) }), x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3])
{
}

template<typename T>
inline hgui::kernel::GLSLvec4<T>& hgui::kernel::GLSLvec4<T>::operator=(const GLSLvec4<T>& vector) noexcept
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
	return *this;
}

template<typename T>
template<typename U>
inline hgui::kernel::GLSLvec4<T>& hgui::kernel::GLSLvec4<T>::operator=(const GLSLvec4<U>& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	z = static_cast<T>(vector.z);
	w = static_cast<T>(vector.w);
	return *this;
}

template<typename T>
inline hgui::kernel::GLSLvec4<T>& hgui::kernel::GLSLvec4<T>::operator=(const glm::vec2& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	return *this;
}

template<typename T>
inline hgui::kernel::GLSLvec4<T>& hgui::kernel::GLSLvec4<T>::operator=(const glm::vec3& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	z = static_cast<T>(vector.z);
	return *this;
}

template<typename T>
inline hgui::kernel::GLSLvec4<T>& hgui::kernel::GLSLvec4<T>::operator=(const glm::vec4& vector) noexcept
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	z = static_cast<T>(vector.z);
	w = static_cast<T>(vector.w);
	return *this;
}

template<typename T>
inline hgui::kernel::Point<T>::Point() noexcept :
	Vector<T, 2>(), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Point<T>::Point(T xy) noexcept :
	Vector<T, 2>(xy), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Point<T>::Point(EM<T> xy) noexcept :
	Vector<T, 2>({ static_cast<T>(xy.value * xy.referenceSize.width),
		static_cast<T>(xy.value * xy.referenceSize.height) }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
template<typename U>
inline hgui::kernel::Point<T>::Point(EM<U> xy) noexcept :
	Vector<T, 2>({ static_cast<T>(xy.value * xy.referenceSize.width),
		static_cast<T>(xy.value * xy.referenceSize.height) }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
template<typename U, typename V>
inline hgui::kernel::Point<T>::Point(EM<U> x, V y) noexcept :
	Vector<T, 2>({ static_cast<T>(x.value * x.referenceSize.width),
		static_cast<T>(y) }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
template<typename U, typename V>
inline hgui::kernel::Point<T>::Point(U x, EM<V> y) noexcept :
	Vector<T, 2>({ static_cast<T>(x),
		static_cast<T>(y.value * y.referenceSize.height) }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Point<T>::Point(T x, T y) noexcept :
	Vector<T, 2>({ x, y }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Point<T>::Point(EM<T> x, T y) noexcept :
	Vector<T, 2>({ static_cast<T>(x.value * x.referenceSize.width), y }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Point<T>::Point(T x, EM<T> y) noexcept :
	Vector<T, 2>({ x, static_cast<T>(y.value * y.referenceSize.height) }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Point<T>::Point(EM<T> x, EM<T> y) noexcept :
	Vector<T, 2>({ static_cast<T>(x.value * x.referenceSize.width),
		static_cast<T>(y.value * y.referenceSize.height) }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
template<typename U, typename V>
inline hgui::kernel::Point<T>::Point(EM<U> x, EM<V> y) noexcept :
	Vector<T, 2>({ static_cast<T>(x.value * x.referenceSize.width),
		static_cast<T>(y.value * y.referenceSize.height) }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Point<T>::Point(const Point<T>& point) noexcept :
	Vector<T, 2>({ point.x, point.y }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Point<T>::Point(const kernel::Vector<T, 2>& point) noexcept :
	Vector<T, 2>({ point[0], point[1] }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
template<typename U, typename V>
inline hgui::kernel::Point<T>::Point(U x, V y) noexcept :
	Vector<T, 2>({ static_cast<T>(x), static_cast<T>(y) }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
template<typename U>
inline hgui::kernel::Point<T>::Point(const Point<U>& point) noexcept :
	Vector<T, 2>({ static_cast<T>(point.x), static_cast<T>(point.y) }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Point<T>::Point(const glm::vec2& point) noexcept :
	Vector<T, 2>({ static_cast<T>(point.x), static_cast<T>(point.y) }), x((*this)[0]), y((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Point<T>& hgui::kernel::Point<T>::operator=(const Point<T>& point) noexcept
{
	x = point.x;
	y = point.y;
	return *this;
}

template<typename T>
template<typename U>
inline hgui::kernel::Point<T>& hgui::kernel::Point<T>::operator=(const Point<U>& point) noexcept
{
	x = static_cast<T>(point.x);
	y = static_cast<T>(point.y);
	return *this;
}

template<typename T>
inline hgui::kernel::Point<T>& hgui::kernel::Point<T>::operator=(const glm::vec2& point) noexcept
{
	x = static_cast<T>(point.x);
	y = static_cast<T>(point.y);
	return *this;
}

template<typename T>
inline hgui::kernel::Size<T>::Size() noexcept :
	Vector<T, 2>(), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Size<T>::Size(T widthANDheight) noexcept :
	Vector<T, 2>(widthANDheight), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Size<T>::Size(EM<T> widthANDheight) noexcept :
	Vector<T, 2>({ static_cast<T>(widthANDheight.value * widthANDheight.referenceSize.width),
		static_cast<T>(widthANDheight.value * widthANDheight.referenceSize.height) }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
template<typename U>
inline hgui::kernel::Size<T>::Size(EM<U> widthANDheight) noexcept :
	Vector<T, 2>({ static_cast<T>(widthANDheight.value * widthANDheight.referenceSize.width),
		static_cast<T>(widthANDheight.value * widthANDheight.referenceSize.height) }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
template<typename U, typename V>
inline hgui::kernel::Size<T>::Size(EM<U> width, V height) noexcept :
	Vector<T, 2>({ static_cast<T>(width.value * width.referenceSize.width),
		static_cast<T>(height) }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
template<typename U, typename V>
inline hgui::kernel::Size<T>::Size(U width, EM<V> height) noexcept :
	Vector<T, 2>({ static_cast<T>(width),
		static_cast<T>(height.value * height.referenceSize.height) }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Size<T>::Size(T width, T height) noexcept :
	Vector<T, 2>({ width, height }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Size<T>::Size(EM<T> width, T height) noexcept :
	Vector<T, 2>({ static_cast<T>(width.value * width.referenceSize.width), height }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Size<T>::Size(T width, EM<T> height) noexcept :
	Vector<T, 2>({ width, static_cast<T>(height.value * height.referenceSize.height) }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Size<T>::Size(EM<T> width, EM<T> height) noexcept :
	Vector<T, 2>({ static_cast<T>(width.value * width.referenceSize.width),
		static_cast<T>(width.value * width.referenceSize.height) }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
template<typename U, typename V>
inline hgui::kernel::Size<T>::Size(EM<U> width, EM<V> height) noexcept :
	Vector<T, 2>({ static_cast<T>(width.value * width.referenceSize.width),
		static_cast<T>(width.value * width.referenceSize.height) }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Size<T>::Size(const Size<T>& size) noexcept :
	Vector<T, 2>({ size.width, size.height }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Size<T>::Size(const kernel::Vector<T, 2>& size) noexcept :
	Vector<T, 2>({ size[0], size[1] }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
template<typename U, typename V>
inline hgui::kernel::Size<T>::Size(U width, V height) noexcept :
	Vector<T, 2>({ static_cast<T>(width), static_cast<T>(height) }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
template<typename U>
inline hgui::kernel::Size<T>::Size(const Size<U>& size) noexcept :
	Vector<T, 2>({ static_cast<T>(size.width), static_cast<T>(size.height) }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Size<T>::Size(const glm::vec2& size) noexcept :
	Vector<T, 2>({ static_cast<T>(size.x), static_cast<T>(size.y) }), width((*this)[0]), height((*this)[1])
{
}

template<typename T>
inline hgui::kernel::Size<T>& hgui::kernel::Size<T>::operator=(const Size<T>& size) noexcept
{
	width = size.width;
	height = size.height;
	return *this;
}

template<typename T>
template<typename U>
inline hgui::kernel::Size<T>& hgui::kernel::Size<T>::operator=(const Size<U>& size) noexcept
{
	width = static_cast<T>(size.width);
	height = static_cast<T>(size.height);
	return *this;
}

template<typename T>
inline hgui::kernel::Size<T>& hgui::kernel::Size<T>::operator=(const glm::vec2& size) noexcept
{
	width = static_cast<T>(size.x);
	height = static_cast<T>(size.y);
	return *this;
}

template<typename T>
inline hgui::kernel::Color<T>::Color() noexcept :
	Vector<T, 3>(), r((*this)[0]), g((*this)[1]), b((*this)[2])
{
}

template<typename T>
inline hgui::kernel::Color<T>::Color(T rgb) noexcept :
	Vector<T, 3>(rgb), r((*this)[0]), g((*this)[1]), b((*this)[2])
{
}

template<typename T>
inline hgui::kernel::Color<T>::Color(T r, T g, T b) noexcept :
	Vector<T, 3>({ r, g, b }), r((*this)[0]), g((*this)[1]), b((*this)[2])
{
}

template<typename T>
inline hgui::kernel::Color<T>::Color(const Color<T>& color) noexcept :
	Vector<T, 3>({ color.r, color.g, color.b }), r((*this)[0]), g((*this)[1]), b((*this)[2])
{
}

template<typename T>
inline hgui::kernel::Color<T>::Color(const kernel::Vector<T, 3>& color) noexcept :
	Vector<T, 3>({ color[0], color[1], color[2] }), r((*this)[0]), g((*this)[1]), b((*this)[2])
{
}

template<typename T>
template<typename U, typename V, typename W>
inline hgui::kernel::Color<T>::Color(U r, V g, W b) noexcept :
	Vector<T, 3>({ static_cast<T>(r), static_cast<T>(g), static_cast<T>(b) }), r((*this)[0]), g((*this)[1]), b((*this)[2])
{
}

template<typename T>
template<typename U>
inline hgui::kernel::Color<T>::Color(const Color<U>& color) noexcept :
	Vector<T, 3>({ static_cast<T>(color.r), static_cast<T>(color.g), static_cast<T>(color.b) }), r((*this)[0]), g((*this)[1]), b((*this)[2])
{
}

template<typename T>
inline hgui::kernel::Color<T>::Color(const glm::vec3& color) noexcept :
	Vector<T, 3>({ static_cast<T>(color.r), static_cast<T>(color.g), static_cast<T>(color.b) }), r((*this)[0]), g((*this)[1]), b((*this)[2])
{
}

template<typename T>
inline hgui::kernel::Color<T>& hgui::kernel::Color<T>::operator=(const Color<T>& color) noexcept
{
	r = color.r;
	g = color.g;
	b = color.b;
	return *this;
}

template<typename T>
template<typename U>
inline hgui::kernel::Color<T>& hgui::kernel::Color<T>::operator=(const Color<U>& color) noexcept
{
	r = static_cast<T>(color.r);
	g = static_cast<T>(color.g);
	b = static_cast<T>(color.b);
	return *this;
}

template<typename T>
inline hgui::kernel::Color<T>& hgui::kernel::Color<T>::operator=(const glm::vec3& color) noexcept
{
	r = static_cast<T>(color.r);
	g = static_cast<T>(color.g);
	b = static_cast<T>(color.b);
	return *this;
}
