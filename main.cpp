#include <iostream>
#include <string>
#include <fstream>
#include "include/stack.hpp"
#include "include/node.hpp"

void checkFile(std::string *filename, std::string* logfile)
{
    std::ifstream file;
    file.open(*filename);
    
    std::ofstream log;
    log.open(*logfile);

    char ch;
    int in_tag, closing = 0, errors = 0, line = 1;

    std::string tag_name;
    eda::Stack stack;
    std::string last_tag;

    while (file.good())
    {
        file.get(ch);

        switch (ch)
        {
        case '<':
            in_tag = 1;
            tag_name = "";
            break;

        case '>':
            // std::cout << "tag name: " << tag_name << std::endl;
            if (closing) {
                last_tag = stack.top()->getData();
                if (last_tag != tag_name) {
                    log << "Error in line " << line << ": expecting </" << last_tag << ">, got </" << tag_name << ">\n";
                    errors ++;
                } else {
                    log << "tag <" << tag_name << "> ok" << std::endl;
                    stack.pop();
                }
            } else {
                stack.push(tag_name);
            }
            in_tag = 0;
            closing = 0;
            break;

        case '/':
            closing = 1;
            break;

        case '\n':
            line ++;
            break;

        default:
            if (in_tag)
            tag_name += ch;
            break;
        }
    }
    if (!errors) {
        log << "0 errors" << std::endl;
    }
}

std::string getName(char* filename) {
    std::string name = "";
    for (int i = 0; filename[i] != '.'; i++)
        name += filename[i];
    return name;
}

int main(int argc, char **argv)
{
    std::string filename = argv[argc - 1];
    std::string name = getName(argv[argc - 1]) + ".log";
    checkFile(&filename, &name);
    std::cout << "output -> " << name << std::endl;
    return 0;
}