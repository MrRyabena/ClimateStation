#pragma once

#include <memory>

// #include "SimplePortal/SimplePortal.cpp"


#include "GUIcore/Widget.h"
#include "GUIcore/Label.h"
#include "Image.h"

#include "GUIcore/shs_ThemeColors.h"

#include "shs_ControlWiFi.h"


#include "shs_ClimateStation.h"
#include "shs_ClimateStationStorage.h"


namespace shs
{
    class PortalWindow;
}


class shs::PortalWindow : public shs::Widget
{
public:
    PortalWindow(std::shared_ptr<TFT_eSPI> tft, std::shared_ptr<shs::ClimateStation> climate_station, std::shared_ptr<shs::ClimateStationStorage> storage)
        : Widget(tft, 0, 0, 320, 240), m_cls(climate_station), m_storage(storage)
    {}

    void start() override;
    void tick() override;



    std::vector<std::shared_ptr<shs::Widget>> buttons;

protected:
    static constexpr auto m_BUTTON_SIZE = 40;
    std::shared_ptr<shs::ClimateStation> m_cls;
    std::shared_ptr<shs::ClimateStationStorage> m_storage;
};
