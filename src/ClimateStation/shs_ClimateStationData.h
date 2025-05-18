#pragma once


#include <stdint.h>
#include <shs_types.h>

namespace shs
{
    struct ClimateStationData;
    enum class ClimateStationMetrics;
}


struct shs::ClimateStationData
{
    uint16_t CO2{};

    shs::t::shs_fixed_t pressure;

    shs::t::shs_fixed_t indoor_temperature;
    shs::t::shs_fixed_t outdoor_temperature;

    shs::t::shs_fixed_t indoor_humidity;
    shs::t::shs_fixed_t outdoor_humidity;

    shs::t::shs_time_t time;
};


enum class shs::ClimateStationMetrics
{
    CO2,
    PRESSURE,
    IN_TEMP,
    OUT_TEMP,
    IN_HUM,
    OUT_HUM,
    TIME
};
