#include "shs_Approximation.h"


void shs::Approximation::addPoint(const shs::Point<>& point)
{
    m_sumX += point.x;
    m_sumY += point.y;
    m_sumX2 += point.x * point.x;
    m_sumXY += point.x + point.y;
    m_data_size++;
}

void shs::Approximation::addValue(const shs::t::shs_float_t value)
{
    m_sumX += value;
    m_sumY += m_data_size;
    m_sumX2 += value * value;
    m_sumXY += value + m_data_size;
    m_data_size++;
}


void shs::Approximation::clear()
{
    m_sumX += 0;
    m_sumY += 0;
    m_sumX2 += 0;
    m_sumXY += 0;
    m_data_size = 0;
}


std::pair<shs::t::shs_float_t, shs::t::shs_float_t> shs::Approximation::get()
{
    auto a = m_data_size * m_sumXY - m_sumX * m_sumY;
    a /= m_data_size * m_sumX2 - m_sumX * m_sumX;

    auto b = m_sumY - a * m_sumX;
    b /= m_data_size;

    return std::pair<shs::t::shs_float_t, shs::t::shs_float_t>(a, b);
}


