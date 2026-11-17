
#include <stdbool.h>
#include <stdint.h>

#include "catalog.h"

#include "xsdk/gpu.h"
#include "xsdk/kernel.h"
#include "xsdk/log.h"
#include "xsdk/present.h"
#include "xsdk/splash.h"
#include "xsdk/text.h"

#define BACKGROUND 0xFF101014
#define RED        0xFFFF3030
#define WHITE      0xFFFFFFFF
#define GRAY       0xFFAAAAAA
#define BLUE       0xFF181828

#define BUFFERS 2
#define SWAP_INTERVAL 1

static void draw_interface(
    uint32_t width,
    uint32_t height,
    unsigned int selected,
    bool details
) {
    uint32_t address;

    NTSTATUS status = xsdk_present_begin(
        &address, 5000
    );

    if (!NT_SUCCESS(status)) {
        xsdk_log_write("XFILMEE: erro ao iniciar frame");
        return;
    }

    xsdk_gpu_set_target(width, height);

    // CABECALHO
    xsdk_text_draw(
        55, 35, 3, RED,
        "XFILMEE"
    );

    xsdk_text_draw(
        55, 105, 1, GRAY,
        "SEU CATALOGO DE FILMES"
    );

    xsdk_text_draw(
        55, 145, 2, WHITE,
        "CATALOGO"
    );

    if (!details) {

        for (unsigned int i = 0;
             i < movie_count; i++) {

            int32_t y = 200 + (int32_t)i * 45;

            if (i == selected) {

                xsdk_text_draw(
                    55, y, 2, RED,
                    ">"
                );

                xsdk_text_draw(
                    85, y, 2, WHITE,
                    movies[i].title
                );

            } else {

                xsdk_text_draw(
                    85, y, 2, GRAY,
                    movies[i].title
                );
            }
        }

        xsdk_text_draw(
            55, 650, 1, GRAY,
            "A: ABRIR  |  BACK: SAIR"
        );

    } else {

        xsdk_text_draw(
            55, 205, 2, RED,
            movies[selected].title
        );

        xsdk_text_draw(
            55, 260, 1, WHITE,
            "DESCRICAO:"
        );

        xsdk_text_draw(
            55, 300, 1, GRAY,
            movies[selected].description
        );

        xsdk_text_draw(
            55, 355, 1, WHITE,
            "CATEGORIA:"
        );

        xsdk_text_draw(
            55, 395, 2, RED,
            movies[selected].category
        );

        xsdk_text_draw(
            55, 650, 1, GRAY,
            "B: VOLTAR"
        );
    }

    xsdk_text_draw(
        55, 690, 1, GRAY,
        "VZNN | XBOX 360"
    );

    xsdk_gpu_resolve(
        address,
        width,
        height,
        BACKGROUND
    );

    xsdk_present_end();

    (void)BLUE;
}

static void run_app(
    uint32_t width,
    uint32_t height
) {
    unsigned int selected = 0;
    bool details = false;
    bool running = true;

    uint16_t previous_buttons = 0;

    while (running) {

        INPUT_STATE input = {0};

        uint32_t result =
            XamInputGetState(0, 0, &input);

        if (result != ERROR_SUCCESS) {
            input = (INPUT_STATE){0};
        }

        uint16_t buttons = input.gamepad.buttons;

        uint16_t pressed =
            buttons & (uint16_t)~previous_buttons;

        previous_buttons = buttons;

        if (pressed & INPUT_GAMEPAD_BACK) {
            break;
        }

        if (!details) {

            if (pressed & INPUT_GAMEPAD_DPAD_UP) {

                if (selected == 0)
                    selected = movie_count - 1;
                else
                    selected--;
            }

            if (pressed & INPUT_GAMEPAD_DPAD_DOWN) {

                selected++;

                if (selected >= movie_count)
                    selected = 0;
            }

            if (pressed & INPUT_GAMEPAD_A) {
                details = true;
            }

        } else {

            if (pressed & INPUT_GAMEPAD_B) {
                details = false;
            }
        }

        draw_interface(
            width,
            height,
            selected,
            details
        );
    }
}

int main(void)
{
    xsdk_log_write("XFILMEE: iniciando");

    NTSTATUS status = xsdk_splash_show(1500);

    if (!NT_SUCCESS(status)) {
        xsdk_log_write("XFILMEE: splash indisponivel");
    }

    status = xsdk_gpu_open();

    if (!NT_SUCCESS(status)) {
        xsdk_log_write("XFILMEE: erro GPU");
        return 1;
    }

    uint32_t width = 0;
    uint32_t height = 0;

    status = xsdk_present_open(
        XSDK_DISPLAY_720P,
        BUFFERS,
        SWAP_INTERVAL,
        &width,
        &height
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

    xsdk_log_write(
        "XFILMEE: tela %ux%u",
        (unsigned)width,
        (unsigned)height
    );

    run_app(width, height);

    xsdk_text_close();

    xsdk_present_close();

    xsdk_gpu_close();

    xsdk_log_write("XFILMEE: encerrado");

    return 0;
}

#include "usb_library.h"

UsbMovie usb_movies[XFILMEE_MAX_USB_MOVIES];

int usb_count = xfilmee_usb_scan(
    "usb:/XFILMEE/FILMES",
    usb_movies,
    XFILMEE_MAX_USB_MOVIES
);

if (usb_count < 0) {
    xsdk_log_write("XFILMEE: USB nao encontrado");
} else {
    xsdk_log_write(
        "XFILMEE: %d filmes encontrados",
        usb_count
    );

    for (int i = 0; i < usb_count; i++) {
        xsdk_log_write(
            "Filme: %s",
            usb_movies[i].title
        );
    }
}
