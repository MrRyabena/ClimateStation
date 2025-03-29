#include "shs_ClimateStation.h"

shs::ClimateStation::ClimateStation(std::shared_ptr<shs::MHZ19> mhz19, std::shared_ptr<shs::BME280> bme, std::shared_ptr<shs::DHT> dht)//, std::shared_ptr<shs::GyverDS3231> m_rtc)
    : m_mhz19(mhz19), m_bme(bme), m_dht(dht)//, m_rtc(rtc)
{}

void shs::ClimateStation::start()
{
    m_mhz19->setup();
    m_bme->setup();


   // m_rtc.setup();

}

void shs::ClimateStation::tick()
{
    //m_rtc.tick();
}
