#pragma once

#include <memory>

#include <TFT_eSPI.h>

#include "GUIcore/Widget.h"
#include "GUIcore/Label.h"
#include "GUIcore/RectWidget.h"
#include "GUIcore/shs_ThemeColors.h"
#include "GUIcore/IndicatorWidget.h"

#include "shs_ClimateStation.h"

#include "Image.h"

namespace shs
{
    class ChartWindow;
}



class shs::ChartWindow : public shs::Widget
{
public:
    ChartWindow(std::shared_ptr<TFT_eSPI> tft, std::shared_ptr<shs::ClimateStationStorage> storage);

    void start() override;
    void tick()override;

    std::vector<std::shared_ptr<shs::Widget>> buttons;

protected:
    static constexpr auto m_BUTTON_SIZE = 40;
    std::shared_ptr<shs::ClimateStationStorage> m_storage;
};
