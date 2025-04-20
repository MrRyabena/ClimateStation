#pragma once

#include <SPI.h>
#include <SD.h>

#include <shs_debug.h>

namespace shs
{
    class SDCard;
}


class shs::SDCard
{
public:
    enum class Status : uint8_t { CARD_NONE, CARD_UNKNOWN, CARD_OK };


    SDCard(const uint8_t CS, const uint8_t MOSI, const uint8_t MISO, const uint8_t SCK)
        : m_CS(CS), m_MOSI(MOSI), m_MISO(MISO), m_SCK(SCK), m_spi(VSPI)
    {
        pinMode(m_CS, OUTPUT);
        digitalWrite(m_CS, HIGH);
    }

    bool begin();

    Status getStatus() const { return m_status; }

    void end()
    {
        SD.end();
        m_spi.end();
        digitalWrite(m_CS, HIGH);
    }

    String readTest()
    {
        if (m_status != Status::CARD_OK)
        {
            return "SD Card not ready";
        }

        File file = SD.open("/test.txt");
        if (!file)
        {
            return "Failed to open file";
        }

        String str = file.readString();
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
