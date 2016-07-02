#pragma once

#include <memory>
#include "range_rule.hpp"

class SlashRule : public Rule {
public:
	/**
	 * Creates a slash rule with the type value. 
	 * @param type s, S, w, W, d, D, .
	 */
	SlashRule(const char type); 
	std::shared_ptr<RangeRule> getRangeRule() const;
private:
	std::shared_ptr<RangeRule> m_rangeRule;
};