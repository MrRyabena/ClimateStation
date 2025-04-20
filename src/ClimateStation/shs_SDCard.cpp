#include "shs_SDCard.h"

bool shs::SDCard::begin()
{
    m_spi.begin(m_SCK, m_MISO, m_MOSI, m_CS);

    bool result = SD.begin(m_CS, m_spi);

    if (!result)
    {
        uint8_t cardType = SD.cardType();
        switch (cardType)
        {
            case CARD_NONE: m_status = Status::CARD_NONE; break;
            case CARD_MMC: [[fallthrough]];
            case CARD_SD: [[fallthrough]];
            case CARD_SDHC: [[fallthrough]];
            default: m_status = Status::CARD_UNKNOWN; break;
        }
    }
    else
    {
        m_status = Status::CARD_OK;
    }

    return result;
}
