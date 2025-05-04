#include "Image.h"

shs::Image::Image(std::shared_ptr<shs::ClimateStationStorage> storage, const shs::t::shs_string_t& fname, std::shared_ptr<TFT_eSPI> tft, shs::t::shs_coord_t set_x, shs::t::shs_coord_t set_y, shs::t::shs_coord_t set_width, shs::t::shs_coord_t set_height)
    : m_storage(storage), m_fname(fname), Widget(tft, set_x, set_y, set_width, set_height)
{}


void shs::Image::loadImage()
{
    if (m_pixels.empty())
    {
        m_pixels.reserve(width * height * 2);
        auto size = m_storage->readFile(m_fname, m_pixels.getPtr(), m_pixels.capacity_back());
        m_pixels.setPositionBack(size);
    }
}


void shs::Image::drawImage(const bool clear_buffer)
{
    if (m_pixels.size() == width * height * 2) m_tft->pushImage(x, y, width, height, reinterpret_cast<const uint16_t*>(m_pixels.getPtr()));
    if (clear_buffer) clear_buffer();
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


