

void CS_start()
{
    sensor.setup();

    LittleFS.begin();

}


void CS_tick()
{
    if (timer.milliseconds() >= updateT)
    {
        CSdata data;
        data.co2 = sensor.getValueI();
        data.temp = sensor.getValueI(shs::MHZ19::TEMPERATURE);

        CS_save(data);

        timer.reset();
    }

}


void CS_save(const CSdata& data)
{
    File file = LittleFS.open(CS_FILE_NAME, "a");
    if (file)
    {
        file.write(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
        file.close();
    }
    else bot.sendMessage("ERROR! file", shs::settings::CHAT_ID);
}
