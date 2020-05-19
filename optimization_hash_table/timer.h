#ifndef HASH_TABLE_TIMER_H
#define HASH_TABLE_TIMER_H

#include <chrono>

class Timer
{
public:
	explicit Timer() :
	    beg_(clock_t::now())
	{}

	void reset()
	{
		beg_ = clock_t::now();
	}

	[[nodiscard]]
	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - beg_).count();
	}

	~Timer()
    {
	    fprintf(stderr, "all time of func = %.3f\n", elapsed());
	    reset();
    }

private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration< double, std::ratio<1> >;

	std::chrono::time_point<clock_t> beg_;
};

#endif //HASH_TABLE_TIMER_H
