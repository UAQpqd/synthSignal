//
// Created by dev on 1/10/2018.
//

#ifndef SYNTHSIGNAL_EVENT_HPP
#define SYNTHSIGNAL_EVENT_HPP

#include "Interpolation.hpp"

namespace SynthSignal {
    enum class EventType { SineWaveform, WhiteNoise, SagSwellInterruption };
    class Event {
    public:
        EventType type;
        explicit Event(EventType inType) : type(inType) {};
        virtual ~Event() = default;
        virtual void interpolate(std::vector<float> *data, const size_t sps, const Interpolation interpolation) {};
    };
}

#endif //SYNTHSIGNAL_EVENT_HPP
