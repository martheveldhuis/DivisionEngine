#include "Clock.h"



void Clock::start()
{
	if (running_) {
		return;
	}

	// Initialize clock at current time
	startTime_ = lastPollTime_ = clock();
	running_ = true;
}

void Clock::reset()
{
	runTime_ = 0;
	lastRunIncrement_ = 0;

	running_ = false;
}

void Clock::stop()
{
	if (!running_)
		return;

	// update runTime_
	getRuntime();

	running_ = false;
}

clock_t Clock::poll()
{
	if (!running_)
		return 0;
	clock_t currentTime = clock();
	
	clock_t passedTime = currentTime - lastPollTime_;
	
	lastPollTime_ = currentTime;
	return passedTime;
}

clock_t Clock::getRuntime()
{
	if (!running_)
		return runTime_;

	if (lastRunIncrement_ == 0) {
		lastRunIncrement_ = startTime_;
	}

	clock_t currentTime = clock();

	runTime_ += currentTime - lastRunIncrement_;

	lastRunIncrement_ = currentTime;

	return runTime_;
}
