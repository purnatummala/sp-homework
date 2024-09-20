#include "grid3d_new.h"
#include <iostream>
#include <iomanip>
#include <stdexcept> // For std::out_of_range and std::invalid_argument

// Constructor
Grid3::Grid3(int nx_, int ny_, int nz_) : nx(nx_), ny(ny_), nz(nz_) {
    if (nx <= 0 || ny <= 0 || nz <= 0) {
        throw std::invalid_argument("Grid3::Grid3: Dimensions must be positive");
    }
    data = new double**[nx];
    for (int i = 0; i < nx; ++i) {
        data[i] = new double*[ny];
        for (int j = 0; j < ny; ++j) {
            data[i][j] = new double[nz]();
        }
    }
}

// Destructor
Grid3::~Grid3() {
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            delete[] data[i][j];
        }
        delete[] data[i];
    }
    delete[] data;
}

// Get the total number of elements
int Grid3::getSize() const {
    return nx * ny * nz;
}

// Get the memory size in bytes
int Grid3::getMemory() const {
    return getSize() * sizeof(double);
}

// Access an element (const version)
double Grid3::operator()(int i, int j, int k) const {
    if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz) {
        throw std::out_of_range("Grid3::operator(): Index out of bounds");
    }
    return data[i][j][k];
}

// Set an element
void Grid3::set(int i, int j, int k, double value) {
    if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz) {
        throw std::out_of_range("Grid3::set: Index out of bounds");
    }
    data[i][j][k] = value;
}

// Add two grids element-wise
Grid3 Grid3::operator+(const Grid3& grid) {
    if (nx != grid.nx || ny != grid.ny || nz != grid.nz) {
        throw std::invalid_argument("Grid3::operator+: Grid dimensions do not match");
    }
    Grid3 result(nx, ny, nz);
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            for (int k = 0; k < nz; ++k) {
                result.data[i][j][k] = data[i][j][k] + grid.data[i][j][k];
            }
        }
    }
    return result;
}

// Print the grid
std::ostream& operator<<(std::ostream& os, const Grid3& grid) {
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