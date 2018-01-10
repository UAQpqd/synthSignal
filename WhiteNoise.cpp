#include "WhiteNoise.hpp"

void
SynthSignal::WhiteNoise::interpolate(std::vector<float> *data, const size_t sps, const Interpolation interpolation) {
    std::pair<float,float> interpolationInterval =
            interpolation.getInterval();
    auto pStart = (size_t) floor(interpolationInterval.first * (float) sps);
    auto pEnd = (size_t) floor(interpolationInterval.second * (float) sps);
    pEnd = std::min(pEnd, data->size());
    if (pStart < data->size()) {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::normal_distribution<float> normalDist(mean,sd);
        for (size_t p = pStart; p < pEnd; p++) {
            float t = (float) p / (float) sps;
            float factor = interpolation.factorAt(t);
            float noise = normalDist(eng);
            data->at(p) += factor * noise;
        }
    }
    Event::interpolate(data, sps, interpolation);
}
