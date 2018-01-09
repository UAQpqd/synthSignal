//
// Created by dev on 1/8/2018.
//

#ifndef SYNTHSIGNAL_SIGNAL_HPP
#define SYNTHSIGNAL_SIGNAL_HPP

#include "SineWaveform.hpp"
#include "Interpolation.hpp"

namespace SynthSignal {
    class Signal {
    public:
        Signal();
        ~Signal() = default;
        void addWaveform(
                const SineWaveform &wf,
                const Interpolation &interpolation);
    };
}

#endif //SYNTHSIGNAL_SIGNAL_HPP
