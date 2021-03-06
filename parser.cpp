#include "parser.hpp"

#include <exception>
#include <chrono>
#include <locale>

namespace simple
{
	constexpr char TOKEN_DEFAULT_VALUE = -1;
	constexpr char TOKEN_SET_START = '[';
	constexpr char TOKEN_SET_END = ']';
	constexpr char TOKEN_QUANTITY_START = '{';
	constexpr char TOKEN_QUANTITY_END = '}';
	constexpr char TOKEN_RANGE = '-';
	constexpr char TOKEN_ESCAPE = '\\';
	constexpr char TOKEN_RULE_END = '\0';

	parser::parser(const std::string& rule)
		: current_token{ TOKEN_DEFAULT_VALUE }, escaping{ false }, rule{ rule },
		random_generator{ static_cast<int>(std::chrono::system_clock::now().time_since_epoch().count()) }
	{
		this->rule >> std::noskipws;
		result << std::noskipws;

		parse_expression();
	}

	std::string parser::password() const
	{
		return result.str();
	}

	void parser::parse_expression()
	{
		while (advance_token()) {
			if (current_token == TOKEN_SET_START && false == escaping) {
				parse_set();
			} else {
				result << current_token;
			}
		}
	}

	void parser::parse_set()
	{
		set_t set;
		bool previous_was_range{ false };
		
		advance_token();

		if (current_token == TOKEN_SET_END && false == escaping)
			throw std::exception{ "A set cannot be empty." };
		
		auto is_valid_range_token = [&]() {
			return current_token == TOKEN_RANGE && false == set.empty() && false == previous_was_range && false == escaping;	
		};

		do {

			if (is_valid_range_token()) {
				char next_token;
				rule >> next_token;

				if (next_token != TOKEN_SET_END && next_token != TOKEN_RULE_END) {
					append_char_range(set, set.back() + 1, next_token);
					previous_was_range = true;
					continue;
				}
			}

			previous_was_range = false;
			set.push_back(current_token);
		} while (advance_token() && false == (current_token == TOKEN_SET_END && false == escaping));

		int quantity = parse_quantity();
		append_random_token_n(set, quantity);
	}

	int parser::parse_quantity()
	{
		advance_token();
		if(current_token != TOKEN_QUANTITY_START) {
			rule.unget();
			return 1;
		}

		advance_token();
		if(current_token == TOKEN_QUANTITY_END && false == escaping)
			throw std::exception{ "A quantity cannot be empty." };

		bool range_crossed{ false };
		int lower{ 0 }, upper{ -1 };
		std::locale locale;
		std::stringstream number;

		do {
			if(std::isdigit(current_token, locale)) {
				number << current_token;
			} else if (current_token == TOKEN_RANGE && false == range_crossed && false == escaping) {
				number >> lower;
				number.str(std::string{});
				number.clear();
				range_crossed = true;
			} else {
				throw std::exception{ "Invalid quantity format specified." };
			}
		} while(advance_token() && false == (current_token == TOKEN_QUANTITY_END && false == escaping));

		if(range_crossed) {
			number >> upper;
			std::uniform_int_distribution<int> distribution{ lower, upper };
			return distribution(random_generator);
		} else {
			number >> lower;
			return lower;
		}
	}

	bool parser::advance_token()
	{
		escaping = false;
		bool success = static_cast<bool>(rule >> current_token);
		
		if (current_token == TOKEN_ESCAPE)
			escaping = true;

		if (escaping)
			success = static_cast<bool>(rule >> current_token);

		return success;
	}

	void parser::append_random_token_n(const set_t& tokens, size_t quantity)
	{
		if(quantity == 0)
			throw std::exception{ "Quantity cannot be zero (0)." };

		std::uniform_int_distribution<int> distribution{ 0, static_cast<int>(tokens.size() - 1) };

		for (size_t count{ 0 }; count < quantity; count++) {
			result << tokens[distribution(random_generator)];
		}
	}

	void parser::append_char_range(set_t& set, char left, char right) const
	{
		using namespace std;
		const char upper = max(left, right);

		for(char lower = min(left, right); lower <= upper; lower++) {
			set.push_back(lower);
		}
	}
}