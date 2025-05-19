#pragma once

#include <vector>
#include <memory>
#include <algorithm>


#include <shs_Process.h>
#include <shs_ProgramTimer.h>

#include "shs_ClimateStation.h"
#include "shs_ClimateStationStorage.h"
#include "shs_ClimateStationData.h"
#include "shs_Approximation.h"

#include "GUIcore/IndicatorWidget.h"
#include <shs_utils.h>


namespace shs
{
    class ClimateStationStatistics;
}


class shs::ClimateStationStatistics : public shs::Process
{
public:
    ClimateStationStatistics(std::shared_ptr<shs::ClimateStation> climate_station, std::shared_ptr<shs::ClimateStationStorage> storage);

    void start() override;
    void tick() override;
    void stop() override {}

    shs::IndicatorWidget::ValueTrend getTrend(shs::ClimateStationMetrics metric);

protected:
    std::shared_ptr<shs::ClimateStationStorage> m_storage;
    std::shared_ptr<shs::ClimateStation> m_climate_station;
    std::vector<shs::ClimateStationData> m_data;

    static constexpr auto m_TICK_TIMEOUT = 30'000;
    static constexpr auto m_PERIOD = 600'000;

    shs::ProgramTimer m_tick_tmr;
    void m_addData(const shs::ClimateStationData& data);

    shs::IndicatorWidget::ValueTrend m_getTrend(shs::t::shs_float_t a);
};
