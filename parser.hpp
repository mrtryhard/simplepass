#ifndef MRT_SP_PARSER
#define MRT_SP_PARSER

#include <sstream>
#include <string>
#include <vector>
#include <random>

namespace simple
{
	class parser final
	{
		char current_token;
		bool escaping;
		std::stringstream rule;
		std::stringstream result;
		std::default_random_engine random_generator;
	public:
		explicit parser(const std::string&);
		parser(parser&&) = delete;
		parser(parser&) = delete;
		parser& operator=(parser&) = delete;

		std::string password() const;
	private:
		void parse_expression();
		void parse_set();
		int parse_quantity();
		bool advance_token();

		void append_random_token_n(const std::vector<char>&, size_t);
		void append_char_range(std::vector<char>&, char, char) const;
	};
}

#endif
