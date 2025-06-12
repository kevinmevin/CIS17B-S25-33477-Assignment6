#include "StorageManager.h"

void StorageManager::addItem(int id, const std::string& description, const std::string& location) {
    if (itemsById.count(id)) {
        throw DuplicateItemException();
    }
    itemsById[id] = std::make_shared<StoredItem>(id, description, location);
}

std::shared_ptr<StoredItem> StorageManager::findById(int id) {
    if (itemsById.find(id) == itemsById.end()) {
        throw ItemNotFoundException();
    }
    return itemsById.at(id);
}

void StorageManager::removeItem(int id) {
    if (itemsById.find(id) == itemsById.end()) {
        throw ItemNotFoundException();
    }
    itemsById.erase(id);
}

std::map<std::string, std::shared_ptr<StoredItem>> StorageManager::listItemsByDescription() {
    std::map<std::string, std::shared_ptr<StoredItem>> sortedItems;
    for (const auto& pair : itemsById) {
        sortedItems[pair.second->description] = pair.second;
    }
    return sortedItems;
}
