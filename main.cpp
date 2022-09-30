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
    bool in_tag = false, closing = false;
    int errors = 0, line = 1;

    std::string tag_name;
    eda::Stack stack;
    std::string last_tag;

    while (file.good())
    {
        file.get(ch);
        switch (ch)
        {
        case '<':
            in_tag = true;
            tag_name = "";
            break;

        case '>':
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
            in_tag = false;
            closing = false;
            break;

        case '/':
            closing = true;
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

    while (!stack.isEmpty()) {
        tag_name = stack.top()->getData();
        log << "Error: tag <" << tag_name << "> never closed" << std::endl;
        stack.pop();
        errors ++;
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