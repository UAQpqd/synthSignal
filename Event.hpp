//
// Created by dev on 1/10/2018.
//

#ifndef SYNTHSIGNAL_EVENT_HPP
#define SYNTHSIGNAL_EVENT_HPP

namespace SynthSignal {
    enum class EventType { SineWaveform, WhiteNoise };
    struct Event {
        EventType type;
        explicit Event(EventType inType) : type(inType) {};
    };
}

#endif //SYNTHSIGNAL_EVENT_HPP
