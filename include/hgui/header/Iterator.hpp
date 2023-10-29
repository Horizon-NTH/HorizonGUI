#pragma once

#include "Include.h"

namespace hgui::kernel
{
	template<typename T>
	class ConstIterator
	{
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = const T;
		using pointer = const T*;
		using reference = const T&;

	public:
		ConstIterator() noexcept;

		explicit ConstIterator(const T* ptr) noexcept;

		reference operator*() const noexcept;

		pointer operator->() const noexcept;

		reference operator[](const difference_type offset) const noexcept;

		ConstIterator<T>& operator++() noexcept;

		ConstIterator<T> operator++(int) noexcept;

		ConstIterator<T>& operator--() noexcept;

		ConstIterator<T> operator--(int) noexcept;

		ConstIterator<T>& operator+=(const difference_type offset) noexcept;

		friend inline ConstIterator<T> operator+(const difference_type offset, ConstIterator<T> it) noexcept
		{
			return it += offset;
		}

		friend inline ConstIterator<T> operator+(ConstIterator<T> it, const difference_type offset) noexcept
		{
			return it += offset;
		}

		ConstIterator<T>& operator-=(const difference_type offset) noexcept;

		friend inline ConstIterator<T> operator-(const difference_type offset, ConstIterator<T> it) noexcept
		{
			return it -= offset;
		}

		friend inline ConstIterator<T> operator-(ConstIterator<T> it, const difference_type offset) noexcept
		{
			return it -= offset;
		}

		friend inline bool operator==(const ConstIterator<T>& lhs, const ConstIterator<T>& rhs) noexcept
		{
			return lhs.m_ptr == rhs.m_ptr;
		}

		friend inline bool operator!=(const ConstIterator<T>& lhs, const ConstIterator<T>& rhs) noexcept
		{
			return lhs.m_ptr != rhs.m_ptr;
		}

		friend inline bool operator<(const ConstIterator<T>& lhs, const ConstIterator<T>& rhs) noexcept
		{
			return lhs.m_ptr < rhs.m_ptr;
		}

		friend inline bool operator<=(const ConstIterator<T>& lhs, const ConstIterator<T>& rhs) noexcept
		{
			return lhs.m_ptr <= rhs.m_ptr;
		}

		friend inline bool operator>(const ConstIterator<T>& lhs, const ConstIterator<T>& rhs) noexcept
		{
			return lhs.m_ptr > rhs.m_ptr;
		}

		friend inline bool operator>=(const ConstIterator<T>& lhs, const ConstIterator<T>& rhs) noexcept
		{
			return lhs.m_ptr >= rhs.m_ptr;
		}

	private:
		pointer m_ptr;
	};

	template<typename T>
	class ConstReverseIterator
	{
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = const T;
		using pointer = const T*;
		using reference = const T&;

	public:
		ConstReverseIterator() noexcept;

		explicit ConstReverseIterator(const T* ptr) noexcept;

		reference operator*() const noexcept;

		pointer operator->() const noexcept;

		reference operator[](const difference_type offset) const noexcept;

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

	template<typename T>
	class Iterator
	{
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

	public:
		Iterator() noexcept;

		explicit Iterator(T* ptr) noexcept;

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

	protected:
		pointer m_ptr;
	};

	template<typename T>
	class ReverseIterator
	{
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

	public:
		ReverseIterator() noexcept;

		explicit ReverseIterator(T* ptr) noexcept;

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

	private:
		pointer m_ptr;
	};
}

template<typename T>
inline hgui::kernel::ConstIterator<T>::ConstIterator() noexcept : m_ptr(nullptr)
{}

template<typename T>
inline hgui::kernel::ConstIterator<T>::ConstIterator(const T* ptr) noexcept : m_ptr(ptr)
{}

template<typename T>
inline typename hgui::kernel::ConstIterator<T>::reference hgui::kernel::ConstIterator<T>::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T>
inline typename hgui::kernel::ConstIterator<T>::pointer hgui::kernel::ConstIterator<T>::operator->() const noexcept
{
	return m_ptr;
}

template<typename T>
inline typename hgui::kernel::ConstIterator<T>::reference hgui::kernel::ConstIterator<T>::operator[](
	const difference_type offset) const noexcept
{
	return *(m_ptr + offset);
}

template<typename T>
inline typename hgui::kernel::ConstIterator<T>& hgui::kernel::ConstIterator<T>::operator++() noexcept
{
	++m_ptr;
	return *this;
}

template<typename T>
inline typename hgui::kernel::ConstIterator<T> hgui::kernel::ConstIterator<T>::operator++(int) noexcept
{
	ConstIterator<T> tmp = *this;
	++m_ptr;
	return tmp;
}

template<typename T>
inline typename hgui::kernel::ConstIterator<T>& hgui::kernel::ConstIterator<T>::operator--() noexcept
{
	--m_ptr;
	return *this;
}

template<typename T>
inline typename hgui::kernel::ConstIterator<T> hgui::kernel::ConstIterator<T>::operator--(int) noexcept
{
	ConstIterator<T> tmp = *this;
	--m_ptr;
	return tmp;
}

template<typename T>
inline typename hgui::kernel::ConstIterator<T>& hgui::kernel::ConstIterator<T>::operator+=(
	const difference_type offset) noexcept
{
	m_ptr += offset;
	return *this;
}

template<typename T>
inline typename hgui::kernel::ConstIterator<T>& hgui::kernel::ConstIterator<T>::operator-=(
	const difference_type offset) noexcept
{
	m_ptr -= offset;
	return *this;
}

template<typename T>
inline hgui::kernel::ConstReverseIterator<T>::ConstReverseIterator() noexcept : m_ptr(nullptr)
{}

template<typename T>
inline hgui::kernel::ConstReverseIterator<T>::ConstReverseIterator(const T* ptr) noexcept : m_ptr(ptr)
{}

template<typename T>
inline typename hgui::kernel::ConstReverseIterator<T>::reference hgui::kernel::ConstReverseIterator<T>::operator
*() const noexcept
{
	return *m_ptr;
}

template<typename T>
inline typename hgui::kernel::ConstReverseIterator<T>::pointer hgui::kernel::ConstReverseIterator<T>::operator
->() const noexcept
{
	return m_ptr;
}

template<typename T>
inline typename hgui::kernel::ConstReverseIterator<T>::reference hgui::kernel::ConstReverseIterator<T>::operator[](
	const difference_type offset) const noexcept
{
	return *(m_ptr - offset);
}

template<typename T>
inline typename hgui::kernel::ConstReverseIterator<T>::ConstReverseIterator& hgui::kernel::ConstReverseIterator<
	T>::operator++() noexcept
{
	--m_ptr;
	return *this;
}

template<typename T>
inline typename hgui::kernel::ConstReverseIterator<T>::ConstReverseIterator hgui::kernel::ConstReverseIterator<
	T>::operator++(int) noexcept
{
	ConstReverseIterator tmp = *this;
	--m_ptr;
	return tmp;
}

template<typename T>
inline typename hgui::kernel::ConstReverseIterator<T>::ConstReverseIterator& hgui::kernel::ConstReverseIterator<
	T>::operator--() noexcept
{
	++m_ptr;
	return *this;
}

template<typename T>
inline typename hgui::kernel::ConstReverseIterator<T>::ConstReverseIterator hgui::kernel::ConstReverseIterator<
	T>::operator--(int) noexcept
{
	ConstReverseIterator tmp = *this;
	++m_ptr;
	return tmp;
}

template<typename T>
inline typename hgui::kernel::ConstReverseIterator<T>::ConstReverseIterator& hgui::kernel::ConstReverseIterator<
	T>::operator+=(const difference_type offset) noexcept
{
	m_ptr -= offset;
	return m_ptr;
}

template<typename T>
inline typename hgui::kernel::ConstReverseIterator<T>::ConstReverseIterator& hgui::kernel::ConstReverseIterator<
	T>::operator-=(const difference_type offset) noexcept
{
	m_ptr += offset;
	return *this;
}

template<typename T>
inline hgui::kernel::Iterator<T>::Iterator() noexcept : m_ptr(nullptr)
{}

template<typename T>
inline hgui::kernel::Iterator<T>::Iterator(T* ptr) noexcept : m_ptr(ptr)
{}

template<typename T>
inline typename hgui::kernel::Iterator<T>::reference hgui::kernel::Iterator<T>::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T>
inline typename hgui::kernel::Iterator<T>::pointer hgui::kernel::Iterator<T>::operator->() const noexcept
{
	return m_ptr;
}

template<typename T>
inline typename hgui::kernel::Iterator<T>::reference hgui::kernel::Iterator<T>::operator[](
	const difference_type offset) const noexcept
{
	return *(m_ptr + offset);
}

template<typename T>
inline typename hgui::kernel::Iterator<T>::Iterator& hgui::kernel::Iterator<T>::operator++() noexcept
{
	++m_ptr;
	return *this;
}

template<typename T>
inline typename hgui::kernel::Iterator<T>::Iterator hgui::kernel::Iterator<T>::operator++(int) noexcept
{
	Iterator tmp = *this;
	++m_ptr;
	return tmp;
}

template<typename T>
inline typename hgui::kernel::Iterator<T>::Iterator& hgui::kernel::Iterator<T>::operator--() noexcept
{
	--m_ptr;
	return *this;
}

template<typename T>
inline typename hgui::kernel::Iterator<T>::Iterator hgui::kernel::Iterator<T>::operator--(int) noexcept
{
	Iterator tmp = *this;
	--m_ptr;
	return tmp;
}

template<typename T>
inline typename hgui::kernel::Iterator<T>::Iterator& hgui::kernel::Iterator<T>::operator+=(
	const difference_type offset) noexcept
{
	m_ptr += offset;
	return *this;
}

template<typename T>
inline typename hgui::kernel::Iterator<T>::Iterator& hgui::kernel::Iterator<T>::operator-=(
	const difference_type offset) noexcept
{
	m_ptr -= offset;
	return *this;
}

template<typename T>
inline hgui::kernel::ReverseIterator<T>::ReverseIterator() noexcept : m_ptr(nullptr)
{}

template<typename T>
inline hgui::kernel::ReverseIterator<T>::ReverseIterator(T* ptr) noexcept : m_ptr(ptr)
{}

template<typename T>
inline typename hgui::kernel::ReverseIterator<T>::reference hgui::kernel::ReverseIterator<T>::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T>
inline typename hgui::kernel::ReverseIterator<T>::pointer hgui::kernel::ReverseIterator<T>::operator->() const noexcept
{
	return m_ptr;
}

template<typename T>
inline typename hgui::kernel::ReverseIterator<T>::reference hgui::kernel::ReverseIterator<T>::operator[](
	const difference_type offset) const noexcept
{
	return *(m_ptr - offset);
}

template<typename T>
inline typename hgui::kernel::ReverseIterator<T>::ReverseIterator& hgui::kernel::ReverseIterator<T>::operator++() noexcept
{
	--m_ptr;
	return *this;
}

template<typename T>
inline typename hgui::kernel::ReverseIterator<T>::ReverseIterator hgui::kernel::ReverseIterator<T>::operator++(int) noexcept
{
	ReverseIterator tmp = *this;
	--m_ptr;
	return tmp;
}

template<typename T>
inline typename hgui::kernel::ReverseIterator<T>::ReverseIterator& hgui::kernel::ReverseIterator<T>::operator--() noexcept
{
	++m_ptr;
	return *this;
}

template<typename T>
inline typename hgui::kernel::ReverseIterator<T>::ReverseIterator hgui::kernel::ReverseIterator<T>::operator--(int) noexcept
{
	ReverseIterator tmp = *this;
	++m_ptr;
	return tmp;
}

template<typename T>
inline typename hgui::kernel::ReverseIterator<T>::ReverseIterator& hgui::kernel::ReverseIterator<T>::operator+=(
	const difference_type offset) noexcept
{
	m_ptr -= offset;
	return *this;
}

template<typename T>
inline typename hgui::kernel::ReverseIterator<T>::ReverseIterator& hgui::kernel::ReverseIterator<T>::operator-=(
	const difference_type offset) noexcept
{
	m_ptr += offset;
	return *this;
}
