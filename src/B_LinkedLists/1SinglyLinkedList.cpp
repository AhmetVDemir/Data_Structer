/*

1. Tek Yönlü Bağlı Liste (Singly Linked List)
Tanım:
Tek yönlü bağlı listeler, her düğümün yalnızca bir sonraki düğüme işaret ettiği lineer bir veri yapısıdır. Son düğümün next pointer’ı nullptr olur.

Avantajlar:

Dinamik Bellek Kullanımı: Elemanlar önceden belirlenmiş bir boyutta depolanmaz, ihtiyaca göre eklenir ve silinir.
Ekleme/Silme Kolaylığı: Dizilerde ekleme/silme işleminde kaydırma gerekirken, bağlı listelerde yalnızca pointer güncellenir.
Dezavantajlar:

Daha Fazla Bellek Kullanımı: Her düğüm ek bir pointer alanı içerir.
Diziye Göre Yavaş Erişim: Rastgele erişim yoktur, baştan itibaren taranarak bulunur.


Bellek Yönetimi ve Performans:
Bellek Kullanımı: Her düğüm için sizeof(Node) = int + pointer kadar bellek harcanır.
Zaman Kompleksitesi:
Ekleme (Başa): O(1)
Silme (Orta/Baş): O(n)
Erişim: O(n)


*/


#include <iostream>

struct Node {
    int data;
    Node* next;
};

// Başa düğüm ekleme
void insertAtHead(Node*& head, int value) {
    Node* newNode = new Node{value, head};
    head = newNode;
}

// Bağlı listeyi yazdırma
void printList(Node* head) {
    while (head) {
        std::cout << head->data << " -> ";
        head = head->next;
    }
    std::cout << "NULL\n";
}

// Düğüm silme
void deleteNode(Node*& head, int key) {
    Node* temp = head;
    Node* prev = nullptr;

    if (temp && temp->data == key) {
        head = temp->next;
        delete temp;
        return;
    }

    while (temp && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) return;
    prev->next = temp->next;
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
