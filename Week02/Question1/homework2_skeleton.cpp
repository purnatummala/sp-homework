#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm> // for std::max
#include <fstream>   // for file operations
using namespace std;

// Vector class to represent both 2D and 3D vectors
class Vector
{
private:
    vector<double> components_;

public:
    // Constructor for initializing with components
    // Handles both 2D and 3D vectors by accepting a vector of components
    Vector(const vector<double> &components) : components_(components) {}

    // Constructor for 2D vector
    Vector(double x, double y) : components_{x, y} {}

    // Constructor for 3D vector
    Vector(double x, double y, double z) : components_{x, y, z} {}

    // Default destructor
    ~Vector() {}

    // Number of components
    // Returns the size of the vector, which can be 2 or 3
    int size() const {
        return components_.size();
    }

    // Vector addition
    // Adds two vectors of the same dimension
    Vector operator+(const Vector &other) const
    {
        if (size() != other.size()) {
            throw runtime_error("Vectors must be of the same size for addition.");
        }

        vector<double> result(size());
        for (size_t i = 0; i < size(); ++i) {
            result[i] = components_[i] + other.components_[i];
        }
        return Vector(result);
    }

    // Vector subtraction
    // Subtracts two vectors of the same dimension
    Vector operator-(const Vector &other) const
    {
        if (size() != other.size()) {
            throw runtime_error("Vectors must be of the same size for subtraction.");
        }

        vector<double> result(size());
        for (size_t i = 0; i < size(); ++i) {
            result[i] = components_[i] - other.components_[i];
        }
        return Vector(result);
    }

    // Access operator with bounds checking
    // Provides access to vector components with bounds checking
    double operator[](const int i) const
    {
        if (i < 0 || i >= size()) {
            throw out_of_range("Index out of bounds.");
        }
        return components_[i];
    }

    // Scalar multiplication
    // Multiplies each component of the vector by a scalar
    Vector operator*(const double &scalar) const
    {
        vector<double> result(size());
        for (size_t i = 0; i < size(); ++i) {
            result[i] = components_[i] * scalar;
        }
        return Vector(result);
    }

    // Scalar multiplication (friend function for symmetry)
    // Allows scalar multiplication from both sides
    friend Vector operator*(const double scalar, const Vector &v)
    {
        return v * scalar;
    }

    // Dot product
    // Computes the dot product of two vectors of the same dimension
    double operator*(const Vector &other) const
    {
        if (size() != other.size()) {
            throw runtime_error("Vectors must be of the same size for dot product.");
        }

        double dotProduct = 0.0;
        for (size_t i = 0; i < size(); ++i) {
            dotProduct += components_[i] * other.components_[i];
        }
        return dotProduct;
    }

    // Stream output operator
    // Allows vectors to be printed in a readable format
    friend ostream &operator<<(ostream &os, const Vector &v)
    {
        os << "(";
        for (size_t i = 0; i < v.size(); ++i)
        {
            os << v.components_[i];
            if (i < v.size() - 1)
                os << ", ";
        }
        os << ")";
        return os;
    }
};

// Function to calculate different norms of the vector
// Supports L1, L2, and Linf norms
double norm(const Vector &v, const string &type)
{
    double normValue = 0.0;
    if (type == "L1") {
        for (size_t i = 0; i < v.size(); ++i) {
            normValue += fabs(v[i]);
        }
    } else if (type == "L2") {
        for (size_t i = 0; i < v.size(); ++i) {
            normValue += v[i] * v[i];
        }
        normValue = sqrt(normValue);
    } else if (type == "Linf") {
        for (size_t i = 0; i < v.size(); ++i) {
            normValue = max(normValue, fabs(v[i]));
        }
    } else {
        throw invalid_argument("Unknown norm type.");
    }
    return normValue;
}

// Particle class to represent particles in 2D and 3D space
class Particle
{
public:
    // Constructor to initialize particle properties
    Particle(double mass, const Vector &position, const Vector &velocity, const Vector &force)
        : mass_(mass), position_(position), velocity_(velocity), force_(force)
    {
        cout << "Particle created at position " << position_ << endl;
    }

    // Destructor to indicate when a particle is destroyed
    ~Particle()
    {
        cout << "Particle destroyed at position " << position_ << endl;
    }

    // Function to update the position of the particle based on time
    void updatePosition(double time)
    {
        position_ = position_ + velocity_ * time;
    }

    // Function to print the current state of the particle
    void printState() const
    {
        if (velocity_.size() == 0) {
            throw runtime_error("printState: Vector is empty");
        }
        cout << "Particle - Mass: " << mass_ << ", Position: " << position_
             << ", Velocity: " << velocity_ << ", Speed: " << norm(velocity_, "L2") << endl;
    }

    // Function to update particle properties at time t, using time step dt
    void update(double t, double dt)
    {
        Vector acceleration = force_ * (1.0 / mass_);
        velocity_ = velocity_ + acceleration * dt;
        position_ = position_ + velocity_ * dt;
    }

    // Function to get the current position of the particle
    const Vector& getPosition() const {
        return position_;
    }

private:
    double mass_;
    Vector position_;
    Vector velocity_;
    Vector force_;
};

// Function to calculate force based on a vector and time
// Example implementation: force is proportional to the vector components and time
Vector force(const Vector &v, double t)
{
    return v * t;
}

// Function to test vector operators
// Demonstrates vector addition, scalar multiplication, and dot product
void test_operators() {
    std::cout << "Inside test operators" << std::endl;

    Vector v1(1.0, 2.0);
    Vector v2(3.0, 4.0);
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "3.2 * v1: " << 3.2 * v1 << std::endl;
    std::cout << "v1 * 3.2: " << v1 * 3.2 << std::endl;
    std::cout << "v1 + v2: " << v1 + v2 << std::endl;
    double prod;
    prod = (2. * v1 + 3. * v2) * (v1 + v2);
    std::cout << "(2.*v1 + 3.*v2) * (v1 + v2) = " << prod << std::endl;
    prod = (2. * v1 + 3. * v2) * v1;
    std::cout << "(2.*v1 + 3.*v2) * v1 = " << prod << std::endl;
    prod = v1 * v2;
    std::cout << "v1 * v2: " << prod << std::endl;
    std::cout << "Vector addition: " << v1 << " + " << v2 << " = " << v1 + v2 << std::endl;
}

// Main function
int main()
{
    // Create a 2D particle with mass 1 and force (0., 0.)
    Particle particle2D(1.0, Vector(0.0, 0.0), Vector(1.0, 2.0), Vector(0., 0.));
    cout << "Initial state of 2D particle:" << endl;
    particle2D.printState();

    // Update position and velocity considering forces
    particle2D.update(0.0, 2.0);
    cout << "2D particle after 2 seconds:" << endl;
    particle2D.printState();

    // Create a 3D particle
    Particle particle3D(1.0, Vector(0.0, 0.0, 0.0), Vector(1.0, 2.0, 3.0), Vector(0., 0., 0.));
    cout << "\nInitial state of 3D particle:" << endl;
    particle3D.printState();

    particle3D.update(0.0, 2.0);

    cout << "3D particle after 2 seconds:" << endl;
    particle3D.printState();

    // Demonstrate vector addition and other operations
    test_operators();

    // Handle particles
    Vector f2d{0., 0.};     // regular parentheses
    Vector f3d{0., 0., 0.}; // curly brackets, safer

    cout << "f2d: " << f2d << endl;
    cout << "f3d: " << f3d << endl;

    double t = 1.0;
    cout << force(f2d, t) << endl;
    cout << force(f3d, t) << endl;

    // Output the 2D and 3D trajectories to files
    ofstream file2D("traject_2d.txt");
    ofstream file3D("traject_3d.txt");

    if (!file2D || !file3D) {
        cerr << "Error opening file for writing." << endl;
        return 1;
    }

    // Simulate trajectory for 2D particle
    double time = 0.0;
    double dt = 0.1;
    for (int i = 0; i <= 20; ++i) {
        file2D << time << " " << particle2D.getPosition()[0] << " " << particle2D.getPosition()[1] << endl;
        particle2D.update(time, dt);
        time += dt;
    }

    // Simulate trajectory for 3D particle
    time = 0.0;
    for (int i = 0; i <= 20; ++i) {
        file3D << time << " " << particle3D.getPosition()[0] << " " << particle3D.getPosition()[1] << " " << particle3D.getPosition()[2] << endl;
        particle3D.update(time, dt);
        time += dt;
    }

    return 0;
}