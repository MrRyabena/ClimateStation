#pragma once

#include <memory>
#include <vector>

#include <TFT_eSPI.h>

#include "GUIcore/Widget.h"
#include "GUIcore/Label.h"
#include "GUIcore/RectWidget.h"
#include "GUIcore/shs_ThemeColors.h"
#include "GUIcore/IndicatorWidget.h"
#include "GUIcore/ValueControl.h"

#include "CO2_chart.h"

#include "shs_ClimateStation.h"

#include <shs_debug.h>

#include "Image.h"

namespace shs
{
    class SettingsWindow;
}



class shs::SettingsWindow : public shs::Widget
{
public:
    SettingsWindow(std::shared_ptr<TFT_eSPI> tft, std::shared_ptr<shs::ClimateStation> climate_station, std::shared_ptr<shs::ClimateStationStorage> storage);

    void start() override;
    void tick() override;

    bool configChanged() { return m_config_changed; }

    std::vector<std::shared_ptr<shs::Widget>> buttons;

protected:
    static constexpr auto m_BUTTON_SIZE = 40;
    std::shared_ptr<shs::ClimateStationStorage> m_storage;
    std::shared_ptr<shs::ClimateStation> m_climate_station;
    std::vector<std::shared_ptr<shs::ValueControl<uint16_t>>> m_vc;

    // To store the touch coordinates
    uint16_t m_touch_x{};
    uint16_t m_touch_y{};

    bool m_config_changed{};
};
