#define DEBUG
#define SHS_SF_DEBUG

#include "settings.h"
#include <shs_settings.h>

#include <shs_debug.h>
#include <shs_ControlWiFi.h>

#include <LittleFS.h>
#include <shs_lib_MHZ19.h>
#include <shs_ProgramTime.h>

#include <FastBot.h>

FastBot bot(shs::settings::SHS_WS_BOT_TOCKEN);


shs::ProgramTime timer;
static constexpr auto updateT = 60'000;

shs::MHZ19 sensor(D1, D2);

struct CSdata
{
    int32_t co2{};
    int32_t temp{};
};

void CS_tick();
void CS_start();
void CS_save();

void setup() {
  dinit();
  shs::ControlWiFi::connectWiFi();
  delay(2000);
  CS_start();
  botSetup();
}


void loop() {
  CS_tick();
  telegramBot();
}
