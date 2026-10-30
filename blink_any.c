/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "i2s_tx.pio.h"
#include <math.h>
#include <stdint.h>

#define I2S_DATA_PIN 20
#define I2S_BCLK_PIN 18
#define I2S_LRCLK_PIN 19

#define SAMPLE_RATE_HZ 44100.0f
#define SINE_FREQUENCY_HZ 220.0f
#define SINE_TABLE_SIZE 256
#define AMPLITUDE 0.50f

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

static int16_t sine_table[SINE_TABLE_SIZE];

static void init_sine_table(void) {
    for (int i = 0; i < SINE_TABLE_SIZE; ++i) {
        float phase = (2.0f * M_PI * (float) i) / (float) SINE_TABLE_SIZE;
        float s = sinf(phase) * AMPLITUDE;
        sine_table[i] = (int16_t) (s * 32760.0f);
    }
}

static inline uint32_t sample_to_i2s_word(int16_t sample) {
    // 16-bit sample in upper bits of 32-bit channel word, MSB first.
    return ((uint32_t) (uint16_t) sample) << 16;
}

int main() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    init_sine_table();

    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &i2s_tx_program);

    pio_sm_config c = i2s_tx_program_get_default_config(offset);
    sm_config_set_out_pins(&c, I2S_DATA_PIN, 1);
    sm_config_set_sideset_pins(&c, I2S_BCLK_PIN);

    // Shift left so bit 31 is output first. Autopull every 32 bits.
    sm_config_set_out_shift(&c, false, true, 32);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);

    // Program uses 130 SM cycles per stereo frame.
    const float sm_clk_hz = SAMPLE_RATE_HZ * 130.0f;
    float clkdiv = (float) clock_get_hz(clk_sys) / sm_clk_hz;
    sm_config_set_clkdiv(&c, clkdiv);

    pio_gpio_init(pio, I2S_DATA_PIN);
    pio_gpio_init(pio, I2S_BCLK_PIN);
    pio_gpio_init(pio, I2S_LRCLK_PIN);
    pio_sm_set_consecutive_pindirs(pio, sm, I2S_DATA_PIN, 1, true);
    pio_sm_set_consecutive_pindirs(pio, sm, I2S_BCLK_PIN, 2, true);

    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);

    float phase = 0.0f;
    const float phase_inc = (SINE_FREQUENCY_HZ * (float) SINE_TABLE_SIZE) / SAMPLE_RATE_HZ;

    while (true) {
        uint32_t index = (uint32_t) phase & (SINE_TABLE_SIZE - 1);
        int16_t sample = sine_table[index];
        uint32_t word = sample_to_i2s_word(sample);

        // Stereo: write left then right channel.
        pio_sm_put_blocking(pio, sm, word);
        pio_sm_put_blocking(pio, sm, word);

        phase += phase_inc;
        if (phase >= (float) SINE_TABLE_SIZE) {
            phase -= (float) SINE_TABLE_SIZE;
        }
    }
}
