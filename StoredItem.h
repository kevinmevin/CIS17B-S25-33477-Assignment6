#ifndef STOREDITEM_H
#define STOREDITEM_H

#include <string>

class StoredItem {
public:
    int id;
    std::string description;
    std::string location;

    StoredItem(int id, const std::string& description, const std::string& location)
        : id(id), description(description), location(location) {}
};

#endif // STOREDITEM_H
