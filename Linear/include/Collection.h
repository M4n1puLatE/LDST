#pragma once
#include <concepts>
namespace Collection
{
	template<typename T>
	concept ACollcetion = requires(T& o)
	{
		{o.size()}->std::same_as<size_t>;
		{
			o.get(0)
		}->std::same_as<T>;
		{
			o.set(0, T())
		}->std::same_as<bool>;
		{
			o.empty()
		}->std::same_as<bool>;
	};
	class Collcetion
	{

	};
}
