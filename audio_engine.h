#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "audio_config.h"
#include <math.h>
#include <stdint.h>

typedef struct audio_engine audio_engine_t;

struct audio_engine {
    HeavyContextInterface *heavy;
    void (*process)(audio_engine_t *self, PIO pio, uint sm);
};

static inline uint32_t sample_to_i2s_word(int16_t sample) {
    return ((uint32_t) (uint16_t) sample) << 16;
}

static inline int16_t float_to_i16(float sample) {
    if (sample > 1.0f) sample = 1.0f;
    if (sample < -1.0f) sample = -1.0f;
    return (int16_t) lroundf(sample * 32767.0f);
}

static inline void audio_render(PIO pio, uint sm, float left, float right) {
    int16_t left_i16 = float_to_i16(left);
    int16_t right_i16 = float_to_i16(right);

    pio_sm_put_blocking(pio, sm, sample_to_i2s_word(left_i16));
    pio_sm_put_blocking(pio, sm, sample_to_i2s_word(right_i16));
}

static void audio_process(audio_engine_t *self, PIO pio, uint sm) {
    float left = heavy_audio_render(self->heavy, HEAVY_OUTPUT_GAIN);
    float right = left;
    audio_render(pio, sm, left, right);
}

static inline audio_engine_t audio_engine_create(PIO pio, uint sm) {
    audio_init(pio, sm);

    HeavyContextInterface *heavy = audio_heavy_init();
    if (heavy == NULL) {
        panic("heavy context creation failed");
    }

    audio_engine_t audio = {
        .heavy = heavy,
        .process = audio_process,
    };

    return audio;
}

#endif
