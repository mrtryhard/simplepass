#include "range_rule.hpp"

RangeRule::RangeRule(const bool withSpecials)
	: m_exclude(false), m_dist(32, 127)
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
	: m_exclude(exclude), m_dist(32, 127)
{
	generateRuleArray(bareRule, length);
}

char RangeRule::getChar() {
	if (m_rule.size() <= 0) return '\0';

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
	char first;

	for (uint32_t i = 0; i < length; ++i) {
		if (rangeStep == 1) {
			first = bareRule[i];
			rangeStep = 2;
		} else if (rangeStep == 2) {
			if (bareRule[i] != '-') {
				appendChar(first);
				first = bareRule[i];
				rangeStep = 2;
			} else {
				rangeStep = 3;
			}
		} else {
			appendRange(first, bareRule[i]);
			rangeStep = 1;
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
