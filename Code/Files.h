#ifndef PROJEKT_FILES_H
#define PROJEKT_FILES_H

#include <vector>
#include <string>

struct Files{

public:
    std::vector<std::string> files;
    void addFile(std::string const& c);
    void removeFile(std::string const& category);
    int size();
    std::string at(int i);

};


#endif //PROJEKT_FILES_H
