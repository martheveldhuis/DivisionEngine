#ifndef DIVISION_LOGGER_H
#define DIVISION_LOGGER_H
#define logError(msg) error(msg, __FILE__, __LINE__)
#define logWarning(msg) warning(msg, __FILE__, __LINE__)
#define logInfo(msg) info(msg, __FILE__, __LINE__)

#include <fstream>
#include <string>

namespace Division 
{
	class Logger
	{
	public:
		Logger(std::string);
		~Logger();
		void error(const std::string& msg, const char *file, const int& line);
		void warning(const std::string& msg, const char *file, const int& line);
		void info(const std::string& msg, const char *file, const int& line);
	private:
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		std::ofstream logFile_;
		std::string filePath_;
	};
}

#endif // !DIVISION_LOGGER_H
