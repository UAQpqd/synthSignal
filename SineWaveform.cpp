#include <cmath>
#include "SineWaveform.hpp"
#include "Event.hpp"

void
SynthSignal::SineWaveform::interpolate(std::vector<float> *data, const size_t sps, const Interpolation interpolation) {
    std::pair<float, float> interpolationInterval =
            interpolation.getInterval();
    auto pStart = (size_t) floor(interpolationInterval.first * (float) sps);
    auto pEnd = (size_t) floor(interpolationInterval.second * (float) sps);
    pEnd = std::min(pEnd, data->size());
    if (pStart < data->size()) {
        if (frequencyVariation.points.size() == 0) {
            for (size_t p = pStart; p < pEnd; p++) {
                float t = (float) p / (float) sps;
                float factor = interpolation.factorAt(t);
                float amplitude =
                        a * (float) sin(omega * t + phi);
                data->at(p) += factor * amplitude;
            }
        } else {
            for (size_t p = pStart; p < pEnd; p++) {
                float t = (float) p / (float) sps;
                float factor = interpolation.factorAt(t);
                float omegaFactor = frequencyVariation.factorAt(t);
                float amplitude =
                        a * (float) sin(omega * t * omegaFactor+ phi);
                data->at(p) += factor * amplitude;
            }
        }
    }
    Event::interpolate(data, sps, interpolation);
}
