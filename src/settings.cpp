
#include "settings.h"

Settings app_settings;

void settings_reset(void)
{
    app_settings.volume = 100;
    app_settings.theme = 0;
    app_settings.resolution = 720;
}
