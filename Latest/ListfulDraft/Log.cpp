#include "Log.h"

Log::Log(void) {
}


Log::~Log(void) {
}

void Log::clear() {
	std::ofstream file;
	file.open("log.txt", std::ios::trunc);
	file << "Log sequence: \n";
	file.close();
}

void Log::log(std::string input) {
	file.open("log.txt", std::ios::app);

	file << input << "\n";

	file.close();
}

void Log::endLog() {
	file.open("log.txt", std::ios::app);

	file << "\n";

	file.close();
}