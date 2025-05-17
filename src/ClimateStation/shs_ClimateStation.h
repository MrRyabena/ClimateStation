#pragma once

#include <memory>
#include <stdint.h>

#include <shs_types.h>
#include <Stamp.h>

#include <shs_lib_MHZ19.h>
#include <shs_lib_BME280.h>
#include <shs_lib_DHT.h>


#include <GyverDS3231.h>
#include <GyverNTP.h>


#include <shs_Process.h>
#include <shs_ProgramTimer.h>

#include <shs_settings_private.h>
#include <shs_utils.h>

#include <WiFi.h>

#define SHS_SF_DEBUG
#include <shs_debug.h>

#include "shs_ClimateStationConfig.h"
#include "shs_ClimateStationStorage.h"


namespace shs
{
    class ClimateStation;
    class ClimateStationVisualizer;
}


class shs::ClimateStation : public shs::Process
{

    friend class shs::ClimateStationVisualizer;
    friend class shs::ClimateStationStorage;

public:
    using Data = shs::ClimateStationData;

    enum class SensorsNumbers : uint8_t
    {
        MHZ19_b = 0b1, BME280_b = 0b10, DHT_b = 0b100,
        DS3231_b = 0b1000, NTP_b = 0b10000, UPDATING_TIMEOUT_b = 0b100000,
    };

    explicit ClimateStation(
        std::shared_ptr<shs::ClimateStationStorage> storage,
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

    Data getData() { Data data; m_updateData(data); return data; }

    uint32_t getTimeUnix();


#ifdef SHS_SF_DEBUG
    void debug_print_data(const Data& data) const;
    void debug_print_status() const;
#endif

protected:
    std::shared_ptr<shs::ClimateStationStorage> m_storage;

    std::shared_ptr<shs::MHZ19> m_mhz19;
    std::shared_ptr<shs::BME280> m_bme;
    std::shared_ptr<shs::DHT> m_dht;

    std::shared_ptr<GyverDS3231> m_rtc;
    std::shared_ptr<GyverNTP> m_ntp;

    static constexpr auto m_SENS_UPDATING_TIMEOUT = 2000u;
    static constexpr auto m_UPDATING_TIMEOUT = 5000u;

    shs::ProgramTimer m_main_tmr;
    shs::ProgramTimer m_sens_updating_tmr;
    shs::ProgramTimer m_save_tmr;

    void m_updateSensors();
    uint8_t m_allSensUpdated();

    void m_updateData(Data& data);
};
