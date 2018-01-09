#include <gtest/gtest.h>
#include "Interpolation.hpp"

namespace SynthSignal {
    class InterpolationRectangle : public ::testing::Test {
    public:
        Interpolation *interpolation;

        void SetUp() override {
            interpolation = new Interpolation();
            interpolation->addPoint(1.0f, 1.0f);
            interpolation->addPoint(2.0, 1.0f);
        }

        void TearDown() override {
            delete interpolation;
        }
    };

    class InterpolationTrapezoid : public ::testing::Test {
    public:
        Interpolation *interpolation;

        void SetUp() override {
            interpolation = new Interpolation();
            interpolation->addPoint(1.0f, 0.0f);
            interpolation->addPoint(2.0f, 1.0f);
            interpolation->addPoint(3.0f, 1.0f);
            interpolation->addPoint(4.0f, 0.0f);
        }

        void TearDown() override {
            delete interpolation;
        }
    };

    TEST_F(InterpolationRectangle, CheckOutOfBoundsNegative) {
        ASSERT_THROW(interpolation->factorAt(0.0f), OutOfBoundsException);
    }

    TEST_F(InterpolationRectangle, CheckOutOfBoundsPositive) {
        ASSERT_THROW(interpolation->factorAt(3.0f), OutOfBoundsException);
    }

    TEST_F(InterpolationRectangle, CheckFactorAtLeftExtreme) {
        ASSERT_FLOAT_EQ(interpolation->factorAt(1.0f), 1.0f);
    }

    TEST_F(InterpolationRectangle, CheckFactorAtRightExtreme) {
        ASSERT_FLOAT_EQ(interpolation->factorAt(2.0f), 1.0f);
    }

    TEST_F(InterpolationTrapezoid, CheckFactorAtMidLeftSlope) {
        ASSERT_FLOAT_EQ(interpolation->factorAt(1.5f),0.5f);
    }
    TEST_F(InterpolationTrapezoid, CheckFactorAt3rdQuartileLeftSlope) {
        ASSERT_FLOAT_EQ(interpolation->factorAt(1.75f),0.75f);
    }
    TEST_F(InterpolationTrapezoid, CheckFactorAtMidRightSlope) {
        ASSERT_FLOAT_EQ(interpolation->factorAt(3.5f),0.5f);
    }
    TEST_F(InterpolationTrapezoid, CheckFactorAt3rdQuartileRightSlope) {
        ASSERT_FLOAT_EQ(interpolation->factorAt(3.75f),0.25f);
    }

    TEST(InterpolationQuadratic, CheckUnimplemented) {
        Interpolation interpolation({},InterpolationType::QUADRATIC);
        interpolation.addPoint(1.0f, 0.0f);
        interpolation.addPoint(2.0f, 1.0f);
        interpolation.addPoint(3.0f, 1.0f);
        interpolation.addPoint(4.0f, 0.0f);
        ASSERT_THROW(interpolation.factorAt(2.0f),UnimplementedInterpolationType);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}