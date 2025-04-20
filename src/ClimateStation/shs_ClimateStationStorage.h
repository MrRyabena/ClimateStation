#pragma once


#include <SPI.h>
#include <SD.h>

#include "shs_ClimateStation.h"


class shs::ClimateStationStorage : public shs::Process
{
public:

    enum class Status : uint8_t { CARD_NONE, CARD_UNKNOWN, CARD_OK };


    ClimateStationStorage(const uint8_t CS, const uint8_t MOSI, const uint8_t MISO, const uint8_t SCK)
        : m_CS(CS), m_MOSI(MOSI), m_MISO(MISO), m_SCK(SCK), m_spi(VSPI)
    {}

    bool begin();

    Status getStatus() const { return m_status; }

    void end()
    {
        SD.end();
        m_spi.end();
    }

    String readTest() 
    {
      auto file = SD.open("/test.txt");
      auto str = file.readString();
      file.close();
      return str;
    }

private:
    SPIClass m_spi;

    Status m_status;

    const uint8_t m_CS;
    const uint8_t m_MOSI;
    const uint8_t m_MISO;
    const uint8_t m_SCK;
};
