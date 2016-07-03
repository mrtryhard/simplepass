#include "quantity_rule.hpp"

// TODO: make sure it is not [a, b[ but [a,b]. Otherwise max + 1.
QuantityRule::QuantityRule(const uint16_t min, const uint16_t max) 
	: m_dist(min, max)
{
	m_rand.seed(std::random_device()());
}

uint16_t QuantityRule::getQuantity() {
	return m_dist(m_rand);
}
