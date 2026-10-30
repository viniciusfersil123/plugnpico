/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "i2s_tx.pio.h"
#include "Heavy_testpatch.h"
#include <math.h>
#include <stdint.h>

#define I2S_DATA_PIN 20
#define I2S_BCLK_PIN 18
#define I2S_LRCLK_PIN 19

#define SAMPLE_RATE_HZ 44100.0f
#define OUTPUT_GAIN 0.25f

typedef struct audio_engine audio_engine_t;

struct audio_engine {
    HeavyContextInterface *heavy;
    void (*process)(audio_engine_t *self, PIO pio, uint sm);
};

static inline uint32_t sample_to_i2s_word(int16_t sample) {
    // 16-bit sample in upper bits of 32-bit channel word, MSB first.
    return ((uint32_t) (uint16_t) sample) << 16;
}

static inline int16_t float_to_i16(float sample) {
    if (sample > 1.0f) sample = 1.0f;
    if (sample < -1.0f) sample = -1.0f;
    return (int16_t) lroundf(sample * 32767.0f);
}

static void audio_process(audio_engine_t *self, PIO pio, uint sm) {
    float output[2] = {0.0f, 0.0f};
    float left = 0.0f;
    float right = 0.0f;

    if (self->heavy != NULL) {
        int num_output_channels = hv_getNumOutputChannels(self->heavy);
        if (num_output_channels > 0) {
            hv_processInline(self->heavy, NULL, output, 1);
            left = output[0] * OUTPUT_GAIN;
            right = (num_output_channels > 1) ? output[1] * OUTPUT_GAIN : output[0] * OUTPUT_GAIN;
        }
    }

    int16_t left_i16 = float_to_i16(left);
    int16_t right_i16 = float_to_i16(right);

    pio_sm_put_blocking(pio, sm, sample_to_i2s_word(left_i16));
    pio_sm_put_blocking(pio, sm, sample_to_i2s_word(right_i16));
}

int main() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

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

    HeavyContextInterface *heavy = hv_testpatch_new(SAMPLE_RATE_HZ);
    if (heavy == NULL) {
        panic("heavy context creation failed");
    }

    audio_engine_t audio = {
        .heavy = heavy,
        .process = audio_process,
    };

    while (true) {
        audio.process(&audio, pio, sm);
    }
}
