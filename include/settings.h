#ifndef XFILMEE_SETTINGS_H
#define XFILMEE_SETTINGS_H

typedef struct {
    int volume;
    int theme;
    int resolution;
} Settings;

extern Settings app_settings;

void settings_reset(void);

#endif

