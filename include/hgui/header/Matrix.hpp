#pragma once

#include "Vector.hpp"
#include <valarray>
#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <iterator>

namespace htools
{
	namespace maths
	{
		template<typename T, std::size_t rows, std::size_t columns = rows>
		class Matrix
		{
		public:
			class Iterator;
			class ConstIterator;
			class ReverseIterator;
			class ConstReverseIterator;

			using iterator = typename Matrix<T, rows, columns>::Iterator;
			using const_iterator = typename Matrix<T, rows, columns>::ConstIterator;
			using reverse_iterator = typename Matrix<T, rows, columns>::ReverseIterator;
			using const_reverse_iterator = typename Matrix<T, rows, columns>::ConstReverseIterator;

			Matrix() noexcept;
			Matrix(const T& initializationValue) noexcept;
			Matrix(const Matrix<T, rows, columns>& matrix) noexcept;
			Matrix(const Matrix<T, rows, columns>&& matrix) noexcept;
			Matrix(const std::valarray<T>& matrix) noexcept;
			Matrix(const std::valarray<T>&& matrix) noexcept;
			Matrix(const std::initializer_list<Vector<T, columns>>& matrix) noexcept;

			void set(const std::initializer_list<T>& newValues) noexcept;

			Vector<T&, columns> operator[](int indice) noexcept;
			const Vector<const T&, columns> operator[](int indice) const noexcept;
			void operator-() noexcept;

			friend inline Matrix<T, rows, columns> operator+(const Matrix<T, rows, columns>& A, const Matrix<T, rows, columns>& B) noexcept
			{
				return Matrix<T, rows, columns>(A.m_data + B.m_data);
			}

			friend inline Matrix<T, rows, columns> operator-(const Matrix<T, rows, columns>& A, const Matrix<T, rows, columns>& B) noexcept
			{
				return Matrix<T, rows, columns>(A.m_data - B.m_data);
			}

			friend inline Matrix<T, rows, columns> operator*(const Matrix<T, rows, columns>& A, const T& element) noexcept
			{
				return Matrix<T, rows, columns>(A.m_data * element);
			}

			friend inline Matrix<T, rows, columns> operator/(const Matrix<T, rows, columns>& A, const T& element) noexcept
			{
				return Matrix<T, rows, columns>(A.m_data * element);
			}

			friend inline Matrix<T, rows, columns> operator*(const T& element, const Matrix<T, rows, columns>& B) noexcept
			{
				return Matrix<T, rows, columns>(B.m_data * element);
			}

			friend inline Matrix<T, rows, columns> operator/(const T& element, const Matrix<T, rows, columns>& B) noexcept
			{
				return Matrix<T, rows, columns>(B.m_data / element);
			}

			friend inline bool operator==(const Matrix<T, rows, columns>& A, const Matrix<T, rows, columns>& B) noexcept
			{
				return A.m_data == B.m_data;
			}

			friend inline bool operator!=(const Matrix<T, rows, columns>& A, const Matrix<T, rows, columns>& B) noexcept
			{
				return A.m_data != B.m_data;
			}

			friend std::ostream& operator<<(std::ostream& stream, const ::htools::maths::Matrix<T, rows, columns>& matrix)
			{
				std::stringstream sstream;
				int size = 0;
				for (auto it = std::begin(matrix.m_data); it < std::end(matrix.m_data); it++)
				{
					sstream << *it;
					size = std::max(size, static_cast<int>(sstream.str().length()));
					sstream.str("");
				}
				const long basef = stream.setf(std::ios::left, std::ios::adjustfield);
				int cpt = 0;
				for (auto it = std::begin(matrix.m_data); it < std::end(matrix.m_data); it++)
				{
					stream << '|' << std::setw(size) << *it;
					cpt++;
					if (!(cpt % columns))
					{
						std::cout << '|' << std::endl;
					}
				}
				stream.setf(basef, std::ios::adjustfield);
				return stream;
			}

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

		public:
			class ConstIterator
			{
				using iterator_category = std::random_access_iterator_tag;
				using difference_type = std::ptrdiff_t;
				using value_type = const T;
				using pointer = const T*;
				using reference = const T&;

			public:
				ConstIterator() noexcept;
				ConstIterator(const T* ptr) noexcept;

				const reference operator*() const noexcept;
				const pointer operator->() const noexcept;
				const reference operator[](const difference_type offset) const noexcept;

				ConstIterator& operator++() noexcept;
				ConstIterator operator++(int) noexcept;
				ConstIterator& operator--() noexcept;
				ConstIterator operator--(int) noexcept;

				ConstIterator& operator+=(const difference_type offset) noexcept;
				friend inline ConstIterator operator+(const difference_type offset, ConstIterator it) noexcept
				{
					return it += offset;
				}

				friend inline ConstIterator operator+(ConstIterator it, const difference_type offset) noexcept
				{
					return it += offset;
				}

				ConstIterator& operator-=(const difference_type offset) noexcept;
				friend inline ConstIterator operator-(const difference_type offset, ConstIterator it) noexcept
				{
					return it -= offset;
				}

				friend inline ConstIterator operator-(ConstIterator it, const difference_type offset) noexcept
				{
					return it -= offset;
				}


				friend inline bool operator==(const ConstIterator& lhs, const ConstIterator& rhs) noexcept
				{
					return lhs.m_ptr == rhs.m_ptr;
				}

				friend inline bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs) noexcept
				{
					return lhs.m_ptr != rhs.m_ptr;
				}

				friend inline bool operator<(const ConstIterator& lhs, const ConstIterator& rhs) noexcept
				{
					return lhs.m_ptr < rhs.m_ptr;
				}

				friend inline bool operator<=(const ConstIterator& lhs, const ConstIterator& rhs) noexcept
				{
					return lhs.m_ptr <= rhs.m_ptr;
				}

				friend inline bool operator>(const ConstIterator& lhs, const ConstIterator& rhs) noexcept
				{
					return lhs.m_ptr > rhs.m_ptr;
				}

				friend inline bool operator>=(const ConstIterator& lhs, const ConstIterator& rhs) noexcept
				{
					return lhs.m_ptr >= rhs.m_ptr;
				}

			private:
				pointer m_ptr;
			};

			class ConstReverseIterator
			{
				using iterator_category = std::random_access_iterator_tag;
				using difference_type = std::ptrdiff_t;
				using value_type = const T;
				using pointer = const T*;
				using reference = const T&;

			public:
				ConstReverseIterator() noexcept;
				ConstReverseIterator(const T* ptr) noexcept;

				const reference operator*() const noexcept;
				const pointer operator->() const noexcept;
				const reference operator[](const difference_type offset) const noexcept;

				ConstReverseIterator& operator++() noexcept;
				ConstReverseIterator operator++(int) noexcept;
				ConstReverseIterator& operator--() noexcept;
				ConstReverseIterator operator--(int) noexcept;

				ConstReverseIterator& operator+=(const difference_type offset) noexcept;
				friend inline ConstReverseIterator operator+(const difference_type offset, ConstReverseIterator it) noexcept
				{
					return it += offset;
				}

				friend inline ConstReverseIterator operator+(ConstReverseIterator it, const difference_type offset) noexcept
				{
					return it += offset;
				}

				ConstReverseIterator& operator-=(const difference_type offset) noexcept;
				friend inline ConstReverseIterator operator-(const difference_type offset, ConstReverseIterator it) noexcept
				{
					return it -= offset;
				}

				friend inline ConstReverseIterator operator-(ConstReverseIterator it, const difference_type offset) noexcept
				{
					return it -= offset;
				}


				friend inline bool operator==(const ConstReverseIterator& lhs, const ConstReverseIterator& rhs) noexcept
				{
					return lhs.m_ptr == rhs.m_ptr;
				}

				friend inline bool operator!=(const ConstReverseIterator& lhs, const ConstReverseIterator& rhs) noexcept
				{
					return lhs.m_ptr != rhs.m_ptr;
				}

				friend inline bool operator<(const ConstReverseIterator& lhs, const ConstReverseIterator& rhs) noexcept
				{
					return lhs.m_ptr > rhs.m_ptr;
				}

				friend inline bool operator<=(const ConstReverseIterator& lhs, const ConstReverseIterator& rhs) noexcept
				{
					return lhs.m_ptr >= rhs.m_ptr;
				}

				friend inline bool operator>(const ConstReverseIterator& lhs, const ConstReverseIterator& rhs) noexcept
				{
					return lhs.m_ptr < rhs.m_ptr;
				}

				friend inline bool operator>=(const ConstReverseIterator& lhs, const ConstReverseIterator& rhs) noexcept
				{
					return lhs.m_ptr <= rhs.m_ptr;
				}

			private:
				pointer m_ptr;
			};

			class Iterator
			{
				using iterator_category = std::random_access_iterator_tag;
				using difference_type = std::ptrdiff_t;
				using value_type = T;
				using pointer = T*;
				using reference = T&;

			public:
				Iterator() noexcept;
				Iterator(T* ptr) noexcept;

				reference operator*() const noexcept;
				pointer operator->() const noexcept;
				reference operator[](const difference_type offset) const noexcept;

				Iterator& operator++() noexcept;
				Iterator operator++(int) noexcept;
				Iterator& operator--() noexcept;
				Iterator operator--(int) noexcept;

				Iterator& operator+=(const difference_type offset) noexcept;
				friend inline Iterator operator+(const difference_type offset, Iterator it) noexcept
				{
					return it += offset;
				}

				friend inline Iterator operator+(Iterator it, const difference_type offset) noexcept
				{
					return it += offset;
				}

				Iterator& operator-=(const difference_type offset) noexcept;
				friend inline Iterator operator-(const difference_type offset, Iterator it) noexcept
				{
					return it -= offset;
				}

				friend inline Iterator operator-(Iterator it, const difference_type offset) noexcept
				{
					return it -= offset;
				}


				friend inline bool operator==(const Iterator& lhs, const Iterator& rhs) noexcept
				{
					return lhs.m_ptr == rhs.m_ptr;
				}

				friend inline bool operator!=(const Iterator& lhs, const Iterator& rhs) noexcept
				{
					return lhs.m_ptr != rhs.m_ptr;
				}

				friend inline bool operator<(const Iterator& lhs, const Iterator& rhs) noexcept
				{
					return lhs.m_ptr < rhs.m_ptr;
				}

				friend inline bool operator<=(const Iterator& lhs, const Iterator& rhs) noexcept
				{
					return lhs.m_ptr <= rhs.m_ptr;
				}

				friend inline bool operator>(const Iterator& lhs, const Iterator& rhs) noexcept
				{
					return lhs.m_ptr > rhs.m_ptr;
				}

				friend inline bool operator>=(const Iterator& lhs, const Iterator& rhs) noexcept
				{
					return lhs.m_ptr >= rhs.m_ptr;
				}

				operator ConstIterator() const noexcept;

			protected:
				pointer m_ptr;
			};

			class ReverseIterator : public Iterator
			{
				using iterator_category = std::random_access_iterator_tag;
				using difference_type = std::ptrdiff_t;
				using value_type = T;
				using pointer = T*;
				using reference = T&;

			public:
				ReverseIterator() noexcept;
				ReverseIterator(T* ptr) noexcept;

				reference operator*() const noexcept;
				pointer operator->() const noexcept;
				reference operator[](const difference_type offset) const noexcept;

				ReverseIterator& operator++() noexcept;
				ReverseIterator operator++(int) noexcept;
				ReverseIterator& operator--() noexcept;
				ReverseIterator operator--(int) noexcept;

				ReverseIterator& operator+=(const difference_type offset) noexcept;
				friend inline ReverseIterator operator+(const difference_type offset, ReverseIterator it) noexcept
				{
					return it += offset;
				}

				friend inline ReverseIterator operator+(ReverseIterator it, const difference_type offset) noexcept
				{
					return it += offset;
				}

				ReverseIterator& operator-=(const difference_type offset) noexcept;
				friend inline ReverseIterator operator-(const difference_type offset, ReverseIterator it) noexcept
				{
					return it -= offset;
				}

				friend inline ReverseIterator operator-(ReverseIterator it, const difference_type offset) noexcept
				{
					return it -= offset;
				}


				friend inline bool operator==(const ReverseIterator& lhs, const ReverseIterator& rhs) noexcept
				{
					return lhs.m_ptr == rhs.m_ptr;
				}

				friend inline bool operator!=(const ReverseIterator& lhs, const ReverseIterator& rhs) noexcept
				{
					return lhs.m_ptr != rhs.m_ptr;
				}

				friend inline bool operator<(const ReverseIterator& lhs, const ReverseIterator& rhs) noexcept
				{
					return lhs.m_ptr > rhs.m_ptr;
				}

				friend inline bool operator<=(const ReverseIterator& lhs, const ReverseIterator& rhs) noexcept
				{
					return lhs.m_ptr >= rhs.m_ptr;
				}

				friend inline bool operator>(const ReverseIterator& lhs, const ReverseIterator& rhs) noexcept
				{
					return lhs.m_ptr < rhs.m_ptr;
				}

				friend inline bool operator>=(const ReverseIterator& lhs, const ReverseIterator& rhs) noexcept
				{
					return lhs.m_ptr <= rhs.m_ptr;
				}

				operator ConstReverseIterator() const noexcept;
			private:
				pointer m_ptr;
			};
		};
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------

template<typename T, std::size_t rows, std::size_t columns>
inline htools::maths::Matrix<T, rows, columns>::Matrix() noexcept :
	m_data(rows * columns)
{
}

template<typename T, std::size_t rows, std::size_t columns>
inline htools::maths::Matrix<T, rows, columns>::Matrix(const T& initializationValue) noexcept :
	m_data(initializationValue, rows * columns)
{
}

template<typename T, std::size_t rows, std::size_t columns>
inline htools::maths::Matrix<T, rows, columns>::Matrix(const Matrix<T, rows, columns>& matrix) noexcept :
	m_data(matrix.m_data)
{
}

template<typename T, std::size_t rows, std::size_t columns>
inline htools::maths::Matrix<T, rows, columns>::Matrix(const Matrix<T, rows, columns>&& matrix) noexcept :
	m_data(std::move(matrix.m_data))
{
}

template<typename T, std::size_t rows, std::size_t columns>
inline htools::maths::Matrix<T, rows, columns>::Matrix(const std::valarray<T>& matrix) noexcept :
	m_data(matrix)
{
}

template<typename T, std::size_t rows, std::size_t columns>
inline htools::maths::Matrix<T, rows, columns>::Matrix(const std::valarray<T>&& matrix) noexcept :
	m_data(std::move(matrix))
{
}

template<typename T, std::size_t rows, std::size_t columns>
inline htools::maths::Matrix<T, rows, columns>::Matrix(const std::initializer_list<Vector<T, columns>>& matrix) noexcept
{
}

template<typename T, std::size_t rows, std::size_t columns>
inline void htools::maths::Matrix<T, rows, columns>::set(const std::initializer_list<T>& newValues) noexcept
{
	m_data = std::valarray<T>(newValues);
}

template<typename T, std::size_t rows, std::size_t columns>
inline htools::maths::Vector<T&, columns> htools::maths::Matrix<T, rows, columns>::operator[](int indice) noexcept
{
	return m_data[indice];
}

template<typename T, std::size_t rows, std::size_t columns>
inline const htools::maths::Vector<const T&, columns> htools::maths::Matrix<T, rows, columns>::operator[](int indice) const noexcept
{
	return m_data[indice];
}

template<typename T, std::size_t rows, std::size_t columns>
inline void htools::maths::Matrix<T, rows, columns>::operator-() noexcept
{
	m_data = -m_data;
}
/*
template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::iterator htools::maths::Vector<T, dimension>::begin() noexcept
{
	return Iterator(std::begin(m_data));
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::const_iterator htools::maths::Vector<T, dimension>::begin() const noexcept
{
	return ConstIterator(std::begin(m_data));
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::iterator htools::maths::Vector<T, dimension>::end() noexcept
{
	return Iterator(std::end(m_data));
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::const_iterator htools::maths::Vector<T, dimension>::end() const noexcept
{
	return ConstIterator(std::end(m_data));
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::reverse_iterator htools::maths::Vector<T, dimension>::rbegin() noexcept
{
	auto it = std::end(m_data);
	return ReverseIterator(--it);
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::const_reverse_iterator htools::maths::Vector<T, dimension>::rbegin() const noexcept
{
	auto it = std::end(m_data);
	return ConstReverseIterator(--it);
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::reverse_iterator htools::maths::Vector<T, dimension>::rend() noexcept
{
	auto it = std::begin(m_data);
	return ReverseIterator(--it);
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::const_reverse_iterator htools::maths::Vector<T, dimension>::rend() const noexcept
{
	auto it = std::begin(m_data);
	return ConstReverseIterator(--it);
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::const_iterator htools::maths::Vector<T, dimension>::cbegin() const noexcept
{
	return ConstIterator(std::begin(m_data));
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::const_iterator htools::maths::Vector<T, dimension>::cend() const noexcept
{
	return ConstIterator(std::end(m_data));
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::const_reverse_iterator htools::maths::Vector<T, dimension>::crbegin() const noexcept
{
	auto it = std::end(m_data);
	return ConstReverseIterator(--it);
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::const_reverse_iterator htools::maths::Vector<T, dimension>::crend() const noexcept
{
	auto it = std::begin(m_data);
	return ConstReverseIterator(--it);
}


template<typename T, std::size_t dimension>
inline htools::maths::Vector<T, dimension>::ConstIterator::ConstIterator() noexcept :
	m_ptr(nullptr)
{
}

template<typename T, std::size_t dimension>
inline htools::maths::Vector<T, dimension>::ConstIterator::ConstIterator(const T* ptr) noexcept :
	m_ptr(ptr)
{
}

template<typename T, std::size_t dimension>
inline const typename htools::maths::Vector<T, dimension>::ConstIterator::reference htools::maths::Vector<T, dimension>::ConstIterator::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T, std::size_t dimension>
inline const typename htools::maths::Vector<T, dimension>::ConstIterator::pointer htools::maths::Vector<T, dimension>::ConstIterator::operator->() const noexcept
{
	return m_ptr;
}

template<typename T, std::size_t dimension>
inline const typename htools::maths::Vector<T, dimension>::ConstIterator::reference htools::maths::Vector<T, dimension>::ConstIterator::operator[](const difference_type offset) const noexcept
{
	return *(m_ptr + offset);
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ConstIterator::ConstIterator& htools::maths::Vector<T, dimension>::ConstIterator::operator++() noexcept
{
	m_ptr++;
	return *this;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ConstIterator::ConstIterator htools::maths::Vector<T, dimension>::ConstIterator::operator++(int) noexcept
{
	ConstIterator tmp = *this;
	m_ptr++;
	return tmp;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ConstIterator::ConstIterator& htools::maths::Vector<T, dimension>::ConstIterator::operator--() noexcept
{
	m_ptr--;
	return *this;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ConstIterator::ConstIterator htools::maths::Vector<T, dimension>::ConstIterator::operator--(int) noexcept
{
	ConstIterator tmp = *this;
	m_ptr--;
	return tmp;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ConstIterator::ConstIterator& htools::maths::Vector<T, dimension>::ConstIterator::operator+=(const difference_type offset) noexcept
{
	m_ptr += offset;
	return *this;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ConstIterator::ConstIterator& htools::maths::Vector<T, dimension>::ConstIterator::operator-=(const difference_type offset) noexcept
{
	m_ptr -= offset;
	return *this;
}

template<typename T, std::size_t dimension>
inline htools::maths::Vector<T, dimension>::ConstReverseIterator::ConstReverseIterator() noexcept :
	m_ptr(nullptr)
{
}

template<typename T, std::size_t dimension>
inline htools::maths::Vector<T, dimension>::ConstReverseIterator::ConstReverseIterator(const T* ptr) noexcept :
	m_ptr(ptr)
{
}

template<typename T, std::size_t dimension>
inline const typename htools::maths::Vector<T, dimension>::ConstReverseIterator::reference htools::maths::Vector<T, dimension>::ConstReverseIterator::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T, std::size_t dimension>
inline const typename htools::maths::Vector<T, dimension>::ConstReverseIterator::pointer htools::maths::Vector<T, dimension>::ConstReverseIterator::operator->() const noexcept
{
	return m_ptr;
}

template<typename T, std::size_t dimension>
inline const typename htools::maths::Vector<T, dimension>::ConstReverseIterator::reference htools::maths::Vector<T, dimension>::ConstReverseIterator::operator[](const difference_type offset) const noexcept
{
	return *(m_ptr - offset);
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ConstReverseIterator::ConstReverseIterator& htools::maths::Vector<T, dimension>::ConstReverseIterator::operator++() noexcept
{
	m_ptr--;
	return *this;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ConstReverseIterator::ConstReverseIterator htools::maths::Vector<T, dimension>::ConstReverseIterator::operator++(int) noexcept
{
	ConstReverseIterator tmp = *this;
	m_ptr--;
	return tmp;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ConstReverseIterator::ConstReverseIterator& htools::maths::Vector<T, dimension>::ConstReverseIterator::operator--() noexcept
{
	m_ptr++;
	return *this;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ConstReverseIterator::ConstReverseIterator htools::maths::Vector<T, dimension>::ConstReverseIterator::operator--(int) noexcept
{
	ConstReverseIterator tmp = *this;
	m_ptr++;
	return tmp;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ConstReverseIterator::ConstReverseIterator& htools::maths::Vector<T, dimension>::ConstReverseIterator::operator+=(const difference_type offset) noexcept
{
	m_ptr -= offset;
	return m_ptr;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ConstReverseIterator::ConstReverseIterator& htools::maths::Vector<T, dimension>::ConstReverseIterator::operator-=(const difference_type offset) noexcept
{
	m_ptr += offset;
	return *this;
}

template<typename T, std::size_t dimension>
inline htools::maths::Vector<T, dimension>::Iterator::Iterator() noexcept :
	m_ptr(nullptr)
{
}

template<typename T, std::size_t dimension>
inline htools::maths::Vector<T, dimension>::Iterator::Iterator(T* ptr) noexcept :
	m_ptr(ptr)
{
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::Iterator::reference htools::maths::Vector<T, dimension>::Iterator::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::Iterator::pointer htools::maths::Vector<T, dimension>::Iterator::operator->() const noexcept
{
	return m_ptr;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::Iterator::reference htools::maths::Vector<T, dimension>::Iterator::operator[](const difference_type offset) const noexcept
{
	return *(m_ptr + offset);
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::Iterator::Iterator& htools::maths::Vector<T, dimension>::Iterator::operator++() noexcept
{
	m_ptr++;
	return *this;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::Iterator::Iterator htools::maths::Vector<T, dimension>::Iterator::operator++(int) noexcept
{
	Iterator tmp = *this;
	m_ptr++;
	return tmp;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::Iterator::Iterator& htools::maths::Vector<T, dimension>::Iterator::operator--() noexcept
{
	m_ptr--;
	return *this;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::Iterator::Iterator htools::maths::Vector<T, dimension>::Iterator::operator--(int) noexcept
{
	Iterator tmp = *this;
	m_ptr--;
	return tmp;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::Iterator::Iterator& htools::maths::Vector<T, dimension>::Iterator::operator+=(const difference_type offset) noexcept
{
	m_ptr += offset;
	return *this;
}


template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::Iterator::Iterator& htools::maths::Vector<T, dimension>::Iterator::operator-=(const difference_type offset) noexcept
{
	m_ptr -= offset;
	return *this;
}

template<typename T, std::size_t dimension>
inline htools::maths::Vector<T, dimension>::Iterator::operator typename htools::maths::Vector<T, dimension>::ConstIterator() const noexcept
{
	return ConstIterator(m_ptr);
}

template<typename T, std::size_t dimension>
inline htools::maths::Vector<T, dimension>::ReverseIterator::ReverseIterator() noexcept :
	m_ptr(nullptr)
{
}

template<typename T, std::size_t dimension>
inline htools::maths::Vector<T, dimension>::ReverseIterator::ReverseIterator(T* ptr) noexcept :
	m_ptr(ptr)
{
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ReverseIterator::reference htools::maths::Vector<T, dimension>::ReverseIterator::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ReverseIterator::pointer htools::maths::Vector<T, dimension>::ReverseIterator::operator->() const noexcept
{
	return m_ptr;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ReverseIterator::reference htools::maths::Vector<T, dimension>::ReverseIterator::operator[](const difference_type offset) const noexcept
{
	return *(m_ptr - offset);
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ReverseIterator::ReverseIterator& htools::maths::Vector<T, dimension>::ReverseIterator::operator++() noexcept
{
	m_ptr--;
	return *this;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ReverseIterator::ReverseIterator htools::maths::Vector<T, dimension>::ReverseIterator::operator++(int) noexcept
{
	ReverseIterator tmp = *this;
	m_ptr--;
	return tmp;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ReverseIterator::ReverseIterator& htools::maths::Vector<T, dimension>::ReverseIterator::operator--() noexcept
{
	m_ptr++;
	return *this;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ReverseIterator::ReverseIterator htools::maths::Vector<T, dimension>::ReverseIterator::operator--(int) noexcept
{
	ReverseIterator tmp = *this;
	m_ptr++;
	return tmp;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ReverseIterator::ReverseIterator& htools::maths::Vector<T, dimension>::ReverseIterator::operator+=(const difference_type offset) noexcept
{
	m_ptr -= offset;
	return *this;
}

template<typename T, std::size_t dimension>
inline typename htools::maths::Vector<T, dimension>::ReverseIterator::ReverseIterator& htools::maths::Vector<T, dimension>::ReverseIterator::operator-=(const difference_type offset) noexcept
{
	m_ptr += offset;
	return *this;
}

template<typename T, std::size_t dimension>
inline htools::maths::Vector<T, dimension>::ReverseIterator::operator typename htools::maths::Vector<T, dimension>::ConstReverseIterator() const noexcept
{
	return ConstReverseIterator(m_ptr);
}*/