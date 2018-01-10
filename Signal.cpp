//
// Created by dev on 1/8/2018.
//

#include "Signal.hpp"

void
SynthSignal::Signal::addEvent(SynthSignal::Event *event, const SynthSignal::Interpolation &interpolation) {
    events.emplace_back(std::make_pair(event, interpolation));
}


std::vector<float> *SynthSignal::Signal::gen(float time, size_t sps) {
    auto dataSize =
            (size_t) floor(time * (float) sps);
    std::vector<float> *data
            = new std::vector<float>(dataSize, 0.0f);
    for (auto event : events) {
        switch(event.first->type) {
            case EventType::SineWaveform:
                ((SineWaveform *)event.first)->interpolate(data,sps,event.second);
                break;
            case EventType::WhiteNoise:
                ((WhiteNoise *)event.first)->interpolate(data,sps,event.second);
                break;
            case EventType::SagSwellInterruption:
                ((SagSwellInterruption *)event.first)->interpolate(data,sps,event.second);
                break;
            default:
                throw NotRecognizedEventType();
                break;
        }

        auto interpolation = event.second;



    }
    lastGen = data;
    lastSps = sps;
    return data;
}

void SynthSignal::Signal::toCsv(std::string filename) {
    std::ofstream ofs;
    ofs.open(filename, std::ofstream::out);
    ofs << "time,amplitude" << std::endl;
    for (size_t p = 0; p < lastGen->size(); p++) {
        float time = (float) p / (float) lastSps;
        float amplitude = lastGen->at(p);
        ofs << time << "," << amplitude << std::endl;
    }
    ofs.close();
}

