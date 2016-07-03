#pragma once

#include <vector>
#include <algorithm>
#include "rule.hpp"

class RangeRule : public Rule {
public:
	/**
	 * Generates with all alpha-numerical characters and if stated, with special chars. 
	 * @param withSpecials If true, will allow special characters. If false, only plain 
	 *                     alphanumerical.
	 */
	RangeRule(const bool withSpecials);

	/**
	 * Generates a range rule with bare rule.
	 * @param bareRule Bare rule (without [, ] and ^ if there was any at the beginning). 
	 * @param length Length of the bare rule. 
	 * @param exclude The rule (if the rule was [^abc], a,b and c are excluded. 
	 */
	RangeRule(const char * const bareRule, const uint16_t length, const bool exclude = false);

	/**
	 * Gets a character valid to the rule.
	 * @returns Character fitting in the rule. 
	 */
	char getChar();

private:
	/**
	 * Determines if a character is valid within the rule.
	 * @param value Character value.
	 * @returns True if valid, false otherwise.
	 */
	bool isValid(const uint16_t value) const;

	/**
	 * Generates the rule array (each allowed characters).
	 * @param bareRule Bare rule
	 * @param length Length of the bare rule.
	 */
	inline void generateRuleArray(const char * const bareRule, const uint16_t length);
	
	/**
	 * Appends a char to the rule array. 
	 * @param c Character
	 */
	inline void appendChar(const char c);

	/**
	 * Generates the range from first to last inclusively and appends the characters
	 * to the array.
	 * @param first First character of the range
	 * @param last Last character of the range (included)
	 */
	void appendRange(const char first, const char last);
private:
	const bool m_exclude;
	std::vector<char> m_rule;
	UIDist m_dist;
};
