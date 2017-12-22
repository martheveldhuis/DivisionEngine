#ifndef DIVISION_LOGGERPOOL_H
#define DIVISION_LOGGERPOOL_H

#include <unordered_map>
#include "Logger.h"
#include <string>

namespace Division
{
	/**
		A pool which can instanciate logger objects. Loggers can be requested
		by name. Each Logger will be kept. Requesting an existing logger will
		not instanciate a new object.
	*/
	class LoggerPool
	{
	public:
		/**
			Get an instance of the loggerpool.
			@returns A logger object that can be used to log data.
		*/
		static LoggerPool* getInstance();
		/**
			Retrieve a logger. When it exists in the pool, return it.
			Otherwise create a new one, add it to the pool and return it.
			@param name The name of the file to log to.
			@returns A logger object that can be used to log data.
		*/
		static Logger* getLogger(std::string name);
		~LoggerPool();
	private:
		LoggerPool(); // private constructor for singleton
		LoggerPool(const LoggerPool&); // Prevent copy-construction
		LoggerPool& operator=(const LoggerPool&); // prevent assign
		static LoggerPool *instance_;
		static std::unordered_map<std::string, Logger*> logPool_;
	};

}

#endif // !DIVISION_LOGGERPOOL_H
