#pragma once

#include <vector>
#include <algorithm>
#include "rule.hpp"

class RangeRule : public Rule {
public:
	RangeRule(const char * const bareRule, const uint16_t length, const bool exclude = false);
	char getChar();

private:
	bool isValid(const uint16_t value) const;
	void generateRuleArray(const char * const bareRule, const uint16_t length);
	void appendChar(const char c);
	void appendRange(const char first, const char last);
private:
	// STACK 
	const bool m_exclude;

	std::vector<char> m_rule;
	UIDist m_dist;
};