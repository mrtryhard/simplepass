#pragma once

#include <cstdint>
#include <random>

// This is core.
static_assert(CHAR_BIT == 8, "Generator requires signed char to be 8 bits!");

using RNG = std::mt19937;

typedef std::uniform_int_distribution<int16_t> UIDist;
