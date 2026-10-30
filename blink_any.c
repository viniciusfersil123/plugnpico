/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "audio_engine.h"
#include <stdint.h>

int main() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    PIO pio = pio0;
    uint sm = 0;

    audio_engine_t audio = audio_engine_create(pio, sm);

    while (true) {
        audio.process(&audio, pio, sm);
    }
}
