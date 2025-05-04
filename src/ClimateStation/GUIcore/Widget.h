#pragma once

#include <memory>
#include <vector>
#include <utility>

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

    enum Align : uint8_t { LEFT = 0b1, HORIZONTAL_CENTER = 0b10, RIGHT = 0b100, TOP = 0b1000, VERTICAL_CENTER = 0b10000, BOTTOM = 0b100000 };

    shs::t::shs_coord_t x;
    shs::t::shs_coord_t y;
    shs::t::shs_coord_t width;
    shs::t::shs_coord_t height;


    Widget(
        const std::shared_ptr<TFT_eSPI> tft,
        const shs::t::shs_coord_t set_x, const shs::t::shs_coord_t set_y,
        const shs::t::shs_coord_t set_width, const shs::t::shs_coord_t set_height
    );


    [[nodiscard]] bool contain(shs::t::shs_coord_t px, shs::t::shs_coord_t py) const;
    void setPressed(bool pressed);
    bool checkPressed(shs::t::shs_coord_t px, shs::t::shs_coord_t py);
    bool isPressed() const;
    bool justPressed() const;
    bool justReleased() const;


    void start() override { for (auto& w : m_layers) w->start(); };
    void tick()  override { for (auto& w : m_layers) w->tick(); };
    void stop()  override { for (auto& w : m_layers) w->stop(); };

    void setPosition(const shs::t::shs_coord_t px, const shs::t::shs_coord_t py);

    void attachLayer(std::shared_ptr<shs::Widget> ptr) { if (ptr) m_layers.push_back(ptr); }
    void attachLayer(std::shared_ptr<shs::Widget> ptr,
        const uint8_t align = 0,
        const shs::t::shs_coord_t horizontal_margin = 0, const shs::t::shs_coord_t vertical_margin = 0
    );

    static std::pair<shs::t::shs_coord_t, shs::t::shs_coord_t> getAligned(const shs::Widget& w1,
        const shs::Widget& w2, const uint8_t align,
        const shs::t::shs_coord_t horizontal_margin = 0, const shs::t::shs_coord_t vertical_margin = 0);

    static void setAligned(const shs::Widget& w1,
        shs::Widget& w2, const uint8_t align,
        const shs::t::shs_coord_t horizontal_margin = 0, const shs::t::shs_coord_t vertical_margin = 0);


protected:
    std::shared_ptr<TFT_eSPI> m_tft;
    std::vector<std::shared_ptr<shs::Widget>> m_layers;

    // They are not combined in one variable, because of the alignment.
    bool m_pressed{};
    bool m_last_pressed{};
};
