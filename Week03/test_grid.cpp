#include <iostream>
#include <cassert>
#include "grid3d_1d_array.h"
#include "grid3d_new.h"
#include "grid3d_vector.h"
using namespace std;

void test_grid1_size() {
    cout << "Running test_grid1_size..." << endl;
    int nx = 2, ny = 3, nz = 4;
    Grid1 grid(nx, ny, nz);
    cout << "Grid1 created." << endl;
    assert(grid.getSize() == nx * ny * nz);
    cout << "Grid1 size test passed." << endl;
}

void test_grid1_values() {
    cout << "Running test_grid1_values..." << endl;
    int nx = 2, ny = 3, nz = 4;
    Grid1 grid(nx, ny, nz);
    cout << "Grid1 created." << endl;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                grid.set(i, j, k, 100 * i + 10 * j + k);
                assert(grid(i, j, k) == 100 * i + 10 * j + k);
            }
        }
    }
    cout << "Grid1 value set/get test passed." << endl;
}

void test_grid2_addition() {
    cout << "Running test_grid2_addition..." << endl;
    int nx = 2, ny = 3, nz = 4;
    Grid2 grid1(nx, ny, nz);
    Grid2 grid2(nx, ny, nz);
    cout << "Grid2 instances created." << endl;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                grid1.set(i, j, k, 100 * i + 10 * j + k);
                grid2.set(i, j, k, 100 * i + 10 * j + k);
            }
        }
    }
    Grid2 grid_sum = grid1 + grid2;
    cout << "Grid2 addition performed." << endl;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                assert(grid_sum(i, j, k) == 2 * (100 * i + 10 * j + k));
            }
        }
    }
    cout << "Grid2 addition test passed." << endl;
}

void test_grid3_memory() {
    std::cout << "Running test_grid3_memory..." << std::endl;
    int nx = 2, ny = 3, nz = 4;
    Grid3 grid(nx, ny, nz);
    std::cout << "Grid3 created." << std::endl;
    assert(static_cast<size_t>(grid.getMemory()) == static_cast<size_t>(nx * ny * nz * sizeof(double)));
    std::cout << "Grid3 memory test passed." << std::endl;
}

void test_grid1_out_of_bounds() {
    cout << "Running test_grid1_out_of_bounds..." << endl;
    int nx = 2, ny = 3, nz = 4;
    Grid1 grid(nx, ny, nz);
    cout << "Grid1 created." << endl;
    try {
        grid.set(nx, ny, nz, 0.0);
        assert(false); // Should not reach here
    } catch (const std::out_of_range&) {
        cout << "Grid1 out-of-bounds test passed." << endl;
    }
}

int main()
{
    cout << "Starting tests..." << endl;
    test_grid1_size();
    test_grid1_values();
    test_grid2_addition();
    test_grid3_memory();
    test_grid1_out_of_bounds();
    cout << "All tests passed." << endl;
    return 0;
}
