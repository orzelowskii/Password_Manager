#include "Category.h"

void Category::addCategory(std::string const& category) {
    categories.push_back(category);
}

void Category::removeCategory(std::string const& category) {
    for (auto it = categories.begin(); it != categories.end(); ++it) {
        if (*it == category) {
            categories.erase(it);
            break;
        }
    }
}