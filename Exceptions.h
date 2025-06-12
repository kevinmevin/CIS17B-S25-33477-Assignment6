#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class DuplicateItemException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Duplicate item ID.";
    }
};

class ItemNotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Item not found.";
    }
};

#endif // EXCEPTIONS_H
