#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <utility>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <functional>
#include <complex>
#include <string>
#include <algorithm>
#include <sstream>

// Abstract base class for scientific objects
class ScientificObject {
public:
    virtual void compute() const = 0;
    virtual ~ScientificObject() = default;
    virtual std::string getType() const = 0;
};

// Derived classes for specific calculations
class VectorCalculation : public ScientificObject {
public:
    void compute() const override {
        std::cout << "Performing vector calculation..." << std::endl;
    }
    std::string getType() const override { return "VectorCalculation"; }
};

class MatrixCalculation : public ScientificObject {
public:
    void compute() const override {
        std::cout << "Performing matrix calculation..." << std::endl;
    }
    std::string getType() const override { return "MatrixCalculation"; }
};

class TensorCalculation : public ScientificObject {
public:
    void compute() const override {
        std::cout << "Performing tensor calculation..." << std::endl;
    }
    std::string getType() const override { return "TensorCalculation"; }
};

// Custom exception class for duplicate elements
class DuplicateElementException : public std::runtime_error {
public:
    DuplicateElementException(const std::string& key)
        : std::runtime_error("Duplicate element with key: " + key) {}
};

// Template function to process scientific data
template <typename T>
void process_data(const T& data) {
    static_assert(std::is_arithmetic<T>::value, "Template type must be arithmetic");
    std::cout << "Processing data: " << data << std::endl;
}

// Template specialization for std::complex, restricted to std::complex<double>
template <typename T>
void process_data(const std::complex<T>& data) {
    static_assert(std::is_same<T, double>::value, "Only std::complex<double> is allowed");
    std::cout << "Processing complex number: Real = " << data.real() << ", Imaginary = " << data.imag() << std::endl;
}

// Function overload for std::string
void process_data(const std::string& data) {
    if (data.empty()) {
        throw std::invalid_argument("String must not be empty");
    }
    std::string reversed(data.rbegin(), data.rend());
    std::cout << "Processing string in reverse: " << reversed << std::endl;
}

// Template class that handles different types of scientific containers
template <typename T>
class ScientificContainer {
private:
    std::list<std::pair<T, std::shared_ptr<ScientificObject>>> container;
    std::unordered_map<T, std::tuple<int, double, std::string, std::function<void()>>> metadata;
    std::unordered_set<T> unique_elements;

public:
    void add_element(const T& key, std::shared_ptr<ScientificObject> obj) {
        if (unique_elements.find(key) != unique_elements.end()) {
            throw DuplicateElementException(std::to_string(key));
        }
        container.emplace_back(key, obj);
        unique_elements.insert(key);
    }

    void add_metadata(const T& key, const std::tuple<int, double, std::string, std::function<void()>>& data) {
        if (metadata.find(key) != metadata.end()) {
            throw std::runtime_error("Metadata for this key already exists.");
        }
        metadata[key] = data;
    }

    void compute_all() const {
        for (const auto& pair : container) {
            try {
                std::cout << "Computing for key: " << pair.first << std::endl;
                pair.second->compute();
            } catch (const std::exception& e) {
                std::cerr << "Error during computation for key " << pair.first << ": " << e.what() << std::endl;
            }
        }
    }

    void print_metadata() const {
        for (const auto& pair : metadata) {
            const auto& key = pair.first;
            const auto& data = pair.second;
            std::cout << "Metadata for key " << key << ": ("
                      << std::get<0>(data) << ", "
                      << std::get<1>(data) << ", "
                      << std::get<2>(data) << ")" << std::endl;
            std::get<3>(data)(); // Execute the stored function
        }
    }

    void filter_elements(const std::function<bool(const T&)>& condition) const {
        for (const auto& pair : container) {
            if (condition(pair.first)) {
                std::cout << "Key " << pair.first << " satisfies the filter condition." << std::endl;
            }
        }
    }

    // Iterator support
    using iterator = typename std::list<std::pair<T, std::shared_ptr<ScientificObject>>>::iterator;
    using const_iterator = typename std::list<std::pair<T, std::shared_ptr<ScientificObject>>>::const_iterator;

    iterator begin() { return container.begin(); }
    iterator end() { return container.end(); }
    const_iterator begin() const { return container.begin(); }
    const_iterator end() const { return container.end(); }

    std::string serialize() const {
        std::stringstream ss;
        ss << "{\n";
        ss << "  \"elements\": [\n";
        for (const auto& pair : container) {
            ss << "    {\"key\": " << pair.first << ", \"type\": \"" << pair.second->getType() << "\"},\n";
        }
        ss << "  ],\n";
        ss << "  \"metadata\": {\n";
        for (const auto& pair : metadata) {
            const auto& key = pair.first;
            const auto& data = pair.second;
            ss << "    \"" << key << "\": {"
               << "\"int_value\": " << std::get<0>(data) << ", "
               << "\"double_value\": " << std::get<1>(data) << ", "
               << "\"string_value\": \"" << std::get<2>(data) << "\""
               << "},\n";
        }
        ss << "  }\n";
        ss << "}\n";
        return ss.str();
    }
};

int main() {
    try {
        ScientificContainer<int> sci_container;

        // Adding elements to the container
        sci_container.add_element(1, std::make_shared<VectorCalculation>());
        sci_container.add_element(2, std::make_shared<MatrixCalculation>());
        sci_container.add_element(3, std::make_shared<TensorCalculation>());

        // Adding metadata
        sci_container.add_metadata(1, std::make_tuple(42, 3.14, "Vector", []() { std::cout << "Vector metadata accessed" << std::endl; }));
        sci_container.add_metadata(2, std::make_tuple(7, 2.718, "Matrix", []() { std::cout << "Matrix metadata accessed" << std::endl; }));
        sci_container.add_metadata(3, std::make_tuple(10, 1.414, "Tensor", []() { std::cout << "Tensor metadata accessed" << std::endl; }));

        // Process some data
        process_data(100);
        process_data(3.1415);

        // Process complex number
        std::complex<double> c(3.0, 4.0);
        process_data(c);

        // Process string
        process_data(std::string("Hello, World!"));

        // Compute all elements
        sci_container.compute_all();

        // Print metadata
        sci_container.print_metadata();

        // Filter elements
        sci_container.filter_elements([](const int& key) { return key % 2 == 0; });

        // Range-based for loop
        for (const auto& pair : sci_container) {
            std::cout << "Iterating over key: " << pair.first << std::endl;
        }

        // Serialize the container
        std::cout << "Serialized container:\n" << sci_container.serialize() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception caught in main: " << e.what() << std::endl;
    }

    return 0;
}
