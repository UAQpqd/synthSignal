//
// Created by dev on 1/10/2018.
//

#ifndef SYNTHSIGNAL_WHITENOISE_HPP
#define SYNTHSIGNAL_WHITENOISE_HPP

#include <vector>
#include <cmath>
#include <random>
#include "Interpolation.hpp"
#include "Event.hpp"

namespace SynthSignal {
    class WhiteNoise : public Event {
    public:
        WhiteNoise(const float inMean, const float inSD) :
        Event(EventType::WhiteNoise),
            mean(inMean),sd(inSD) {};
        void interpolate(std::vector<float> *data, const size_t sps, const Interpolation interpolation);

        float mean;
        float sd;
    };
}

#endif //SYNTHSIGNAL_WHITENOISE_HPP
