//
// Created by dev on 1/10/2018.
//

#include "SagSwellInterruption.hpp"

void SynthSignal::SagSwellInterruption::interpolate(std::vector<float> *data, const size_t sps,
                                                    const SynthSignal::Interpolation interpolation) {
    std::pair<float,float> interpolationInterval =
            interpolation.getInterval();
    auto pStart = (size_t) floor(interpolationInterval.first * (float) sps);
    auto pEnd = (size_t) floor(interpolationInterval.second * (float) sps);
    pEnd = std::min(pEnd, data->size());
    if (pStart < data->size()) {
        for (size_t p = pStart; p < pEnd; p++) {
            float t = (float) p / (float) sps;
            float interpolationFactor = interpolation.factorAt(t);
            data->at(p) *= 1.0f+(factor-1.0f)*interpolationFactor;
        }
    }
    Event::interpolate(data, sps, interpolation);
}
