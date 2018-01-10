//
// Created by dev on 1/8/2018.
//

#ifndef SYNTHSIGNAL_SINEWAVEFORM_HPP
#define SYNTHSIGNAL_SINEWAVEFORM_HPP

#include <vector>
#include <cstddef>
#include "Event.hpp"

namespace SynthSignal {
    class SineWaveform : public Event {
    public:
        SineWaveform(float inA, float inOmega, float inPhi, Interpolation inFrequencyVariation = Interpolation()) :
                Event(EventType::SineWaveform),
                a(inA), omega(inOmega), phi(inPhi), frequencyVariation(inFrequencyVariation) {};

        ~SineWaveform() {};

        void interpolate(std::vector<float> *data, const size_t sps, const Interpolation interpolation);

        float a;
        float omega;
        float phi;
        Interpolation frequencyVariation;
    };
}

#endif //SYNTHSIGNAL_SINEWAVEFORM_HPP
