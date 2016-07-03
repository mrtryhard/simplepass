#include <cstring>
#include <cstdlib>
#include <cstdint>

#include <iostream>
#include <limits>
#include <string>
#include <sstream>

#include "generator.hpp"
#include "rule_executor.hpp"

using std::string;

string parseParameters(uint16_t&, bool&, const int, char**);
string parseLengthParameter(uint16_t&, char*);
string showHelp();

int main(int argc, char *argv[]) {    

    bool special = false;
    uint16_t length = 0;

    string msg = parseParameters(length, special, argc, argv);
    
    if(msg.empty()) {
        // No message
        Generator g(length, special);
        std::cout << g.generate() << std::endl;
    } else {
        // Message, output.
        std::cout << msg << std::endl;
    }
    
    return 0;
}

/**
 * Parses the command line parameters.
 * -l [integer], -s, -h 
 *
 * @param length Length recipient.
 * @param special Special character flag recipient.
 * @param argc Argument count. 
 * @param argv Arguments.
 *
 * Note: - The special character parameter (-s) is only set to true when shown.
 *       - When an invalid flag is passed, it shows help.
 *       - The help parameter (-h) cancels out everything else.
 */
string parseParameters(uint16_t &length, bool &special, const int argc, char **argv) {
    string msg;

	if (argc == 1) {
		msg = showHelp();
		return msg;
	}

	for(int i = 1; i < argc && msg.empty(); ++i) {
		if (strcmp(argv[i], "-r") == 0) {
			if ((i + 1) >= argc) {
				msg = "Option error: -r requires a rule.";
				break;
			}

			RuleExecutor re(argv[i + 1]);
			if (re.isError()) {
				msg = "Option error: rule is invalid. Check syntax.";
				break;
			}
			msg = re.executeAll();
			break;
		} else if(strcmp(argv[i], "-l") == 0) {
            // Check if we at least got a next param.
            if((i+1) >= argc) {
                msg = "Option error: -l requires an integer parameter.";
                break;
            }
            
            char *rawLength = argv[i + 1]; 
            msg = parseLengthParameter(length, rawLength); 
            
            i++;
        } else if (strcmp(argv[i], "-s") == 0) {
            special = true;
        } else {
            msg = showHelp();
        }
    }
    
    return msg;
}

/**
 * Parses the value of the length parameter.
 * -l [integer]
 *
 * @param length Reference to the length of the password.
 * @param rawLength [integer] argument value as raw string.
 * @returns True if everything is okay, false if the parameter is sad.
 *
 * Note: - This function will return the parsed length in the length parameter.
 *       - If integer is <= 0, it will be left at 0. 
 *       - If integer is > uint16_t max value, it will set length at uint16_t max value.
 *       - When given bad parameter, atoi returns 0, which remains an invalid parameter. 
 */
string parseLengthParameter(uint16_t &length, char *rawLength) {
    constexpr uint16_t max_length = std::numeric_limits<uint16_t>::max();

    int parsedLength = atoi(rawLength);
    
    if(parsedLength > max_length) {
        length = max_length;
    } else if (parsedLength <= 0) {
        length = 0;
        return "Option error: -l requires a valid positive integer.";
    } else {
        length = static_cast<uint16_t>(parsedLength);   
    }
            
    return string();
}

/**
 * Shows help. 
 * -h
 */
string showHelp() {
    std::stringstream out;
    out << "Simple-Pass - Password generator." << std::endl;
    out << "Git repo: https://github.com/mrtryhard/simplepass" << std::endl;
    out << std::endl;
    out << "Parameters:" << std::endl;
    
    out << "\t" << "-l [len]" << "\t";
    out << "Defines password's length." << std::endl;
    
    out << "\t" << "-s" << "\t\t";
    out << "Allows special characters." << std::endl;
    
    return out.str();
}
