#pragma once

#include "rule.hpp"

class QuantityRule : public Rule {

public:
	QuantityRule(const uint16_t min, const uint16_t max);
	uint16_t getQuantity();
private:
	UIDist m_dist;
};