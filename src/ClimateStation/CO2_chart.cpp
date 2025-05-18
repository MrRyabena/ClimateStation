#include "CO2_chart.h"


shs::CO2_chart::CO2_chart(std::shared_ptr<shs::ClimateStationStorage> storage, std::shared_ptr<TFT_eSPI> tft, std::shared_ptr<shs::ChartAnalyzer> analyzer, shs::t::shs_coord_t set_x, shs::t::shs_coord_t set_y, shs::t::shs_coord_t set_width, shs::t::shs_coord_t set_height)
    : Widget(tft, set_x, set_y, set_width, set_height), chart(tft.get()), tracer(&chart),
    m_analyzer(analyzer), m_storage(storage)
{}


void shs::CO2_chart::start()
{
    chart.createGraph(width, height, shs::utils::rgb565(background_color));
    chart.setGraphPosition(x, y);
    dout(x); dout(y); dout(width); doutln(height);



    chart.setGraphGrid(m_analyzer->min_values.time / 60, 120.0, 0.0, 500.0, shs::utils::rgb565(shs::ThemeColors::BACKGROUND_LIGHT));
    chart.setGraphScale(m_analyzer->min_values.time / 60, m_analyzer->max_values.time / 60, 0.0, 3000.0);
    chart.drawGraph(x, y);

    shs::Point<> p;
    m_analyzer->beginPoints();

    dout(m_analyzer->min_values.time / 60); doutln(m_analyzer->max_values.time / 60);
    
    tracer.startTrace(shs::utils::rgb565(shs::ThemeColors::LIGHT));
    while (m_analyzer->getNextPoint(p, shs::ClimateStationMetrics::CO2))
    {
        tracer.addPoint(p.x, p.y);

        // dout(p.x); doutln(p.y);
    }


    Widget::start();
}



