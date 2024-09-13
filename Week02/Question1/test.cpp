#include <gtest/gtest.h>
#include "./homework2_skeleton.cpp"  // Adjust the include path based on your project structure

// Test Vector class

TEST(VectorTest, Constructor2D) {
    Vector v(1.0, 2.0);
    EXPECT_EQ(v[0], 1.0);
    EXPECT_EQ(v[1], 2.0);
}

TEST(VectorTest, Constructor3D) {
    Vector v(1.0, 2.0, 3.0);
    EXPECT_EQ(v[0], 1.0);
    EXPECT_EQ(v[1], 2.0);
    EXPECT_EQ(v[2], 3.0);
}

TEST(VectorTest, Addition) {
    Vector v1(1.0, 2.0);
    Vector v2(3.0, 4.0);
    Vector result = v1 + v2;
    EXPECT_EQ(result[0], 4.0);
    EXPECT_EQ(result[1], 6.0);
}

TEST(VectorTest, Subtraction) {
    Vector v1(3.0, 4.0);
    Vector v2(1.0, 2.0);
    Vector result = v1 - v2;
    EXPECT_EQ(result[0], 2.0);
    EXPECT_EQ(result[1], 2.0);
}

TEST(VectorTest, ScalarMultiplication) {
    Vector v(1.0, 2.0);
    Vector result = v * 3.0;
    EXPECT_EQ(result[0], 3.0);
    EXPECT_EQ(result[1], 6.0);
}

TEST(VectorTest, DotProduct) {
    Vector v1(1.0, 2.0);
    Vector v2(3.0, 4.0);
    double result = v1 * v2;
    EXPECT_EQ(result, 11.0);
}

TEST(VectorTest, NormL1) {
    Vector v(1.0, -2.0, 3.0);
    double result = norm(v, "L1");
    EXPECT_EQ(result, 6.0);
}

TEST(VectorTest, NormL2) {
    Vector v(1.0, -2.0, 3.0);
    double result = norm(v, "L2");
    EXPECT_NEAR(result, 3.74166, 1e-5);
}

TEST(VectorTest, NormLinf) {
    Vector v(1.0, -2.0, 3.0);
    double result = norm(v, "Linf");
    EXPECT_EQ(result, 3.0);
}

// Test Particle class

TEST(ParticleTest, Initialization2D) {
    Vector position(0.0, 0.0);
    Vector velocity(1.0, 2.0);
    Vector force(0.0, 0.0);
    Particle p(1.0, position, velocity, force);
    EXPECT_EQ(p.getPosition()[0], 0.0);
    EXPECT_EQ(p.getPosition()[1], 0.0);
}

TEST(ParticleTest, UpdatePosition2D) {
    Vector position(0.0, 0.0);
    Vector velocity(1.0, 2.0);
    Vector force(0.0, 0.0);
    Particle p(1.0, position, velocity, force);
    p.updatePosition(2.0);
    EXPECT_EQ(p.getPosition()[0], 2.0);
    EXPECT_EQ(p.getPosition()[1], 4.0);
}

TEST(ParticleTest, UpdateVelocityAndPosition) {
    Vector position(0.0, 0.0);
    Vector velocity(1.0, 2.0);
    Vector force(0.0, 0.0);
    Particle p(1.0, position, velocity, force);
    p.update(0.0, 2.0);
    EXPECT_EQ(p.getPosition()[0], 2.0);
    EXPECT_EQ(p.getPosition()[1], 4.0);
}

TEST(ParticleTest, ForceCalculation) {
    Vector v(1.0, 2.0);
    double t = 2.0;
    Vector result = force(v, t);
    EXPECT_EQ(result[0], 2.0);
    EXPECT_EQ(result[1], 4.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}