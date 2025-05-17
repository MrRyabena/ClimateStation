#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdint.h>
#include <algorithm>

std::string getBaseName(const std::string& filename)
{
    size_t lastSlash = filename.find_last_of("/\\");
    size_t lastDot = filename.find_last_of(".");
    if (lastDot == std::string::npos)
    {
        lastDot = filename.length(); // No extension found
    }
    return filename.substr(lastSlash + 1, lastDot - lastSlash - 1);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> [--output <output_file>]" << std::endl;
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = getBaseName(inputFilename) + ".shsf"; // Default output filename

    // Check for optional output filename
    if (argc == 4 && std::string(argv[2]) == "--output")
    {
        outputFilename = argv[3];
    }

    std::ifstream inFile(inputFilename);
    if (!inFile)
    {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    std::vector<uint16_t> values;
    std::string line;

    // Read each line from the input file
    while (std::getline(inFile, line))
    {
        // Remove newlines and carriage returns
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

        std::istringstream iss(line);
        std::string hexValue;

        // Reading values from the line
        while (std::getline(iss, hexValue, ','))
        {
            // Removing spaces
            hexValue.erase(std::remove(hexValue.begin(), hexValue.end(), ' '), hexValue.end());

            // Check for empty value
            if (hexValue.empty())
            {
                // std::cerr << "Empty hexadecimal value encountered." << std::endl;
                continue; // Skip empty values
            }

            // Debugging output
            //std::cout << "Processing value: '" << hexValue << "'" << std::endl;

            try
            {
                // Converting to uint16_t
                uint16_t value = static_cast<uint16_t>(std::stoi(hexValue, nullptr, 16));
                values.push_back(value);
            } catch (const std::invalid_argument& e)
            {
                std::cerr << "Invalid hexadecimal value: " << hexValue << std::endl;
                return 1; // Exit on error
            } catch (const std::out_of_range& e)
            {
                std::cerr << "Hexadecimal value out of range: " << hexValue << std::endl;
                return 1; // Exit on error
            }
        }
    }

    inFile.close();

    // Writing to the binary file
    std::ofstream outFile(outputFilename, std::ios::binary);
    if (!outFile)
    {
        std::cerr << "Error opening output file for writing." << std::endl;
        return 1;
    }

    // Writing values to the file
    for (const auto& value : values)
    {
        outFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    outFile.close();
    std::cout << "Data successfully written to file " << outputFilename << std::endl;

    return 0;
}