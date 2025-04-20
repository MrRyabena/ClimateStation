#pragma once

#include <memory>

#include "GUIcore/Widget.h"
#include "GUIcore/Label.h"
#include "GUIcore/RectWidget.h"
#include "GUIcore/shs_ThemeColors.h"

namespace shs
{
    class MainWindow;
}


class shs::MainWindow : public shs::Widget
{
public:
    MainWindow(std::shared_ptr<TFT_eSPI> tft) : Widget(tft, 0, 0, 320, 240) {}

    void start() override;
    void tick() override;

};
