#ifndef DIVISION_LOGGER_H
#define DIVISION_LOGGER_H

#define logError(msg) error(msg, __FILE__, __LINE__)
#define logWarning(msg) warning(msg, __FILE__, __LINE__)
#define logInfo(msg) info(msg, __FILE__, __LINE__)

#include <fstream>
#include <string>

namespace Division 
{
	/**
		File logger which can write log data to a file.
	*/
	class Logger
	{
	public:
		/**
			Create a logger by name, the name will be used to determine the file
			name to output to. The extension will be appended.
			@param name The clean filename to log to. ".log" will be appended
		*/
		Logger(std::string);
		~Logger();
		/**
			Log info with error level.
			@param msg The info message.
			@param file The file name the info originated from.
			@param line The line the log was called from.
		*/
		void error(const std::string& msg, const char *file, const int& line);
		/**
			Log info with warning level.
			@param msg The info message.
			@param file The file name the info originated from.
			@param line The line the log was called from.
		*/
		void warning(const std::string& msg, const char *file, const int& line);
		/**
			Log info with info level.
			@param msg The info message.
			@param file The file name the info originated from.
			@param line The line the log was called from.
		*/
		void info(const std::string& msg, const char *file, const int& line);
		/**
			Log info with info level.
			@param msg The info integer.
			@param file The file name the info originated from.
			@param line The line the log was called from.
		*/
		void info(const int msg, const char *file, const int& line);
	private:
		char drive_[_MAX_DRIVE];
		char dir_[_MAX_DIR];
		char fname_[_MAX_FNAME];
		char ext_[_MAX_EXT];
		std::ofstream logFile_;
		std::string filePath_;
	};
}

#endif // !DIVISION_LOGGER_H
