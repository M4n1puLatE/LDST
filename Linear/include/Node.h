#pragma once
#include <concepts> // 引入 concepts 头文件
#define DYNAMIC template<typename T>


template<std::default_initializable T>
concept Container =
std::constructible_from<T, const T&>&& // 可拷贝构造
std::constructible_from<T, T&&>;
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
			: m_next(nullptr)
		{
			m_data = data;
		}
		Node(Node&& node) noexcept
			:m_data(std::move(node.m_data)),m_next(node.m_next)
		{
			node.m_next = nullptr;
		}
		T* next()
		{
			return m_next;
		}
		bool hasNext()
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
		int count()const
		{
			int count = 0;
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
	};

}