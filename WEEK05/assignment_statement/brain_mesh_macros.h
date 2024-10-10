#ifndef BRAIN_MESH_MACROS_H
#define BRAIN_MESH_MACROS_H

// Macros for template and class definitions
#define BM_TEMPLATE template <typename T, typename INT>
#define BM_CLASS BrainMesh<T, INT>

#include <vector>
#include <array>

// Alias template for a triangle, represented as an array of 3 indices
template <typename INT>
using Triangle = std::array<INT, 3>;

// Alias template for a collection of triangles
template <typename INT>
using Triangles = std::vector<Triangle<INT>>;

// Alias template for a vertex, represented as an array of 3 coordinates (x, y, z)
template <typename T>
using Vertex = std::array<T, 3>;

// Alias template for a collection of vertices
template <typename T>
using Vertices = std::vector<Vertex<T>>;

#endif // BRAIN_MESH_MACROS_H