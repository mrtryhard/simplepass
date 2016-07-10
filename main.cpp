#include <iostream>
#include <sstream>
#include <exception>

#include "rules/rule_executor_builder.hpp"

using std::string;
typedef std::numeric_limits<uint16_t> limits16;

string showHelp(const string& command);
bool in_string(const char * const src, const char str);

int main(int argc, char *argv[]) {
	
	RuleExecutorBuilder reb;
	bool isShowHelp = false;
	bool isError = false;
	string result;
	string helpCommand;

	reb.addAscii()
		.addDigits();

	if (argc == 1) {
		isShowHelp = true;
	}

	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			// -h
			if (in_string(argv[i], 'h')) {
				if ((i + 1) < argc) {
					helpCommand = argv[i + 1];
				} 
				isShowHelp = true;
				break;
			}

			// -r [rule]
			if (in_string(argv[i], 'r')) {
				if(argc > 3) {
					isError = true;
					result = "-r option cannot be used with other options.";
					break;
				}

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
		std::cout << "Use -h to get a list of the options." << std::endl;
		return 1;
	}

	result = reb.getExecutor().executeAll();

	if (isShowHelp) {
		result = showHelp(helpCommand);
	}

	std::cout << result << std::endl;

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
 * @param command Command to get help (e.g. "-l", "-h", "-s", "-r")
 * @returns Help message.
 */
string showHelp(const string& command) {
	std::stringstream out;
	if (command == "-l") {
		out << "-l [length]" << std::endl;
		out << "Length setter. Defines the total length of the password. Overridden by -r." << std::endl;
		out << "Must be a valid integer. Between " << limits16::min() << " and ";
		out << limits16::max() << " characters inclusively." << std::endl;
		out << "Example: " << "simplepass -l 20" << std::endl;
	} else if (command == "-s") {
		out << "-s" << std::endl; 
		out << "Special characters setter. Allows to have special characters in generated password.";
		out << std::endl; 
		out << "Example: " << "simplepass -l 20 -s" << std::endl;
	} else if (command == "-r") {
		out << "-r [rule]" << std::endl;
		out << "Rules are regex-like patterns. " << std::endl; 
		out << "  [] is the range rule." << std::endl;
		out << "  {} is the quantity rule." << std::endl;
		out << "  . is the universal character (when not escaped, nor in range)." << std::endl;
		out << "  \\ is either the escaping character of the slash rule (\\W, \\w, \\s, \\S, \\., \\d, \\D)." << std::endl;
		out << "  ^ is the exclusion character (see notes)." << std::endl << std::endl;
		out << "Examples (rulse are passed between quotes):" << std::endl;
		out << "  [abc]{4}\tWill choose 4 characters being either a, b or c." << std::endl;
		out << std::endl;
		out << "  [a-z]{10}\tWill choose 10 characters ranging from a to z. All lower cases." << std::endl;
		out << std::endl;
		out << "  [A-Z0-9]{5}\tWill choose 5 characters ranging from A to Z (upper case only) and/";
		out << "or from 0 up to 9. e.g.: A1F9G ." << std::endl;
		out << std::endl;
		out << "  .{20}\t\tWill generate 20 characters including digits and special characters." << std::endl;
		out << std::endl;
		out << "  [.] or \\.\tWill generate a single dot." << std::endl;
		out << std::endl << "Notes:" << std::endl;
		out << "  - Slash rules are invalid within RangeRule (e.g. [\\da-z])." << std::endl;
		out << "  - The exclusion character works everywhere (e.g. ^a is everything but a)." << std::endl;
		out << "    ^[a-z] is everything that is not in the range (same as [^a-z])." << std::endl;
		out << "  - Escaping character \\ works everywhere." << std::endl;
	} else {
		out << "Simple-Pass - Password generator." << std::endl;
		out << "Git repo: https://github.com/mrtryhard/simplepass" << std::endl;
		out << "Documentation: https://github.com/mrtryhard/simplepass/wiki" << std::endl;
		out << std::endl;
		out << "Parameters:" << std::endl;

		out << "\t" << "-h [command]" << "\t";
		out << "Gets the command help." << std::endl << std::endl;

		out << "\t" << "-l [len]" << "\t";
		out << "Defines password's length." << std::endl << std::endl;

		out << "\t" << "-s" << "\t\t";
		out << "Allows special characters." << std::endl << std::endl;

		out << "\t" << "-r [rule]" << "\t";
		out << "Applies a regex-like rule to generate password. Disregards -l and -s.";
		out << std::endl;
	}

	return out.str();
}
