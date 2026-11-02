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
#include "components_runtime.h"
#include <stdint.h>

static void init_analog_controls(void) {
#if ANALOG_CONTROL_COUNT > 0
    adc_init();
    for (uint i = 0; i < ANALOG_CONTROL_COUNT; ++i) {
        adc_gpio_init(analog_control_pins[i]);
    }
#endif
}

int main() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    init_analog_controls();

    PIO pio = pio0;
    uint sm = 0;
    float receptor_value = 0.0f;

    audio_engine_t audio = audio_engine_create(pio, sm);
    audio.set_receptor(&audio, receptor_value);

    while (true) {
#if ANALOG_CONTROL_COUNT > 0
        adc_select_input(analog_control_inputs[0]);
        uint16_t adc_raw = adc_read();
        receptor_value = (float) adc_raw;
#else
        receptor_value = 0.0f;
#endif
        audio.set_receptor(&audio, receptor_value);
        audio.process(&audio, pio, sm);
    }
}
