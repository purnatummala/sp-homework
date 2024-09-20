/*
1) Create a 3D grid in 3 different ways: 

The object is a class: Grid
Size in each direction: nx, ny, nz

Method 1) 
*/
#ifndef __GRID3D_1D_ARRAY_H__
#define __GRID3D_1D_ARRAY_H__

#include <iostream>

class Grid1
{
public:
    Grid1(int nx_=1, int ny_=1, int nz_=1);
    ~Grid1();
    int getSize() const;
    int getMemory() const;
    // Get a value
    double operator()(int i, int j, int k) const;
    // Set a value. Using operator() is more elegant, but requires
    // more knowledge to implement
    void set(int i, int j, int k, double value);
    Grid1 operator+(const Grid1& grid);
    friend std::ostream& operator<<(std::ostream& os, const Grid1& grid);


private:
    double* data;
    int nx, ny, nz;
};

#endif
