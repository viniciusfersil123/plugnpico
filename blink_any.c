/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "audio_engine.h"
#include <stdint.h>

int main() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    adc_init();
    adc_gpio_init(28);
    adc_select_input(2);

    PIO pio = pio0;
    uint sm = 0;
    float receptor_value = 0.0f;

    audio_engine_t audio = audio_engine_create(pio, sm);
    audio.set_receptor(&audio, receptor_value);

    while (true) {
        uint16_t adc_raw = adc_read();
        receptor_value = (float) adc_raw;
        audio.set_receptor(&audio, receptor_value);
        audio.process(&audio, pio, sm);
    }
}
