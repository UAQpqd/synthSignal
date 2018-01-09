//
// Created by dev on 1/8/2018.
//

#ifndef SYNTHSIGNAL_SINEWAVEFORM_HPP
#define SYNTHSIGNAL_SINEWAVEFORM_HPP

#include <vector>
#include <cstddef>

namespace SynthSignal {
    class SineWaveform {
    public:
        SineWaveform(float inA, float inOmega, float inPhi) :
        a(inA), omega(inOmega), phi(inPhi) {};
        ~SineWaveform() = default;
        float a;
        float omega;
        float phi;
    };
}

#endif //SYNTHSIGNAL_SINEWAVEFORM_HPP
