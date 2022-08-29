#include <iostream>
#include <filesystem>
#include <vector>
#include <iterator>
#include <algorithm>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) 
{
    const fs::path startPath{ fs::path("files/QRcodes/") };
    std::vector<fs::path> files{};
    std::copy_if(fs::directory_iterator(startPath), {}, std::back_inserter(files), [](const fs::directory_entry& de) { return de.path().extension() == ".svg"; });
    for (const fs::path& p : files) std::cout << p.string() << '\n';
    std::cout << files.size()<< "\n";

    

    return 0;
}