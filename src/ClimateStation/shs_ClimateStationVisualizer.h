#include "shs_ClimateStation.h"


#include <memory>
#include <vector>
#include <stdint.h>
#include <Arduino.h>

#include <SPI.h>
#include <TFT_eSPI.h>       // https://github.com/Bodmer/TFT_eSPI

#include <FastLED.h>

#include <shs_Process.h>
#include <shs_ProgramTime.h>
#include <shs_ProgramTimer.h>
#include <shs_types.h>

#include "shs_ClimateStation.h"
#include "shs_ClimateStationStorage.h"

#include "MainWindow.h"
#include "ChartWindow.h"
#include "GUIcore/shs_ThemeColors.h"
#include "GUIcore/utils.h"


class shs::ClimateStationVisualizer : public shs::Process
{
public:
    static constexpr auto TICK_TIME = 10'000;

    ClimateStationVisualizer(
        std::shared_ptr<shs::ClimateStation> climate_station,
        std::shared_ptr<shs::ClimateStationStorage> storage,
        std::shared_ptr<TFT_eSPI> tft, uint8_t tft_led_pin,
        uint16_t leds_num, shs::t::shs_pin_t leds_pin
    );

    ~ClimateStationVisualizer() = default;


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


    std::shared_ptr<shs::MainWindow> m_main_window;
    std::shared_ptr<shs::ChartWindow> m_chart_window;

    // To store the touch coordinates
    uint16_t m_touch_x{};
    uint16_t m_touch_y{};

    shs::ProgramTime m_main_tmr;
    shs::ProgramTime m_sleep_tmr;
    shs::ProgramTime m_button_tmr;

    static constexpr auto m_SLEEP_TIMEOUT = 120'000;     // 2 minutes
    static constexpr auto m_BUTTON_TIMEOUT = 200;        // 200 milliseconds


    static constexpr auto M_MIN_CO2 = 400u;
    static constexpr auto M_MAX_CO2 = 2200u;
    static constexpr auto M_MIN_COLOR_H = HUE_RED;
    static constexpr auto M_MAX_COLOR_H = HUE_GREEN;

    void m_updateLED();

    const uint8_t m_tft_LED_pin;
    bool m_tft_enabled{};

    void m_touch_calibrate();
    void m_touch_tick();

    void m_enable_MainWindow();
    void m_disable_MainWindow();

    void m_enable_ChartWindow();
    void m_disable_ChartWindow();
};
