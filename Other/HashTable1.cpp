#include <iostream>
#include <string>
#include <list>

using namespace std;

class City {
public:
    string name;
    string region;
    int population;

    City(const string &n, const string &r, int p)
        : name(n), region(r), population(p) {}

    void display() const {
        cout << "Name: " << name << ", Region: " << region << ", Population: " << population;
    }
};

struct Node {
    City city;
    Node* next;
    
    Node(const City& c) : city(c), next(nullptr) {}
};

class HashTable {
private:
    static const int INITIAL_TABLE_SIZE = 4;
    Node** table;
    int table_size;
    int current_size;

    int hashFunction(const string &key) const {
        int hash = 0;
        for (char c : key) {
            hash += c;
        }
        return hash % table_size;
    }

    void rehash() {
        int old_table_size = table_size;
        table_size *= 2;
        Node** old_table = table;
        table = new Node*[table_size]();

        for (int i = 0; i < old_table_size; ++i) {
            Node* temp = old_table[i];
            while (temp) {
                Node* next = temp->next;
                int index = hashFunction(temp->city.name);
                temp->next = table[index];
                table[index] = temp;
                temp = next;
            }
        }
        delete[] old_table;
    }

    void shrink() {
        if (current_size <= table_size / 4 && table_size > INITIAL_TABLE_SIZE) {
            int old_table_size = table_size;
            table_size /= 2;
            Node** old_table = table;
            table = new Node*[table_size]();

            for (int i = 0; i < old_table_size; ++i) {
                Node* temp = old_table[i];
                while (temp) {
                    Node* next = temp->next;
                    int index = hashFunction(temp->city.name);
                    temp->next = table[index];
                    table[index] = temp;
                    temp = next;
                }
            }
            delete[] old_table;
        }
    }

public:
    HashTable() {
        table_size = INITIAL_TABLE_SIZE;
        table = new Node*[table_size]();
        current_size = 0;
    }

    ~HashTable() {
        for (int i = 0; i < table_size; ++i) {
            Node* temp = table[i];
            while (temp) {
                Node* next = temp->next;
                delete temp;
                temp = next;
            }
        }
        delete[] table;
    }

    void insert(const City &city) {
        if (current_size >= table_size / 2) {
            rehash();
        }

        int index = hashFunction(city.name);
        Node* newNode = new Node(city);
        newNode->next = table[index];
        table[index] = newNode;
        current_size++;
    }

    City* search(const string &name) {
        int index = hashFunction(name);
        Node* temp = table[index];
        while (temp) {
            if (temp->city.name == name) {
                return &temp->city;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    bool remove(const string &name) {
        int index = hashFunction(name);
        Node* temp = table[index];
        Node* prev = nullptr;
        while (temp) {
            if (temp->city.name == name) {
                if (prev) {
                    prev->next = temp->next;
                } else {
                    table[index] = temp->next;
                }
                delete temp;
                current_size--;
                shrink();
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    void display() const {
        for (int i = 0; i < table_size; ++i) {
            cout << "Bucket " << i << ": ";
            Node* temp = table[i];
            if (!temp) {
                cout << "Empty";
            } else {
                while (temp) {
                    temp->city.display();
                    if (temp->next) cout << " | ";
                    temp = temp->next;
                }
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable ht;

    ht.insert(City("Kyiv", "Kyivska", 2804000));
    ht.insert(City("Lviv", "Lvivska", 721301));
    ht.insert(City("Odesa", "Odeska", 1010000));
    ht.insert(City("Kharkiv", "Kharkivska", 1430000));
    ht.insert(City("Kharkiv", "Kharkivska", 141000));

    cout << "\nHashTable contents:" << endl;
    ht.display();

    cout << "\nRemoving city 'Odesa'..." << endl;
    ht.remove("Odesa");

    cout << "\nUpdated HashTable contents:" << endl;
    ht.display();

    cout << "\nRemoving city 'Lviv'..." << endl;
    ht.remove("Lviv");

    cout << "\nUpdated HashTable contents after removing 'Lviv':" << endl;
    ht.display();

    return 0;
}
