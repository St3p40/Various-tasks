#include <iostream>
#include <vector>

struct PC {
    int model;
    int speed;

    PC(int m, int s) : model(m), speed(s) {}
};

class HashTable {
public:
    HashTable(size_t size) : table(size) {}

    void insert(int model, int speed) {
        size_t index = combineHashes(model, speed);
        for (auto& pc : table[index]) {
            if (pc.model == model) {
                return;
            }
        }
        table[index].emplace_back(model, speed);
    }

    PC* search(int model, int speed) {
        size_t index = combineHashes(model, speed);
        for (auto& pc : table[index]) {
            if (pc.model == model && pc.speed == speed) {
                return &pc;
            }
        }
        return nullptr;
    }

    bool remove(int model, int speed) {
        size_t index = combineHashes(model, speed);
        auto& segment = table[index];
        for (auto it = segment.begin(); it != segment.end(); ++it) {
            if (it->model == model && it->speed == speed) {
                segment.erase(it);
                return true;
            }
        }
        return false;
    }

    void printAll() const {
        for (size_t i = 0; i < table.size(); ++i) {
            std::cout << "Segment " << i << ":\n";
            for (const auto& pc : table[i]) {
                std::cout << "Model: " << pc.model << ", Speed: " << pc.speed << std::endl;
            }
        }
    }

private:
    std::vector<std::vector<PC>> table;

    size_t hashModel(int model) {
        return (model % 100) % 4;
    }

    size_t hashSpeed(int speed) {
        return ((speed / 100) - 7) % 4;
    }

    size_t combineHashes(int model, int speed) {
        size_t hash1 = hashModel(model);
        size_t hash2 = hashSpeed(speed) << 2;

        return (hash1 ^ hash2);
    }
};

int main() {
    HashTable hashTable(16);

    hashTable.insert(1001, 700);
    hashTable.insert(1002, 1500);
    hashTable.insert(1003, 866);
    hashTable.insert(1004, 866);
    hashTable.insert(1005, 1000);
    hashTable.insert(1006, 1300);
    hashTable.insert(1007, 1400);
    hashTable.insert(1008, 700);
    hashTable.insert(1009, 1200);
    hashTable.insert(1010, 750);
    hashTable.insert(1011, 1100);
    hashTable.insert(10013, 733);

    std::cout << "Initial HashTable:\n";
    hashTable.printAll();

    int searchModel = 1006;
    int searchSpeed = 1300;
    PC* found = hashTable.search(searchModel, searchSpeed);
    if (found) {
        std::cout << "\nFound: Model " << found->model << ", Speed " << found->speed << std::endl;
    } else {
        std::cout << "\nNot found: Model " << searchModel << ", Speed " << searchSpeed << std::endl;
    }

    int removeModel = 1007;
    int removeSpeed = 1400;
    if (hashTable.remove(removeModel, removeSpeed)) {
        std::cout << "\nRemoved: Model " << removeModel << ", Speed " << removeSpeed << std::endl;
    } else {
        std::cout << "\nNot found for removal: Model " << removeModel << ", Speed " << removeSpeed << std::endl;
    }

    std::cout << "\nUpdated HashTable:\n";
    hashTable.printAll();

    return 0;
}
