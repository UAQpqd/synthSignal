//
// Created by dev on 1/8/2018.
//

#ifndef SYNTHSIGNAL_SINEWAVEFORM_HPP
#define SYNTHSIGNAL_SINEWAVEFORM_HPP

#include <vector>
#include <cstddef>
#include "Event.hpp"

namespace SynthSignal {
    struct SineWaveform : public Event {
    public:
        SineWaveform(float inA, float inOmega, float inPhi) :
        Event(EventType::SineWaveform),
        a(inA), omega(inOmega), phi(inPhi) {};
        float a;
        float omega;
        float phi;
    };
}

#endif //SYNTHSIGNAL_SINEWAVEFORM_HPP
