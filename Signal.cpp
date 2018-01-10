//
// Created by dev on 1/8/2018.
//

#include <cmath>
#include <fstream>
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
        auto interpolation = event.second;
        float tStart = interpolation.points.begin()->first;
        float tEnd = interpolation.points.rbegin()->first;
        auto pStart = (size_t) floor(tStart * (float) sps);
        auto pEnd = (size_t) floor(tEnd * (float) sps);
        pEnd = std::min(pEnd, dataSize);
        if (pStart < dataSize) {
            if (event.first->type == EventType::SineWaveform) {
                auto waveform = (SineWaveform*) event.first;
                for (size_t p = pStart; p < pEnd; p++) {
                    float t = (float) p / (float) sps;
                    float factor = interpolation.factorAt(t);
                    float amplitude =
                            waveform->a * (float)sin(waveform->omega * t + waveform->phi);
                    data->at(p) += factor * amplitude;
                }
            }
        }
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

