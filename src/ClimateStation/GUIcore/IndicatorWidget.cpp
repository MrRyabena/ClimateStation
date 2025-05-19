#include "IndicatorWidget.h"

shs::IndicatorWidget::IndicatorWidget(std::shared_ptr<TFT_eSPI> tft,
    const shs::t::shs_coord_t set_x, const shs::t::shs_coord_t set_y,
    const shs::t::shs_coord_t set_width, const shs::t::shs_coord_t set_height,
    const shs::t::shs_string_t& set_unit,
    const shs::t::shs_font_t set_value_font, const shs::t::shs_font_t set_unit_font,
    const shs::t::shs_coord_t set_value_size, const shs::t::shs_coord_t set_unit_size,
    const shs::t::shs_color_t set_foreground_color, const shs::t::shs_color_t set_background_color,
    const uint8_t set_value_align, const uint8_t set_unit_align)
    : Widget(tft, set_x, set_y, set_width, set_height),
    m_unit(set_unit),
    value_font(set_value_font), unit_font(set_unit_font),
    value_size(set_value_size), unit_size(set_unit_size),
    value_align(set_value_align), unit_align(set_unit_align),
    foreground_color(set_foreground_color), background_color(set_background_color),
    value_horizontal_margin(5)

{
    if (!m_tft) return;

    if (height == 0)
    {
        m_tft->setTextFont(value_font);
        m_tft->setTextSize(value_size);

        height = m_tft->fontHeight();
    }

    m_tft->setTextFont(unit_font);
    m_tft->setTextSize(unit_size);

    m_unit_width = m_tft->textWidth(set_unit);
    m_unit_height = m_tft->fontHeight();

    unit_vertical_margin = m_unit_height / 4;
    unit_horizontal_margin = -(m_unit_width + 4);
}


void shs::IndicatorWidget::draw(const shs::t::shs_string_t& value, const ValueTrend trend, const shs::t::shs_color_t color)
{
    if (!m_tft) return;

    m_tft->setTextColor(shs::utils::rgb565(foreground_color), shs::utils::rgb565(background_color));


    // draw background

    m_tft->fillRect(x, y, width, height, shs::utils::rgb565(background_color));


    // print value

    m_tft->setTextFont(value_font);
    m_tft->setTextSize(value_size);

    shs::t::shs_coord_t value_width = m_tft->textWidth(value);
    shs::Widget value_widget(m_tft, 0, 0, value_width, height);
    shs::Widget::setAligned(*this, value_widget, value_align, value_horizontal_margin, value_vertical_margin);

    drawArrow(value_widget, trend, color);

    value_widget.x += value_widget.height / 2 + value_horizontal_margin;

    m_tft->setCursor(value_widget.x, value_widget.y);

    m_tft->print(value);


    // print unit

    m_tft->setTextFont(unit_font);
    m_tft->setTextSize(unit_size);

    auto unit_coords = shs::Widget::getAligned(value_widget, shs::Widget(m_tft, 0, 0, m_unit_width, m_unit_height),
        shs::Widget::RIGHT | shs::Widget::BOTTOM, unit_horizontal_margin, unit_vertical_margin);

    m_tft->setCursor(unit_coords.first, unit_coords.second);

    m_tft->print(m_unit);

}


void shs::IndicatorWidget::setUnit(const shs::t::shs_string_t& unit)
{
    m_unit = unit;

    m_tft->setTextFont(unit_font);
    m_tft->setTextSize(unit_size);

    m_unit_width = m_tft->textWidth(unit);
    m_unit_height = m_tft->fontHeight();
}


void shs::IndicatorWidget::drawArrow(const shs::Widget& base, const ValueTrend trend, const shs::t::shs_color_t color)
{
    if (!m_tft) return;

    auto h = base.height / 4;
    auto a = 2 * h;

    switch (trend)
    {
        case ValueTrend::INCREASING:
            {

                auto y0 = base.y + base.height - 0.75 * height / 2;

                m_tft->fillTriangle(
                    base.x,                                               // x1
                    y0,                                                   // y1
                    base.x + a,                                           // x2
                    y0,                                                   // y2
                    base.x + h,                                           // x3
                    y0 - h,                                               // y3
                    color ? shs::utils::rgb565(color) : TFT_GREEN);
            }
            break;
        case ValueTrend::DECREASING:
            {
                auto y0 = base.y + base.height - 0.75 * height / 2;

                m_tft->fillTriangle(
                    base.x,                                               // x1
                    y0 - h,                                               // y1
                    base.x + a,                                           // x2
                    y0 - h,                                               // y2
                    base.x + h,                                           // x3
                    y0,                                                   // y3 
                    color ? shs::utils::rgb565(color) : TFT_RED);
            }
            break;
        case ValueTrend::CONST:
            {
                auto y0 = base.y + (base.height - a) / 2;
                auto x0 = base.x + h / 2;

                m_tft->fillTriangle(
                    x0,                                                   // x1
                    y0,                                                   // y2
                    x0,                                                   // x2
                    y0 + a,                                               // y2
                    x0 + h,                                               // x3
                    y0 + h,                                               // y3
                    color ? shs::utils::rgb565(color) : TFT_YELLOW);
            }
            break;
        default:
            break;
    }
}


