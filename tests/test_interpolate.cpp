#include <gtest/gtest.h>
#include <cmath>
#include "../include/interpolate.h"

class InterpolateTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any test fixtures if needed
    }
    
    void TearDown() override {
        // Clean up after tests
    }
    
    // Helper function to compare floating point arrays
    template<size_t N>
    void expectArrayNear(const double (&expected)[N], const double* actual, double tolerance = 1e-10) {
        for (size_t i = 0; i < N; ++i) {
            EXPECT_NEAR(expected[i], actual[i], tolerance) 
                << "Arrays differ at index " << i;
        }
    }
};

// Test the dot product function
TEST_F(InterpolateTest, DotProduct) {
    double x[] = {1.0, 2.0, 3.0};
    double y[] = {4.0, 5.0, 6.0};
    
    double result = dot(x, y);
    double expected = 1.0*4.0 + 2.0*5.0 + 3.0*6.0; // 4 + 10 + 18 = 32
    
    EXPECT_DOUBLE_EQ(expected, result);
}

TEST_F(InterpolateTest, DotProductZeroVector) {
    double x[] = {0.0, 0.0, 0.0};
    double y[] = {1.0, 2.0, 3.0};
    
    double result = dot(x, y);
    EXPECT_DOUBLE_EQ(0.0, result);
}

TEST_F(InterpolateTest, DotProductUnitVectors) {
    double x[] = {1.0, 0.0, 0.0};
    double y[] = {0.0, 1.0, 0.0};
    
    double result = dot(x, y);
    EXPECT_DOUBLE_EQ(0.0, result);
}

// Test the normalize function
TEST_F(InterpolateTest, NormalizeUnitVector) {
    double x[] = {1.0, 0.0, 0.0};
    
    bool result = normalize(x);
    
    EXPECT_TRUE(result);
    double expected1[] = {1.0, 0.0, 0.0};
    expectArrayNear(expected1, x);
}

TEST_F(InterpolateTest, NormalizeVector) {
    double x[] = {3.0, 4.0, 0.0};
    
    bool result = normalize(x);
    
    EXPECT_TRUE(result);
    double expected2[] = {0.6, 0.8, 0.0};
    expectArrayNear(expected2, x);
    
    // Verify it's actually normalized
    double length = sqrt(dot(x, x));
    EXPECT_NEAR(1.0, length, 1e-10);
}

TEST_F(InterpolateTest, NormalizeZeroVector) {
    double x[] = {0.0, 0.0, 0.0};
    
    bool result = normalize(x);
    
    EXPECT_FALSE(result);
}

TEST_F(InterpolateTest, NormalizeVerySmallVector) {
    double x[] = {1e-20, 0.0, 0.0};
    
    bool result = normalize(x);
    
    EXPECT_FALSE(result);
}

// Test quaternion normalization
TEST_F(InterpolateTest, QuaternionNormalize) {
    double q[] = {2.0, 0.0, 0.0, 0.0};
    
    qnormalize(q);
    
    double expected3[] = {1.0, 0.0, 0.0, 0.0};
    expectArrayNear(expected3, q);
}

TEST_F(InterpolateTest, QuaternionNormalizeGeneral) {
    double q[] = {1.0, 1.0, 1.0, 1.0};
    
    qnormalize(q);
    
    double expected = 1.0 / 2.0; // 1/sqrt(4)
    double expected4[] = {expected, expected, expected, expected};
    expectArrayNear(expected4, q);
    
    // Verify magnitude is 1
    double magnitude = sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    EXPECT_NEAR(1.0, magnitude, 1e-10);
}

// Test quaternion inversion
TEST_F(InterpolateTest, QuaternionInvert) {
    double q[] = {0.5, 0.5, 0.5, 0.5};
    double qout[4];
    
    qinvert(qout, q);
    
    // The function computes conjugate and then normalizes
    // conjugate: {-0.5, -0.5, -0.5, 0.5}
    // Already normalized since original was unit quaternion
    double expected5[] = {-0.5, -0.5, -0.5, 0.5};
    expectArrayNear(expected5, qout);
}

TEST_F(InterpolateTest, QuaternionInvertIdentity) {
    double q[] = {0.0, 0.0, 0.0, 1.0}; // Identity quaternion
    double qout[4];
    
    qinvert(qout, q);
    
    double expected6[] = {0.0, 0.0, 0.0, 1.0};
    expectArrayNear(expected6, qout);
}

// Test matrix to quaternion conversion (basic test)
TEST_F(InterpolateTest, MatrixToQuaternionIdentity) {
    // Identity matrix
    double m[] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    double q[4];
    
    mat2quat(m, q);
    
    // Identity quaternion should be close to (0, 0, 0, 1) or (0, 0, 0, -1)
    double expected_magnitude = sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    EXPECT_NEAR(1.0, expected_magnitude, 1e-10);
}

// Test quaternion to matrix conversion
TEST_F(InterpolateTest, QuaternionToMatrixIdentity) {
    double q[] = {0.0, 0.0, 0.0, 1.0}; // Identity quaternion
    double m[16] = {0}; // Initialize to zeros
    
    quat2mat(q, m);
    
    // Should produce identity rotation matrix (ignoring translation part)
    EXPECT_NEAR(1.0, m[0], 1e-10);  // m[0][0]
    EXPECT_NEAR(0.0, m[1], 1e-10);  // m[0][1]
    EXPECT_NEAR(0.0, m[2], 1e-10);  // m[0][2]
    
    EXPECT_NEAR(0.0, m[4], 1e-10);  // m[1][0]
    EXPECT_NEAR(1.0, m[5], 1e-10);  // m[1][1]
    EXPECT_NEAR(0.0, m[6], 1e-10);  // m[1][2]
    
    EXPECT_NEAR(0.0, m[8], 1e-10);  // m[2][0]
    EXPECT_NEAR(0.0, m[9], 1e-10);  // m[2][1]
    EXPECT_NEAR(1.0, m[10], 1e-10); // m[2][2]
}

// Test SLERP with t=0 and t=1
TEST_F(InterpolateTest, SlerpEndpoints) {
    double q1[] = {1.0, 0.0, 0.0, 0.0};
    double q2[] = {0.0, 1.0, 0.0, 0.0};
    double qr[4];
    
    // Test t=0 (should return q1)
    qslerp(q1, q2, qr, 0.0);
    expectArrayNear(q1, qr, 1e-10);
    
    // Test t=1 (should return q2)
    qslerp(q1, q2, qr, 1.0);
    expectArrayNear(q2, qr, 1e-10);
}

// Test quaternion multiplication
TEST_F(InterpolateTest, QuaternionMultiplication) {
    double q1[] = {0.0, 0.0, 0.0, 1.0}; // Identity
    double q2[] = {1.0, 0.0, 0.0, 0.0}; // 180-degree rotation around x-axis
    
    qmul(q1, q2); // q1 *= q2
    
    double expected7[] = {1.0, 0.0, 0.0, 0.0};
    expectArrayNear(expected7, q1, 1e-10);
}

TEST_F(InterpolateTest, QuaternionMultiplicationWithIdentity) {
    double q1[] = {1.0, 2.0, 3.0, 4.0};
    double q2[] = {0.0, 0.0, 0.0, 1.0}; // Identity
    double original[] = {1.0, 2.0, 3.0, 4.0};
    
    qmul(q1, q2); // q1 *= identity
    
    expectArrayNear(original, q1, 1e-10);
}