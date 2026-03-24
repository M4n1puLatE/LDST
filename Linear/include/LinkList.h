#pragma once
#include <exception>
#include <format>
#include <initializer_list>
#include <iostream>

#include "Views.h"
#include "Node.h"

namespace Collection
{
	namespace Exceptions
	{
		class OutOfRangeException : public std::exception
		{
			mutable std::string variable;
		public:
			OutOfRangeException(std::string_view str) noexcept
				:variable(str)
			{}
			const char* what() const noexcept override
			{
				variable = std::format("[OutOfRangeException] thrown by {}\n", variable);
				return variable.c_str();
			}
		};
		
	}

	namespace Linear
	{
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
			const Node<T>* iterateUntil(size_t index)const
			{
				if (index >= m_size)
					throw Exceptions::OutOfRangeException(__func__);
				else
				{
					return iterate(m_head, index);
				}
			}
			Node<T>* iterateUntilValue(const T& value)const
			{
				return iterate(m_head, value, m_size);
			}
			std::pair<const Node<T>*, const Node<T>*> iterateInterval(size_t index, size_t end)const
			{
				if (index >= m_size || end >= m_size)
					throw Exceptions::OutOfRangeException(__func__);
				Node<T>* begin = m_head;
				size_t n = 0;
				for (; n < index; n++)
				{
					begin = begin->next();
				}
				Node<T>* finish = begin;
				for (;n < end; ++n)
				{
					finish = finish->next();
				}
				return std::make_pair(begin,finish);
			}
			std::pair<Node<T>*, Node<T>*> iterateNonInterval(size_t index, size_t end)
			{
				if (index >= m_size || end > m_size)
					throw Exceptions::OutOfRangeException(__func__);
				Node<T>* begin = m_head;
				size_t n = 0;
				for (; n < index; n++)
				{
					begin = begin->next();
				}
				Node<T>* finish = begin;
				for (; n < end; ++n)
				{
					finish = finish->next();
				}
				return std::make_pair(begin, finish);
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
			{}
		public:
			LinkList()
				: m_size(0), m_head(nullptr), m_end(nullptr)
			{}
			View::ListView<Node<T>> range(size_t begin, size_t end)
			{
				if (end >= begin && end <= m_size)
					return View::ListView<Node<T>>(iterateUntil(begin), end - begin);
				else
					return View::ListView<Node<T>>();
			}
			long long find(const T& value)
			{
				auto iter = m_head;
				long long pos = 0;
				while (iter != nullptr)
				{
					if (value == iter->get())
						return pos;
					pos++;
					iter = iter->next();
				}
				return -1;
			}
			void add(const LinkList& object)
			{
				for (size_t i = 0; i < object.size(); i++)
					add(object[i]);
			}
			void add(const std::initializer_list<T>& values)
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
				:LinkList()
			{
				overwrite(object);
			}
			LinkList(const std::initializer_list<T>& values)
				:LinkList()
			{
				add(values);
			}
			LinkList(LinkList&& move)noexcept
				: m_size(move.m_size), m_head(move.m_head), m_end(move.m_end)
			{
				move.m_head = nullptr;
				move.m_end = nullptr;
				move.m_size = 0;
			}
			LinkList(size_t size)
				:LinkList()
			{
				reserve(size);
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
				return iterateUntilValue(value) != nullptr;
			}
			bool insert(size_t where, const T& value)
			{
				try
				{
					if (where == m_size-1)
					{
						add(value);
						return true;
					}
					else if (where == 0)
					{
						if (m_head)
						{
							m_head = new Node<T>(value, nullptr, m_head);
							m_size++;
						}
						else
						{
							add(value);
						}
						return true;
					}

					auto ptr = iterateUntil(where-1);
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
					Node<T>* ptr;
					Node<T>* cur;
					if (where == 0)
					{
						cur = m_head;
						m_head = cur->next();
					}
					else
					{
						ptr = iterateUntil(where - 1);
						cur = ptr->next();
						ptr->setNext(cur->next());
						if (where == m_size - 1)
                            m_end = ptr;
					}
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
				{
					clear();
					return true;
				}				
				try
				{
					std::pair<Node<T>*, Node<T>*> interval;
					if (where == 0)
					{
						interval = iterateNonInterval(0, count-1);
						m_head = interval.second->next();
					}
					else
					{
						interval = iterateNonInterval(where - 1, where + count - 1);
					}
					auto [father, end] = interval;
					Node<T>* begin = father->next();
					father->setNext(end->next());
					end->setNext(nullptr);
					if (end == m_end)
					{
						m_end = father;
					}
					father = begin;
					while (begin != nullptr)
					{
						father = father->next();
						delete begin;

                        begin = father;
					}
					m_size -= count;
					return true;
				}
				catch (Exceptions::OutOfRangeException& e)
				{
					std::cerr << e.what();
					return false;
				}
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
				return m_size == 0 || m_head == nullptr;
			}
			[[nodiscard]]
			size_t size() const
			{
				return m_size;
			}
			//设置所有成员变量为初始值，并回收内存
			void clear()
			{
				auto* iter = m_head;
				while (iter != nullptr)
				{
					auto* next = iter->next();
					delete iter;
					iter = next;
				}
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
	
	
}
