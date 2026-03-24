#pragma once
#include <concepts>
namespace Collection
{
	template<typename T>
	concept is_collection = requires(T* o)
	{
		{
			o->size()
		}->std::same_as<const size_t>;
		{
			o->get(0)
		}->std::same_as<T>;
		{
			o->set(0, T())
		}->std::same_as<bool>;
		{
			o->empty()
		}->std::same_as<bool>;
		{
			o->first()
		}->std::same_as<T>;
		{
			o->last()
		}->std::same_as<T>;
	};
	
	template<is_collection Collection>
	class CollectionOperation
	{
		Collection* m_this;

	protected:
        CollectionOperation()
        {
            m_this = static_cast<Collection*>(this);
        }
	public:
		template<is_collection Other>
		bool assign(Other target)
		{
			if (m_this->size() < target.size())
			{
				return false;
			}
			for (size_t i = 0; i < target.size(); i++)
			{
				m_this->set(i, target.get(i));
			}
			return true;
		}
        template<is_collection Other>
		bool assignTo(Other target)
		{
			if (m_this->size() > target.size())
			{
				return false;
			}
			for (size_t i = 0; i < m_this.size(); i++)
			{
				target.set(i, m_this.get(i));
			}
			return true;
		}
        template<is_collection Other>
		bool compare(Other target)const
		{
			for (size_t i = 0; i < m_this.size(); i++)
			{
				if (target.get(i)!= m_this->get(i))
					return false;
			}
			return true;
		}

	};
}
