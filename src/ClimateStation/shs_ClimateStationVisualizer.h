#include "shs_ClimateStation.h"


#include <memory>
#include <Arduino.h>
//#include <microLED.h>

#include <SPI.h>
#include <TFT_eSPI.h>       // https://github.com/Bodmer/TFT_eSPI


#include <shs_Process.h>
#include <shs_ProgramTime.h>

#include "shs_ClimateStation.h"
#include "shs_ClimateStationStorage.h"
#include "GUIcore/shs_ThemeColors.h"


class shs::ClimateStationVisualizer : public shs::Process
{
public:
    static constexpr auto TICK_TIME = 10'000;

    ClimateStationVisualizer(
        std::shared_ptr<shs::ClimateStation> climate_station,
        std::shared_ptr<shs::ClimateStationStorage> storage,
        std::shared_ptr<TFT_eSPI> tft,
        uint8_t tft_led_pin
        //,
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

    void enableTFT();
    void disableTFT();

protected:

    std::shared_ptr<TFT_eSPI> m_tft;
    std::shared_ptr<shs::ClimateStation> m_cls;
    std::shared_ptr<shs::ClimateStationStorage> m_storage;

    //    std::shared_ptr<microLED> m_aled;

    shs::ProgramTime m_main_tmr;
    shs::ProgramTime m_sleep_tmr;

    static constexpr auto m_SLEEP_TIMEOUT = 10000;     // 10 seconds

    const uint8_t m_tft_LED_pin;
    bool m_tft_enabled{};


    constexpr uint16_t m_rgb565(const uint8_t r, const uint8_t g, const uint8_t b) const
    {
        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }

    constexpr uint16_t m_rgb565(const uint32_t rgb) { return m_rgb565(rgb >> 16, rgb >> 8, rgb); }

    void m_touch_calibrate();
};
