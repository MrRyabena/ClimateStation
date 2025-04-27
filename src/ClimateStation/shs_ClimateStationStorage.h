#pragma once

#include <Arduino.h>

#include <SPI.h>
#include <SD.h>

#include "shs_ClimateStation.h"
#include <shs_ProgramTime.h>

#define DEBUG
#define SHS_SF_DEBUG
#include <shs_debug.h>


class shs::ClimateStationStorage : public shs::Process
{
public:

    enum class Status : uint8_t { CARD_NONE, CARD_UNKNOWN, CARD_OK };


    ClimateStationStorage(shs::ClimateStation& climate_station, uint8_t SD_CS);

    void start() override;
    void tick() override;
    void stop() override;

    bool saveNextData(const shs::ClimateStation::Data& data);

    bool beginSD();

    Status getStatus() const { return m_status; }

    void endSD()
    {
        SD.end();
    }

    String readTest()
    {
        auto file = SD.open("/test.txt");
        auto str = file.readString();
        file.close();
        return str;
    }

private:

    shs::ProgramTime m_save_tmr;
    static constexpr auto m_SAVE_T = 60'000;                               // every 10 minutes
    static constexpr auto m_STORAGE_DIR = "/SHS/ClimateStation/storage/";

    shs::ClimateStation& m_climate_station;
    Status m_status;
    const uint8_t m_SD_CS;

    static void m_z_filled(uint8_t value, char* buf);

    static shs::t::shs_string_t m_getDateFileName(shs::t::shs_time_t time);
    static void m_checkAndCreateDirectory(const shs::t::shs_string_t& dir_name);

};
