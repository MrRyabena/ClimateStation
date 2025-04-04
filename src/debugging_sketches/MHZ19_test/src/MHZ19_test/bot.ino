

void handleBot(FB_msg& message);

void botSetup()
{

#ifdef BOT_UPDATE_TIME
    bot.setPeriod(BOT_UPDATE_TIME);
#endif
    bot.attach(handleBot);

    bot.setTextMode(FB_HTML);
    botSendNotification("I am started!");
}

void telegramBot()
{

#ifdef BOT_ACTIVE
    static bool botSetup_flag{};
    if (shs::ControlWiFi::WiFiConnected() && !botSetup_flag)
    {
        botSetup_flag = true;
        botSetup();
    }
    bot.tick();

#endif
}

void botSendNotification(const String& message)
{
#ifdef BOT_ACTIVE

    bot.sendMessage("<b><u><i>SYSTEM NOTIFICATION!</i></u>\n" + message + "</b>", shs::settings::CHAT_ID);

#endif
}



void handleBot(FB_msg& message)
{
    if (message.OTA && message.text.equals(F("/OTA")))
    {
        if (message.fileName.indexOf("mklittlefs") > 0 || message.fileName.indexOf("spiffs") > 0)
        {
            bot.updateFS();  // update spiffs
        }
        else
        {
            bot.update();  // update sketch
        }
    }

    auto ind = message.text.indexOf('@');
    if (ind != -1)
        if (message.text.indexOf(BOT_NAME) != -1) message.text.remove(ind, strlen(BOT_NAME + 1));
    if (message.text.startsWith("/")) message.text.remove(0, 1);


    if (message.text.startsWith("getdata"))
    {

        String str = "CO2:   ";
        str.reserve(30);

        str += sensor.getValueI();
        str += " ppm\nTemp:  ";
        str += sensor.getValueI(shs::MHZ19::TEMPERATURE);
        str += " *C";

        bot.sendMessage(str, message.chatID);
    }

    else if (message.text.startsWith("getfile"))
    {
        bot.sendMessage("Sending...", message.chatID);

        File file = LittleFS.open(CS_FILE_NAME, "r");

        String name = "csd_";
        name.reserve(15);
        name += bot.getUnix();
        name += ".shsf";

        bot.sendFile(file, FB_DOC, name, message.chatID);
        file.close();
    }

    else if (message.text.startsWith("resetfile"))
    {
        if (message.chatID == shs::settings::CHAT_ID)
        {
            botSendNotification("Reset file!");
            bot.sendMessage("Sending current file...", message.chatID);
            File file = LittleFS.open(CS_FILE_NAME, "r");

            String name = "сsd_";
            name.reserve(15);
            name += bot.getUnix();
            name += ".shsf";

            bot.sendFile(file, FB_DOC, name, message.chatID);
            file.close();

            LittleFS.remove(CS_FILE_NAME) ? botSendNotification("The file has been reset!") : botSendNotification("Error!");
        }
    }

}
