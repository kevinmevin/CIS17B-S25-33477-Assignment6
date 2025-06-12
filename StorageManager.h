#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include "StoredItem.h"
#include "Exceptions.h"
#include <unordered_map>
#include <map>
#include <memory>
#include <vector>

class StorageManager {
public:
    void addItem(int id, const std::string& description, const std::string& location);
    std::shared_ptr<StoredItem> findById(int id);
    void removeItem(int id);
    std::map<std::string, std::shared_ptr<StoredItem>> listItemsByDescription();

private:
    std::unordered_map<int, std::shared_ptr<StoredItem>> itemsById;
};

#endif // STORAGEMANAGER_H
