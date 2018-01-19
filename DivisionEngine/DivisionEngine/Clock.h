#ifndef DIVISION_CLOCK_H
#define DIVISION_CLOCK_H

#include <time.h>

namespace Division
{
	/**
		A timer or clock to keep track of difference in time.
	*/
	class Clock
	{
	public:
		/**
			Start or resume the clock counter. Will reset the startTime_ to the
			current time if the clock is not running. Will reset lastPollTime_ if
			the clock was not running.

			Does nothing if the clock is already running.
		*/
		void start();
		/**
			Resets the clock. runTime_ will be set to 0. The clock will be stopped.
		*/
		void reset();
		/**
			Stops the clock counter, does not affect polling. Does nothing when
			the clock is not running.
		*/
		void stop();
		/**
			Polls for the difference between last poll and the current time. Also
			sets the lastPollTime_ to the current timestamp;
			@returns Time in ms between current time and last poll.
		*/
		clock_t poll();
		/**
			Gets the total runtime of the clock excluding the time the clock
			was stopped.
			@returns Get the total run time in ms.
		*/
		clock_t getRuntime();
		/**
			Checks whether the clock is running.
			@returns True if the clock is running, false if not.
		*/
		bool isRunning();
	private:
		clock_t startTime_;
		clock_t lastPollTime_;
		clock_t lastRunIncrement_ = 0;
		clock_t runTime_ = 0;
		bool running_ = false;
	};
}

#endif // ! DIVISION_CLOCK_H