
#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include <SD.h>

#include <shs_types.h>


#include "GUIcore/types.h"
#include "GUIcore/Point.h"
#include "shs_ClimateStation.h"
#include "shs_ClimateStationStorage.h"
#include "shs_ClimateStationData.h"

#define SHS_SF_DEBUG
#define DEBUG
#include <shs_debug.h>

namespace shs
{
    class ChartAnalyzer;
}


class shs::ChartAnalyzer
{
public:

    shs::ClimateStationData min_values;
    shs::ClimateStationData max_values;

    ChartAnalyzer(std::shared_ptr<shs::ClimateStationStorage> storage, shs::t::shs_coord_t width, shs::t::shs_coord_t height);
    ~ChartAnalyzer();

    bool addFile(const shs::t::shs_string_t& fname);

    bool beginPoints();
    bool getNextPoint(shs::Point<> &point, shs::ClimateStationMetrics metric);
    bool openNextFile();
    void endPoints();


protected:
    std::shared_ptr<shs::ClimateStationStorage> m_storage;
    std::vector<shs::t::shs_string_t> m_files;
    uint16_t m_cursor{};
    File m_file{};
    shs::t::shs_coord_t m_width;
    shs::t::shs_coord_t m_height;

    shs::t::shs_float_t m_getMetric(const shs::ClimateStationData &data, shs::ClimateStationMetrics metric);
};
