#ifndef HEAVY_AUDIO_H
#define HEAVY_AUDIO_H

#include "Heavy_testpatch.h"

#define HEAVY_OUTPUT_GAIN 0.25f

static inline HeavyContextInterface *heavy_audio_init(float sample_rate_hz) {
    return hv_testpatch_new(sample_rate_hz);
}

static inline float heavy_audio_render(HeavyContextInterface *heavy, float gain) {
    float output[2] = {0.0f, 0.0f};

    if (heavy == NULL) {
        return 0.0f;
    }

    int num_output_channels = hv_getNumOutputChannels(heavy);
    if (num_output_channels <= 0) {
        return 0.0f;
    }

    hv_processInline(heavy, NULL, output, 1);

    float sample = output[0];
    if (num_output_channels > 1) {
        sample = (output[0] + output[1]) * 0.5f;
    }

    sample *= gain;

    if (sample > 1.0f) sample = 1.0f;
    if (sample < -1.0f) sample = -1.0f;

    return sample;
}

#endif
