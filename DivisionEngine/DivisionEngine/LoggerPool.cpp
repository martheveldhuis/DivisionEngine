#include "LoggerPool.h"

namespace Division {
	
	LoggerPool::LoggerPool()
	{
	}



	LoggerPool* LoggerPool::getInstance()
	{
		static LoggerPool* instance_;
		return instance_;
	}



	Logger* Division::LoggerPool::getLogger(std::string name)
	{
		std::unordered_map<std::string, Logger*> logPool_;

		std::unordered_map<std::string, Logger*>::const_iterator found = logPool_.find(name);
		
		Logger* retrievedLogger = NULL;

		if (found == logPool_.end()) {
			retrievedLogger = new Logger(name);
			logPool_[name] = retrievedLogger;
		}
		else {
			retrievedLogger = found->second;
		}
		
		return retrievedLogger;
	}



	LoggerPool::~LoggerPool()
	{
	}

}