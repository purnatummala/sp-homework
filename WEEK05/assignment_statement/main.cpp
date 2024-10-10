#include "brain_mesh_macros.h"
#include "brain_mesh.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>

// Function to save a vector to a file
template <typename T>
void saveVector(const std::string& fileName, const std::vector<T>& vec) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    for (const auto& val : vec) {
        file << val << std::endl;
    }
    file.close();
}

// Function to calculate mean and standard deviation
template <typename T>
void calculateMeanAndStdDev(const std::vector<T>& vec, T& mean, T& stddev) {
    T sum = 0;
    for (const auto& val : vec) {
        sum += val;
    }
    mean = sum / vec.size();

    T variance = 0;
    for (const auto& val : vec) {
        variance += (val - mean) * (val - mean);
    }
    stddev = std::sqrt(variance / vec.size());
}

int main() {
    // Set to true to run tests, false for normal execution
    bool test_code = false;

    // Write to cout with 14 decimal precision
    std::cout << std::setprecision(14) << std::endl;

    if (test_code) {
        std::cout << "Running test code..." << std::endl;

        // Create an instance of BrainMesh for double precision
        BrainMesh<double, long> brainDouble("tetrahedron");
        brainDouble.readData("test_file.vtk");

        // Compute total area of the tetrahedron
        double totalArea = brainDouble.getTotalArea();
        std::cout << "Total surface area: " << totalArea << std::endl;
        
        // The actual surface area of the tetrahedron should be sqrt(3)
        double expectedArea = std::sqrt(3.0);
        std::cout << "Expected surface area: " << expectedArea << std::endl;
        std::cout << "Difference: " << std::abs(totalArea - expectedArea) << std::endl;
        assert(std::abs(totalArea - expectedArea) < 1e-6);

        brainDouble.computeVertexAreas();
        std::vector<double> vertexAreas = brainDouble.getVertexAreas();

        std::cout << "Vertex areas (first 10):" << std::endl;
        for (size_t i = 0; i < std::min(vertexAreas.size(), size_t(10)); ++i) {
            std::cout << "Vertex " << i << ": " << vertexAreas[i] << std::endl;
        }

        // Each vertex should have an area of sqrt(3)/4
        for (const auto& area : vertexAreas) {
            assert(std::abs(area - expectedArea / 4) < 1e-6);
        }

        // Print summary of vertex areas
        std::cout << "Total number of vertices: " << vertexAreas.size() << std::endl;
        std::cout << "First vertex area: " << vertexAreas.front() << std::endl;
        std::cout << "Last vertex area: " << vertexAreas.back() << std::endl;

        // Get edge lengths
        std::vector<double> edgeLengths = brainDouble.getEdgeLengths();
        std::cout << "Edge lengths (first 10):" << std::endl;
        for (size_t i = 0; i < std::min(edgeLengths.size(), size_t(10)); ++i) {
            std::cout << "Edge " << i << ": " << edgeLengths[i] << std::endl;
        }

        // Each edge should have a length of 1 or sqrt(2)
        for (const auto& length : edgeLengths) {
            assert(std::abs(length - 1.0) < 1e-6 || std::abs(length - std::sqrt(2.0)) < 1e-6);
        }

        // Print summary of edge lengths
        std::cout << "Total number of edges: " << edgeLengths.size() << std::endl;
        std::cout << "First edge length: " << edgeLengths.front() << std::endl;
        std::cout << "Last edge length: " << edgeLengths.back() << std::endl;

        // Get triangle areas
        std::vector<double> triangleAreas = brainDouble.getTriangleAreas();
        std::cout << "Triangle areas (first 10):" << std::endl;
        for (size_t i = 0; i < std::min(triangleAreas.size(), size_t(10)); ++i) {
            std::cout << "Triangle " << i << ": " << triangleAreas[i] << std::endl;
        }

        // Each triangle should have an area of sqrt(3)/4
        for (const auto& area : triangleAreas) {
            assert(std::abs(area - expectedArea / 4) < 1e-6);
        }

        // Print summary of triangle areas
        std::cout << "Total number of triangles: " << triangleAreas.size() << std::endl;
        std::cout << "First triangle area: " << triangleAreas.front() << std::endl;
        std::cout << "Last triangle area: " << triangleAreas.back() << std::endl;

        std::cout << "All tests passed successfully!" << std::endl;

        // 2 & 3. Test with actual brain mesh (double and single precision)
        {
            BrainMesh<double, long> brainDouble("brain_double");
            brainDouble.readData("Cort_lobe_poly.vtk");

            BrainMesh<float, long> brainFloat("brain_float");
            brainFloat.readData("Cort_lobe_poly.vtk");

            double totalAreaDouble = brainDouble.getTotalArea();
            float totalAreaFloat = brainFloat.getTotalArea();

            std::cout << "Brain total area (double): " << totalAreaDouble << std::endl;
            std::cout << "Brain total area (float): " << totalAreaFloat << std::endl;

            // Check if double and float results are close (within 0.1%)
            assert(std::abs(totalAreaDouble - totalAreaFloat) / totalAreaDouble < 0.001);

            // 4. Validate conservation of area
            brainDouble.computeVertexAreas();
            auto vertexAreas = brainDouble.getVertexAreas();
            double sumVertexAreas = 0.0;
            for (const auto& area : vertexAreas) {
                sumVertexAreas += area;
            }
            std::cout << "Sum of vertex areas: " << sumVertexAreas << std::endl;
            assert(std::abs(sumVertexAreas - totalAreaDouble) / totalAreaDouble < 1e-6);

            // 5. Check for reasonable values
            auto edgeLengths = brainDouble.getEdgeLengths();
            double meanEdgeLength, stddevEdgeLength;
            calculateMeanAndStdDev(edgeLengths, meanEdgeLength, stddevEdgeLength);
            std::cout << "Mean edge length: " << meanEdgeLength << std::endl;
            std::cout << "Stddev of edge lengths: " << stddevEdgeLength << std::endl;
            assert(meanEdgeLength > 0 && meanEdgeLength < 100);  // Adjust based on expected size

            auto triangleAreas = brainDouble.getTriangleAreas();
            double meanTriangleArea, stddevTriangleArea;
            calculateMeanAndStdDev(triangleAreas, meanTriangleArea, stddevTriangleArea);
            std::cout << "Mean triangle area: " << meanTriangleArea << std::endl;
            std::cout << "Stddev of triangle areas: " << stddevTriangleArea << std::endl;
            assert(meanTriangleArea > 0 && meanTriangleArea < 1000);  // Adjust based on expected size

            std::cout << "Brain mesh tests passed." << std::endl;
        }

        std::cout << "All tests passed successfully!" << std::endl;
    } else {
        // Normal execution code
        // Create an instance of BrainMesh for double precision
        BrainMesh<double, long> brainDouble("brain");
        brainDouble.readData("Cort_lobe_poly.vtk");

        // Compute total area of the brain in double precision
        double totalAreaDouble = brainDouble.getTotalArea();
        std::cout << "Total brain area (double precision): " << totalAreaDouble << std::endl;

        // Create an instance of BrainMesh for single precision
        BrainMesh<float, long> brainFloat("brain");
        brainFloat.readData("Cort_lobe_poly.vtk");

        // Compute total area of the brain in single precision
        float totalAreaFloat = brainFloat.getTotalArea();
        std::cout << "Total brain area (single precision): " << totalAreaFloat << std::endl;

        // Compute vertex areas in double precision
        brainDouble.computeVertexAreas();
        std::vector<double> vertexAreasDouble = brainDouble.getVertexAreas();

        // Save the vertex areas to a file named "vertex_areas.txt"
        saveVector("vertex_areas.txt", vertexAreasDouble);

        // Save the triangle edge lengths to a file named "edge_lengths.txt"
        std::vector<double> edgeLengthsDouble = brainDouble.getEdgeLengths();
        saveVector("edge_lengths.txt", edgeLengthsDouble);

        // Save the triangles areas to a file named "triangle_areas.txt"
        std::vector<double> triangleAreasDouble = brainDouble.getTriangleAreas();
        saveVector("triangle_areas.txt", triangleAreasDouble);

        // Sum the vertex areas in double precision
        double sumVertexAreasDouble = 0;
        for (auto area : vertexAreasDouble) {
            sumVertexAreasDouble += area;
        }
        std::cout << "Sum of vertex areas (double precision): " << sumVertexAreasDouble << std::endl;

        // Calculate mean and standard deviation of edge lengths
        double meanEdgeLength, stddevEdgeLength;
        calculateMeanAndStdDev(edgeLengthsDouble, meanEdgeLength, stddevEdgeLength);
        std::cout << "Mean edge length: " << meanEdgeLength << std::endl;
        std::cout << "Standard deviation of edge lengths: " << stddevEdgeLength << std::endl;
    }

    return 0;
}