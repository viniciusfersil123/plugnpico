#ifndef AUDIO_CONFIG_H
#define AUDIO_CONFIG_H

#include "heavy_audio.h"
#include "i2s_audio.h"

#define SAMPLE_RATE_HZ 44100.0f

static inline void audio_init(PIO pio, uint sm) {
    init_i2s_audio(pio, sm, SAMPLE_RATE_HZ);
}

static inline HeavyContextInterface *audio_heavy_init(void) {
    return heavy_audio_init(SAMPLE_RATE_HZ);
}

#endif
