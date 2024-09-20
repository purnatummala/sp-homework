#include "Grid3d_1d_array.h"
#include <iostream>
#include <iomanip>
#include <stdexcept> // For std::out_of_range and std::invalid_argument

// Constructor
Grid1::Grid1(int nx_, int ny_, int nz_) : nx(nx_), ny(ny_), nz(nz_) {
    if (nx <= 0 || ny <= 0 || nz <= 0) {
        throw std::invalid_argument("Grid1::Grid1: Dimensions must be positive");
    }
    data = new double[nx * ny * nz]();
}

// Destructor
Grid1::~Grid1() {
    delete[] data;
}

// Get the total number of elements
int Grid1::getSize() const {
    return nx * ny * nz;
}

// Get the memory size in bytes
int Grid1::getMemory() const {
    return getSize() * sizeof(double);
}

// Access an element (const version)
double Grid1::operator()(int i, int j, int k) const {
    if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz) {
        throw std::out_of_range("Grid1::operator(): Index out of bounds");
    }
    return data[i + nx * (j + ny * k)];
}

// Set an element
void Grid1::set(int i, int j, int k, double value) {
    if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz) {
        throw std::out_of_range("Grid1::set: Index out of bounds");
    }
    data[i + nx * (j + ny * k)] = value;
}

// Add two grids element-wise
Grid1 Grid1::operator+(const Grid1& grid) {
    if (nx != grid.nx || ny != grid.ny || nz != grid.nz) {
        throw std::invalid_argument("Grid1::operator+: Grid dimensions do not match");
    }
    Grid1 result(nx, ny, nz);
    for (int i = 0; i < getSize(); ++i) {
        result.data[i] = data[i] + grid.data[i];
    }
    return result;
}

// Print the grid
std::ostream& operator<<(std::ostream& os, const Grid1& grid) {
    for (int k = 0; k < grid.nz; ++k) {
        for (int j = 0; j < grid.ny; ++j) {
            for (int i = 0; i < grid.nx; ++i) {
                os << std::setw(10) << grid(i, j, k) << " ";
            }
            os << std::endl;
        }
        os << std::endl;
    }
    return os;
}