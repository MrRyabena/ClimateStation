#pragma once

#include <memory>


#include "GUIcore/Widget.h"
#include "GUIcore/Label.h"
#include "GUIcore/shs_ThemeColors.h"

#include <AutoOTA.h>

namespace shs
{
    class UpdateWindow;
}


class shs::UpdateWindow : public shs::Widget
{
public:
    UpdateWindow(std::shared_ptr<TFT_eSPI> tft, const char* version)
        : Widget(tft, 0, 0, 320, 240), m_version(version)
    {}

    void start() override;



protected:
    const char* m_version;
};
