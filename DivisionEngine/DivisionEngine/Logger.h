#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger
{
public:
	Logger();
	~Logger();
	void logInfo(const std::string& file, const int& line, const std::string& message);
	void logWarning(const std::string& file, const int& line, const std::string& message);
	void logError(const std::string& file, const int& line, const std::string& message);
private:
	std::ofstream logFile_;
	std::string filePath_;
	std::string getLog(const std::string& level, const std::string& msg);
};


#endif // !LOGGER_H
