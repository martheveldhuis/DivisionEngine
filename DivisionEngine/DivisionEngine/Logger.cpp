#include "Logger.h"
#include <windows.h>

namespace Division 
{
	Logger::Logger()
	{
		CreateDirectory("logs", NULL);

		std::string fileName = "logs/division.log";

		filePath_ = fileName;

		logFile_.open(filePath_);
	}

	Logger::~Logger()
	{
		logFile_.close();
	}

	void Logger::logInfo(const std::string& file, const int& line, const std::string& message)
	{
		logFile_ << "[INFO] In file " << file << " at line " << line << ": " << message << std::endl;
	}

	void Logger::logWarning(const std::string& file, const int& line, const std::string& message)
	{
		logFile_ << "[WARNING] In file " << file << " at line " << line << ": " << message << std::endl;
	}

	void Logger::logError(const std::string& file, const int& line, const std::string& message)
	{
		logFile_ << "[ERROR] In file " << file << " at line " << line << ": " << message << std::endl;
	}
}