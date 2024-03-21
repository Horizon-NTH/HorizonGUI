#pragma once

#include "Vector.hpp"

namespace hgui
{
	namespace kernel
	{
		template<typename T>
		class GLSLvec2 final : public Vector<T, 2>
		{
		public:
			GLSLvec2() noexcept;
			explicit GLSLvec2(T initializationValue) noexcept;
			GLSLvec2(T x, T y) noexcept;
			GLSLvec2(const GLSLvec2& vector) noexcept;
			GLSLvec2(const Vector<T, 2>& vector) noexcept;
			GLSLvec2(const glm::vec<2, T>& vector) noexcept;

			template<typename U, typename V>
			GLSLvec2(U x, V y) noexcept;
			template<typename U>
			explicit GLSLvec2(const GLSLvec2<U>& vector) noexcept;
			template<typename U>
			GLSLvec2(const glm::vec<2, U>& vector) noexcept;

			GLSLvec2& operator=(const GLSLvec2& vector) noexcept;
			template<typename U>
			GLSLvec2& operator=(const GLSLvec2<U>& vector) noexcept;
			GLSLvec2& operator=(const glm::vec2& vector) noexcept;

			friend std::ostream& operator<<(std::ostream& stream, const GLSLvec2& vec2)
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
			GLSLvec3(const glm::vec<2, T>& vector, T z = {}) noexcept;
			GLSLvec3(const glm::vec<3, T>& vector) noexcept;

			template<typename U, typename V, typename W>
			GLSLvec3(U x, V y, W z) noexcept;
			template<typename U>
			explicit GLSLvec3(const GLSLvec3<U>& vector) noexcept;
			template<typename U, typename V>
			GLSLvec3(const glm::vec<2, U>& vector, V z = {}) noexcept;
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
			GLSLvec4(const glm::vec<2, T>& vector, T z = {}, T w = {}) noexcept;
			GLSLvec4(const glm::vec<3, T>& vector, T w = {}) noexcept;
			GLSLvec4(const glm::vec<4, T>& vector) noexcept;

			template<typename U, typename V, typename W, typename X>
			GLSLvec4(U x, V y, W z, X w) noexcept;
			template<typename U>
			explicit GLSLvec4(const GLSLvec4<U>& vector) noexcept;
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
		class Color final : public Vector<T, 4>
		{
		public:
			Color() noexcept;
			explicit Color(T rgb, T a = static_cast<T>(1)) noexcept;
			explicit Color(const std::string& hexColor, T a = static_cast<T>(1)) noexcept;
			Color(T r, T g, T b, T a = static_cast<T>(1)) noexcept;
			template<typename U>
			Color(U r, U g, U b, U a = static_cast<U>(1)) noexcept;
			Color(const Color& color) noexcept;
			Color(const Vector<T, 3>& color) noexcept;
			Color(const Vector<T, 4>& color) noexcept;
			explicit Color(const glm::vec<3, T>& color) noexcept;
			explicit Color(const glm::vec<4, T>& color) noexcept;

			template<typename U, typename V, typename W, typename X>
			Color(U r, V g, W b, X a = static_cast<X>(1)) noexcept;
			template<typename U>
			explicit Color(const Color<U>& color) noexcept;

			Color& operator=(const Color& color) noexcept;
			template<typename U>
			Color& operator=(const Color<U>& color) noexcept;
			Color& operator=(const glm::vec3& color) noexcept;
			Color& operator=(const glm::vec4& color) noexcept;

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
	typedef kernel::Color<HGUI_PRECISION> color;
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
hgui::kernel::GLSLvec2<T>::GLSLvec2(const glm::vec<2, T>& vector) noexcept :
	Vector<T, 2>({vector.x, vector.y}),
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
inline hgui::kernel::GLSLvec3<T>::GLSLvec3(const glm::vec<2, T>& vector, T z) noexcept :
	Vector<T, 3>({vector.x, vector.y, z}),
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
inline hgui::kernel::GLSLvec4<T>::GLSLvec4(const glm::vec<2, T>& vector, T z, T w) noexcept :
	Vector<T, 4>({
			vector.x, vector.y, z, w
		}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2]),
	w((*this)[3])
{
}

template<typename T>
inline hgui::kernel::GLSLvec4<T>::GLSLvec4(const glm::vec<3, T>& vector, T w) noexcept :
	Vector<T, 4>({
			vector.x, vector.y, vector.z, w
		}),
	x((*this)[0]),
	y((*this)[1]),
	z((*this)[2]),
	w((*this)[3])
{
}

template<typename T>
inline hgui::kernel::GLSLvec4<T>::GLSLvec4(const glm::vec<4, T>& vector) noexcept :
	Vector<T, 4>({
			vector.x, vector.y, vector.z, vector.w
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
hgui::kernel::Color<T>::Color(const std::string& hexColor, T a) noexcept :
	Vector<T, 4>({T(), T(), T(), a}),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
	const std::string hex = hexColor[0] == '#' ? hexColor.substr(1) : hexColor;
	std::stringstream ss;
	ss << std::hex << hex;
	int rgbValue;
	ss >> rgbValue;
	r = static_cast<T>((rgbValue >> 16 & 0xFF) / 255.);
	g = static_cast<T>((rgbValue >> 8 & 0xFF) / 255.);
	b = static_cast<T>((rgbValue & 0xFF) / 255.);
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
hgui::kernel::Color<T>::Color(const glm::vec<3, T>& color) noexcept :
	Vector<T, 4>({
			color.r, color.g,
			color.b, static_cast<T>(1)
		}),
	r((*this)[0]),
	g((*this)[1]),
	b((*this)[2]),
	a((*this)[3])
{
}

template<typename T>
hgui::kernel::Color<T>::Color(const glm::vec<4, T>& color) noexcept :
	Vector<T, 4>({
			color.r, color.g,
			color.b, color.a
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
