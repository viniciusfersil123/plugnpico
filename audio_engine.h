#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "audio_config.h"
#include "components_runtime.h"
#include <math.h>
#include <stdint.h>

typedef struct audio_engine audio_engine_t;

struct audio_engine {
    HeavyContextInterface *heavy;
    hv_uint32_t receptor_hash;
    void (*process)(audio_engine_t *self, PIO pio, uint sm);
    void (*set_receptor)(audio_engine_t *self, float value);
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

static void audio_set_receptor(audio_engine_t *self, float value) {
    if (self == NULL || self->heavy == NULL) {
        return;
    }

    hv_sendFloatToReceiver(self->heavy, self->receptor_hash, value);
}

static inline audio_engine_t audio_engine_create(PIO pio, uint sm) {
    audio_init(pio, sm);

    HeavyContextInterface *heavy = audio_heavy_init();
    if (heavy == NULL) {
        panic("heavy context creation failed");
    }

    audio_engine_t audio = {
        .heavy = heavy,
        .receptor_hash = hv_stringToHash(ANALOG_CONTROL_PRIMARY_RECEIVER),
        .process = audio_process,
        .set_receptor = audio_set_receptor,
    };

    return audio;
}

#endif
