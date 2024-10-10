#ifndef BRAIN_MESH_H
#define BRAIN_MESH_H

#include "brain_mesh_macros.h"
#include <vector>
#include <array>
#include <string>

// BrainMesh class definition
template <typename T, typename I>
class BrainMesh {
private:
    std::vector<std::array<T, 3>> vertices; // Collection of vertices
    std::vector<std::array<I, 3>> triangles; // Collection of triangles
    std::vector<T> triangleAreas; // Areas of triangles
    std::vector<T> vertexAreas; // Areas associated with vertices
    std::vector<T> edgeLengths; // Lengths of edges
    T totalArea; // Total surface area
    int nbPoints; // Number of points
    int nbTriangles; // Number of triangles
    int nbVertices; // Number of vertices
    int nbEdges; // Number of edges
    std::string name; // Name of the mesh

public:
    // Constructor
    BrainMesh(const std::string& name);

    // Copy constructor
    BrainMesh(const BrainMesh& other);

    // Assignment operator
    BrainMesh& operator=(const BrainMesh& other);

    // Destructor
    ~BrainMesh() {}

    // Method to read data from a file
    void readData(const std::string& fileName);

    // Method to compute the area of a triangle
    T getTriangleArea(const std::array<I, 3>& triangle,  
        std::array<T, 3>& r12, std::array<T, 3>& r13, std::array<T, 3>& cross);

    // Getters for triangle areas, edge lengths, and total area
    std::vector<T>& getTriangleAreas();
    std::vector<T>& getEdgeLengths();
    T getTotalArea();

    // Method to compute areas associated with vertices
    void computeVertexAreas();
    std::vector<T> getVertexAreas();
    void saveVertexAreas(const std::string& fileName);
};

#include "brain_mesh.hxx"

#endif // BRAIN_MESH_H