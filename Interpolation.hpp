//
// Created by dev on 1/8/2018.
//
#ifndef SYNTHSIGNAL_INTERPOLATION_HPP
#define SYNTHSIGNAL_INTERPOLATION_HPP

#include <utility>
#include <vector>
#include <map>
#include <exception>


namespace SynthSignal {
    enum class InterpolationType {
        LINEAR, QUADRATIC
    };

    class OutOfBoundsException: public std::exception {
        const char* what() const throw() override {
            return "Out of bounds exception";
        }
    };
    class UnimplementedInterpolationType: public std::exception {
        const char* what() const throw() override {
            return "Unimplemented interpolation type";
        }
    };
    class Interpolation {
    public:
        Interpolation(
                std::map<float, float> inPoints = {},
                InterpolationType inType = InterpolationType::LINEAR) : points(inPoints), type(inType) {};

        ~Interpolation() = default;
        bool addPoint(const float &time, const float &factor);
        float factorAt (const float time, bool zeroPadding = false) const;
        std::pair<float,float> getInterval() const;

        std::map<float, float> points;
        InterpolationType type;
    };
}

#endif //SYNTHSIGNAL_INTERPOLATION_HPP
