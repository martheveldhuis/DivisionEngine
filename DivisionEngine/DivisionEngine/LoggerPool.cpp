#include "LoggerPool.h"

namespace Division {

	std::unordered_map<std::string, Logger*> LoggerPool::logPool_;

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

		std::unordered_map<std::string, Logger*>::const_iterator found = logPool_.find(name);
		
		Logger* retrievedLogger = NULL;

		if (found == logPool_.end()) {
			retrievedLogger = new Logger(name);
			logPool_.insert(std::make_pair(name, retrievedLogger));
		}
		else {
			retrievedLogger = found->second;
			retrievedLogger->logInfo("This logger already existed, retrieved from pool");
		}
		
		return retrievedLogger;
	}



	LoggerPool::~LoggerPool()
	{
	}

}