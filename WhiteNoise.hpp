//
// Created by dev on 1/10/2018.
//

#ifndef SYNTHSIGNAL_WHITENOISE_HPP
#define SYNTHSIGNAL_WHITENOISE_HPP

namespace SynthSignal {
    struct WhiteNoise : public Event {
        WhiteNoise(const float inMean, const float inSD) :
        Event(EventType::WhiteNoise),
            mean(inMean),sd(inSD) {};
        float mean;
        float sd;
    };
}

#endif //SYNTHSIGNAL_WHITENOISE_HPP
