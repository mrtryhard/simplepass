#pragma once

#include <vector>
#include <sstream>
#include <string>
#include <utility>

#include "quantity_rule.hpp"
#include "range_rule.hpp"
#include "slash_rule.hpp"

class RuleExecutor {
	using ExecutionPair = std::pair<std::shared_ptr<RangeRule>, std::shared_ptr<QuantityRule>>;

private:
	const std::shared_ptr<RangeRule> RULE_DOT = std::make_shared<RangeRule>(".", 2);
	const std::shared_ptr<RangeRule> RULE_SPACE = std::make_shared<RangeRule>(" ", 2);
	const std::shared_ptr<RangeRule> RULE_SPACE_EX = std::make_shared<RangeRule>(" ", 2, true);
	const std::shared_ptr<RangeRule> RULE_WORD = std::make_shared<RangeRule>("a-zA-Z", 7);
	const std::shared_ptr<RangeRule> RULE_WORD_EX = std::make_shared<RangeRule>("a-zA-Z", 7, true);
	const std::shared_ptr<RangeRule> RULE_DIGIT = std::make_shared<RangeRule>("0-9", 4);
	const std::shared_ptr<RangeRule> RULE_DIGIT_EX = std::make_shared<RangeRule>("0-9", 4, true);

public:
	/**
	 * @param rawRule Complete rule set (e.g. [abc]{5}a{10})
	 */
	RuleExecutor(const char * const rawRule);

	/**
	 * Return wether or not the RuleExecutor is in error. 
	 * @returns True if in error, false otherwise. 
	 */
	bool isError() const;

	/**
	 * Executes the rule set to generate the defined string. 
	 * @returns Rule restricted password.
	 */
	std::string executeAll();
private: 
	/**
	 * Parses the raw rule. 
	 * @param rawRule Raw rule to parse. 
	 */
	void parseRule(const char * const rawRule);

	/**
	 * Parses the range rule (e.g. [...]) 
	 * Note: This function will affect the external iterator.
	 *
	 * @param it Character's iterator
	 * @param pair ExecutionPair (<RangeRule, QuantityRule>) reference.
	 * @returns True if an error occured. 
	 */
	bool parseRange(const char **it, ExecutionPair& pair, const bool isWholeExclusion) const;

	/**
	 * Parses the quantity rule (e.g. {...})
	 * Note: this function will affect the external iterator and both first and last. 
	 *
	 * @param it Character's iterator 
	 * @param first First limit (lower limit)
	 * @param last Last quantity (upper limit)
	 * @returns True if an error occured.
	 */
	bool parseQuantity(const char **it, uint16_t& first, uint16_t& last) const;
	
	/**
	 * Determines if the character is a slash rule.
	 * 
	 * @param c Character
	 * @returns True if the character is a slash rule.
	 */
	bool isSlashRule(const char c) const;

	/**
	 * Gets the corresponding RangeRule of the SlashRule. 
	 * 
	 * @param c SlashRule 
	 * @returns Shared pointer to the RangeRule.
	 */
	std::shared_ptr<RangeRule> slashToRange(const char c, const bool isExclusion) const;

private:
	bool m_error;
	std::vector<ExecutionPair> m_rules;
	const std::shared_ptr<QuantityRule> CONST_ONE = std::make_shared<QuantityRule>(1, 1);
};