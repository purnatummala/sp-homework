#include "brain_mesh.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <set>

// Implementation of the constructor
template <typename T, typename I>
BrainMesh<T, I>::BrainMesh(const std::string& name) : totalArea(0), nbPoints(0), nbTriangles(0), nbVertices(0), nbEdges(0), name(name) {}

// Implementation of the copy constructor
template <typename T, typename I>
BrainMesh<T, I>::BrainMesh(const BrainMesh& other)
    : vertices(other.vertices), triangles(other.triangles), triangleAreas(other.triangleAreas),
      vertexAreas(other.vertexAreas), edgeLengths(other.edgeLengths), totalArea(other.totalArea),
      nbPoints(other.nbPoints), nbTriangles(other.nbTriangles), nbVertices(other.nbVertices),
      nbEdges(other.nbEdges), name(other.name) {}

// Implementation of the assignment operator
template <typename T, typename I>
BrainMesh<T, I>& BrainMesh<T, I>::operator=(const BrainMesh& other) {
    if (this != &other) {
        vertices = other.vertices;
        triangles = other.triangles;
        triangleAreas = other.triangleAreas;
        vertexAreas = other.vertexAreas;
        edgeLengths = other.edgeLengths;
        totalArea = other.totalArea;
        nbPoints = other.nbPoints;
        nbTriangles = other.nbTriangles;
        nbVertices = other.nbVertices;
        nbEdges = other.nbEdges;
        name = other.name;
    }
    return *this;
}

// Implementation of the readData method
template <typename T, typename I>
void BrainMesh<T, I>::readData(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    // Skip the first 5 lines
    for (int i = 0; i < 5; ++i) {
        std::getline(file, line);
    }
    // Count unique edges
    std::set<std::pair<I, I>> uniqueEdges; 
    for (const auto& triangle : triangles) {
        for (int i = 0; i < 3; ++i) {
            int v1 = triangle[i];
            int v2 = triangle[(i + 1) % 3];
            // Ensure consistent ordering for the edge pair
            if (v1 > v2) { 
                std::swap(v1, v2); 
            }
            uniqueEdges.insert({v1, v2});
        }
    }
    nbEdges = uniqueEdges.size(); 
    // Read vertices
    for (int i = 0; i < 191724; ++i) {
        std::getline(file, line);
        std::istringstream iss(line);
        T x, y, z;
        iss >> x >> y >> z;
        vertices.push_back({x, y, z});
    }

    // Skip line 191730
    std::getline(file, line);

    // Read triangles
    for (int i = 0; i < 383241; ++i) {
        std::getline(file, line);
        std::istringstream iss(line);
        int dummy, v1, v2, v3;
        iss >> dummy >> v1 >> v2 >> v3;
        if (dummy == 3) {
            triangles.push_back({v1, v2, v3});
        }
    }

    file.close();

    nbPoints = vertices.size();
    nbTriangles = triangles.size();
    nbVertices = vertices.size();
    nbEdges = triangles.size() * 3; // Assuming each triangle has 3 edges
}

// Implementation of the getTotalArea method
template <typename T, typename I>
T BrainMesh<T, I>::getTotalArea() {
    // Compute the total area if it hasn't been computed yet
    if (totalArea == 0) {
        for (const auto& triangle : triangles) {
            std::array<T, 3> r12, r13, cross;
            totalArea += getTriangleArea(triangle, r12, r13, cross);
        }
    }
    return totalArea;
}

// Implementation of the computeVertexAreas method
template <typename T, typename I>
void BrainMesh<T, I>::computeVertexAreas() {
    vertexAreas.resize(vertices.size(), 0);
    for (const auto& triangle : triangles) {
        std::array<T, 3> r12, r13, cross;
        T area = getTriangleArea(triangle, r12, r13, cross);
        for (int i = 0; i < 3; ++i) {
            vertexAreas[triangle[i]] += area / 3.0;
        }
    }
}

// Implementation of the getVertexAreas method
template <typename T, typename I>
std::vector<T> BrainMesh<T, I>::getVertexAreas() {
    return vertexAreas;
}

// Implementation of the getEdgeLengths method
template <typename T, typename I>
std::vector<T>& BrainMesh<T, I>::getEdgeLengths() {
    if (edgeLengths.empty()) {
        std::set<std::pair<I, I>> processedEdges; // To track processed edges
        for (const auto& triangle : triangles) {
            for (int i = 0; i < 3; ++i) {
                int v1 = triangle[i];
                int v2 = triangle[(i + 1) % 3];
                if (v1 > v2) {
                    std::swap(v1, v2);
                }
                // Only calculate if this edge hasn't been processed
                if (processedEdges.find({v1, v2}) == processedEdges.end()) { 
                    T length = std::sqrt(
                        std::pow(vertices[v1][0] - vertices[v2][0], 2) +
                        std::pow(vertices[v1][1] - vertices[v2][1], 2) +
                        std::pow(vertices[v1][2] - vertices[v2][2], 2)
                    );
                    edgeLengths.push_back(length);
                    processedEdges.insert({v1, v2});
                }
            }
        }
    }
    return edgeLengths;
}

// Implementation of the getTriangleAreas method
template <typename T, typename I>
std::vector<T>& BrainMesh<T, I>::getTriangleAreas() {
    if (triangleAreas.empty()) {
        for (const auto& triangle : triangles) {
            std::array<T, 3> r12, r13, cross;
            triangleAreas.push_back(getTriangleArea(triangle, r12, r13, cross));
        }
    }
    return triangleAreas;
}

// Implementation of the getTriangleArea method
template <typename T, typename I>
T BrainMesh<T, I>::getTriangleArea(const std::array<I, 3>& triangle,  
    std::array<T, 3>& r12, std::array<T, 3>& r13, std::array<T, 3>& cross) {
    for (int i = 0; i < 3; ++i) {
        r12[i] = vertices[triangle[1]][i] - vertices[triangle[0]][i];
        r13[i] = vertices[triangle[2]][i] - vertices[triangle[0]][i];
    }
    cross[0] = r12[1] * r13[2] - r12[2] * r13[1];
    cross[1] = r12[2] * r13[0] - r12[0] * r13[2];
    cross[2] = r12[0] * r13[1] - r12[1] * r13[0];
    return 0.5 * std::sqrt(cross[0] * cross[0] + cross[1] * cross[1] + cross[2] * cross[2]);
}