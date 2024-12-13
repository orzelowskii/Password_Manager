#ifndef PROJEKT_CATEGORY_H
#define PROJEKT_CATEGORY_H

#include <vector>
#include <string>

struct Category{

public:
    std::vector<std::string> categories;
    void addCategory(std::string const& category);
    void removeCategory(std::string const& category);

};

#endif //PROJEKT_CATEGORY_H
