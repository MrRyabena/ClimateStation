#pragma once

#include <memory>
#include <vector>

#include <TFT_eSPI.h>

#include <shs_Process.h>


#include "types.h"


namespace shs
{
    class Widget;
}


class shs::Widget : public shs::Process
{
public:

    shs::t::shs_coord_t x;
    shs::t::shs_coord_t y;
    shs::t::shs_coord_t width;
    shs::t::shs_coord_t height;


    Widget(const std::shared_ptr<TFT_eSPI> tft, const shs::t::shs_coord_t set_x, const shs::t::shs_coord_t set_y, const shs::t::shs_coord_t set_width, const shs::t::shs_coord_t set_height);


    [[nodiscard]] bool contain(const shs::t::shs_coord_t px, const shs::t::shs_coord_t py) const { return px >= x && px <= x + width && py >= y && py <= y + height; }

    void start() override { for (auto& x : m_layers) x->start(); };
    void tick() override { for (auto& x : m_layers) x->tick(); };
    void stop() override { for (auto& x : m_layers) x->stop(); };

    void attachLayer(std::shared_ptr<shs::Widget> ptr) { m_layers.push_back(ptr); }

protected:
    std::shared_ptr<TFT_eSPI> m_tft;
    std::vector<std::shared_ptr<shs::Widget>> m_layers;
};
