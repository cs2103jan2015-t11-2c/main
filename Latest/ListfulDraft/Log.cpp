//@author A0115871E
#include "Log.h"

void Log::clear() {
	std::ofstream file;

	file.open("log.txt", std::ios::trunc);
	file << "Log sequence: \n";

	file.close();
}

void Log::log(std::string input) {
	std::ofstream file;

	file.open("log.txt", std::ios::app);
	file << input << "\n";

	file.close();
}

void Log::endLog() {
	std::ofstream file;

	file.open("log.txt", std::ios::app);
	file << "\n";

	file.close();
}