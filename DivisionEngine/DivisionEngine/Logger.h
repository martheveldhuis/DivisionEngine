#ifndef LOGGER_H
#define LOGGER_H
#define logError(msg) log(msg, __TIME__, "error", __FILE__, __FUNCTION__, __LINE__)
#define logWarning(msg) log(msg, __TIME__, "warning", __FILE__, __FUNCTION__, __LINE__)
#define logInfo(msg) log(msg, __TIME__, "info", __FILE__, __FUNCTION__, __LINE__)

#include <fstream>
#include <string>

class Logger
{
public:
	Logger();
	~Logger();
	void log(const std::string& msg, const std::string& time, const std::string& logtype, const char *file, const char *function, const int& line);
private:
	std::ofstream logFile_;
	std::string filePath_;
	std::string getLog(const std::string& level, const std::string& msg);
};


#endif // !LOGGER_H
