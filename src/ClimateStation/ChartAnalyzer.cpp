#include "ChartAnalyzer.h"

shs::ChartAnalyzer::ChartAnalyzer(std::shared_ptr<shs::ClimateStationStorage> storage, const shs::t::shs_coord_t width, const shs::t::shs_coord_t height)
    : m_width(width), m_height(height)
{
    min_values.CO2 = UINT16_MAX;
    min_values.indoor_humidity = 100.0;
    min_values.indoor_temperature = 100.0;
    min_values.outdoor_humidity = 100.0;
    min_values.outdoor_temperature = 100.0;
    min_values.pressure = 2000000.0;
    min_values.time = UINT32_MAX;
}

shs::ChartAnalyzer::~ChartAnalyzer()
{
    if (m_file) m_file.close();
}


bool shs::ChartAnalyzer::addFile(const shs::t::shs_string_t& fname)
{
    File file = SD.open(fname, FILE_READ);

    if (!file) return false;

    shs::ClimateStationData data;


    while (file.available())
    {
        if (file.read(reinterpret_cast<uint8_t*>(&data), sizeof(data)) != sizeof(data)) break;

        min_values.CO2 = min(min_values.CO2, data.CO2);
        max_values.CO2 = max(max_values.CO2, data.CO2);

        min_values.indoor_humidity = min(min_values.indoor_humidity.toFloat(), data.indoor_humidity.toFloat());
        max_values.indoor_humidity = max(max_values.indoor_humidity.toFloat(), data.indoor_humidity.toFloat());

        min_values.indoor_temperature = min(min_values.indoor_temperature.toFloat(), data.indoor_temperature.toFloat());
        max_values.indoor_temperature = max(max_values.indoor_temperature.toFloat(), data.indoor_temperature.toFloat());


        min_values.outdoor_humidity = min(min_values.outdoor_humidity.toFloat(), data.outdoor_humidity.toFloat());
        max_values.outdoor_humidity = max(max_values.outdoor_humidity.toFloat(), data.outdoor_humidity.toFloat());

        min_values.outdoor_temperature = min(min_values.outdoor_temperature.toFloat(), data.outdoor_temperature.toFloat());
        max_values.outdoor_temperature = max(max_values.outdoor_temperature.toFloat(), data.outdoor_temperature.toFloat());

        min_values.pressure = min(min_values.pressure.toFloat(), data.pressure.toFloat());
        max_values.pressure = max(max_values.pressure.toFloat(), data.pressure.toFloat());


        min_values.time = min(min_values.time, data.time);
        max_values.time = max(max_values.time, data.time);
    }

    m_files.push_back(fname);

    return true;
}

bool shs::ChartAnalyzer::beginPoints()
{
    if (m_files.empty()) return false;
    m_cursor = 0;

    std::sort(m_files.begin(), m_files.end());
    auto currentFileName = m_files[m_cursor];

    if (m_file) m_file.close();
    m_file = SD.open(currentFileName, FILE_READ);

    return true;
}


bool shs::ChartAnalyzer::getNextPoint(shs::Point<>& point, const  shs::ClimateStationMetrics metric)
{
    if (m_file && m_file.available())
    {
        shs::ClimateStationData data;
        m_file.read(reinterpret_cast<uint8_t*>(&data), sizeof(data));

       // point.y = map(m_getMetric(data, metric), m_getMetric(min_values, metric), m_getMetric(max_values, metric), 0, m_height);
       // point.x = map(data.time, min_values.time, max_values.time, 0, m_width);
       point.y = m_getMetric(data, metric);
       point.x = data.time / 60;
    }
    else
    {
        if (openNextFile()) getNextPoint(point, metric);
        else return false;
    }

    return true;
}

bool shs::ChartAnalyzer::openNextFile()
{
    if (m_file) m_file.close();
    if (++m_cursor == m_files.size()) return false;

    auto currentFileName = m_files[m_cursor];
    m_file = SD.open(currentFileName, FILE_READ);

    return true;
}


void shs::ChartAnalyzer::endPoints()
{
    if (m_file) m_file.close();
}

shs::t::shs_float_t shs::ChartAnalyzer::m_getMetric(const shs::ClimateStationData& data, const shs::ClimateStationMetrics metric)
{
    switch (shs::etoi(metric))
    {
        using m = shs::ClimateStationMetrics;
        case shs::etoi(m::CO2):      return data.CO2; break;
        case shs::etoi(m::IN_HUM):   return data.indoor_humidity; break;
        case shs::etoi(m::IN_TEMP):  return data.indoor_temperature; break;
        case shs::etoi(m::OUT_HUM):  return data.outdoor_humidity; break;
        case shs::etoi(m::OUT_TEMP): return data.outdoor_temperature; break;
        case shs::etoi(m::PRESSURE): return data.pressure; break;

        default: return 0;
            break;
    }
    return 0;
}









