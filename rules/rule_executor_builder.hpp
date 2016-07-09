#pragma once
#include "rule_executor.hpp"

/**
 * RuleExecutorBuilder
 * Allows to build easily a RuleExecutor without write manually rules. 
 * This builder should be used in apps instead of playing directly with 
 * RuleExecutor and rules. 
 *
 * You can still use directly from raw rule with formRule method. 
 * 
 * Internally, the RuleExecutor will build a rule with this format: 
 * [<defined chars>]{<defined length>} 
 * Which should satisfy most needs. 
 *
 * If no length is defined, RuleExecutorBuilder will use length of 1.
 */
class RuleExecutorBuilder {
public:
	RuleExecutorBuilder();
	RuleExecutorBuilder& addAscii() noexcept;
	RuleExecutorBuilder& addUpperCaseAscii() noexcept;
	RuleExecutorBuilder& addLowerCaseAscii() noexcept;
	RuleExecutorBuilder& addSpecialCharacters() noexcept;
	RuleExecutorBuilder& addDigits() noexcept;

	RuleExecutorBuilder& removeAscii() noexcept;
	RuleExecutorBuilder& removeUpperCaseAscii() noexcept;
	RuleExecutorBuilder& removeLowerCaseAscii() noexcept;
	RuleExecutorBuilder& removeSpecialCharacters() noexcept;
	RuleExecutorBuilder& removeDigits() noexcept;

	RuleExecutorBuilder& setLength(const uint16_t length) noexcept;

	/**
	 * Will use the rule to generate the RuleExecutor 
	 * Will ignore the previous set settings. 
	 */
	RuleExecutorBuilder& fromRule(const std::string& rawRule) noexcept;

	/**
	 * Creates a new RuleExecutor. 
	 * @returns RuleExecutor object.
	 */
	RuleExecutor getExecutor() const;

private:
	bool m_specials;
	bool m_digits;
	bool m_upperCaseAscii;
	bool m_lowerCaseAscii;

	uint16_t m_length;
	std::string m_rawRule;
};