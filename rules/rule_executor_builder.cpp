#include "rule_executor_builder.hpp"

RuleExecutorBuilder::RuleExecutorBuilder() 
	: m_specials(false), m_digits(false), m_upperCaseAscii(false), m_lowerCaseAscii(false), 
	m_length(1)
{

}

RuleExecutorBuilder&
RuleExecutorBuilder::addAscii() noexcept {
	addLowerCaseAscii();
	addUpperCaseAscii();
	return *this;
}

RuleExecutorBuilder&
RuleExecutorBuilder::addLowerCaseAscii() noexcept {
	m_lowerCaseAscii = true;
	return *this;
}

RuleExecutorBuilder&
RuleExecutorBuilder::addUpperCaseAscii() noexcept {
	m_upperCaseAscii = true;
	return *this;
}

RuleExecutorBuilder& 
RuleExecutorBuilder::addSpecialCharacters() noexcept {
	m_specials = true;
	return *this;
}

RuleExecutorBuilder&
RuleExecutorBuilder::addDigits() noexcept {
	m_digits = true;
	return *this;
}

RuleExecutorBuilder&
RuleExecutorBuilder::removeAscii() noexcept {
	removeLowerCaseAscii();
	removeUpperCaseAscii();
	return *this;
}

RuleExecutorBuilder&
RuleExecutorBuilder::removeLowerCaseAscii() noexcept {
	m_lowerCaseAscii = false;
	return *this;
}

RuleExecutorBuilder&
RuleExecutorBuilder::removeUpperCaseAscii() noexcept {
	m_upperCaseAscii = false;
	return *this;
}

RuleExecutorBuilder&
RuleExecutorBuilder::removeSpecialCharacters() noexcept {
	m_specials = false;
	return *this;
}

RuleExecutorBuilder&
RuleExecutorBuilder::removeDigits() noexcept {
	m_upperCaseAscii = false;
	return *this;
}

RuleExecutorBuilder&
RuleExecutorBuilder::setLength(const uint16_t length) noexcept {
	m_length = length;
	return *this;
}


RuleExecutorBuilder& 
RuleExecutorBuilder::fromRule(const std::string& rawRule) noexcept {
	m_rawRule = rawRule;
	return *this;
}

RuleExecutor 
RuleExecutorBuilder::getExecutor() const {
	// This is overriding any other settings.
	if (!m_rawRule.empty()) {
		return RuleExecutor(m_rawRule);
	}

	std::string rule = "";
	if (m_lowerCaseAscii) {
		rule.append("a-z");
	}

	if (m_upperCaseAscii) {
		rule.append("A-Z");
	}

	if (m_digits) {
		rule.append("0-9");
	}

	if (m_specials) {
		rule.append(" -/");
		rule.append(":-@");
		rule.append("{-~");
		rule.append("[-`");
	}

	rule.insert(rule.cbegin(), '[');
	rule.insert(rule.cend(), ']');

	if (m_length != 0) {
		rule.append("{");
		rule.append(std::to_string(m_length));
		rule.append("}");
	}

	return RuleExecutor(rule);
}