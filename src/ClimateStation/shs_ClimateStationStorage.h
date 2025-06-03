#pragma once

#include <memory>

#include <Arduino.h>
#include <Stamp.h>

#include <SPI.h>
#include <SD.h>

#include <shs_ProgramTimer.h>
#include <shs_Process.h>

#include "shs_ClimateStationData.h"
#include "shs_ClimateStationConfig.h"



namespace shs
{
    class ClimateStationStorage;
}


class shs::ClimateStationStorage : public shs::Process
{
public:

    shs::ClimateStationConfig cs_config;

    enum class Status : uint8_t { CARD_NONE, CARD_UNKNOWN, CARD_OK };


    ClimateStationStorage(uint8_t SD_CS);


    void start() override;
    void tick() override;
    void stop() override;

    bool saveNextData(const shs::ClimateStationData& data);

    bool beginSD();

    Status getStatus() const { return m_status; }

    bool save_TFT_calData(const uint16_t* calData);
    [[nodiscard]] bool get_TFT_calData(uint16_t* calData);

    bool saveConfig(const shs::ClimateStationConfig& config);
    bool getConfig(shs::ClimateStationConfig& config);

    void endSD()
    {
        SD.end();
    }

    [[nodiscard]] size_t readFile(const shs::t::shs_string_t& fname, uint8_t* buf, size_t size);
    [[nodiscard]] size_t writeFile(const shs::t::shs_string_t& fname, const uint8_t* buf, size_t size);

    String readTest()
    {
        auto file = SD.open("/test.txt");
        auto str = file.readString();
        file.close();
        return str;
    }

    static shs::t::shs_string_t m_getDateFileName(shs::t::shs_time_t time);

private:
    static constexpr auto m_CONFIG_FILE = "/SHS/SHS_ClimateStation/config/";
    static constexpr auto m_STORAGE_DIR = "/SHS/SHS_ClimateStation/storage/";
    static constexpr auto m_TFT_DATA_DIR = "/SHS/SHS_ClimateStation/TFT_data/";
    static constexpr auto m_TFT_TOUCH_CALIBRATION_DATA_SIZE = 5;                  // size in uint16_t (10 bytes)

    Status m_status;
    const uint8_t m_SD_CS;

    static void m_z_filled(uint8_t value, char* buf);


    static void m_checkAndCreateDirectory(const shs::t::shs_string_t& dir_name);
};
