#include "Logger.h"
#include <windows.h>

#define MAX_PATH_LEN 200

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

void Logger::log(const std::string& msg, const std::string& time, const std::string& logtype, const char *file, const char *function, const int& line)
{
	logFile_ << time << "[" << logtype << "] In file " << file << " while executing the function: " << function << " at line " << line << ": " << msg << std::endl;
}