#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>

#include <Magick++.h>


namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    
    const fs::path QRcodes{"files/QRcodes"};
    const fs::path finalFiles{"files/finalFiles"};
    const fs::path baseSVG{"files/baseSVG/baseSVG.svg"};

    uint64_t numCreatedFiles{0};

    for (auto &path : fs::directory_iterator(finalFiles))
    {
        fs::remove_all(path);
    }

    for (auto const &dirEntry : fs::directory_iterator{QRcodes})
    {
        auto currentFilePath = dirEntry.path();

        if (currentFilePath.extension() == ".svg")
        {

            auto currentFileName = currentFilePath.filename();

            std::ifstream inFile;
            std::ofstream outFile;

            inFile.open(baseSVG);
            outFile.open((finalFiles / currentFileName), std::ios::app);

            std::string inFileLine;
            while (std::getline(inFile, inFileLine))
            {
                inFileLine = std::regex_replace(inFileLine, std::regex("\\Name_Here"), currentFileName.replace_extension().string());
                outFile << inFileLine;
            }

            inFile.close();
            outFile.close();
            numCreatedFiles++;
        }
    }

    std::cout << "\033[1;32mDone\033[0m\n";
    std::cout << "Created " << numCreatedFiles << " files.\n";



    return 0;
}