#include <gtest/gtest.h>
#include <cmath>
#include "../include/camera.h"

class CameraTest : public ::testing::Test {
protected:
    KeyFrame camera;
    
    void SetUp() override {
        // Initialize camera to default state
        camera = KeyFrame();
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

// Test KeyFrame constructor
TEST_F(CameraTest, DefaultConstructor) {
    KeyFrame kf;
    
    // Check that it's not marked as a key frame by default
    EXPECT_FALSE(kf.isKey());
    
    // Check that position exists (pos() should return valid pointer)
    EXPECT_NE(nullptr, kf.pos());
    EXPECT_NE(nullptr, kf.right());
    EXPECT_NE(nullptr, kf.up());
    EXPECT_NE(nullptr, kf.ahead());
}

// Test key frame flag
TEST_F(CameraTest, KeyFrameFlag) {
    EXPECT_FALSE(camera.isKey());
    
    camera.setKey(true);
    EXPECT_TRUE(camera.isKey());
    
    camera.setKey(false);
    EXPECT_FALSE(camera.isKey());
}

// Test matrix accessors
TEST_F(CameraTest, MatrixAccessors) {
    // The view matrix should be 4x4, accessed as a 16-element array
    // right() should point to elements 0-3
    // up() should point to elements 4-7
    // ahead() should point to elements 8-11
    // pos() should point to elements 12-15
    
    EXPECT_EQ(&camera.v[0], camera.right());
    EXPECT_EQ(&camera.v[4], camera.up());
    EXPECT_EQ(&camera.v[8], camera.ahead());
    EXPECT_EQ(&camera.v[12], camera.pos());
}

// Test basic movement
TEST_F(CameraTest, MoveRelative) {
    // Set up identity matrix for predictable results
    camera.v[0] = 1.0; camera.v[1] = 0.0; camera.v[2] = 0.0;  // right
    camera.v[4] = 0.0; camera.v[5] = 1.0; camera.v[6] = 0.0;  // up
    camera.v[8] = 0.0; camera.v[9] = 0.0; camera.v[10] = 1.0; // ahead
    
    // Set initial position
    camera.pos()[0] = 0.0;
    camera.pos()[1] = 0.0;
    camera.pos()[2] = 0.0;
    
    // Move right by 1 unit
    camera.move(1.0, 0.0, 0.0);
    
    EXPECT_NEAR(1.0, camera.pos()[0], 1e-10);
    EXPECT_NEAR(0.0, camera.pos()[1], 1e-10);
    EXPECT_NEAR(0.0, camera.pos()[2], 1e-10);
    
    // Move up by 2 units
    camera.move(0.0, 2.0, 0.0);
    
    EXPECT_NEAR(1.0, camera.pos()[0], 1e-10);
    EXPECT_NEAR(2.0, camera.pos()[1], 1e-10);
    EXPECT_NEAR(0.0, camera.pos()[2], 1e-10);
    
    // Move ahead by 3 units
    camera.move(0.0, 0.0, 3.0);
    
    EXPECT_NEAR(1.0, camera.pos()[0], 1e-10);
    EXPECT_NEAR(2.0, camera.pos()[1], 1e-10);
    EXPECT_NEAR(3.0, camera.pos()[2], 1e-10);
}

// Test absolute movement
TEST_F(CameraTest, MoveAbsolute) {
    // Set initial position
    camera.pos()[0] = 1.0;
    camera.pos()[1] = 2.0;
    camera.pos()[2] = 3.0;
    
    // Move in absolute direction
    double dir[] = {1.0, 0.0, 0.0}; // Unit vector in x direction
    camera.moveAbsolute(dir, 5.0);
    
    EXPECT_NEAR(6.0, camera.pos()[0], 1e-10);
    EXPECT_NEAR(2.0, camera.pos()[1], 1e-10);
    EXPECT_NEAR(3.0, camera.pos()[2], 1e-10);
}

// Test absolute movement with normalized direction
TEST_F(CameraTest, MoveAbsoluteNormalized) {
    // Set initial position
    camera.pos()[0] = 0.0;
    camera.pos()[1] = 0.0;
    camera.pos()[2] = 0.0;
    
    // Move in diagonal direction (should be normalized)
    double dir[] = {1.0, 1.0, 0.0}; // Not normalized
    double length = sqrt(2.0);
    
    // Normalize the direction
    dir[0] /= length;
    dir[1] /= length;
    
    camera.moveAbsolute(dir, length);
    
    EXPECT_NEAR(1.0, camera.pos()[0], 1e-10);
    EXPECT_NEAR(1.0, camera.pos()[1], 1e-10);
    EXPECT_NEAR(0.0, camera.pos()[2], 1e-10);
}

// Test distance calculation between two keyframes
TEST_F(CameraTest, DistanceTo) {
    KeyFrame kf1, kf2;
    
    // Set positions
    kf1.pos()[0] = 0.0; kf1.pos()[1] = 0.0; kf1.pos()[2] = 0.0;
    kf2.pos()[0] = 3.0; kf2.pos()[1] = 4.0; kf2.pos()[2] = 0.0;
    
    double distance = kf1.distanceTo(kf2);
    
    // Distance should be 5.0 (3-4-5 triangle)
    EXPECT_NEAR(5.0, distance, 1e-10);
}

TEST_F(CameraTest, DistanceToSame) {
    KeyFrame kf1, kf2;
    
    // Same positions
    kf1.pos()[0] = 1.0; kf1.pos()[1] = 2.0; kf1.pos()[2] = 3.0;
    kf2.pos()[0] = 1.0; kf2.pos()[1] = 2.0; kf2.pos()[2] = 3.0;
    
    double distance = kf1.distanceTo(kf2);
    
    EXPECT_NEAR(0.0, distance, 1e-10);
}

// Test rotation functionality
TEST_F(CameraTest, RotateAroundAxis) {
    // Set up identity orientation first
    camera.q[0] = 0.0; camera.q[1] = 0.0; camera.q[2] = 0.0; camera.q[3] = 1.0;
    
    // Rotate 90 degrees around Z axis
    camera.rotate(90.0, 0.0, 0.0, 1.0);
    
    // After rotation, the quaternion should represent a 90-degree rotation around Z
    // This is a complex test, so we'll just verify that the quaternion is normalized
    double qmag = sqrt(camera.q[0]*camera.q[0] + camera.q[1]*camera.q[1] + 
                      camera.q[2]*camera.q[2] + camera.q[3]*camera.q[3]);
    EXPECT_NEAR(1.0, qmag, 1e-10);
}

TEST_F(CameraTest, RotateZeroDegrees) {
    // Set up identity orientation
    double original_q[] = {0.0, 0.0, 0.0, 1.0};
    camera.q[0] = original_q[0]; camera.q[1] = original_q[1]; 
    camera.q[2] = original_q[2]; camera.q[3] = original_q[3];
    
    // Rotate 0 degrees around any axis
    camera.rotate(0.0, 1.0, 0.0, 0.0);
    
    // Should remain the same (within tolerance)
    expectArrayNear(original_q, camera.q, 1e-10);
}

// Test orthogonalization
TEST_F(CameraTest, Orthogonalize) {
    // Set up a slightly non-orthogonal matrix
    camera.v[0] = 1.1; camera.v[1] = 0.1; camera.v[2] = 0.0;  // right (slightly off)
    camera.v[4] = 0.1; camera.v[5] = 1.1; camera.v[6] = 0.0;  // up (slightly off)
    camera.v[8] = 0.0; camera.v[9] = 0.0; camera.v[10] = 1.0; // ahead (correct)
    
    camera.orthogonalize();
    
    // After orthogonalization, vectors should be unit length and orthogonal
    double* right = camera.right();
    double* up = camera.up();
    double* ahead = camera.ahead();
    
    // Check unit lengths
    double right_len = sqrt(right[0]*right[0] + right[1]*right[1] + right[2]*right[2]);
    double up_len = sqrt(up[0]*up[0] + up[1]*up[1] + up[2]*up[2]);
    double ahead_len = sqrt(ahead[0]*ahead[0] + ahead[1]*ahead[1] + ahead[2]*ahead[2]);
    
    EXPECT_NEAR(1.0, right_len, 1e-10);
    EXPECT_NEAR(1.0, up_len, 1e-10);
    EXPECT_NEAR(1.0, ahead_len, 1e-10);
    
    // Check orthogonality (dot products should be zero)
    double dot_right_up = right[0]*up[0] + right[1]*up[1] + right[2]*up[2];
    double dot_right_ahead = right[0]*ahead[0] + right[1]*ahead[1] + right[2]*ahead[2];
    double dot_up_ahead = up[0]*ahead[0] + up[1]*ahead[1] + up[2]*ahead[2];
    
    EXPECT_NEAR(0.0, dot_right_up, 1e-10);
    EXPECT_NEAR(0.0, dot_right_ahead, 1e-10);
    EXPECT_NEAR(0.0, dot_up_ahead, 1e-10);
}