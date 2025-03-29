#include "shs_ClimateStation.h"


#include <memory>

#include <microLED.h>

#include <shs_Process.h>



class shs::ClimateStationVisualizer : public shs::Process
{
public:
    ClimateStationVisualizer(
        shs::ClimateStation& climate_station,
        std::shared_ptr<TFT_eSPI> tft,
        std::shared_ptr<microLED> aled
    );

    void start() override;
    void tick() override;
    void stop() override;

protected:
    std::shared_ptr<TFT_eSPI> m_tft;
    std::shared_ptr<microLED> m_aled;

};
