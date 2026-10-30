#ifndef I2S_AUDIO_H
#define I2S_AUDIO_H

#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "i2s_tx.pio.h"
#include "pico/stdlib.h"

#define I2S_DATA_PIN 20
#define I2S_BCLK_PIN 18
#define I2S_LRCLK_PIN 19
#define I2S_SAMPLE_RATE_HZ 44100.0f

static inline void init_i2s_audio(PIO pio, uint sm, float sample_rate_hz) {
    uint offset = pio_add_program(pio, &i2s_tx_program);

    pio_sm_config c = i2s_tx_program_get_default_config(offset);
    sm_config_set_out_pins(&c, I2S_DATA_PIN, 1);
    sm_config_set_sideset_pins(&c, I2S_BCLK_PIN);

    // Shift left so bit 31 is output first. Autopull every 32 bits.
    sm_config_set_out_shift(&c, false, true, 32);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);

    // Program uses 130 SM cycles per stereo frame.
    const float sm_clk_hz = sample_rate_hz * 130.0f;
    float clkdiv = (float) clock_get_hz(clk_sys) / sm_clk_hz;
    sm_config_set_clkdiv(&c, clkdiv);

    pio_gpio_init(pio, I2S_DATA_PIN);
    pio_gpio_init(pio, I2S_BCLK_PIN);
    pio_gpio_init(pio, I2S_LRCLK_PIN);
    pio_sm_set_consecutive_pindirs(pio, sm, I2S_DATA_PIN, 1, true);
    pio_sm_set_consecutive_pindirs(pio, sm, I2S_BCLK_PIN, 2, true);

    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);
}

#endif
