#include "Files.h"

void Files::addFile(std::string const& file) {
    files.push_back(file);
}

void Files::removeFile(std::string const& file) {
    for (auto it = files.begin(); it != files.end(); ++it) {
        if (*it == file) {
            files.erase(it);
            break;
        }
    }
}
int Files::size() {
    return files.size();
}

std::string Files::at(int i) {
    return files.at(i);
}
