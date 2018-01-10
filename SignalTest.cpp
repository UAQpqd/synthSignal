#include <gtest/gtest.h>
#include <cmath>
#include "Signal.hpp"

namespace SynthSignal {
    class SignalWithOneWaveformWithoutInterpolation : public ::testing::Test {
    public:
        Signal *signal = nullptr;
        SineWaveform *wf = nullptr;

        void SetUp() override {
            signal = new Signal();
            Interpolation interpolation({},InterpolationType::LINEAR);
            interpolation.addPoint(0.0f,1.0f);
            interpolation.addPoint(6.0f,1.0f);
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
    class SignalWithOneWaveformFrequencyChanging : public ::testing::Test {
    public:
        Signal *signal = nullptr;
        SineWaveform *wf = nullptr;

        void SetUp() override {
            signal = new Signal();
            Interpolation interpolation({},InterpolationType::LINEAR);
            interpolation.addPoint(0.0f,1.0f);
            interpolation.addPoint(4.0f,1.0f);
            Interpolation frequencyVariation({},InterpolationType::LINEAR);
            frequencyVariation.addPoint(0.0f,1.0f);
            frequencyVariation.addPoint(4.0f,1.5f);
            wf =
                    new SineWaveform(1.0f,2.0f*(float)M_PI*1.0f,0.0f,frequencyVariation);
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
    class SignalWithWhiteNoise : public ::testing::Test {
    public:
        Signal *signal = nullptr;
        WhiteNoise *n = nullptr;

        void SetUp() override {
            signal = new Signal();
            Interpolation interpolation({},InterpolationType::LINEAR);
            interpolation.addPoint(0.0f,1.0f);
            interpolation.addPoint(0.2f,1.0f);
            n =
                    new WhiteNoise(0.0f,0.05f);
            signal->addEvent(
                    n,
                    interpolation
            );
        }
        void TearDown() override {
            delete n;
            delete signal;
        }
    };

    class SignalWithHarmonics : public ::testing::Test {
    public:
        Signal *signal = nullptr;
        SineWaveform *wf = nullptr;
        SineWaveform *h3 = nullptr;
        SineWaveform *h5 = nullptr;
        SineWaveform *h7 = nullptr;

        void SetUp() override {
            Interpolation interpolation({},InterpolationType::LINEAR);
            interpolation.addPoint(0.0f,1.0f);
            interpolation.addPoint(1.0f,1.0f);
            signal = new Signal();
            const float omega = 2.0f*(float)M_PI*4.0f;
            wf = new SineWaveform(1.0f,omega,0.0f);
            h3 = new SineWaveform(0.25f,omega*3.0f,0.0f);
            h5 = new SineWaveform(0.25f,omega*5.0f,0.0f);
            h7 = new SineWaveform(0.25f,omega*7.0f,0.0f);
            signal->addEvent(wf,interpolation);
            signal->addEvent(h3,interpolation);
            signal->addEvent(h5,interpolation);
            signal->addEvent(h7,interpolation);
        }
        void TearDown() override {
            delete wf;
            delete h3;
            delete h5;
            delete h7;
            delete signal;
        }
    };
    class SignalWith3rdHarmonic : public ::testing::Test {
    public:
        Signal *signal = nullptr;
        SineWaveform *wf = nullptr;
        SineWaveform *h3 = nullptr;

        void SetUp() override {
            Interpolation interpolation({},InterpolationType::LINEAR);
            interpolation.addPoint(0.0f,1.0f);
            interpolation.addPoint(1.0f,1.0f);
            signal = new Signal();
            const float omega = 2.0f*(float)M_PI*4.0f;
            wf = new SineWaveform(1.0f,omega,0.0f);
            h3 = new SineWaveform(0.25f,omega*3.0f,0.0f);
            signal->addEvent(wf,interpolation);
            signal->addEvent(h3,interpolation);
        }
        void TearDown() override {
            delete wf;
            delete h3;
            delete signal;
        }
    };

    TEST_F(SignalWithOneWaveform, CheckWaveformVectorSize) {
        ASSERT_EQ(signal->events.size(), 1u);
    }
    TEST_F(SignalWithOneWaveform, CheckWaveformIsGenerated) {
        auto data = signal->gen(6.0f,8000);
        auto timePoint =
                (size_t)floor(1.25f*8000.0f);
        signal->toCsv("CheckWaveformIsGenerated.csv");
        ASSERT_NEAR(data->at(timePoint),1.0f,0.001f);
        delete data;
    }
    TEST_F(SignalWithOneWaveformFrequencyChanging, CheckFrequencyChanging) {
        auto data = signal->gen(4.0f,8000);
        signal->toCsv("CheckFrequencyChanging.csv");
        ASSERT_NEAR(*data->rbegin(),0.0f,0.010f);
        delete data;
    }
    TEST_F(SignalWithWhiteNoise, CheckWhiteNoiseMeanIsZero) {
        auto data = signal->gen(0.2f,8000);
        float sum = std::accumulate(data->begin(),data->end(),0.0f,std::plus<float>());
        signal->toCsv("CheckWhiteNoiseMeanIsZero.csv");
        ASSERT_NEAR(sum/(float)data->size(),0.0f,0.001f);
        delete data;
    }
    TEST_F(SignalWith3rdHarmonic, Check3rdHarmonicIsPresent) {
        auto data = signal->gen(1.0f,8000);
        signal->toCsv("Check3rdHarmonicIsPresent.csv");
        ASSERT_NEAR(*data->rbegin(),0.0f,0.050f);
        delete data;
    }
    TEST_F(SignalWithHarmonics, CheckHarmonicsArePresent) {
        auto data = signal->gen(1.0f,8000);
        signal->toCsv("CheckHarmonicsArePresent.csv");
        ASSERT_NEAR(*data->rbegin(),0.0f,0.050f);
        delete data;
    }
    TEST_F(SignalWithOneWaveformWithoutInterpolation, CheckSag) {

        Interpolation sagInterpolation({},InterpolationType::LINEAR);
        sagInterpolation.addPoint(1.0f,0.0f);
        sagInterpolation.addPoint(2.0f,1.0f);
        sagInterpolation.addPoint(4.0f,1.0f);
        sagInterpolation.addPoint(5.0f,0.0f);
        auto sag = new SagSwellInterruption(0.5f);
        signal->addEvent(sag,sagInterpolation);
        auto data = signal->gen(6.0f,8000);
        auto timePoint =
                (size_t)floor(3.25f*8000.0f);
        signal->toCsv("CheckSag.csv");
        ASSERT_NEAR(data->at(timePoint),0.5f,0.001f);
        delete sag;
        delete data;
    }
    TEST_F(SignalWithOneWaveformWithoutInterpolation, CheckSwell) {

        Interpolation sagInterpolation({},InterpolationType::LINEAR);
        sagInterpolation.addPoint(1.0f,0.0f);
        sagInterpolation.addPoint(2.0f,1.0f);
        sagInterpolation.addPoint(4.0f,1.0f);
        sagInterpolation.addPoint(5.0f,0.0f);
        auto swell = new SagSwellInterruption(1.5f);
        signal->addEvent(swell,sagInterpolation);
        auto data = signal->gen(6.0f,8000);
        auto timePoint =
                (size_t)floor(3.25f*8000.0f);
        signal->toCsv("CheckSwell.csv");
        ASSERT_NEAR(data->at(timePoint),1.5f,0.001f);
        delete swell;
        delete data;
    }
}