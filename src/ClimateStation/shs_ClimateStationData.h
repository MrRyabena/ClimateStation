#pragma once


#include <stdint.h>
#include <shs_types.h>

namespace shs
{
    struct ClimateStationData;
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
