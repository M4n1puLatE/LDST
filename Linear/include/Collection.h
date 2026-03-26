#pragma once
#include <concepts>
namespace Collection
{

	template<class ACollection, class DataType>
	class Collection
	{
		ACollection* m_this;

		void init()
		{
			m_this = static_cast<ACollection*>(this);
		}
	protected:
		size_t m_size;
		
        Collection()
        {
			init();
        }
		Collection(const Collection& other) noexcept
			:m_size(other.size())
        {
			init();
        }
		Collection(const size_t size) noexcept
			:m_size(size)
        {
			init();
        }
	public:
		size_t size() const noexcept
		{
			return m_size;
		}
		bool empty() const noexcept
		{
			return m_size == 0;
		}
		bool assign(const Collection& target)
		{
			return m_this->assign(target);
		}
		bool contains(const DataType& data)
		{
			return m_this->contains(data);
		}
        const DataType& get(const size_t index)const
		{
			return m_this->get(index);
		}
		bool equals(const Collection& target)const
		{
			for (size_t i = 0; i < m_this.size(); i++)
			{
				if (target.get(i) != get(i))
					return false;
			}
			return true;
		}
		void clear()
		{
			return m_this->clear();
		}
		bool set(size_t pos, const DataType& data)
		{
			return m_this->set(pos, data);
		}

	};
}
