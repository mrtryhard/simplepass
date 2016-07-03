#pragma once

#include <climits>
#include <cstdint>
#include <random>

// This is core.
static_assert(CHAR_BIT == 8, "Generator requires signed char to be 8 bits!");

using RNG = std::mt19937;

typedef std::uniform_int_distribution<uint16_t> UIDist;
