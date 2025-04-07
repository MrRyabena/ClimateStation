#include "shs_ClimateStation.h"


shs::ClimateStation::ClimateStation(std::shared_ptr<shs::MHZ19> mhz19, std::shared_ptr<shs::BME280> bme, std::shared_ptr<shs::DHT> dht, std::shared_ptr<GyverDS3231> rtc, std::shared_ptr<GyverNTP> ntp)
    : m_mhz19(mhz19), m_bme(bme), m_dht(dht), m_rtc(rtc), m_ntp(ntp)
{}


void shs::ClimateStation::start()
{
    if (m_mhz19) m_mhz19->setup();
    if (m_bme) m_bme->setup();

    setStampZone(shs::settings::GMT);
    if (m_rtc) m_rtc->begin();
    if (m_ntp)
    {
        m_ntp->begin(shs::settings::GMT);

        if (m_rtc) m_ntp->attachRTC(*m_rtc);
    }
}


void shs::ClimateStation::tick()
{
    if (m_rtc) m_rtc->tick();
    if (m_ntp) m_ntp->tick();

    if (m_main_tmr.milliseconds() > M_UPDATING_TIMEOUT)
    {
        Data data;
        m_updateSensors();
        m_updateData(data);

        m_main_tmr.reset();
    }
}

void shs::ClimateStation::stop()
{}


void shs::ClimateStation::m_updateSensors()
{
    m_sens_updating_tmr.reset();

    if (m_mhz19) m_mhz19->update();
    if (m_bme)   m_bme->update();
    if (m_dht)   m_dht->update();
}


uint8_t shs::ClimateStation::m_allSensUpdated()
{
    uint8_t out{};

    out |= m_mhz19 && m_mhz19->isUpdated() ? M_SensorsNumbers::MHZ19_b : 0;
    out |= m_bme && m_bme->isUpdated() ? M_SensorsNumbers::BME280_b : 0;
    out |= m_dht && m_dht->isUpdated() ? M_SensorsNumbers::DHT_b : 0;

    out |= m_sens_updating_tmr.milliseconds() >= M_SENS_UPDATING_TIMEOUT ? M_SensorsNumbers::UPDATING_TIMEOUT_b : 0;

    return out;
}


void shs::ClimateStation::m_updateData(Data& data)
{
    m_updateSensors();
    if (m_mhz19) data.CO2 = m_mhz19->getValueI(shs::etoi(shs::MHZ19::Metrics::PPM));
    else data.CO2 = 0;

    if (m_bme)
    {
        doutln(m_bme->getStatus());
        data.pressure = m_bme->getValueFx(shs::etoi(shs::BME280::Metrics::PRESSURE_BAR));
        data.indoor_temperature = m_bme->getValueFx(shs::etoi(shs::BME280::Metrics::TEMPERATURE));
        data.indoor_humidity = m_bme->getValueFx(shs::etoi(shs::BME280::Metrics::HUMIDITY));
    }
    else
    {
        data.pressure = shs::t::shs_fixed_t(0);
        data.indoor_temperature = shs::t::shs_fixed_t(0);
        data.outdoor_temperature = shs::t::shs_fixed_t(0);
    }

    if (m_dht)
    {
        data.outdoor_temperature = m_dht->getValueFx(shs::etoi(shs::DHT::Metrics::TEMPERATURE));
        data.outdoor_humidity = m_dht->getValueFx(shs::etoi(shs::DHT::Metrics::HUMIDITY));
    }
    else
    {
        data.outdoor_temperature = shs::t::shs_fixed_t(0);
        data.outdoor_humidity = shs::t::shs_fixed_t(0);
    }

    if (m_rtc) data.time = Datime(*m_rtc).getUnix();
    else if (m_ntp) data.time = m_ntp->getUnix();
    else data.time = 0;

}


#ifdef SHS_SF_DEBUG
void shs::ClimateStation::debug_print_data(const Data& data) const
{
    dsep();
    doutln("CLIMATE_STATION_DATA\n");
    dout("CO2:                  "); doutln(data.CO2);
    dout("pressure:             "); doutln(static_cast<float>(data.pressure));
    dout("indoor_temperature:   "); doutln(static_cast<float>(data.indoor_temperature));
    dout("outdoor_temperature:  "); doutln(static_cast<float>(data.outdoor_temperature));
    dout("indoor_humidity:      "); doutln(static_cast<float>(data.indoor_humidity));
    dout("outdoor_humidity:     "); doutln(static_cast<float>(data.outdoor_humidity));
    dout("time:                 "); doutln(data.time);
    if (m_ntp) doutln(m_ntp->timeToString());
    if (m_rtc) dout("ds time: "); dout(m_rtc->isOK()); doutln(m_rtc->getTime().timeToString());
    dsep();

}


void shs::ClimateStation::debug_print_status() const
{
    dsep();
    doutln("CLIMATE_STATION_STATUSES");

}
#endif
