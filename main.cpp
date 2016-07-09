#include <iostream>
#include <sstream>
#include <exception>

#include "rules/rule_executor_builder.hpp"

using std::string;
typedef std::numeric_limits<uint16_t> limits16;

string showHelp();

bool in_string(const char * const src, const char str);

int main(int argc, char *argv[]) {
	
	RuleExecutorBuilder reb;
	bool isShowHelp = false;
	bool isError = false;
	string result;
	
	reb.addAscii()
		.addDigits();

	if (argc == 1) {
		isShowHelp = true;
	}

	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			// -h
			if (in_string(argv[i], 'h')) {
				isShowHelp = true;
				break;
			}

			// -r [rule]
			if (in_string(argv[i], 'r')) {
				if ((i + 1) < argc) {
					reb.fromRule(argv[i + 1]);
				} else {
					isError = true;
					result = "-r expects a rule.";
				}
				break;
			}

			// -s 
			if (in_string(argv[i], 's')) {
				reb.addSpecialCharacters();
			}

			// -l [integer]
			if (in_string(argv[i], 'l')) {
				if ((i + 1) < argc) {
					int realVal = 0;
					try {
						realVal = std::stoi(argv[i + 1]);
					}
					catch (...) {
						isError = true;
						result = "-l received invalid integer.";
						break;
					}

					if (realVal < limits16::min() && realVal > limits16::max()) {
						isError = true;
						result = "-l received invalid integer.";
						break;
					}

					uint16_t val = static_cast<uint16_t>(realVal);
					reb.setLength(val);
					i++;
				} else {
					isError = true;
					result = "-l expects an integer.";
					break;
				}
			}
		}
	}

	if (isError) {
		std::cout << result << std::endl;
		std::cout << "Use -h to get a list of the options" << std::endl;
		return 1;
	}

	result = reb.getExecutor().executeAll();

	if (isShowHelp) {
		result = showHelp();
	}

	std::cout << result;

	return 0;
}

bool in_string(const char * const src, const char c) {
	if (src == nullptr) return false;

	for (const char *it = src; *it != '\0'; ++it) {
		if (*it == c) return true;
	}

	return false;
}

/**
 * Shows help.
 * -h
 */
string showHelp() {
	std::stringstream out;
	out << "Simple-Pass - Password generator." << std::endl;
	out << "Git repo: https://github.com/mrtryhard/simplepass" << std::endl;
	out << "Documentation: https://github.com/mrtryhard/simplepass/wiki" << std::endl;
	out << std::endl;
	out << "Parameters:" << std::endl;

	out << "\t" << "-l [len]" << "\t";
	out << "Defines password's length." << std::endl << std::endl;

	out << "\t" << "-s" << "\t\t";
	out << "Allows special characters." << std::endl << std::endl;

	out << "\t" << "-r [rule]" << "\t";
	out << "Applies a regex-like rule to generate password. Disregards -l and -s.";
	out << std::endl;

	return out.str();
}
