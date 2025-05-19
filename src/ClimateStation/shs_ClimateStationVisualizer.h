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
#include "SettingsWindow.h"
#include "GUIcore/shs_ThemeColors.h"
#include "GUIcore/utils.h"


class shs::ClimateStationVisualizer : public shs::Process
{
public:
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
    std::shared_ptr<shs::SettingsWindow> m_settings_window;

    // To store the touch coordinates
    uint16_t m_touch_x{};
    uint16_t m_touch_y{};

    static constexpr auto m_TICK_TIMEOUT = 10'000;        // 10 seconds
    static constexpr auto m_BUTTON_TIMEOUT = 200;         // 200 milliseconds
    static constexpr auto m_TFT_TOUCH_CALIBRATION_DATA_SIZE = 5;


    shs::ProgramTimer m_main_tmr;
    shs::ProgramTimer m_sleep_tmr;
    shs::ProgramTimer m_led_tmr;
    shs::ProgramTimer m_smoothing_tmr;
    shs::ProgramTimer m_button_tmr;

    void m_updateLED();
    void m_enableLED();
    void m_disableLED();
    uint8_t m_led_hue{};

    const uint8_t m_tft_LED_pin;

    bool m_tft_enabled{};


    void m_touch_calibrate();
    void m_touch_tick();

    void m_enable_MainWindow();
    void m_disable_MainWindow();

    void m_enable_ChartWindow();
    void m_disable_ChartWindow();

    void m_enable_SettingsWindow();
    void m_disable_SettingsWindow();

    void m_all_disable();
};
