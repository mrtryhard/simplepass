#include "range_rule.hpp"

RangeRule::RangeRule(const bool withSpecials)
	: m_exclude(false), m_dist(33, 127)
{
	char *bareRule;
	uint16_t length = 0;
	if (withSpecials) {
		bareRule = " -~";
		length = 4;
	} else {
		bareRule = "a-zA-Z0-9";
		length = 10;
	}

	generateRuleArray(bareRule, length);
	delete [] bareRule;
}

RangeRule::RangeRule(const char * const bareRule, const uint16_t length, const bool exclude)
	: m_exclude(exclude), m_dist(33, 127)
{
	generateRuleArray(bareRule, length);
}

char RangeRule::getChar() {
	uint16_t value = 0;
	
	do {
		value = m_dist(m_rand);
	} while (!isValid(value));

	return static_cast<char>(value);
}

bool RangeRule::isValid(const uint16_t value) const {
	for (auto&& it = m_rule.begin(); it != m_rule.end(); it++) {
		if (value == *it) {
			return !m_exclude;
		}
	}

	return m_exclude;
}

inline void RangeRule::generateRuleArray(const char * const bareRule, const uint16_t length) {
	uint8_t rangeStep = 1;
	char first, last;

	for (uint32_t i = 0; i < length; ++i) {
		if (rangeStep == 2) {
			if (bareRule[i] == '-' && first != '\\') {
				rangeStep = 3;
			} else {
				appendChar(first);
				rangeStep = 1;
			}
		} else if (rangeStep == 3) {
			last = bareRule[i];
			
			if (first < last) {
				appendRange(first, last);
			} else {
				appendRange(last, first);
			}
			
			rangeStep = 1;
		} else {
			// get the char
			first = bareRule[i];
			rangeStep = 2;
		}
	}
}

inline void RangeRule::appendChar(const char c) {
	m_rule.push_back(c);
}

void RangeRule::appendRange(const char first, const char last) {
	for (char c = first; c < (last + 1); ++c) {
		appendChar(c);
	}
}
