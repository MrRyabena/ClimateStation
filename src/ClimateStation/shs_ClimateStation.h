#pragma once

#include <memory>
#include <stdint.h>

#include <shs_types.h>

#include <shs_lib_MHZ19.h>
#include <shs_lib_BME280.h>
#include <shs_lib_DHT.h>


#include <GyverDS3231.h>


#include <shs_Process.h>
#include <shs_ProgramTime.h>




namespace shs
{
    class ClimateStation;
}


class shs::ClimateStation : public shs::Process
{
public:
    explicit ClimateStation(
        std::shared_ptr<shs::MHZ19> mhz19,
        std::shared_ptr<shs::BME280> bme,
        std::shared_ptr<shs::DHT> dht//,
       // std::shared_ptr<shs::GyverDS3231> m_rtc
    );


    ~ClimateStation() = default;


    void start() override;
    void tick() override;
    void stop() override;

    struct Data
    {
        uint16_t CO2{};

        shs::t::shs_fixed_t pressure;
  
        shs::t::shs_fixed_t indoor_temperature;
        shs::t::shs_fixed_t outdoor_temperature;

        shs::t::shs_fixed_t indoor_humidity;
        shs::t::shs_fixed_t outdoor_humidity;

        shs::t::shs_time_t time;
    };


private:

    std::shared_ptr<shs::MHZ19> m_mhz19;
    std::shared_ptr<shs::BME280> m_bme;
    std::shared_ptr<shs::DHT> m_dht;

    std::shared_ptr<GyverDS3231> m_rtc;


};
