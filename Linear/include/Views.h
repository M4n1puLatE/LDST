#pragma once
#include <concepts>
namespace Collection
{
	namespace View
	{
		template<typename NodeType>
		concept is_node = requires(NodeType * node)
		{
			{
				node->next()
			}->std::same_as<NodeType*>;
			{
				node->get()
			};
		};
		template<is_node Node>
		class ListView
		{
			Node* m_head;
			size_t m_size;
		public:
			ListView() noexcept
				:m_head(nullptr), m_size(0)
			{}
            ListView(Node* head, size_t size) noexcept
				:m_head(head), m_size(size)
			{}
			[[nodiscard]]
            size_t size() const noexcept
			{
				return m_size;
			}
            const Node* begin() const noexcept
			{
				return m_head;
			}
			[[nodiscard]]
			bool empty() const noexcept
			{
				return m_size == 0 || m_head == nullptr;
			}
			const Node* get(size_t index) const
			{ 
				if (index < m_size && !empty())
				{
					auto cur = m_head;
					for (size_t i = 0; i < index; i++)
					{
						cur = cur->next();
					}
					return cur;
				}
				return nullptr;
			}
		};
	}
}