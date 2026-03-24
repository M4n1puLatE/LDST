#pragma once
#include <chrono>
namespace Util {
	using seconds = std::chrono::seconds;
	using minutes = std::chrono::minutes;
	using hours = std::chrono::hours;
	using milliseconds = std::chrono::milliseconds;
	using nanoseconds = std::chrono::nanoseconds;

	template<class TimeType>
	class Timer
	{
		TimeType m_begin;
		
	public:
		Timer()
			:m_begin(0)
		{}
		Timer(TimeType begin)
			:m_begin(begin)
		{}
		Timer(const Timer& copy)
			:m_begin(copy.m_begin)
		{
			
		}
		Timer(Timer&& move) noexcept
			:m_begin(std::move(move.m_begin))
		{
			move.reset();
		}
		bool isStarted() const
		{
			return m_begin != TimeType(0);
		}
		void start()
		{
			m_begin = Now();
		}
		void reset()
		{
			m_begin = TimeType(0);
		}
		TimeType end()
		{
			if (!isEmpty())
			{
				auto interval = Now() - m_begin;
				reset();
				return interval;
			}
			return m_begin;
		}
		bool isEmpty()const
		{
			return m_begin == TimeType(0);
		}
		TimeType get()
		{
			return m_begin;
		}
		Timer& operator=(const Timer& copy)
		{
			m_begin = copy.m_begin;
		}
		Timer& operator=(Timer&& move)noexcept
		{
			m_begin = std::move(move.m_begin);
		}
		static auto Now()
		{
			return std::chrono::duration_cast<TimeType>(std::chrono::system_clock::now().time_since_epoch());
		}

	};
}