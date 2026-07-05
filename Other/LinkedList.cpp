#include <iostream>

struct Node {
    int data;
    Node* next;
};

class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}
    
    ~SinglyLinkedList() {
        while (!isEmpty()) {
            deleteFirst();
        }
    }

    void addToFront(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    void addToEnd(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void deleteFirst() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void displayPositiveInReverse() {
        displayPositiveInReverseHelper(head);
    }

private:
    void displayPositiveInReverseHelper(Node* node) {
        if (node == nullptr) return;
        displayPositiveInReverseHelper(node->next);
        if (node->data > 0) {
            std::cout << node->data << " ";
        }
    }
};

int main() {
    SinglyLinkedList list;

    list.addToEnd(3);
    list.addToEnd(-1);
    list.addToFront(5);
    list.addToEnd(10);
    list.addToFront(-2);

    std::cout << "List: ";
    list.display();

    std::cout << "Reversed list of positive elements: ";
    list.displayPositiveInReverse();
    std::cout << std::endl;

    std::cout << "Delete first element." << std::endl;
    list.deleteFirst();

    std::cout << "List after deleteing first element: ";
    list.display();

    return 0;
}