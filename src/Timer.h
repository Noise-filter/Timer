#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>
#include <iostream>
#include <string_view>

template <class DURATION_TYPE = std::chrono::nanoseconds>
class Timer {
public:
	constexpr Timer(std::string_view name = "Timer") noexcept : name_(name), start_(std::chrono::high_resolution_clock::now()) {}

	constexpr void printTime() const noexcept {
		std::cout << *this << std::endl;
	}

	constexpr int64_t getTime() const noexcept {
		return std::chrono::duration_cast<DURATION_TYPE>(std::chrono::high_resolution_clock::now() - start_).count();
	}

	template <class FRIEND_DURATION_TYPE>
	friend std::ostream& operator<<(std::ostream& out, const Timer<FRIEND_DURATION_TYPE>& timer) noexcept;

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

	const std::string_view& getName() const noexcept { return name_; }

private:
	std::string_view name_;
	std::chrono::high_resolution_clock::time_point start_;

};

template <class DURATION_TYPE>
std::ostream& operator<<(std::ostream& out, const Timer<DURATION_TYPE>& timer) noexcept {
	auto time = timer.getTime();
	out << timer.getName() << ": " << time << timer.getPostfix();
	return out;
}

#endif