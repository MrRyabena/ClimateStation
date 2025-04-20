#include "shs_ClimateStation.h"


#include <memory>

//#include <microLED.h>

#include <SPI.h>
#include <TFT_eSPI.h>       // https://github.com/Bodmer/TFT_eSPI


#include <shs_Process.h>
#include <shs_ProgramTime.h>

#include <shs_debug.h>


class shs::ClimateStationVisualizer : public shs::Process
{
public:
    static constexpr auto TICK_TIME = 10'000;

    ClimateStationVisualizer(
        shs::ClimateStation& climate_station,
        std::shared_ptr<TFT_eSPI> tft//,
        //    std::shared_ptr<microLED> aled
    );

    /*
    21:31:41.039 -> // Use this calibration code in setup():
21:31:41.039 ->   uint16_t calData[5] = { 314, 3494, 332, 3321, 7 };
21:31:41.039 ->   tft.setTouch(calData);
*/

    void start() override;
    void tick() override;
    void stop() override {}

    void printDebug(const String& str, const uint16_t x, const uint16_t y);

protected:
    std::shared_ptr<TFT_eSPI> m_tft;
    shs::ClimateStation& m_cls;
    //    std::shared_ptr<microLED> m_aled;

    shs::ProgramTime m_main_tmr;

    constexpr uint16_t m_rgb565(const uint8_t r, const uint8_t g, const uint8_t b) const 
    {
        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }

    constexpr uint16_t m_rgb565(const uint32_t rgb) { return m_rgb565(rgb >> 16, rgb >> 8, rgb); }

};
