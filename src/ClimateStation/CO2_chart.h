#pragma once

#include <memory>

#include <TFT_eSPI.h>
#include <TFT_eWidget.h>   // https://github.com/Bodmer/TFT_eWidget

#include <shs_types.h>

#include "GUIcore/Widget.h"
#include "GUIcore/types.h"
#include "GUIcore/shs_ThemeColors.h"
#include "GUIcore/Point.h"
#include "GUIcore/utils.h"
#include "shs_ClimateStationStorage.h"
#include "ChartAnalyzer.h"
#include "shs_ClimateStationData.h"

#include <shs_debug.h>

namespace shs
{
    class CO2_chart;
}


class shs::CO2_chart : public shs::Widget
{
public:
    shs::t::shs_color_t background_color = shs::ThemeColors::BACKGROUND;

    GraphWidget chart;
    TraceWidget tracer;

    CO2_chart(std::shared_ptr<shs::ClimateStationStorage> storage, std::shared_ptr<TFT_eSPI> tft, std::shared_ptr<shs::ChartAnalyzer> analyzer,
        shs::t::shs_coord_t set_x, shs::t::shs_coord_t set_y, shs::t::shs_coord_t set_width, shs::t::shs_coord_t set_height);

    void start() override;




protected:
    std::shared_ptr<shs::ClimateStationStorage> m_storage;
    std::shared_ptr<shs::ChartAnalyzer> m_analyzer;

};
