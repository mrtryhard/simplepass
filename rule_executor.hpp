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

public:
	RuleExecutor(const char * const rawRule);
	bool isError() const;
	std::string executeAll();
private: 
	void parseRule(const char * const rawRule);
	bool parseRange(const char **it, ExecutionPair& pair);
	bool parseQuantity(const char **it, uint16_t& first, uint16_t& last);
	bool isSlash(const char c) const;

private:
	bool m_error;
	std::vector<ExecutionPair> m_rules;
	const std::shared_ptr<QuantityRule> CONST_ONE = std::make_shared<QuantityRule>(1, 1);
};