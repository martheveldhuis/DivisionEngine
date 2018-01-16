#include "Clock.h"

namespace Division
{
	void Clock::start()
	{
		if (running_) {
			return;
		}

		// Initialize clock at current time.
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

		// Update to reset pending time. This keeps the run time valid when starting again.
		getRuntime();

		// Reset last run increment.
		lastRunIncrement_ = 0;

		running_ = false;
	}



	clock_t Clock::poll()
	{
		if (!running_)
			return 0;

		clock_t currentTime = clock();

		// Calculate the passed time since the last poll.
		clock_t passedTime = currentTime - lastPollTime_;

		// Reset the last poll time to now
		lastPollTime_ = currentTime;

		return passedTime;
	}



	clock_t Clock::getRuntime()
	{
		if (!running_)
			return runTime_;

		// In case the last increment was not set, update to the start time.
		if (lastRunIncrement_ == 0) {
			lastRunIncrement_ = startTime_;
		}

		clock_t currentTime = clock();

		// Update the runtime by adding the pending time.
		runTime_ += currentTime - lastRunIncrement_;

		// Set the last increment time to now, as to reset pending time.
		lastRunIncrement_ = currentTime;

		return runTime_;
	}
	clock_t Clock::isRunning()
	{
		return running_;
	}
}