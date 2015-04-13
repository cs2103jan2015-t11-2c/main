#include "Log.h"

void Log::clear() {
	std::ofstream file;
	std::string actualLogFileName = "log_" +_logFileName;
	file.open(actualLogFileName, std::ios::trunc);
	file << "Log sequence: \n";
	file.close();
}

void Log::log(std::string input) {
	std::ofstream file;
	std::string actualLogFileName = "log_" +_logFileName;
	file.open(actualLogFileName, std::ios::app);

	file << input << "\n";

	file.close();
}

void Log::endLog() {
	std::ofstream file;
	std::string actualLogFileName = "log_" +_logFileName;
	file.open(actualLogFileName, std::ios::app);

	file << "\n";

	file.close();
}

std::string &Log::get_logFileName() {
	return _logFileName;
}