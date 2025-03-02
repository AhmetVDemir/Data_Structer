/*
2. Çift Yönlü Bağlı Liste (Doubly Linked List)
Tanım:
Çift yönlü bağlı listelerde her düğüm hem bir önceki hem de bir sonraki düğüme işaret eder.

Avantajlar:

Geriye Doğru Erişim: prev pointer ile geriye doğru gezinebiliriz.
Daha Hızlı Silme: Önceki düğüme erişim olduğu için O(1) sürede düğüm silebiliriz.
Dezavantajlar:

Daha Fazla Bellek Tüketimi: Ekstra prev pointer belleği harcanır.


Bellek Yönetimi ve Performans:
Bellek Kullanımı: sizeof(Node) = int + 2 * pointer
Zaman Kompleksitesi:
Ekleme/Silme: O(1)
Erişim: O(n)

*/
#include <iostream>

struct Node {
    int data;
    Node* prev;
    Node* next;
};

void insertAtHead(Node*& head, int value) {
    Node* newNode = new Node{value, nullptr, head};
    if (head) head->prev = newNode;
    head = newNode;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        std::cout << temp->data << " <-> ";
        temp = temp->next;
    }
    std::cout << "NULL\n";
}

void deleteNode(Node*& head, int key) {
    Node* temp = head;
    while (temp && temp->data != key)
        temp = temp->next;

    if (!temp) return;

    if (temp->prev) temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    
    if (temp == head) head = temp->next;

    delete temp;
}

int main() {
    Node* head = nullptr;
    
    insertAtHead(head, 10);
    insertAtHead(head, 20);
    insertAtHead(head, 30);

    printList(head);

    deleteNode(head, 20);
    printList(head);

    return 0;
}
