#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>
#include <iostream>
#include <string_view>

template <class DURATION_TYPE = std::chrono::nanoseconds>
class Timer {
public:
	Timer(const std::string_view name = "Timer", std::ostream& out = std::cout) noexcept
		: out_(out), name_(name), start_(std::chrono::high_resolution_clock::now()) {}

	void printTime() const noexcept {
		out_ << *this << '\n';
	}

	int64_t getTime() const noexcept {
		return std::chrono::duration_cast<DURATION_TYPE>(std::chrono::high_resolution_clock::now() - start_).count();
	}

	std::string_view getName() const noexcept { return name_; }

	constexpr const char* getPostfix() const noexcept {
		if constexpr (std::is_same<DURATION_TYPE, std::chrono::nanoseconds>::value) {
			return " ns";
		} else if constexpr (std::is_same<DURATION_TYPE, std::chrono::microseconds>::value) {
			return " us";
		} else if constexpr (std::is_same<DURATION_TYPE, std::chrono::milliseconds>::value) {
			return " ms";
		} else if constexpr (std::is_same<DURATION_TYPE, std::chrono::seconds>::value) {
			return " s";
		} else if constexpr (std::is_same<DURATION_TYPE, std::chrono::minutes>::value) {
			return " min";
		} else if constexpr (std::is_same<DURATION_TYPE, std::chrono::hours>::value) {
			return " h";
		}
	}

	template <class FRIEND_DURATION_TYPE>
	friend std::ostream& operator<<(std::ostream& out, const Timer<FRIEND_DURATION_TYPE>& timer) noexcept;

private:
	const std::string_view name_;
	const std::chrono::high_resolution_clock::time_point start_;
	std::ostream& out_;

};

template <class DURATION_TYPE>
std::ostream& operator<<(std::ostream& out, const Timer<DURATION_TYPE>& timer) noexcept {
	auto time = timer.getTime();
	out << timer.getName() << ": " << time << timer.getPostfix();
	return out;
}

template <class DURATION_TYPE = std::chrono::nanoseconds>
class ScopedTimer : public Timer<DURATION_TYPE> {
public:
	ScopedTimer(std::string_view name = "Timer", std::ostream& out = std::cout) noexcept 
		: Timer<DURATION_TYPE>(name, out) {}

	~ScopedTimer() {
		this->printTime();
	}
};

#endif
