#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    const fs::path QRcodes{"files/QRcodes"};
    const fs::path finalFiles{"files/finalFiles"};
    const fs::path baseSVG{"files/baseSVG/baseSVG.svg"};
    std::ifstream inFile;

    for (auto& path: fs::directory_iterator(finalFiles))
    {
        fs::remove_all(path);
    }

    for (auto const &dir_entry : fs::directory_iterator{QRcodes})
    {
        auto currentFilePath = dir_entry.path();

        if (currentFilePath.extension() == ".svg")
        {
            inFile.open(baseSVG);
            auto currentFileName = currentFilePath.filename();
            //auto currentFileNameString = currentFileName.string();

            std::ofstream outFile;
            outFile.open((finalFiles/currentFileName), std::ios::app);

            std::string inFileLine;
            while (std::getline(inFile, inFileLine))
            {
                inFileLine = std::regex_replace(inFileLine, std::regex("\\Name_Here"), currentFileName.replace_extension().string());
                //std::cout<<inFileLine<< "\n";
                outFile << inFileLine;
            }
            outFile.close();
            inFile.close();
        }
    }

    return 0;
}