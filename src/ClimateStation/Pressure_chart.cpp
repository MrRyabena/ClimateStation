#include "Pressure_chart.h"


shs::Pressure_chart::Pressure_chart(std::shared_ptr<shs::ClimateStationStorage> storage, std::shared_ptr<TFT_eSPI> tft, std::shared_ptr<shs::ChartAnalyzer> analyzer, shs::t::shs_coord_t set_x, shs::t::shs_coord_t set_y, shs::t::shs_coord_t set_width, shs::t::shs_coord_t set_height)
    : Widget(tft, set_x, set_y, set_width, set_height), chart(tft.get()), tracer(&chart),
    m_analyzer(analyzer), m_storage(storage)
{}


void shs::Pressure_chart::start()
{
    chart.createGraph(width, height, shs::utils::rgb565(background_color));
    chart.setGraphPosition(x, y);
   

    chart.setGraphGrid(m_analyzer->min_values.time / 60, 120.0, 720, 10, shs::utils::rgb565(shs::ThemeColors::BACKGROUND_LIGHT));
    chart.setGraphScale(m_analyzer->min_values.time / 60, m_analyzer->max_values.time / 60, 720, 780);
    chart.drawGraph(x, y);

    shs::Point<> p;
    m_analyzer->beginPoints();

        
    tracer.startTrace(shs::utils::rgb565(shs::ThemeColors::LIGHT));
    while (m_analyzer->getNextPoint(p, shs::ClimateStationMetrics::PRESSURE))
    {
        tracer.addPoint(p.x, pressureToMmHg(p.y));
        yield();

        // dout(p.x); doutln(p.y);
    }

    m_analyzer->endPoints();


    Widget::start();
}



