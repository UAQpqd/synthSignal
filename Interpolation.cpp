//
// Created by dev on 1/8/2018.
//

#include <algorithm>
#include "Interpolation.hpp"

float SynthSignal::Interpolation::factorAt(float time) {
    if (time < points.begin()->first ||
        time > points.rbegin()->first)
        throw OutOfBoundsException();
    else {
        float factor = 0.0f;
        if (type == InterpolationType::LINEAR) {
            auto right = points.lower_bound(time); //>= time
            auto left = right;
            if (left != points.begin()) left--;
            else return right->second;
            float limitsFactorDiff = right->second - left->second;
            float limitsTimeDiff = right->first - left->first;
            factor =
                    left->second + limitsFactorDiff /
                                   limitsTimeDiff * (time - left->first);
        } else if (type == InterpolationType::QUADRATIC)
            throw UnimplementedInterpolationType();
        return factor;
    }
}

bool SynthSignal::Interpolation::addPoint(const float &time, const float &factor) {
    if(points.find(time) != points.end()) return false;
    else
        points.insert(std::pair<float,float>(time,factor));
    return true;
}
