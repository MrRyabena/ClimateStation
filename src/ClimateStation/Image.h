#pragma once

#include <memory>
#include <stdint.h>

#include <TFT_eSPI.h>


#include "GUIcore/Widget.h"
#include "GUIcore/types.h"
#include "shs_ClimateStationStorage.h"
#include "shs_ByteCollector.h"


namespace shs
{
    class Image;
}


class shs::Image : public shs::Widget
{
public:
    Image(std::shared_ptr<shs::ClimateStationStorage> storage, const shs::t::shs_string_t& fname,
        std::shared_ptr<TFT_eSPI> tft,
        shs::t::shs_coord_t set_x = 0, shs::t::shs_coord_t set_y = 0,
        shs::t::shs_coord_t set_width = 0, shs::t::shs_coord_t set_height = 0);

    void loadImage();
    void drawImage(bool clear_buffer = true);
    void clearBuffer();

    void start() override;
    void tick() override;
    void stop() override;

protected:
    shs::ByteCollector<uint8_t, uint32_t> m_pixels;
    shs::t::shs_string_t m_fname;
    std::shared_ptr<shs::ClimateStationStorage> m_storage;
};
