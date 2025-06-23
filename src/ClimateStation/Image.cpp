#include "Image.h"

shs::Image::Image(std::shared_ptr<shs::ClimateStationStorage> storage, const shs::t::shs_string_t& fname, std::shared_ptr<TFT_eSPI> tft, shs::t::shs_coord_t set_x, shs::t::shs_coord_t set_y, shs::t::shs_coord_t set_width, shs::t::shs_coord_t set_height)
    : m_storage(storage), m_fname("/SHS/SHS_ClimateStation/images/" + fname), Widget(tft, set_x, set_y, set_width, set_height)
{
    uint32_t size{};
    auto res = m_storage->readFile(m_fname, reinterpret_cast<uint8_t*>(&size), sizeof(size));
    if (res && (width == 0 || height == 0)) { width = size >> 16; height = size & 0xffff; }
}


void shs::Image::loadImage()
{
    if (m_pixels.empty())
    {
        m_pixels.reserve(width * height * 2 + 4);
        auto size = m_storage->readFile(m_fname, m_pixels.getPtr(), m_pixels.capacity_back());
        m_pixels.setPositionBack(size);
    }
}


void shs::Image::drawImage(const bool clear_buffer)
{
    if (m_pixels.size() == width * height * 2 + 4) m_tft->pushImage(x, y, width, height, reinterpret_cast<const uint16_t*>(m_pixels.getPtr() + 4));
    if (clear_buffer) clearBuffer();
}


void shs::Image::clearBuffer()
{
    m_pixels.reset();
    m_pixels.shrink_to_fit();
}


void shs::Image::start()
{
    m_tft->setSwapBytes(true);

    loadImage();
    drawImage();
    Widget::start();
}


void shs::Image::tick()
{
    Widget::tick();
}


void shs::Image::stop()
{
    clearBuffer();
}


