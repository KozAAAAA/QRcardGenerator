
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>

#include <lunasvg.h>
//#include <sstream>


using namespace lunasvg;


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



    std::string filename = "files/baseSVG/moon.svg";
    std::uint32_t width = 512, height = 512;
    std::uint32_t bgColor = 0xff00ffff;

    auto document = Document::loadFromFile(filename);

    auto bitmap = document->renderToBitmap(width, height, bgColor);

    auto basename = filename.substr(filename.find_last_of("/\\") + 1);
    basename.append(".png");

    bitmap.convertToRGBA();
    stbi_write_png(basename.c_str(), int(bitmap.width()), int(bitmap.height()), 4, bitmap.data(), 0);



    return 0;
}