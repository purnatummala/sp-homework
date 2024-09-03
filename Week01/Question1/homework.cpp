#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <optional>
#include <filesystem>
#include <sstream>

/**
 * Normalizes the temperature values in the given vector.
 *
 * @param T The vector of temperature values to be normalized.
 * @param Tmin The minimum desired temperature value.
 * @param Tmax The maximum desired temperature value.
 * @return The vector of normalized temperature values.
 */
std::optional<std::vector<float>> normalize_temperature(const std::vector<float>& T, float Tmin, float Tmax)
{
    if (T.empty())
    {
        std::cerr << "Error: Empty temperature vector provided for normalization." << std::endl;
        return std::nullopt;
    }

    float T_min = *std::min_element(T.begin(), T.end());
    float T_max = *std::max_element(T.begin(), T.end());

    if (T_min == T_max)
    {
        std::cerr << "Error: All temperature values are the same. Normalization is not possible." << std::endl;
        return std::nullopt;
    }

    std::vector<float> normalized_T;
    normalized_T.reserve(T.size());
    for (const auto& temp : T)
    {
        normalized_T.push_back(Tmin + (temp - T_min) * (Tmax - Tmin) / (T_max - T_min));
    }

    return normalized_T;
}

/**
 * Reads a temperature profile from a CSV file.
 *
 * @param filename The name of the file to read the temperature profile from.
 * @return A vector of floats representing the temperature profile read from the file, or nullopt on failure.
 */
std::optional<std::vector<float>> read_temperature_profile(const std::string& filename)
{
    if (!std::filesystem::exists(filename))
    {
        std::cerr << "Error: File does not exist: " << filename << std::endl;
        return std::nullopt;
    }

    std::ifstream temp_in(filename);
    if (!temp_in.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return std::nullopt;
    }

    std::vector<float> T;
    std::string line;
    while (std::getline(temp_in, line))
    {
        std::stringstream ss(line);
        std::string temp_str;
        while (std::getline(ss, temp_str, ','))
        {
            try
            {
                T.push_back(std::stof(temp_str));
            }
            catch (const std::invalid_argument& e)
            {
                std::cerr << "Invalid data in file: " << filename << std::endl;
                return std::nullopt;
            }
        }
    }

    if (T.empty())
    {
        std::cerr << "Error: No temperature data found in file: " << filename << std::endl;
        return std::nullopt;
    }

    return T;
}

/**
 * Writes the normalized temperature profile to a file.
 *
 * @param filename The name of the file to write the normalized temperature profile to.
 * @param T The vector of normalized temperature values.
 */
void write_normalized_temperature_profile(const std::string& filename, const std::vector<float>& T)
{
    std::ofstream outfile(filename);
    if (!outfile.is_open())
    {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& temp : T)
    {
        outfile << temp << std::endl;
    }

    if (outfile.fail())
    {
        std::cerr << "Error writing to file: " << filename << std::endl;
    }
}

/**
 * @brief Main function that reads a temperature profile from a file, normalizes it, and writes the normalized values to a file.
 *
 * @return int The exit status of the program.
 */
int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <filename> <Tmin> <Tmax>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    float Tmin = std::stof(argv[2]);
    float Tmax = std::stof(argv[3]);

    auto T_opt = read_temperature_profile(filename);

    if (!T_opt)
    {
        std::cerr << "No valid temperature data to process. Exiting program." << std::endl;
        return 1;
    }

    auto& T = *T_opt;

    std::cout << "Read " << T.size() << " temperature values." << std::endl;

    auto normalized_T_opt = normalize_temperature(T, Tmin, Tmax);

    if (!normalized_T_opt)
    {
        std::cerr << "Normalization failed. Exiting program." << std::endl;
        return 1;
    }

    write_normalized_temperature_profile("normalized_temperature.txt", *normalized_T_opt);

    std::cout << "Normalized temperature profile written to 'normalized_temperature.txt'." << std::endl;

    return 0;
}