#pragma once

#include <memory>


#include "GUIcore/Widget.h"
#include "GUIcore/Label.h"
#include "GUIcore/RectWidget.h"
#include "GUIcore/shs_ThemeColors.h"

#include "shs_ClimateStationStorage.h"
#include "Image.h"



namespace shs
{
    class FirstWindow;
}


class shs::FirstWindow : public shs::Widget
{
public:
    FirstWindow(std::shared_ptr<TFT_eSPI> tft, std::shared_ptr<shs::ClimateStationStorage> storage)
        : Widget(tft, 0, 0, 320, 240), m_storage(storage)
    {}

    void start() override;


protected:
    std::shared_ptr<shs::ClimateStationStorage> m_storage;
};
