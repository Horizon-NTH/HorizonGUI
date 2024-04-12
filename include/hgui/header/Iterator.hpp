#pragma once

#include "Include.h"

namespace hgui::kernel
{
	template<typename T>
	class ConstIterator final
	{
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = const T;
		using pointer = const T*;
		using reference = const T&;

	public:
		ConstIterator() noexcept;
		explicit ConstIterator(const T* ptr) noexcept;
		ConstIterator(const ConstIterator& iterator) noexcept = default;
		ConstIterator(ConstIterator&& iterator) noexcept = default;

		~ConstIterator() = default;

		ConstIterator& operator=(const ConstIterator& iterator) noexcept = default;
		ConstIterator& operator=(ConstIterator&& iterator) noexcept = default;

		reference operator*() const noexcept;

		pointer operator->() const noexcept;

		reference operator[](difference_type offset) const noexcept;

		ConstIterator& operator++() noexcept;

		ConstIterator operator++(int) noexcept;

		ConstIterator& operator--() noexcept;

		ConstIterator operator--(int) noexcept;

		ConstIterator& operator+=(difference_type offset) noexcept;

		friend ConstIterator operator+(const difference_type offset, ConstIterator it) noexcept
		{
			return it += offset;
		}

		friend ConstIterator operator+(ConstIterator it, const difference_type offset) noexcept
		{
			return it += offset;
		}

		ConstIterator& operator-=(difference_type offset) noexcept;

		friend ConstIterator operator-(const difference_type offset, ConstIterator it) noexcept
		{
			return it -= offset;
		}

		friend ConstIterator operator-(ConstIterator it, const difference_type offset) noexcept
		{
			return it -= offset;
		}

		friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs) noexcept
		{
			return lhs.m_ptr == rhs.m_ptr;
		}

		friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs) noexcept
		{
			return lhs.m_ptr != rhs.m_ptr;
		}

		friend bool operator<(const ConstIterator& lhs, const ConstIterator& rhs) noexcept
		{
			return lhs.m_ptr < rhs.m_ptr;
		}

		friend bool operator<=(const ConstIterator& lhs, const ConstIterator& rhs) noexcept
		{
			return lhs.m_ptr <= rhs.m_ptr;
		}

		friend bool operator>(const ConstIterator& lhs, const ConstIterator& rhs) noexcept
		{
			return lhs.m_ptr > rhs.m_ptr;
		}

		friend bool operator>=(const ConstIterator& lhs, const ConstIterator& rhs) noexcept
		{
			return lhs.m_ptr >= rhs.m_ptr;
		}

	private:
		pointer m_ptr;
	};

	template<typename T>
	class ConstReverseIterator final
	{
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = const T;
		using pointer = const T*;
		using reference = const T&;

	public:
		ConstReverseIterator() noexcept;
		explicit ConstReverseIterator(const T* ptr) noexcept;
		ConstReverseIterator(const ConstReverseIterator& iterator) noexcept = default;
		ConstReverseIterator(ConstReverseIterator&& iterator) noexcept = default;

		~ConstReverseIterator() = default;

		ConstReverseIterator& operator=(const ConstReverseIterator& iterator) noexcept = default;
		ConstReverseIterator& operator=(ConstReverseIterator&& iterator) noexcept = default;

		reference operator*() const noexcept;

		pointer operator->() const noexcept;

		reference operator[](difference_type offset) const noexcept;

		ConstReverseIterator& operator++() noexcept;

		ConstReverseIterator operator++(int) noexcept;

		ConstReverseIterator& operator--() noexcept;

		ConstReverseIterator operator--(int) noexcept;

		ConstReverseIterator& operator+=(difference_type offset) noexcept;

		friend ConstReverseIterator operator+(const difference_type offset, ConstReverseIterator it) noexcept
		{
			return it += offset;
		}

		friend ConstReverseIterator operator+(ConstReverseIterator it, const difference_type offset) noexcept
		{
			return it += offset;
		}

		ConstReverseIterator& operator-=(difference_type offset) noexcept;

		friend ConstReverseIterator operator-(const difference_type offset, ConstReverseIterator it) noexcept
		{
			return it -= offset;
		}

		friend ConstReverseIterator operator-(ConstReverseIterator it, const difference_type offset) noexcept
		{
			return it -= offset;
		}

		friend bool operator==(const ConstReverseIterator& lhs, const ConstReverseIterator& rhs) noexcept
		{
			return lhs.m_ptr == rhs.m_ptr;
		}

		friend bool operator!=(const ConstReverseIterator& lhs, const ConstReverseIterator& rhs) noexcept
		{
			return lhs.m_ptr != rhs.m_ptr;
		}

		friend bool operator<(const ConstReverseIterator& lhs, const ConstReverseIterator& rhs) noexcept
		{
			return lhs.m_ptr > rhs.m_ptr;
		}

		friend bool operator<=(const ConstReverseIterator& lhs, const ConstReverseIterator& rhs) noexcept
		{
			return lhs.m_ptr >= rhs.m_ptr;
		}

		friend bool operator>(const ConstReverseIterator& lhs, const ConstReverseIterator& rhs) noexcept
		{
			return lhs.m_ptr < rhs.m_ptr;
		}

		friend bool operator>=(const ConstReverseIterator& lhs, const ConstReverseIterator& rhs) noexcept
		{
			return lhs.m_ptr <= rhs.m_ptr;
		}

	private:
		pointer m_ptr;
	};

	template<typename T>
	class Iterator final
	{
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

	public:
		Iterator() noexcept;
		explicit Iterator(T* ptr) noexcept;
		Iterator(const Iterator& iterator) noexcept = default;
		Iterator(Iterator&& iterator) noexcept = default;

		~Iterator() = default;

		Iterator& operator=(const Iterator& iterator) noexcept = default;
		Iterator& operator=(Iterator&& iterator) noexcept = default;

		reference operator*() const noexcept;

		pointer operator->() const noexcept;

		reference operator[](difference_type offset) const noexcept;

		Iterator& operator++() noexcept;

		Iterator operator++(int) noexcept;

		Iterator& operator--() noexcept;

		Iterator operator--(int) noexcept;

		Iterator& operator+=(difference_type offset) noexcept;

		friend Iterator operator+(const difference_type offset, Iterator it) noexcept
		{
			return it += offset;
		}

		friend Iterator operator+(Iterator it, const difference_type offset) noexcept
		{
			return it += offset;
		}

		Iterator& operator-=(difference_type offset) noexcept;

		friend Iterator operator-(const difference_type offset, Iterator it) noexcept
		{
			return it -= offset;
		}

		friend Iterator operator-(Iterator it, const difference_type offset) noexcept
		{
			return it -= offset;
		}

		friend bool operator==(const Iterator& lhs, const Iterator& rhs) noexcept
		{
			return lhs.m_ptr == rhs.m_ptr;
		}

		friend bool operator!=(const Iterator& lhs, const Iterator& rhs) noexcept
		{
			return lhs.m_ptr != rhs.m_ptr;
		}

		friend bool operator<(const Iterator& lhs, const Iterator& rhs) noexcept
		{
			return lhs.m_ptr < rhs.m_ptr;
		}

		friend bool operator<=(const Iterator& lhs, const Iterator& rhs) noexcept
		{
			return lhs.m_ptr <= rhs.m_ptr;
		}

		friend bool operator>(const Iterator& lhs, const Iterator& rhs) noexcept
		{
			return lhs.m_ptr > rhs.m_ptr;
		}

		friend bool operator>=(const Iterator& lhs, const Iterator& rhs) noexcept
		{
			return lhs.m_ptr >= rhs.m_ptr;
		}

	protected:
		pointer m_ptr;
	};

	template<typename T>
	class ReverseIterator final
	{
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

	public:
		ReverseIterator() noexcept;
		explicit ReverseIterator(T* ptr) noexcept;
		ReverseIterator(const ReverseIterator& iterator) noexcept = default;
		ReverseIterator(ReverseIterator&& iterator) noexcept = default;

		~ReverseIterator() = default;

		ReverseIterator& operator=(const ReverseIterator& iterator) noexcept = default;
		ReverseIterator& operator=(ReverseIterator&& iterator) noexcept = default;

		reference operator*() const noexcept;

		pointer operator->() const noexcept;

		reference operator[](difference_type offset) const noexcept;

		ReverseIterator& operator++() noexcept;

		ReverseIterator operator++(int) noexcept;

		ReverseIterator& operator--() noexcept;

		ReverseIterator operator--(int) noexcept;

		ReverseIterator& operator+=(difference_type offset) noexcept;

		friend ReverseIterator operator+(const difference_type offset, ReverseIterator it) noexcept
		{
			return it += offset;
		}

		friend ReverseIterator operator+(ReverseIterator it, const difference_type offset) noexcept
		{
			return it += offset;
		}

		ReverseIterator& operator-=(difference_type offset) noexcept;

		friend ReverseIterator operator-(const difference_type offset, ReverseIterator it) noexcept
		{
			return it -= offset;
		}

		friend ReverseIterator operator-(ReverseIterator it, const difference_type offset) noexcept
		{
			return it -= offset;
		}

		friend bool operator==(const ReverseIterator& lhs, const ReverseIterator& rhs) noexcept
		{
			return lhs.m_ptr == rhs.m_ptr;
		}

		friend bool operator!=(const ReverseIterator& lhs, const ReverseIterator& rhs) noexcept
		{
			return lhs.m_ptr != rhs.m_ptr;
		}

		friend bool operator<(const ReverseIterator& lhs, const ReverseIterator& rhs) noexcept
		{
			return lhs.m_ptr > rhs.m_ptr;
		}

		friend bool operator<=(const ReverseIterator& lhs, const ReverseIterator& rhs) noexcept
		{
			return lhs.m_ptr >= rhs.m_ptr;
		}

		friend bool operator>(const ReverseIterator& lhs, const ReverseIterator& rhs) noexcept
		{
			return lhs.m_ptr < rhs.m_ptr;
		}

		friend bool operator>=(const ReverseIterator& lhs, const ReverseIterator& rhs) noexcept
		{
			return lhs.m_ptr <= rhs.m_ptr;
		}

	private:
		pointer m_ptr;
	};
}

template<typename T>
hgui::kernel::ConstIterator<T>::ConstIterator() noexcept :
	m_ptr(nullptr)
{
}

template<typename T>
hgui::kernel::ConstIterator<T>::ConstIterator(const T* ptr) noexcept :
	m_ptr(ptr)
{
}

template<typename T>
typename hgui::kernel::ConstIterator<T>::reference hgui::kernel::ConstIterator<T>::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T>
typename hgui::kernel::ConstIterator<T>::pointer hgui::kernel::ConstIterator<T>::operator->() const noexcept
{
	return m_ptr;
}

template<typename T>
typename hgui::kernel::ConstIterator<T>::reference hgui::kernel::ConstIterator<T>::operator[](const difference_type offset) const noexcept
{
	return *(m_ptr + offset);
}

template<typename T>
hgui::kernel::ConstIterator<T>& hgui::kernel::ConstIterator<T>::operator++() noexcept
{
	++m_ptr;
	return *this;
}

template<typename T>
hgui::kernel::ConstIterator<T> hgui::kernel::ConstIterator<T>::operator++(int) noexcept
{
	ConstIterator tmp = *this;
	++m_ptr;
	return tmp;
}

template<typename T>
hgui::kernel::ConstIterator<T>& hgui::kernel::ConstIterator<T>::operator--() noexcept
{
	--m_ptr;
	return *this;
}

template<typename T>
hgui::kernel::ConstIterator<T> hgui::kernel::ConstIterator<T>::operator--(int) noexcept
{
	ConstIterator tmp = *this;
	--m_ptr;
	return tmp;
}

template<typename T>
hgui::kernel::ConstIterator<T>& hgui::kernel::ConstIterator<T>::operator+=(const difference_type offset) noexcept
{
	m_ptr += offset;
	return *this;
}

template<typename T>
hgui::kernel::ConstIterator<T>& hgui::kernel::ConstIterator<T>::operator-=(const difference_type offset) noexcept
{
	m_ptr -= offset;
	return *this;
}

template<typename T>
hgui::kernel::ConstReverseIterator<T>::ConstReverseIterator() noexcept :
	m_ptr(nullptr)
{
}

template<typename T>
hgui::kernel::ConstReverseIterator<T>::ConstReverseIterator(const T* ptr) noexcept :
	m_ptr(ptr)
{
}

template<typename T>
typename hgui::kernel::ConstReverseIterator<T>::reference hgui::kernel::ConstReverseIterator<T>::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T>
typename hgui::kernel::ConstReverseIterator<T>::pointer hgui::kernel::ConstReverseIterator<T>::operator->() const noexcept
{
	return m_ptr;
}

template<typename T>
typename hgui::kernel::ConstReverseIterator<T>::reference hgui::kernel::ConstReverseIterator<T>::operator[](const difference_type offset) const noexcept
{
	return *(m_ptr - offset);
}

template<typename T>
hgui::kernel::ConstReverseIterator<T>& hgui::kernel::ConstReverseIterator<T>::operator++() noexcept
{
	--m_ptr;
	return *this;
}

template<typename T>
hgui::kernel::ConstReverseIterator<T> hgui::kernel::ConstReverseIterator<T>::operator++(int) noexcept
{
	ConstReverseIterator tmp = *this;
	--m_ptr;
	return tmp;
}

template<typename T>
hgui::kernel::ConstReverseIterator<T>& hgui::kernel::ConstReverseIterator<T>::operator--() noexcept
{
	++m_ptr;
	return *this;
}

template<typename T>
hgui::kernel::ConstReverseIterator<T> hgui::kernel::ConstReverseIterator<T>::operator--(int) noexcept
{
	ConstReverseIterator tmp = *this;
	++m_ptr;
	return tmp;
}

template<typename T>
hgui::kernel::ConstReverseIterator<T>& hgui::kernel::ConstReverseIterator<T>::operator+=(const difference_type offset) noexcept
{
	m_ptr -= offset;
	return m_ptr;
}

template<typename T>
hgui::kernel::ConstReverseIterator<T>& hgui::kernel::ConstReverseIterator<T>::operator-=(const difference_type offset) noexcept
{
	m_ptr += offset;
	return *this;
}

template<typename T>
hgui::kernel::Iterator<T>::Iterator() noexcept :
	m_ptr(nullptr)
{
}

template<typename T>
hgui::kernel::Iterator<T>::Iterator(T* ptr) noexcept :
	m_ptr(ptr)
{
}

template<typename T>
typename hgui::kernel::Iterator<T>::reference hgui::kernel::Iterator<T>::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T>
typename hgui::kernel::Iterator<T>::pointer hgui::kernel::Iterator<T>::operator->() const noexcept
{
	return m_ptr;
}

template<typename T>
typename hgui::kernel::Iterator<T>::reference hgui::kernel::Iterator<T>::operator[](const difference_type offset) const noexcept
{
	return *(m_ptr + offset);
}

template<typename T>
hgui::kernel::Iterator<T>& hgui::kernel::Iterator<T>::operator++() noexcept
{
	++m_ptr;
	return *this;
}

template<typename T>
hgui::kernel::Iterator<T> hgui::kernel::Iterator<T>::operator++(int) noexcept
{
	Iterator tmp = *this;
	++m_ptr;
	return tmp;
}

template<typename T>
hgui::kernel::Iterator<T>& hgui::kernel::Iterator<T>::operator--() noexcept
{
	--m_ptr;
	return *this;
}

template<typename T>
hgui::kernel::Iterator<T> hgui::kernel::Iterator<T>::operator--(int) noexcept
{
	Iterator tmp = *this;
	--m_ptr;
	return tmp;
}

template<typename T>
hgui::kernel::Iterator<T>& hgui::kernel::Iterator<T>::operator+=(const difference_type offset) noexcept
{
	m_ptr += offset;
	return *this;
}

template<typename T>
hgui::kernel::Iterator<T>& hgui::kernel::Iterator<T>::operator-=(const difference_type offset) noexcept
{
	m_ptr -= offset;
	return *this;
}

template<typename T>
hgui::kernel::ReverseIterator<T>::ReverseIterator() noexcept :
	m_ptr(nullptr)
{
}

template<typename T>
hgui::kernel::ReverseIterator<T>::ReverseIterator(T* ptr) noexcept :
	m_ptr(ptr)
{
}

template<typename T>
typename hgui::kernel::ReverseIterator<T>::reference hgui::kernel::ReverseIterator<T>::operator*() const noexcept
{
	return *m_ptr;
}

template<typename T>
typename hgui::kernel::ReverseIterator<T>::pointer hgui::kernel::ReverseIterator<T>::operator->() const noexcept
{
	return m_ptr;
}

template<typename T>
typename hgui::kernel::ReverseIterator<T>::reference hgui::kernel::ReverseIterator<T>::operator[](const difference_type offset) const noexcept
{
	return *(m_ptr - offset);
}

template<typename T>
hgui::kernel::ReverseIterator<T>& hgui::kernel::ReverseIterator<T>::operator++() noexcept
{
	--m_ptr;
	return *this;
}

template<typename T>
hgui::kernel::ReverseIterator<T> hgui::kernel::ReverseIterator<T>::operator++(int) noexcept
{
	ReverseIterator tmp = *this;
	--m_ptr;
	return tmp;
}

template<typename T>
hgui::kernel::ReverseIterator<T>& hgui::kernel::ReverseIterator<T>::operator--() noexcept
{
	++m_ptr;
	return *this;
}

template<typename T>
hgui::kernel::ReverseIterator<T> hgui::kernel::ReverseIterator<T>::operator--(int) noexcept
{
	ReverseIterator tmp = *this;
	++m_ptr;
	return tmp;
}

template<typename T>
hgui::kernel::ReverseIterator<T>& hgui::kernel::ReverseIterator<T>::operator+=(const difference_type offset) noexcept
{
	m_ptr -= offset;
	return *this;
}

template<typename T>
hgui::kernel::ReverseIterator<T>& hgui::kernel::ReverseIterator<T>::operator-=(const difference_type offset) noexcept
{
	m_ptr += offset;
	return *this;
}
