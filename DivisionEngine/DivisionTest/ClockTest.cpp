#include "CppUnitTest.h"
#include "Clock.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Division;

namespace DivisionTest
{

	TEST_CLASS(ClockTest)
	{
	public:

		TEST_METHOD(testClockStart)
		{
			Clock clock;

			clock.start();

			Assert::IsTrue(clock.isRunning());
		}

		TEST_METHOD(testClockPoll)
		{
			Clock clock;

			clock.start();

			// Sleep for 1000 ms.
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			// Retrieve the time that has past.
			int timePast = clock.poll();

			// Check if the time is between a certain timespan.
			// Usually the past time will be 1001 ms. For cpu-threading
			// priority delay occasions we will allow for a 5ms delay.
			int isBetween = 1000 <= timePast && timePast < 1005;

			Assert::IsTrue(isBetween);
		}



		TEST_METHOD(testClockStop)
		{
			Clock clock;

			clock.start();
			clock.stop();

			Assert::IsFalse(clock.isRunning());
		}



		TEST_METHOD(testClockRuntime)
		{
			Clock clock;

			clock.start();

			// Sleep for 500 ms.
			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			clock.stop();

			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			clock.start();

			// Sleep for 500 ms.
			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			clock.stop();

			int timePast = clock.getRuntime();

			int isBetween = 1000 <= timePast && timePast < 1005;

			Assert::IsTrue(isBetween);
		}



		TEST_METHOD(testClockReset)
		{
			Clock clock;

			clock.start();

			// Sleep for 500 ms.
			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			clock.stop();
			clock.reset();

			int timePast = clock.getRuntime();

			Assert::AreEqual(0, timePast);
		}
	};
}