#pragma once
#include <concepts> // 引入 concepts 头文件
#define DYNAMIC template<typename T>


template<std::default_initializable T>
concept Container =
std::default_initializable<T> &&           // 默认构造函数
std::copy_constructible<T> &&              // 拷贝构造函数
std::move_constructible<T> &&              // 移动构造函数
	requires(const T & a, const T & b)
{
	{
		a == b
	} -> std::convertible_to<bool>;  // 相等比较
	{
		a != b
	} -> std::convertible_to<bool>;  // 不等比较
	{
		a < b
	}  -> std::convertible_to<bool>;  // 小于比较
	{
		a <= b
	} -> std::convertible_to<bool>;  // 小于等于比较
	{
		a > b
	}  -> std::convertible_to<bool>;  // 大于比较
	{
		a >= b
	} -> std::convertible_to<bool>;  // 大于等于比较
};
#define CONTAINER template<Container T>
namespace Collection
{
	CONTAINER
	class Node
	{
		T m_data;
		T* m_next;

	public:
		Node()
			: m_next(nullptr)
		{}
		Node(const T& data)
			:m_data(data),m_next(nullptr)
		{}
		Node(Node&& node) noexcept
			:m_data(std::move(node.m_data)), m_next(node.m_next)
		{
			node.m_next = nullptr;
		}
		Node(Node* prev, Node* next)
			:m_next(next)
		{
			prev->m_next = this;
		}
		Node(const T& data,Node* prev, Node* next)
			:m_data(data),m_next(next)
		{
			prev->m_next = this;
		}
		T* next()
		{
			return m_next;
		}
		[[nodiscard]]
		bool hasNext()const
		{
			return m_next != nullptr;
		}
		void setNext(T* next)
		{
			m_next = next;
		}
		void update(const T& data)
		{
			m_data = data;
		}
		void moveData(T&& data)
		{
			m_data = std::move(data);
		}
		[[nodiscard]]
		size_t count()const
		{
			size_t count = 0;
			auto tempPtr = m_next;
			while (tempPtr != nullptr)
			{
                count++;
				tempPtr = tempPtr->next();
			}
			return count;
		}
		T& get() const
		{
			return m_data;
		}
		T& get()
		{
			return m_data;
		}
		Node* unlink()
		{
			auto tempPtr = m_next;
			m_next = nullptr;
			return tempPtr;
		}
		operator T&()
		{
			return m_data;
		}
		operator const T&() const
		{
			return m_data;
		}
		Node& operator=(Node&& node) noexcept
		{
			m_data = std::move(node.m_data);
			m_next = node.m_next;
			node.m_next = nullptr;
			return *this;
		}
		Node& operator=(Node* next)
		{
			setNext(next);
			return *this;
		}
	};

}