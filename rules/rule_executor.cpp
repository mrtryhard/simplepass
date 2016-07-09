#include "rule_executor.hpp"

RuleExecutor::RuleExecutor(const std::string& rawRule)
 : m_error(false) 
{
	parseRule(rawRule.c_str());
}

RuleExecutor::RuleExecutor(const RuleExecutor& re) {
	selfCopy(re);
}

RuleExecutor& RuleExecutor::operator=(const RuleExecutor& re) {
	
	return selfCopy(re);
}

RuleExecutor& RuleExecutor::selfCopy(const RuleExecutor& re) {
	this->m_error = re.m_error;
	for (auto&& it = re.m_rules.cbegin(); it != re.m_rules.cend(); ++it) {
		this->m_rules.push_back(*it);
	}
	return *this;
}

bool RuleExecutor::isError() const noexcept {
	return m_error;
}

std::string RuleExecutor::executeAll() {
	if (m_error) return "";
	std::stringstream ss;

	for (auto&& it = m_rules.begin(); it != m_rules.end(); it++) {
		uint16_t length = (*it).second.get()->getQuantity();

		for (uint16_t i = 0; i < length; ++i) {
			ss << std::noskipws << (*it).first.get()->getChar();
		}
	}

	return ss.str();
}

void RuleExecutor::parseRule(const char * const rawRule) {
	const char *it = rawRule;
	bool isExclusion = false;

	for (; *it != '\0' && !m_error; it++) {
		ExecutionPair pair;
		if (*it == '\\') {
			it++;
			if (isSlashRule(*it)) {
				pair.first = slashToRange(*it, isExclusion);
			} else if (*it == '\0') {
				pair.first = std::make_shared<RangeRule>((it - 1), 2, isExclusion);
			} else {
				pair.first = std::make_shared<RangeRule>(it, 2, isExclusion);
			}
			pair.second = CONST_ONE;
			isExclusion = false;
			m_rules.push_back(pair);
		} else if (*it == '^') {
			isExclusion = true;
		} else if (*it == '[') {
			it++;
			m_error = parseRange(&it, pair, isExclusion);
			if (m_error) break;
			m_rules.push_back(pair);
			isExclusion = false;
		} else if (*it == '{') {
			it++;
			uint16_t first = 0, last = 0;
			m_error = parseQuantity(&it, first, last);
			if (m_error) break;
			m_rules.back().second = std::make_shared<QuantityRule>(first, last);
		} else if (*it == '.') {
			// The dot cannot be excluded as per \. is already defined.
			pair.first = std::make_shared<RangeRule>(true);
			pair.second = CONST_ONE;
			m_rules.push_back(pair);
		} else {
			pair.first = std::make_shared<RangeRule>(it, 2, isExclusion);
			pair.second = CONST_ONE;
			m_rules.push_back(pair);
			isExclusion = false;
		}
	}
}
#include <iostream>
bool RuleExecutor::parseRange(const char **it, ExecutionPair& pair, const bool isWholeExclusion) const {
	if (**it == '\0' || **it == ']') {
		return true;
	}
	bool isExclusion = false || isWholeExclusion;
	if (**it == '^') {
		(*it)++;
		isExclusion = true;
	}

	std::stringstream ss;

	while (**it != ']' && **it != '\0') {
		ss << **it;
		(*it)++;
	}
	ss << '\0';
	std::string str(ss.str());

	pair.first = std::make_shared<RangeRule>(
			str.c_str(),
			static_cast<uint16_t>(str.length()),
			isExclusion
		);

	pair.second = CONST_ONE;

	return false;
}

bool RuleExecutor::parseQuantity(const char **it, uint16_t& first, uint16_t& last) const {
	if (m_rules.size() <= 0) {
		return true;
	}

	std::stringstream ss;

	if (**it == '}' || **it == ',' || **it == '\0') {
		return true;
	}

	while (**it != '}' && **it != ',' && **it != '\0') {
		ss << **it;
		(*it)++;
	}
	ss << '\0';

	int value = std::stoi(ss.str());

	first = static_cast<uint16_t>(value);
	last = first;
	
	ss.str("");
	if (**it == ',') {
		(*it)++;

		while (**it != '}' && **it != '\0') {
			ss << **it;
			(*it)++;
		}
		
		ss << '\0';
		value = std::stoi(ss.str());
		last = static_cast<uint16_t>(value);
	}

	return false;
}

bool RuleExecutor::isSlashRule(const char c) const noexcept {
	switch (c) {
		case 'd': return true;
		case 'D': return true;
		case 'w': return true;
		case 'W': return true;
		case 's': return true;
		case 'S': return true;
		case '.': return true;
		default: return false;
	}
}

std::shared_ptr<RangeRule> RuleExecutor::slashToRange(const char c, const bool isExclusion) const noexcept {
	switch (c) {
		case 'd': return isExclusion ? RULE_DIGIT_EX : RULE_DIGIT;
		case 'D': return isExclusion ? RULE_DIGIT : RULE_DIGIT_EX;
		case 'w': return isExclusion ? RULE_WORD_EX : RULE_WORD;
		case 'W': return isExclusion ? RULE_WORD : RULE_WORD_EX;
		case 's': return isExclusion ? RULE_SPACE_EX : RULE_SPACE;
		case 'S': return isExclusion ? RULE_SPACE : RULE_SPACE_EX;
		case '.': return RULE_DOT;
		default: return RULE_SPACE_EX;
	}
}
