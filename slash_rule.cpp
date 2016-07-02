#include "slash_rule.hpp"

SlashRule::SlashRule(const char type) {
	switch (type) {
		case 's':
			m_rangeRule = std::make_shared<RangeRule>(" ", 2);
			break;
		case 'S':
			m_rangeRule = std::make_shared<RangeRule>(" ", 2, true);
			break;
		case 'w':
			m_rangeRule = std::make_shared<RangeRule>("a-zA-Z", 7);
			break;
		case 'W':
			m_rangeRule = std::make_shared<RangeRule>("a-zA-Z", 7, true);
			break;
		case '.':
			m_rangeRule = std::make_shared<RangeRule>(".", 2);
			break;
		case 'd':
			m_rangeRule = std::make_shared<RangeRule>("0-9", 4);
			break;
		case 'D':
			m_rangeRule = std::make_shared<RangeRule>("0-9", 4, true);
			break;
		default:
			m_rangeRule = std::make_shared<RangeRule>("a-zA-Z0-9", 10);
			break;
	}
}

std::shared_ptr<RangeRule> SlashRule::getRangeRule() const {
	return m_rangeRule;
}