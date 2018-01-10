//
// Created by dev on 1/8/2018.
//

#ifndef SYNTHSIGNAL_SIGNAL_HPP
#define SYNTHSIGNAL_SIGNAL_HPP

#include "SineWaveform.hpp"
#include "WhiteNoise.hpp"
#include "SagSwellInterruption.hpp"
#include "Interpolation.hpp"
#include <exception>
#include <cmath>
#include <fstream>

namespace SynthSignal {
    class NotRecognizedEventType: public std::exception {
        const char* what() const throw() override {
            return "Not recognized event type";
        }
    };
    class Signal {
    public:
        Signal() = default;
        ~Signal() = default;
        void addEvent(
                Event *event,
                const Interpolation &interpolation);
        std::vector<float> *gen(float time, size_t sps);
        void toCsv(std::string filename);
        std::vector<float> *lastGen = nullptr;
        size_t lastSps = 0;
        std::vector<std::pair<Event *,Interpolation> > events;
    };
}

#endif //SYNTHSIGNAL_SIGNAL_HPP
