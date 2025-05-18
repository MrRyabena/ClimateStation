#pragma once

#include <shs_types.h>

namespace shs
{
    template <typename> struct Point;
}


template <typename CoordT = shs::t::shs_float_t>
struct shs::Point
{
    CoordT x{};
    CoordT y{};
};
