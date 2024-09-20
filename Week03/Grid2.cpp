#include "grid3d_vector.h"
#include <iostream>
#include <iomanip>
#include <stdexcept> // For std::out_of_range and std::invalid_argument

// Constructor
Grid2::Grid2(int nx_, int ny_, int nz_) : nx(nx_), ny(ny_), nz(nz_) {
    if (nx <= 0 || ny <= 0 || nz <= 0) {
        throw std::invalid_argument("Grid2::Grid2: Dimensions must be positive");
    }
    data.resize(nx, std::vector<std::vector<double>>(ny, std::vector<double>(nz, 0.0)));
}

// Destructor
Grid2::~Grid2() {
    // No need to manually delete data, vector handles it
}

// Get the total number of elements
int Grid2::getSize() const {
    return nx * ny * nz;
}

// Get the memory size in bytes
int Grid2::getMemory() const {
    return getSize() * sizeof(double);
}

// Access an element (const version)
double Grid2::operator()(int i, int j, int k) const {
    if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz) {
        throw std::out_of_range("Grid2::operator(): Index out of bounds");
    }
    return data[i][j][k];
}

// Set an element
void Grid2::set(int i, int j, int k, double value) {
    if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz) {
        throw std::out_of_range("Grid2::set: Index out of bounds");
    }
    data[i][j][k] = value;
}

// Add two grids element-wise
Grid2 Grid2::operator+(const Grid2& grid) {
    if (nx != grid.nx || ny != grid.ny || nz != grid.nz) {
        throw std::invalid_argument("Grid2::operator+: Grid dimensions do not match");
    }
    Grid2 result(nx, ny, nz);
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
std::ostream& operator<<(std::ostream& os, const Grid2& grid) {
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