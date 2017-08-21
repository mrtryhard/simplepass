#include "parser.hpp"

#include <exception>
#include <iostream>
#include <iomanip>
#include <cstring>

constexpr int FIRST_PARAM_POS = 1;

bool same(const char*, const char*) noexcept;
std::string execute_basic(const int, const bool);
std::string try_execute_rule(const int, const int, char**);
std::string execute_rule(const char*);
std::string show_help();

void main(int argc, char** argv)
{
	if (argc == FIRST_PARAM_POS) {
		std::cout << "Unsufficient parameters given." << std::endl;
		std::cout << show_help();
		return;
	}

	int length{ 0 };
	bool allow_specials{ false };
	try {
		for (int index = FIRST_PARAM_POS; index < argc; index++) {
			if (same("-r", argv[index]) || same("--rule", argv[index])) {
				std::cout << try_execute_rule(index, argc, argv);
				break;
			} else if (same("-l", argv[index]) || same("--length", argv[index])) {
				if(index + 1 == argc)
					throw std::exception{ "Missing length for parameter -l." };

				length = std::atoi(argv[index + 1]);
			} else if (same("-s", argv[index]) || same("--specials", argv[index])){
				allow_specials = true;
			}
		}

		//std::cout << execute_basic(length, allow_specials);
	} catch(std::exception& ex)	{
		std::cout << ex.what() << std::endl;
	}
}

std::string execute_basic(const int length, const bool allow_specials)
{
	std::stringstream rule;
	rule << "[a-zA-Z";
	if(allow_specials) {
		rule << " -/" << ":-@" << "\\[-`" << "{-~";
	}
	rule << "]{" << length << '}';
	std::cout << rule.str() << std::endl;
	return execute_rule(rule.str().c_str());
}

std::string try_execute_rule(const int current_index, const int argc, char** argv)
{
	const int next_index = current_index + 1;

	if (next_index == argc)
		throw std::exception{"Expected a rule after the '-r' flag."};

	return execute_rule(argv[next_index]);
}

std::string execute_rule(const char* rule)
{
	simple::parser parser{ rule };
	return parser.str();
}

bool same(const char* first, const char* second) noexcept
{
	return std::strcmp(first, second) == 0;
}

std::string show_help()
{
	constexpr const char* padw = "    ";

	std::stringstream out;
	out << "simplepass" << std::endl;
	out << "mrtryhard @ mrtryhard.info" << std::endl;
	out << std::endl;
	out << "-h | --help" << std::endl;
	out << padw << "Displays help (this)." << std::endl << std::endl;
	out << "-r | --rule \"<rule>\"" << std::endl;
	out << padw << "Uses the given rule to generate password." << std::endl;
	out << padw << "<rule> is a minimalist regular expression-like syntax:" << std::endl << std::endl;
	out << padw << padw << "{<number>} | {<num_range>} represents either a fixed quantity" << std::endl;
	out << padw << padw << padw << "or a range. In case of a range, it will be randomly selected" << std::endl;
	out << padw << padw << padw << "within the bound inclusively." << std::endl << std::endl;
	out << padw << padw << "[<string>] | [<char_range>] represents a set from which a character" << std::endl;
	out << padw << padw << padw << "will be randomly selected." << std::endl << std::endl;
	out << padw << padw << "\\ is used to escape characters." << std::endl;

	return out.str();
}
