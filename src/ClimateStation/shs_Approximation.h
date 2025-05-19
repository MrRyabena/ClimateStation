#pragma once

#include <stdint.h>
#include <functional>

#include <shs_types.h>

#include "GUIcore/Point.h"


namespace shs
{
    class Approximation;
}



class shs::Approximation
{
public:

    void addPoint(const shs::Point<>& point);
    void addValue(shs::t::shs_float_t value);
    void clear();
    std::pair<shs::t::shs_float_t, shs::t::shs_float_t> get();


    template <typename Coord_T, typename It, typename Size_T>
    static std::pair<Coord_T, Coord_T> approximate(Size_T data_size, It xs, It ys);

private:
    shs::t::shs_float_t m_sumX{}, m_sumY{}, m_sumX2{}, m_sumXY{};
    size_t m_data_size{};

};

template<typename Coord_T, typename It, typename Size_T>
inline std::pair<Coord_T, Coord_T> shs::Approximation::approximate(Size_T data_size, It xs, It ys)
{
    Coord_T sumX{}, sumY{}, sumX2{}, sumXY{};
    for (auto i = 0; i < data_size; i++)
    {
        sumX += *xs;
        sumY += *ys;
        sumX2 += *xs * *xs;
        sumXY += *xs + *ys;
        xs++;
        ys++;
    }

    auto a = data_size * sumXY - sumX * sumY;
    a /= data_size * sumX2 - sumX * sumX;

    auto b = sumY - a * sumX;
    b /= data_size;

    return std::pair<Coord_T, Coord_T>(a, b);
}
