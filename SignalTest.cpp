#include <gtest/gtest.h>
#include <cmath>
#include "Signal.hpp"

namespace SynthSignal {
    class SignalWithOneWaveform : public ::testing::Test {
    public:
        Signal *signal = nullptr;
        SineWaveform *wf = nullptr;

        void SetUp() override {
            signal = new Signal();
            Interpolation interpolation({},InterpolationType::LINEAR);
            interpolation.addPoint(0.0f,0.0f);
            interpolation.addPoint(1.0f,1.0f);
            interpolation.addPoint(5.0f,1.0f);
            interpolation.addPoint(6.0f,0.0f);
            wf =
                    new SineWaveform(1.0f,2.0f*(float)M_PI*1.0f,0.0f);
            signal->addEvent(
                    wf,
                    interpolation
            );
        }
        void TearDown() override {
            delete wf;
            delete signal;
        }
    };

    TEST_F(SignalWithOneWaveform, CheckWaveformVectorSize) {
        ASSERT_EQ(signal->events.size(), 1u);
    }
    TEST_F(SignalWithOneWaveform, CheckWaveformIsGenerated) {
        const size_t sps = 8000;
        const float time = 6.0f;
        auto data = signal->gen(time,sps);
        auto timePoint =
                (size_t)floor(1.25f*(float)sps);
        const float expectedAmplitude = 1.0f;
        signal->toCsv("CheckWaveformIsGenerated.csv");
        ASSERT_NEAR(data->at(timePoint),expectedAmplitude,0.001f);
    }
}