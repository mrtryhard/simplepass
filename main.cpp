#include "parser.hpp"

#include "main.hpp"

#include <exception>
#include <iostream>
#include <cstring>

int main(int argc, char** argv)
{
	if (argc == FIRST_PARAM_POS) {
		std::cout << "Unsufficient parameters given." << std::endl;
		std::cout << help();
		return RETCODE_ERROR;
	}

	int password_length{ 0 };
	bool allow_specials{ false };
	bool is_rule{ false }, is_help{ false };
	int index = FIRST_PARAM_POS;

	auto cmdline_continue = [&index, &is_rule, &argc, &is_help]() { 
		return index < argc && false == is_rule && false == is_help; 
	};

	try {
		for ( ; cmdline_continue(); index++) {
			const char* arg = argv[index];
			
			if(same(SWITCH_SHORT_RULE, arg) || same(SWITCH_RULE, arg)) {
				is_rule = true;
			} else if (same(SWITCH_SHORT_LENGTH, arg) || same(SWITCH_LENGTH, arg)) {
				
				if (index + 1 == argc)
					throw std::exception{ "Missing length for parameter -l." };

				password_length = std::atoi(argv[index + 1]);
			} else if (same(SWITCH_SHORT_SPECIALS, arg) || same(SWITCH_SPECIALS, arg)) {
				allow_specials = true;
			} else if (same(SWITCH_SHORT_HELP, arg) || same(SWITCH_HELP, arg)) {
				is_help = true;
			}
		}

		if (is_help) {
			std::cout << help() << std::endl;
		} else if (is_rule) {
			std::cout << try_execute_rule(index, argc, argv);
		} else {
			std::cout << execute_basic(password_length, allow_specials);
		}
	} catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return RETCODE_ERROR;
	}

	return RETCODE_SUCCESS;
}

std::string execute_basic(const int length, const bool allow_specials)
{
	if(length < 1)
		throw std::exception{ "A password cannot be smaller than one (1) character long." };

	std::stringstream rule;
	rule << "[a-zA-Z";
	
	if (allow_specials) {
		rule << " -/" << ":-@" << "\\[-`" << "{-~";
	}

	rule << "]{" << length << '}';
	return execute_rule(rule.str().c_str());
}

std::string try_execute_rule(const int current_index, const int argc, char** argv)
{
	const int next_index = current_index + 1;

	if (next_index == argc)
		throw std::exception{ "Expected a rule for rule flag. Use --help." };

	return execute_rule(argv[next_index]);
}

std::string execute_rule(const char* rule)
{
	simple::parser parser{ rule };
	return parser.password();
}

bool same(const char* first, const char* second) noexcept
{
	return std::strcmp(first, second) == 0;
}

std::string help()
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
