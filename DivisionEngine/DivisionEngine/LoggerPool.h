#ifndef DIVISION_LOGGERPOOL_H
#define DIVISION_LOGGERPOOL_H

#include <unordered_map>
#include "Logger.h"
#include <string>

namespace Division
{
	/// <summary>
	/// TBA
	/// </summary>
	class LoggerPool
	{
	public:
		static LoggerPool* getInstance();
		/// <summary>Retrieve a logger. When it exists in the pool, return it.
		///	Otherwise create a new one, add it to the pool and return it.
		/// </summary>  
		static Logger* getLogger(std::string name);
		~LoggerPool();
	private:
		LoggerPool(); // private constructor
		LoggerPool(const LoggerPool&); // Prevent copy-construction
		LoggerPool& operator=(const LoggerPool&); // prevent assign
		static LoggerPool *instance_;
		static std::unordered_map<std::string, Logger*> logPool_;
	};

}

#endif // !DIVISION_LOGGERPOOL_H
