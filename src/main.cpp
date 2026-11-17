
#include <stdint.h>
#include <stdbool.h>

#include "xsdk/gpu.h"
#include "xsdk/kernel.h"
#include "xsdk/log.h"
#include "xsdk/present.h"
#include "xsdk/text.h"

#define BG_COLOR 0xFF101014

typedef struct {
    const char *title;
    const char *description;
} Movie;

static Movie movies[] = {
    {"FILME 01", "Catalogo de filmes"},
    {"FILME 02", "Catalogo de filmes"},
    {"FILME 03", "Catalogo de filmes"},
    {"FILME 04", "Catalogo de filmes"}
};

int main(void)
{
    xsdk_log_write("XFILMEE: iniciando");

    NTSTATUS status = xsdk_gpu_open();

    if (!NT_SUCCESS(status))
        return 1;

    uint32_t width = 0;
    uint32_t height = 0;

    status = xsdk_present_open(
        XSDK_DISPLAY_720P, 2, 1, &width, &height
    );

    if (!NT_SUCCESS(status)) {
        xsdk_gpu_close();
        return 1;
    }

    status = xsdk_text_open();

    if (!NT_SUCCESS(status)) {
        xsdk_present_close();
        xsdk_gpu_close();
        return 1;
    }

    bool running = true;

    while (running) {
        INPUT_STATE input = {0};

        if (XamInputGetState(0, 0, &input) == ERROR_SUCCESS) {
            if (input.gamepad.buttons & INPUT_GAMEPAD_BACK)
                running = false;
        }

        uint32_t address;

        status = xsdk_present_begin(&address, 5000);

        if (!NT_SUCCESS(status))
            break;

        xsdk_gpu_set_target(width, height);

        xsdk_text_draw(
            50, 35, 3, 0xFFFF3333,
            "XFILMEE"
        );

        xsdk_text_draw(
            50, 110, 2, 0xFFFFFFFF,
            "CATALOGO DE FILMES"
        );

        for (uint32_t i = 0; i < 4; i++) {
            xsdk_text_draw(
                60, 180 + i * 65, 2,
                0xFFFFFFFF, movies[i].title
            );

            xsdk_text_draw(
                60, 210 + i * 65, 1,
                0xFFAAAAAA, movies[i].description
            );
        }

        xsdk_gpu_resolve(
            address, width, height, BG_COLOR
        );

        xsdk_present_end();
    }

    xsdk_text_close();
    xsdk_present_close();
    xsdk_gpu_close();

    xsdk_log_write("XFILMEE: encerrado");

    return 0;
}
