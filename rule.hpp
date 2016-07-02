#pragma once

#include "common.hpp"

class Rule {
public:
	Rule() { m_rand.seed(std::random_device()()); };

protected:	
	RNG m_rand;
};