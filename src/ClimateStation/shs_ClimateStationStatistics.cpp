#include "shs_ClimateStationStatistics.h"

shs::ClimateStationStatistics::ClimateStationStatistics(std::shared_ptr<shs::ClimateStation> climate_station, std::shared_ptr<shs::ClimateStationStorage> storage)
    : m_climate_station(climate_station), m_storage(storage), m_data(m_PERIOD / m_TICK_TIMEOUT), m_tick_tmr(m_TICK_TIMEOUT)
{}

void shs::ClimateStationStatistics::start()
{

}

void shs::ClimateStationStatistics::tick()
{
    if (m_tick_tmr.check())
    {
        m_addData(m_climate_station->getData());
    }
}

shs::IndicatorWidget::ValueTrend shs::ClimateStationStatistics::getTrend(shs::ClimateStationMetrics metric)
{
    shs::Approximation apr;
    switch (metric)
    {
        using m = shs::ClimateStationMetrics;

        case m::CO2: for (auto& x : m_data) apr.addValue(x.CO2); break;
        case m::IN_HUM: for (auto& x : m_data) apr.addValue(x.indoor_humidity.toFloat()); break;
        case m::IN_TEMP: for (auto& x : m_data) apr.addValue(x.indoor_temperature.toFloat()); break;
        case m::OUT_HUM: for (auto& x : m_data) apr.addValue(x.outdoor_humidity.toFloat()); break;
        case m::OUT_TEMP: for (auto& x : m_data) apr.addValue(x.outdoor_temperature.toFloat()); break;
        case m::PRESSURE: for (auto& x : m_data) apr.addValue(x.pressure.toFloat()); break;

        default: return shs::IndicatorWidget::ValueTrend(); break;
    }

    return m_getTrend(apr.get().first);
}


void shs::ClimateStationStatistics::m_addData(const shs::ClimateStationData& data)
{
    std::rotate(m_data.rbegin(), m_data.rbegin() + 1, m_data.rend());
    m_data[0] = data;
}

shs::IndicatorWidget::ValueTrend shs::ClimateStationStatistics::m_getTrend(const shs::t::shs_float_t a)
{
    if (a > 0.1) return shs::IndicatorWidget::ValueTrend::INCREASING;
    if (a < -0.1) return shs::IndicatorWidget::ValueTrend::DECREASING;
    return shs::IndicatorWidget::ValueTrend::CONST;
}

