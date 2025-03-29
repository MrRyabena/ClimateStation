#pragma once

#include <memory>
#include <stdint.h>

#include <shs_types.h>

#include <shs_lib_MHZ19.h>
#include <shs_lib_BME280.h>
#include <shs_lib_DHT.h>


#include <GyverDS3231.h>
#include <GyverNTP.h>


#include <shs_Process.h>
#include <shs_ProgramTime.h>

#include <shs_settings_private.h>
#include <shs_utils.h>

#define SHS_SF_DEBUG
#include <shs_debug.h>


namespace shs
{
    class ClimateStation;
    class ClimateStationVisualizer;
}


class shs::ClimateStation : public shs::Process
{
    
    friend class shs::ClimateStationVisualizer;

public:
    explicit ClimateStation(
        std::shared_ptr<shs::MHZ19> mhz19 = nullptr,
        std::shared_ptr<shs::BME280> bme = nullptr,
        std::shared_ptr<shs::DHT> dht = nullptr,
        std::shared_ptr<GyverDS3231> rtc = nullptr,
        std::shared_ptr<GyverNTP> ntp = nullptr
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


protected:
    enum M_SensorsNumbers { MHZ19_b = 0b1, BME280_b = 0b10, DHT_b = 0b100, UPDATING_TIMEOUT_b = 0b1000 };

    std::shared_ptr<shs::MHZ19> m_mhz19;
    std::shared_ptr<shs::BME280> m_bme;
    std::shared_ptr<shs::DHT> m_dht;

    std::shared_ptr<GyverDS3231> m_rtc;
    std::shared_ptr<GyverNTP> m_ntp;

    static constexpr auto M_SENS_UPDATING_TIMEOUT = 2000u;
    static constexpr auto M_UPDATING_TIMEOUT = 5000u;

    shs::ProgramTime m_main_tmr;
    shs::ProgramTime m_sens_updating_tmr;

    void m_updateSensors();
    uint8_t m_allSensUpdated();

    void m_updateData(Data& data);
};
