#pragma once

#include <memory>

#include <Stamp.h>

#include "GUIcore/Widget.h"
#include "GUIcore/Label.h"
#include "GUIcore/RectWidget.h"
#include "GUIcore/shs_ThemeColors.h"
#include "GUIcore/IndicatorWidget.h"

#include "shs_ClimateStation.h"
#include "shs_ClimateStationStorage.h"
#include "Image.h"

#define DEBUG
#define SHS_SF_DEBUG
#include <shs_debug.h>

namespace shs
{
    class MainWindow;
}


class shs::MainWindow : public shs::Widget
{
public:
    MainWindow(std::shared_ptr<TFT_eSPI> tft, std::shared_ptr<shs::ClimateStation> climate_station, std::shared_ptr<shs::ClimateStationStorage> storage)
        : Widget(tft, 0, 0, 320, 240), m_cls(climate_station), m_storage(storage)
    {}

    void start() override;
    void tick() override;

    void updateData(const shs::ClimateStation::Data& data);

    std::vector<std::shared_ptr<shs::Widget>> buttons;

protected:
    static constexpr auto m_BUTTON_SIZE = 40;
    std::shared_ptr<shs::ClimateStation> m_cls;
    std::shared_ptr<shs::ClimateStationStorage> m_storage;
};
