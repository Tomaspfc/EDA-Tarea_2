#include <iostream>
#include <string>
#include <fstream>

int checkFile(std::string *filename) {
    std::ifstream file;
    file.open(*filename);
    char ch;
    while (file.good()) {
        file.get(ch);
        std::cout << ch << "-";
    }
     

    return 0;
}

int main(int argc, char** argv) {
    std::string filename = argv[argc - 1];
    checkFile(&filename);
    return 0;
}