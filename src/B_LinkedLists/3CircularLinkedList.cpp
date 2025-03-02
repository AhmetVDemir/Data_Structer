/*
3. Dairesel Bağlı Liste (Circular Linked List)
Tanım:
Son düğümün next pointer'ı başa işaret eder.

Avantajlar:

Sürekli Dolaşım: Döngü yapıları için uygundur.
Sonsuz Liste İmkanı: Son öğeden başa dönülebilir.



Bellek Yönetimi ve Performans:
Bellek Kullanımı: sizeof(Node) = int + pointer
Zaman Kompleksitesi:
Ekleme: O(1)
Erişim: O(n)

*/

#include <iostream>

struct Node {
    int data;
    Node* next;
};

void insertAtHead(Node*& head, int value) {
    Node* newNode = new Node{value, head};
    if (!head) {
        newNode->next = newNode;
    } else {
        Node* temp = head;
        while (temp->next != head)
            temp = temp->next;
        temp->next = newNode;
        newNode->next = head;
    }
    head = newNode;
}

void printList(Node* head) {
    if (!head) return;
    Node* temp = head;
    do {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    } while (temp != head);
    std::cout << "(Head)\n";
}

int main() {
    Node* head = nullptr;
    
    insertAtHead(head, 10);
    insertAtHead(head, 20);
    insertAtHead(head, 30);

    printList(head);

    return 0;
}
