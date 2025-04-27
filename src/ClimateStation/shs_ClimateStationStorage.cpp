#include "shs_ClimateStationStorage.h"


shs::ClimateStationStorage::ClimateStationStorage(shs::ClimateStation& climate_station, const uint8_t SD_CS)
    : m_climate_station(climate_station), m_SD_CS(SD_CS)
{}


void shs::ClimateStationStorage::start()
{
    beginSD();
}


void shs::ClimateStationStorage::tick()
{
    if (m_status != Status::CARD_OK) beginSD();

    if (m_save_tmr.milliseconds() >= m_SAVE_T)
    {
        saveNextData(m_climate_station.getData());
        m_save_tmr.reset();
    }
}


void shs::ClimateStationStorage::stop()
{}


bool shs::ClimateStationStorage::saveNextData(const shs::ClimateStation::Data& data)
{
    if (m_status != Status::CARD_OK) return false;

    File file = SD.open(m_getDateFileName(data.time), FILE_WRITE);
    if (!file) return false;

    file.write(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
    file.close();

    doutln(F("saved"));
    return true;
}


bool shs::ClimateStationStorage::beginSD()
{
    bool result = SD.begin(m_SD_CS);

    if (!result)
    {
        uint8_t cardType = SD.cardType();
        switch (cardType)
        {
            case CARD_NONE: m_status = Status::CARD_NONE; doutln("SD: none") break;
            case CARD_MMC: [[fallthrough]];
            case CARD_SD: [[fallthrough]];
            case CARD_SDHC: [[fallthrough]];
            default: m_status = Status::CARD_UNKNOWN; doutln("SD: OK"); break;
        }
    }
    else
    {
        m_status = Status::CARD_OK;
        doutln("SD: OK");
    }

    m_checkAndCreateDirectory(m_STORAGE_DIR);

    return result;
}


shs::t::shs_string_t shs::ClimateStationStorage::m_getDateFileName(const shs::t::shs_time_t time)
{
    Datime datime(time);
    char buf[3]{};

    shs::t::shs_string_t file_name = m_STORAGE_DIR;
    file_name.reserve(4 + 2 + 2);

    file_name += datime.year;

    m_z_filled(datime.month, buf);
    file_name += buf;

    m_z_filled(datime.day, buf);
    file_name += buf;

    file_name += F(".shsf");

    return file_name;
}


void shs::ClimateStationStorage::m_checkAndCreateDirectory(const shs::t::shs_string_t& dir_name)
{
    if (!SD.exists(dir_name)) SD.mkdir(dir_name);
}


void shs::ClimateStationStorage::m_z_filled(const uint8_t value, char* buf)
{
    buf[0] += '0' + value / 10;
    buf[1] += '0' + value % 10;
}
