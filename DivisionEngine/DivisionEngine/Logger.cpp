#include "Logger.h"
#include <windows.h>

namespace Division
{
	Logger::Logger(std::string name)
	{
		CreateDirectory("logs", NULL);

		std::string fileName = "logs/" + name + ".log";

		filePath_ = fileName;

		logFile_.open(filePath_);
		logFile_ << __TIME__ << "[INFO] Logger " << name << " created" << std::endl;
	}



	Logger::~Logger()
	{
		logFile_ << __TIME__ << "[INFO] Logger destroyed" << std::endl;
		logFile_.close();
	}



	void Logger::error(const std::string& msg, const char *file, const int& line)
	{
		_splitpath_s(file, drive_, dir_, fname_, ext_);
		logFile_ << __TIME__ << "[ERROR] In file " << fname_ << ext_ << " at line " << line << ": " << msg << std::endl;
	}



	void Logger::warning(const std::string& msg, const char *file, const int& line)
	{
		_splitpath_s(file, drive_, dir_, fname_, ext_);
		logFile_ << __TIME__ << "[WARNING] In file " << fname_ << ext_ << " at line " << line << ": " << msg << std::endl;
	}



	void Logger::info(const std::string& msg, const char *file, const int& line)
	{
		_splitpath_s(file, drive_, dir_, fname_, ext_);
		logFile_ << __TIME__ << "[INFO] In file " << fname_ << ext_ << " at line " << line << ": " << msg << std::endl;
	}

	void Logger::info(const int msg, const char *file, const int& line)
	{
		_splitpath_s(file, drive_, dir_, fname_, ext_);
		logFile_ << __TIME__ << "[INFO] In file " << fname_ << ext_ << " at line " << line << ": " << msg << std::endl;
	}
}