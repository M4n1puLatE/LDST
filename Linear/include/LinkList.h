#pragma once
#include <exception>
#include <format>
#include <initializer_list>
#include <iostream>
#include "Node.h"

namespace Collection
{
	namespace Exceptions
	{
		class OutOfRangeException : public std::exception
		{
			std::string_view variable;
		public:
			OutOfRangeException(std::string_view str) noexcept
				:variable(str)
			{}
			const char* what() const noexcept override
			{
				return std::format("[OutOfRangeException] thrown by {}",variable).c_str();
			}
		};
		
	}

	
	CONTAINER
	class LinkList
	{
		size_t m_size;
        Node<T>* m_head;
        Node<T>* m_end;
	private:
		//抛出OutOfRangeException
		Node<T>* iterateUntil(size_t index)
		{
			if (index >= m_size)
                throw Exceptions::OutOfRangeException(__func__);
			else
			{
                return iterate(m_head, index);
			}
		}
		Node<T>* iterateUntil(const T& value)
		{
			return iterate(m_head, value, m_size);
		}
		static Node<T>* iterate(Node<T>* begin, size_t index)
		{
			Node<T>* iter = begin;
			for (size_t n = 0; n < index; n++)
			{
				iter = iter->next();
			}
			return iter;
		}
		static Node<T>* iterate(Node<T>* begin, const T& value, size_t size)
		{
			Node<T>* iter = begin;
			for (size_t n = 0; n < size; n++)
			{
				if (iter->get() == value)
					return iter;
				iter = iter->next();
			}
			return nullptr;
		}

		LinkList(Node<T>* head, Node<T>* end, size_t size)
			:m_size(size), m_head(head), m_end(end)
		{
		}
	public:
		LinkList()
			: m_size(0), m_head(nullptr), m_end(nullptr)
        {}
		const LinkList range(size_t begin, size_t end)
		{
            return LinkList(iterate(m_head, begin), iterate(m_head, end), end - begin);
		}
		void copy(const LinkList& object)
		{
			for (size_t i = 0; i < object.size(); i++)
                add(object[i]);
		}
		void copy(const std::initializer_list<T>& values)
		{
			for (auto& value : values)
			{
				add(value);
			}
		}
		void overwrite(const LinkList& object)
		{
			reserve(object.size());
			for (size_t i = 0; i < object.size(); i++)
			{
				get(i) = object[i];
			}
			if (m_size > object.size())
                removeFrom(object.size(), m_size - object.size());
		}
		LinkList(const LinkList& object)
			:m_size(object.m_size)
		{
			copy(object);
		}
		LinkList(const std::initializer_list<T>& values)
		{
			copy(values);
		}
		LinkList(LinkList&& move)noexcept
			: m_size(move.m_size), m_head(move.m_head),m_end(move.m_end)
		{
			move.m_head = nullptr;
			move.m_end = nullptr;
			move.m_size = 0;
		}
		//抛出OutOfRangeException
		T& get(size_t index)
		{
			return iterateUntil(index)->get();
		}
		//抛出OutOfRangeException
		const T& get(size_t index)const
		{
			return iterateUntil(index)->get();
		}
		T& add(const T& value)
		{
			if (empty())
			{
				m_head = m_end = new Node<T>(value);
			}
			else
			{
				m_end->setNext(new Node<T>(value));
                m_end = m_end->next();
			}
			m_size++;
			return last();
		}
		T& add(T&& move)
		{
			if (empty())
			{
				m_head = m_end = new Node<T>(std::move(move));
			}
			else
			{
				m_end->setNext(new Node<T>(std::move(move)));
				m_end = m_end->next();
			}
			m_size++;
			return last();
		}
		bool contains(const T& value)const
		{
			return iterateUntil(value) != nullptr;
		}
		bool insert(size_t where, const T& value)
		{
			try
			{
				if (where == 0)
				{
					add(value);
					return true;
				}

				auto ptr = iterateUntil(where);
				ptr->setNext(new Node<T>(value, ptr, ptr->next()));
				++m_size;
				return true;
			}
			catch (Exceptions::OutOfRangeException& e)
			{
				std::cerr << e.what();
				return false;
			}
		}
		bool remove(size_t where)
		{
			try
			{
				if (empty())
					return false;
				if (where == 0)
				{
					auto head = m_head;
                    m_head = head->next();
                    delete head;
					return true;
				}
                auto ptr = iterateUntil(where-1);
				auto cur = ptr->next();
				ptr->setNext(cur->next());
				delete cur;
				--m_size;
				return true;
			}
			catch (Exceptions::OutOfRangeException& e)
			{
				std::cerr << e.what();
				return false;
			}
		}
		bool removeFrom(size_t where, size_t count)
		{
			if (count == 0)
				return true;
			if (where + count > m_size)
			{
				return false;
			}
			else if (where == 0 && count == m_size)
                clear();
			Node<T>* prev = where == 0 ? m_head : iterateUntil(where-1);
            Node<T>* begin = prev->next();
			Node<T>* end = iterate(begin, count);
			prev->setNext(end->next());
			end->setNext(nullptr);
			while (begin != end)
			{
				prev = begin;
				delete prev;
                begin = begin->next();
			}
			delete end;
			return true;
		}
		void reserve(size_t size)
		{
			if (size <= m_size)
				return;
			else
			{
				for (size_t i = m_size; i < size; i++)
					add(T());
			}
		}
		T& first()
		{
			return *m_head;
		}
		T& first()const
		{
			return *m_head;
		}
        T& last()
        {
            return *m_end;
        }
		T& last()const
		{
			return *m_end;
		}
		[[nodiscard]]
		bool empty()const
		{
			return m_size == 0;
		}
		[[nodiscard]]
		size_t size() const
		{
			return m_size;
		}
		//设置所有成员变量为初始值，并回收内存
		void clear()
		{
			T* iter = m_head;
			while (m_head != m_end&&m_head != nullptr)
			{
				m_head = iter->next;
                delete iter;
			}
			delete m_end;
			m_head = nullptr;
			m_end = nullptr;
			m_size = 0;
		}
		bool set(size_t index, const T& value)
		{
			try
			{
				iterateUntil(index)->update(value);
				return true;
			}
			catch (Exceptions::OutOfRangeException& e)
			{
				std::cerr << e.what();
				return false;
			}
		}
		size_t count(const T& value)
		{
			size_t count = 0;
            for (size_t i = 0; i < m_size; i++)
            {
                if (get(i) == value)
                    count++;
            }
            return count;
		}
		//抛出OutOfRangeException
		T& operator[](size_t index)
		{
			return get(index);
		}
		//抛出OutOfRangeException
        const T& operator[](size_t index)const
        {
            return get(index);
        }
		LinkList& operator=(const LinkList& object)
		{
			if (this == &object)
				return *this;
			overwrite(object);
			return *this;
		}
		LinkList& operator=(LinkList&& object)noexcept
		{
			clear();
            m_size = object.m_size;
            m_head = object.m_head;
            m_end = object.m_end;
            object.m_size = 0;
            object.m_head = nullptr;
            object.m_end = nullptr;
			return *this;
		}

		~LinkList()
		{
			clear();
		}

	};
}
