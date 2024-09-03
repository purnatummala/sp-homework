#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string> // Include this header for std::stoi

/**
 * Generates a CSV file with random temperature data.
 *
 * @param filename The name of the file to write the temperature data to.
 * @param num_steps The number of time steps to generate.
 */
void generate_temperature_csv(const std::string& filename, int num_steps)
{
    std::ofstream outfile(filename);
    if (!outfile.is_open())
    {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    std::srand(std::time(nullptr));
    for (int i = 0; i < num_steps; ++i)
    {
        float temp = static_cast<float>(std::rand()) / RAND_MAX * 100.0f; // Random temperature between 0 and 100
        outfile << temp;
        if (i < num_steps - 1)
        {
            outfile << ",";
        }
    }

    if (outfile.fail())
    {
        std::cerr << "Error writing to file: " << filename << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <filename> <num_steps>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int num_steps = std::stoi(argv[2]);

    generate_temperature_csv(filename, num_steps);

    std::cout << "Temperature data written to '" << filename << "'." << std::endl;

    return 0;
}