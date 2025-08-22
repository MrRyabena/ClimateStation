#pragma once

#include <vector>
#include <memory>
#include <stdint.h>

#include <FastBot2.h>         // https://github.com/GyverLibs/FastBot2
#include <Stamp.h>            // https://github.com/GyverLibs/Stamp

#include <LittleFS.h>

#include <shs_Process.h>

#include "shs_ClimateStation.h"
#include "shs_ClimateStationStorage.h"
#include "ChartAnalyzer.h"
#include "settings.h"
#include <shs_settings_private.h>


namespace shs
{
    class ClimateStationTBot;
}


class shs::ClimateStationTBot : public shs::Process
{
public:
    ClimateStationTBot(std::shared_ptr<shs::ClimateStation> climate_station, std::shared_ptr<shs::ClimateStationStorage> storage);

    void handleUpdate(fb::Update& update);
    void handleCommand(fb::Update& u);
    void handleMessage(fb::Update& u);
    void handleDocument(fb::Update& u);
    void handleQuery(fb::Update& u) {}


    void start() override { bot.begin(); bot.skipUpdates(); }
    void tick() override;
    void stop() override { bot.end(); }

    FastBot2 bot;

protected:
    std::shared_ptr<shs::ClimateStation> m_climate_station;
    std::shared_ptr<shs::ClimateStationStorage> m_storage;
    std::vector<std::pair<String, String>> m_users;


};
