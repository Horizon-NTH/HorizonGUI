#pragma once

#include "Include.h"
#include "Iterator.hpp"

namespace hgui
{
	namespace kernel
	{
		template<typename T, std::size_t dimension>
		class Vector
		{
		public:
			using iterator = Iterator<T>;
			using const_iterator = ConstIterator<T>;
			using reverse_iterator = ReverseIterator<T>;
			using const_reverse_iterator = ConstReverseIterator<T>;

			Vector() noexcept;
			explicit Vector(const T& initializationValue) noexcept;
			Vector(const Vector<T, dimension>& vector) noexcept;
			Vector(const Vector<T, dimension>&& vector) noexcept;
			Vector(const std::valarray<T>& vector) noexcept;
			Vector(const std::valarray<T>&& vector) noexcept;

			T length() const;
			void normalize();
			void set(const std::initializer_list<T>& newValues) noexcept;

			T& operator[](int indice) noexcept;
			const T& operator[](int indice) const noexcept;
			void operator-() noexcept;

			inline Vector<T, dimension>& operator=(const Vector<T, dimension>& vector) noexcept;

			friend inline Vector<T, dimension> operator+(const Vector<T, dimension>& u, const Vector<T, dimension>& v) noexcept
			{
				return Vector<T, dimension>(u.m_data + v.m_data);
			}

			inline Vector<T, dimension>& operator+=(const Vector<T, dimension>& u) noexcept;

			friend inline Vector<T, dimension> operator-(const Vector<T, dimension>& u, const Vector<T, dimension>& v) noexcept
			{
				return Vector<T, dimension>(u.m_data - v.m_data);
			}

			inline Vector<T, dimension>& operator-=(const Vector<T, dimension>& u) noexcept;

			friend inline Vector<T, dimension> operator*(const Vector<T, dimension>& u, const T& element) noexcept
			{
				return Vector<T, dimension>(u.m_data * element);
			}

			inline Vector<T, dimension>& operator*=(const T& element) noexcept;

			friend inline Vector<T, dimension> operator/(const Vector<T, dimension>& u, const T& element) noexcept
			{
				return Vector<T, dimension>(u.m_data * element);
			}

			inline Vector<T, dimension>& operator/=(const T& element) noexcept;

			friend inline Vector<T, dimension> operator*(const T& element, const Vector<T, dimension>& v) noexcept
			{
				return Vector<T, dimension>(v.m_data * element);
			}

			friend inline Vector<T, dimension> operator/(const T& element, const Vector<T, dimension>& v) noexcept
			{
				return Vector<T, dimension>(v.m_data / element);
			}

			friend inline bool operator==(const Vector<T, dimension>& u, const Vector<T, dimension>& v) noexcept
			{
				return u.m_data == v.m_data;
			}

			friend inline bool operator!=(const Vector<T, dimension>& u, const Vector<T, dimension>& v) noexcept
			{
				return u.m_data != v.m_data;
			}

			friend std::ostream& operator<<(std::ostream& stream, const ::hgui::kernel::Vector<T, dimension>& vector)
			{
				std::stringstream sstream;
				int size = 0;
				for (auto it = std::begin(vector.m_data); it < std::end(vector.m_data); it++)
				{
					sstream << *it;
					size = std::max(size, static_cast<int>(sstream.str().length()));
					sstream.str("");
				}
				long basef = stream.setf(std::ios::left, std::ios::adjustfield);
				for (auto it = std::begin(vector.m_data); it < std::end(vector.m_data); it++)
				{
					stream << '|' << std::setw(size) << *it << '|' << std::endl;
				}
				stream.setf(basef, std::ios::adjustfield);
				return stream;
			}

			friend T dot(const Vector<T, dimension>& u, const Vector<T, dimension>& v);
			friend  Vector<T, 3> cross(const Vector<T, 3>& u, const Vector<T, 3>& v);
			friend  T distance(const Vector<T, dimension>& u, const Vector<T, dimension>& v);

			iterator begin() noexcept;
			const_iterator begin() const noexcept;
			iterator end() noexcept;
			const_iterator end() const noexcept;
			reverse_iterator rbegin() noexcept;
			const_reverse_iterator rbegin() const noexcept;
			reverse_iterator rend() noexcept;
			const_reverse_iterator rend() const noexcept;
			const_iterator cbegin() const noexcept;
			const_iterator cend() const noexcept;
			const_reverse_iterator crbegin() const noexcept;
			const_reverse_iterator crend() const noexcept;

		private:
			std::valarray<T> m_data;
		};

		template<typename T, std::size_t dimension>
		T dot(const Vector<T, dimension>& u, const Vector<T, dimension>& v)
		{
			return std::inner_product(std::begin(u.m_data), std::end(u.m_data), std::begin(v.m_data), T{});
		}

		template<typename T, std::size_t dimension>
		Vector<T, 3> cross(const Vector<T, 3>& u, const Vector<T, 3>& v)
		{
			return hgui::kernel::Vector<T, 3>({ u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0] });
		}

		template<typename T, std::size_t dimension>
		T distance(const Vector<T, dimension>& u, const Vector<T, dimension>& v)
		{
			return (u - v).length();
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------

template<typename T, std::size_t dimension>
inline hgui::kernel::Vector<T, dimension>::Vector() noexcept :
	m_data(dimension)
{
}

template<typename T, std::size_t dimension>
inline hgui::kernel::Vector<T, dimension>::Vector(const T& initializationValue) noexcept :
	m_data(initializationValue, dimension)
{
}

template<typename T, std::size_t dimension>
inline hgui::kernel::Vector<T, dimension>::Vector(const Vector<T, dimension>& vector) noexcept :
	m_data(vector.m_data)
{
}

template<typename T, std::size_t dimension>
inline hgui::kernel::Vector<T, dimension>::Vector(const Vector<T, dimension>&& vector) noexcept :
	m_data(std::move(vector.m_data))
{
}

template<typename T, std::size_t dimension>
inline hgui::kernel::Vector<T, dimension>::Vector(const std::valarray<T>& vector) noexcept :
	m_data(vector)
{
}

template<typename T, std::size_t dimension>
inline hgui::kernel::Vector<T, dimension>::Vector(const std::valarray<T>&& vector) noexcept :
	m_data(std::move(vector))
{
}

template<typename T, std::size_t dimension>
inline T hgui::kernel::Vector<T, dimension>::length() const
{
	return static_cast<T>(std::sqrt(std::inner_product(std::begin(m_data), std::end(m_data), std::begin(m_data), T{})));
}

template<typename T, std::size_t dimension>
inline void hgui::kernel::Vector<T, dimension>::normalize()
{
	T length = this->length();
	std::for_each(std::begin(m_data), std::end(m_data), [&](T& element) { element /= length; });
}

template<typename T, std::size_t dimension>
inline void hgui::kernel::Vector<T, dimension>::set(const std::initializer_list<T>& newValues) noexcept
{
	m_data = std::valarray<T>(newValues);
}

template<typename T, std::size_t dimension>
inline T& hgui::kernel::Vector<T, dimension>::operator[](int indice) noexcept
{
	return m_data[indice];
}

template<typename T, std::size_t dimension>
inline const T& hgui::kernel::Vector<T, dimension>::operator[](int indice) const noexcept
{
	return m_data[indice];
}

template<typename T, std::size_t dimension>
inline void hgui::kernel::Vector<T, dimension>::operator-() noexcept
{
	m_data = -m_data;
}

template<typename T, std::size_t dimension>
inline hgui::kernel::Vector<T, dimension>& hgui::kernel::Vector<T, dimension>::operator=(const Vector<T, dimension>& vector) noexcept
{
	m_data = vector.m_data;
}

template<typename T, std::size_t dimension>
inline hgui::kernel::Vector<T, dimension>& hgui::kernel::Vector<T, dimension>::operator+=(const Vector<T, dimension>& u) noexcept
{
	m_data += u.m_data;
	return *this;
}

template<typename T, std::size_t dimension>
inline hgui::kernel::Vector<T, dimension>& hgui::kernel::Vector<T, dimension>::operator-=(const Vector<T, dimension>& u) noexcept
{
	m_data -= u.m_data;
	return *this;
}

template<typename T, std::size_t dimension>
inline hgui::kernel::Vector<T, dimension>& hgui::kernel::Vector<T, dimension>::operator*=(const T& element) noexcept
{
	m_data *= element;
	return *this;
}

template<typename T, std::size_t dimension>
inline hgui::kernel::Vector<T, dimension>& hgui::kernel::Vector<T, dimension>::operator/=(const T& element) noexcept
{
	m_data /= element;
	return *this;
}

template<typename T, std::size_t dimension>
inline typename hgui::kernel::Vector<T, dimension>::iterator hgui::kernel::Vector<T, dimension>::begin() noexcept
{
	return Iterator(std::begin(m_data));
}

template<typename T, std::size_t dimension>
inline typename hgui::kernel::Vector<T, dimension>::const_iterator hgui::kernel::Vector<T, dimension>::begin() const noexcept
{
	return ConstIterator(std::begin(m_data));
}

template<typename T, std::size_t dimension>
inline typename hgui::kernel::Vector<T, dimension>::iterator hgui::kernel::Vector<T, dimension>::end() noexcept
{
	return Iterator(std::end(m_data));
}

template<typename T, std::size_t dimension>
inline typename hgui::kernel::Vector<T, dimension>::const_iterator hgui::kernel::Vector<T, dimension>::end() const noexcept
{
	return ConstIterator(std::end(m_data));
}

template<typename T, std::size_t dimension>
inline typename hgui::kernel::Vector<T, dimension>::reverse_iterator hgui::kernel::Vector<T, dimension>::rbegin() noexcept
{
	auto it = std::end(m_data);
	return ReverseIterator(--it);
}

template<typename T, std::size_t dimension>
inline typename hgui::kernel::Vector<T, dimension>::const_reverse_iterator hgui::kernel::Vector<T, dimension>::rbegin() const noexcept
{
	auto it = std::end(m_data);
	return ConstReverseIterator(--it);
}

template<typename T, std::size_t dimension>
inline typename hgui::kernel::Vector<T, dimension>::reverse_iterator hgui::kernel::Vector<T, dimension>::rend() noexcept
{
	auto it = std::begin(m_data);
	return ReverseIterator(--it);
}

template<typename T, std::size_t dimension>
inline typename hgui::kernel::Vector<T, dimension>::const_reverse_iterator hgui::kernel::Vector<T, dimension>::rend() const noexcept
{
	auto it = std::begin(m_data);
	return ConstReverseIterator(--it);
}

template<typename T, std::size_t dimension>
inline typename hgui::kernel::Vector<T, dimension>::const_iterator hgui::kernel::Vector<T, dimension>::cbegin() const noexcept
{
	return ConstIterator(std::begin(m_data));
}

template<typename T, std::size_t dimension>
inline typename hgui::kernel::Vector<T, dimension>::const_iterator hgui::kernel::Vector<T, dimension>::cend() const noexcept
{
	return ConstIterator(std::end(m_data));
}

template<typename T, std::size_t dimension>
inline typename hgui::kernel::Vector<T, dimension>::const_reverse_iterator hgui::kernel::Vector<T, dimension>::crbegin() const noexcept
{
	auto it = std::end(m_data);
	return ConstReverseIterator(--it);
}

template<typename T, std::size_t dimension>
inline typename hgui::kernel::Vector<T, dimension>::const_reverse_iterator hgui::kernel::Vector<T, dimension>::crend() const noexcept
{
	auto it = std::begin(m_data);
	return ConstReverseIterator(--it);
}