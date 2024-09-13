#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Vector class to represent both 2D and 3D vectors
class Vector
{
private:
    vector<double> components_;

public:
    Vector(vector<double> components) : components_(components) {}

    // Constructor for 2D vector
    Vector(double x, double y) : components_{x, y} {}

    // Constructor for 3D vector
    Vector(double x, double y, double z) : components_{x, y, z} {}

    // Destructor
    ~Vector() {}

    // Function to return the number of components of the vector
    int size() const {
        return components_.size();
    }

    // Overloaded + operator to add two vectors of any size
    Vector operator+(const Vector &other) const {
        if (this->size() != other.size()) {
            throw std::invalid_argument("Vectors must have the same size");
        }
        vector<double> result;
        for (size_t i = 0; i < components_.size(); ++i) {
            result.push_back(components_[i] + other.components_[i]);
        }
        return Vector(result);
    }

    // Overloaded [] operator with error check for out of bounds index
    double operator[](const int i) const {
        if (i < 0 || i >= size()) {
            throw std::out_of_range("Index out of bounds");
        }
        return components_[i];
    }

    // Overloaded * operator for product with a scalar (vector * scalar)
    Vector operator*(const double &scalar) const {
        vector<double> result;
        for (auto &component : components_) {
            result.push_back(component * scalar);
        }
        return Vector(result);
    }

    // Overloaded * operator for dot product (Vector * Vector)
    double operator*(const Vector &other) const {
        if (this->size() != other.size()) {
            throw std::invalid_argument("Vectors must have the same size for dot product");
        }
        double dotProduct = 0.0;
        for (size_t i = 0; i < components_.size(); ++i) {
            dotProduct += components_[i] * other.components_[i];
        }
        return dotProduct;
    }

    // Overloaded * operator for product of a double and a Vector (double * Vector)
    friend Vector operator*(const double &scalar, const Vector &v) {
        return v * scalar;
    }

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

    // Function to calculate the norm of the vector
    double norm(const string &type) const {
        double result = 0.0;
        if (type == "L1") {
            for (auto &component : components_) {
                result += abs(component);
            }
        } else if (type == "L2") {
            for (auto &component : components_) {
                result += component * component;
            }
            result = sqrt(result);
        } else if (type == "Linf") {
            for (auto &component : components_) {
                result = max(result, abs(component));
            }
        } else {
            throw std::invalid_argument("Unknown norm type");
        }
        return result;
    }
};

// Function to calculate force applied to a vector over time
Vector &force(Vector &f, double t) {
    if (f.size() == 2) {
        f = Vector(sin(2 * t), cos(2 * t)); // Force for 2D case
    } else if (f.size() == 3) {
        f = Vector(sin(2 * t), cos(2 * t), sin(t)); // Force for 3D case
    }
    return f;
}


class Particle
{
private:
    double mass_;
    Vector position_;
    Vector velocity_;
    Vector force_;
    vector<double> time_;

public:
    // Last two arguments are position and velocity at time zero
    Particle(double mass, const Vector &position, const Vector &velocity, const Vector &force)
        : mass_(mass), position_(position), velocity_(velocity), force_(force)
    {
        cout << "Particle created at position " << position_ << endl;
    }

    ~Particle()
    {
        cout << "Particle destroyed at position " << position_ << endl;
    }

    void updatePosition(double time)
    {
        position_ = position_ + velocity_ * time;
    }

    void printState() const
    {
        if (velocity_.size() == 0) {
            throw runtime_error("printState: Vector is empty");
        }
        cout << "Particle - Mass: " << mass_ << ", Position: " << position_
             << ", Velocity: " << velocity_ << ", Speed: " << velocity_.norm("L2") << endl;
    }

    // Update particle properties at time t, using time step dt.
    // force_: force applied to the particle
    void update(double t, double dt)
    {
        // Update force
        force_ = ::force(force_, t);

        // Update velocity based on force and mass
        Vector acceleration = force_ * (1.0 / mass_);
        velocity_ = velocity_ + acceleration * dt;

        // Update position based on velocity
        position_ = position_ + velocity_ * dt;

        // Record time
        time_.push_back(t);

        // Debugging statement
        cout << "Updated at time " << t << ": Position = " << position_ << ", Velocity = " << velocity_ << endl;
    }

    // Function to calculate force applied to the particle
    Vector &force(Vector &f, double t)
    {
        return ::force(f, t);
    }

    // Function to get the position of the particle
    Vector getPosition() const {
        return position_;
    }

    // Function to get the velocity of the particle
    Vector getVelocity() const {
        return velocity_;
    }

    // Function to get the time vector
    vector<double> getTime() const {
        return time_;
    }
};

// Forward declaration of test_operators function
void test_operators();

// Function to demonstrate vector operations
void test_operators()
{
    cout << "Inside test operators" << endl;

    Vector v1(1.0, 2.0);
    Vector v2(3.0, 4.0);
    cout << "v2: " << v2 << endl;
    cout << "v1: " << v1 << endl;
    cout << "3.2 * v1: " << 3.2 * v1 << endl;
    cout << "v1 * 3.2: " << v1 * 3.2 << endl;
    cout << "v1 + v2: " << v1 + v2 << endl;
    double prod;
    prod = (2. * v1 + 3. * v2) * (v1 + v2);
    cout << "( 2.*v1 + 3.*v2 ) * (v1 + v2) = " << prod << endl;
    prod = (2. * v1 + 3. * v2) * v1;
    cout << "( 2.*v1 + 3.*v2 ) * v1 = " << prod << endl;
    prod = v1 * v2;
    cout << "v1 * v2 : " << prod << endl;
    cout << "Vector addition: " << v1 << " + " << v2 << " = " << v1 + v2 << endl;

    // test particles
}

int main(int argc, char *argv[]) {
    // Check the number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <output_2d_file> <output_3d_file>" << endl;
        return 1;
    }

    // Open output files
    ofstream output2D(argv[1]);
    ofstream output3D(argv[2]);

    // Check if the files were opened successfully
    if (!output2D.is_open() || !output3D.is_open()) {
        cerr << "Error opening output files." << endl;
        return 1;
    }

    // Create a 2D particle with mass 1 and initial conditions
    Particle particle2D(1.0, Vector(0.0, 0.0), Vector(1.0, 2.0), Vector(0., 0.));
    cout << "Initial state of 2D particle:" << endl;
    particle2D.printState();

    // Create a 3D particle
    Particle particle3D(1.0, Vector(0.0, 0.0, 0.0), Vector(1.0, 2.0, 3.0), Vector(0., 0.));
    cout << "\nInitial state of 3D particle:" << endl;
    particle3D.printState();

    double t = 0.0;
    double dt = 0.1;
    double endTime = 10.0;

    // Record the movement of 2D and 3D particles
    while (t <= endTime) {
        // Update particles
        particle2D.update(t, dt);
        particle3D.update(t, dt);

        // Get positions
        Vector pos2D = particle2D.getPosition();
        Vector pos3D = particle3D.getPosition();

        // Output positions to files (with appropriate error handling)
        if (output2D.good()) {
            output2D << t << " " << pos2D[0] << " " << pos2D[1] << endl;
        } else {
            cerr << "Error writing to 2D output file at time " << t << endl;
            break;
        }

        if (output3D.good()) {
            output3D << t << " " << pos3D[0] << " " << pos3D[1] << " " << pos3D[2] << endl;
        } else {
            cerr << "Error writing to 3D output file at time " << t << endl;
            break;
        }

        // Print to console for debugging
        cout << "Time: " << t << " 2D Position: (" << pos2D[0] << ", " << pos2D[1] << ")" << endl;
        cout << "Time: " << t << " 3D Position: (" << pos3D[0] << ", " << pos3D[1] << ", " << pos3D[2] << ")" << endl;

        // Increment time
        t += dt;
    }

    // Close output files
    output2D.close();
    output3D.close();

    // Verify if the files were written correctly by printing their content
    ifstream check2D(argv[1]);
    ifstream check3D(argv[2]);

    if (check2D.is_open() && check3D.is_open()) {
        string line;
        cout << "\nContents of " << argv[1] << ":" << endl;
        while (getline(check2D, line)) {
            cout << line << endl;
        }

        cout << "\nContents of " << argv[2] << ":" << endl;
        while (getline(check3D, line)) {
            cout << line << endl;
        }

        check2D.close();
        check3D.close();
    } else {
        cerr << "Error opening output files for verification." << endl;
    }

    return 0;
}