#include "shs_ClimateStationTBot.h"


shs::ClimateStationTBot::ClimateStationTBot(std::shared_ptr<shs::ClimateStation> climate_station, std::shared_ptr<shs::ClimateStationStorage> storage)
  : m_climate_station(climate_station), m_storage(storage)
{
    bot.setToken(m_storage->getTBotToken());
    // bot.setToken(SHS_CS_DEFAULT_TBOT_TOKEN);
    // bot.sendMessage(fb::Message("Hi", CHAT_ID));
    bot.setPollMode(fb::Poll::Long, 60000);
    bot.onUpdate([this](fb::Update& update){ this->handleUpdate(update); });
}


void shs::ClimateStationTBot::handleUpdate(fb::Update& update)
{
    if (update.isMessage()) update.message().text().startsWith('/') ? handleCommand(update) : handleMessage(update);
    if (update.isMessage() && update.message().hasDocument()) handleDocument(update);
    if (update.isQuery()) handleQuery(update);
}


void shs::ClimateStationTBot::handleMessage(fb::Update& update)
{
    if (update.message().text().hash() == SH("Получить данные")) handleCommand(update);
}


void shs::ClimateStationTBot::handleCommand(fb::Update& update)
{
    Text chat_id = update.message().chat().id();

    switch (update.message().text().hash()) 
    {   
        case SH("/help"): [[fallthrough]];
        case SH("/start"):
        {
           fb::Message msg;

           msg.text = F("Привет, ");
           msg.text += update.message().from().firstName().toString();
           msg.text += ' ';
           msg.text += update.message().from().lastName().toString();
           msg.text += "!\n\nЯ бот ClimateStation и могу помочь получить актуальную информацию с датчиков. Чтобы узнать текущие показатели пришли мне /getData или воспользуйся специальной кнопкой.\n\n"
            "Я могу присылать данные каждый день в указанное время, для этого отправь \"/notify чч:мм\", где вместо чч:мм укажи время, в которое будут приходить уведомления.\n"
            "Если ты устанешь от моих сообщений, отправь мне /mute, и я перестану их присылать!\n\n";
           
            msg.chatID = chat_id;

            fb::Menu menu;
            menu.addButton(F("Получить данные"));
            msg.setMenu(menu);

            bot.sendMessage(msg);
        }
        break;

        case SH("Получить данные"): [[fallthrough]];
        case SH("/getData"):
        {
            auto data = m_climate_station->getData();
            fb::Message msg;
            
            msg.mode = fb::Message::Mode::HTML;

            msg.text = "<b><i>Общие показатели:</i></b>\n    Атмосферное давление: ";
            msg.text += pressureToMmHg(data.pressure);
            msg.text += " mmHg\n\n<b><i>Снаружи:</i></b>\n    Температура: ";
            msg.text += data.outdoor_temperature.toFloat();
            msg.text += " °C\n    Влажность: ";
            msg.text += data.outdoor_humidity.toFloat();
            msg.text += "%\n\n<b><i>Внутри:</i></b>\n    Температура: ";
            msg.text += data.indoor_temperature.toFloat();
            msg.text += " °C\n    Влажность: ";
            msg.text += data.indoor_humidity.toFloat();
            msg.text += F("%");
            
            msg.chatID = chat_id;

            bot.sendMessage(msg);
        }
        break;

        // case SH("/getWeatherTrend"):
        // {
            
        // }
        // break;

        case SH("/mute"):
        {
            for (auto x = std::begin(m_users); x != std::end(m_users); x++) 
                if (x->first == chat_id.toString()) m_users.erase(x);
            
            fb::Message msg;

            msg.text = "Теперь я больше не буду присылать тебе уведомления(\nЕсли ты захочешь получать их снова, отправь мне \"/notify чч:мм\", где вместо чч:мм укажи время, в которое будут приходить уведомления.";
            msg.chatID = chat_id;

            bot.sendMessage(msg);
        }
        break;

                case SH("/getStorage"):
        {
 
          auto dir = LittleFS.open("/SHS/SHS_ClimateStation/storage/", "r");
    
 
          while (true)
          {
           auto next = dir.openNextFile();
           if (!next) break;
 
           
           fb::File f(next.name(), fb::File::Type::document, next);
           f.chatID = CHAT_ID;
           f.caption = "File";
           bot.sendFile(f);
           
           next.close();
          }
 
           
        }
        break;

        case SH("/clearTouch"):
        {
            LittleFS.remove("/SHS/SHS_ClimateStation/TFT_data/TOUCH_calibration_data.shsf");
            bot.sendMessage(fb::Message("Removed", chat_id));
        }
        break;

        case SH("/clearConfig"):
        {
            LittleFS.remove("/SHS/SHS_ClimateStation/config/config.shsf");
            bot.sendMessage(fb::Message("Removed", chat_id));
        }
        break;

        case SH("/getT"):
        {
            bot.sendMessage(fb::Message(m_storage->getTBotToken(), chat_id));
        }
        break;

        case SH("/getChart"):
        {
            shs::ChartAnalyzer analyzer(m_storage, 320, 240);

            auto fname = shs::ClimateStationStorage::m_getDateFileName(m_climate_station->getData().time);
            analyzer.addFile(fname);

            fb::Message msg;

            msg.text = analyzer.min_values.time;
            msg.text += " - ";
            msg.text += analyzer.max_values.time;
            msg.text += "\n";
            msg.text += analyzer.min_values.pressure.toFloat();
            msg.text += " (";
            msg.text += pressureToMmHg(analyzer.min_values.pressure.toFloat());
            msg.text += ") - ";
            msg.text += analyzer.max_values.pressure.toFloat();
            msg.text += " (";
            msg.text += pressureToMmHg(analyzer.max_values.pressure.toFloat());
            msg.text += ")\n\n";

            shs::Point<> p;
            analyzer.beginPoints();
            int i = 0;
            while (analyzer.getNextPoint(p, shs::ClimateStationMetrics::PRESSURE))
            {
                if (i++ > 10) break;
                msg.text += p.x;
                msg.text += " - ";
                msg.text += pressureToMmHg(p.y);
                msg.text += "\n";
                yield();
            }
            // analyzer.endPoints();

            // msg.text += analyzer.min_values.co2.toFloat();
            // msg.text += " - ";
            // msg.text += analyzer.max_values.co2.toFloat();
            // msg.text += "\n";

            msg.chatID = chat_id;

            bot.sendMessage(msg);
        }
        break;
    }

    if (update.message().text().startsWith(F("/notify")))
    {
        auto time_str = update.message().text().substring(update.message().text().indexOf(' '));
        // Datime time(time_str);
        m_users.push_back({update.message().from().id().toString(), time_str});
        m_storage->saveTBotUsers(m_users);

        fb::Message msg;

        msg.text = "Отлично, теперь я буду присылать показания датчиков каждый день в ";
        msg.text += time_str.toString();
        msg.text += ".\nЕсли хочешь получать несколько уведомлений, можешь добавить время, повторив предыдущую команду.\n"
            "Если ты устанешь от моих сообщений, отправь мне /mute, и я перестану их присылать!";
        
        msg.chatID = chat_id;

        bot.sendMessage(msg);
    }
}


void shs::ClimateStationTBot::handleDocument(fb::Update& update)
{

    Text chat_id = update.message().chat().id();

    if (update.message().document().name().endsWith(".bin") && update.message().caption().startsWith("/OTA"))
    {
        fb::Fetcher fetch = bot.downloadFile(update.message().document().id());
            
        bot.sendMessage(fb::Message(F("OTA started"), update.message().chat().id()));

        bool ok = fetch.updateFlash();

        bot.sendMessage(fb::Message(ok ? "OTA done" : "OTA error", update.message().chat().id()));
    }
    
    switch (update.message().caption().hash()) 
    {
        case SH("/setFile"):
        {
            fb::Fetcher fetch = bot.downloadFile(update.message().document().id());

            if (fetch)
            {
                
                String fname = F("/SHS/SHS_ClimateStation/images/");
                File file = LittleFS.open(fname + update.message().document().name().toString(), "w");
                if (!file) bot.sendMessage(fb::Message("Error!", chat_id));
                fetch.writeTo(file);
                file.close();

                fb::Message msg;
                String str = "File saved: ";
                str += update.message().document().name().toString();
                msg.text = str;
                msg.chatID = chat_id;
                bot.sendMessage(msg);
            }
        }
        break;
    }
}

void shs::ClimateStationTBot::tick()
{
    bot.tick();
}

