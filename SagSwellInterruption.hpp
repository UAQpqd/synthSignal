//
// Created by dev on 1/10/2018.
//

#ifndef SYNTHSIGNAL_SAGSWELLINTERRUPTION_HPP
#define SYNTHSIGNAL_SAGSWELLINTERRUPTION_HPP

#include <cmath>
#include "Event.hpp"

namespace SynthSignal {
    class SagSwellInterruption : public Event {
    public:
        SagSwellInterruption(float inFactor) :
                Event(EventType::SineWaveform),
                factor(inFactor) {};

        ~SagSwellInterruption() {};

        void interpolate(std::vector<float> *data, const size_t sps, const Interpolation interpolation);

        float factor;
    };
}

#endif //SYNTHSIGNAL_SAGSWELLINTERRUPTION_HPP
