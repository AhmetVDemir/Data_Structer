/*
Aşağıdaki tek bir C++ dosyası örneğinde, üç farklı bağlı liste türü (tek yönlü, çift yönlü ve dairesel) tanımlanmış; ayrıca tek yönlü bağlı liste üzerinde iki farklı sıralama algoritması (Merge Sort ve Insertion Sort) detaylı yorumlarla açıklanmıştır. Her bir kısımda bellek yönetimi, işlemci performansı ve algoritmanın çalışma mantığı ile ilgili açıklamalar da bulunmaktadır.

Açıklamalar:
Tek Yönlü Liste:
Merge Sort: Listeyi ortadan bölüp iki alt listeye ayırır, özyineleme ile sıralar ve sıralı alt listeleri birleştirir. Bellek yönetimi açısından düğümlerin pointer'larının güncellenmesi söz konusudur.
Insertion Sort: Her düğümü sıralı alt listeye yerleştirerek doğru konumda ekler; neredeyse sıralı listelerde hızlı çalışır.
Çift Yönlü Liste:
Her düğümde prev ve next pointer'ı bulunur. Bu sayede liste üzerinde ileri ve geri hareket edilebilir, fakat ek bellek kullanımı gerektirir.
Dairesel Liste:
Son düğüm, ilk düğüme işaret eder. Bu yapı, sürekli döngüsel işlemler için kullanışlıdır.
Bu örnek program, konsol uygulaması şeklinde tek bir dosyada hem üç farklı bağlı liste yapısını hem de iki farklı sıralama algoritmasını kapsamlı yorumlarla göstermektedir.
*/

#include <iostream>
using namespace std;

/*
 * ====================
 * 1. Tek Yönlü Bağlı Liste (Singly Linked List)
 * ====================
 */

// Tek yönlü bağlı listede her düğüm yalnızca bir sonraki düğümü işaret eder.
// Bu yapı, dinamik bellek kullanımı ve ekleme/silme işlemlerinde hızlılık sağlar,
// ancak rastgele erişimde O(n) zaman alır.
struct SNode {
    int data;
    SNode* next;
};

// Listenin başına yeni bir düğüm ekleyen fonksiyon.
// Bellekte yeni düğüm için yer ayrılır ve pointer güncellenir (O(1) zaman).
void insertSNode(SNode*& head, int value) {
    SNode* newNode = new SNode{value, head};
    head = newNode;
}

// Tek yönlü bağlı listeyi yazdıran fonksiyon.
void printSList(SNode* head) {
    while (head) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

/*
 * --- Merge Sort (Birleştirme Sıralaması) ---
 *
 * Merge sort, bağlı listelerde O(n log n) performansa sahip kararlı bir sıralama yöntemidir.
 * Bellek yönetiminde ek alan kullanılabilir ancak düğümlerin pointer'ları güncellenerek
 * yeniden yapılandırıldığı için diziye göre avantajlıdır.
 */

// Listenin ortasını bulan yardımcı fonksiyon. (Slow-Fast pointer yöntemi)
void splitList(SNode* source, SNode*& front, SNode*& back) {
    SNode* slow = source;
    SNode* fast = source->next;
    // fast iki adım, slow bir adım ilerler. fast sona ulaştığında slow ortada olur.
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    front = source;
    back = slow->next;
    slow->next = nullptr; // İlk yarıyı sonlandırıyoruz.
}

// İki sıralı listeyi birleştiren fonksiyon.
SNode* sortedMerge(SNode* a, SNode* b) {
    if (!a) return b;
    if (!b) return a;
    SNode* result = nullptr;
    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

// Merge Sort algoritmasının kendisi.
SNode* mergeSort(SNode* head) {
    // 0 veya 1 düğüm varsa zaten sıralıdır.
    if (!head || !head->next) {
        return head;
    }
    SNode* a;
    SNode* b;
    // Listeyi ikiye bölüyoruz.
    splitList(head, a, b);
    // Alt listeleri özyinelemeli olarak sıralıyoruz.
    a = mergeSort(a);
    b = mergeSort(b);
    // İki sıralı listeyi birleştiriyoruz.
    return sortedMerge(a, b);
}

/*
 * --- Insertion Sort (Ekleme Sıralaması) ---
 *
 * Insertion sort, listeyi baştan sona tarayarak her elemanı doğru pozisyona yerleştirir.
 * Küçük veya neredeyse sıralı listeler için oldukça etkilidir ancak en kötü durumda O(n^2) çalışır.
 */
SNode* insertionSort(SNode* head) {
    SNode* sorted = nullptr;  // Sıralı liste
    SNode* current = head;
    while (current) {
        SNode* next = current->next; // Bir sonraki düğümü sakla
        // Sıralı listede current'in yerini bul
        if (!sorted || current->data < sorted->data) {
            current->next = sorted;
            sorted = current;
        } else {
            SNode* temp = sorted;
            while (temp->next && temp->next->data < current->data)
                temp = temp->next;
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    return sorted;
}

/*
 * ====================
 * 2. Çift Yönlü Bağlı Liste (Doubly Linked List)
 * ====================
 */

// Çift yönlü bağlı listede her düğüm, hem önceki hem sonraki düğümü işaret eder.
// Bu, liste üzerinde ileri-geri dolaşmayı kolaylaştırır ancak bellek maliyeti iki pointer içerir.
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
};

// Listenin başına ekleme işlemi.
void insertDNode(DNode*& head, int value) {
    DNode* newNode = new DNode{value, nullptr, head};
    if (head)
        head->prev = newNode;
    head = newNode;
}

// Çift yönlü bağlı listeyi yazdırma (ileri yön).
void printDList(DNode* head) {
    while (head) {
        cout << head->data << " <-> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

/*
 * ====================
 * 3. Dairesel Bağlı Liste (Circular Linked List)
 * ====================
 */

// Dairesel bağlı listede son düğüm, ilk düğüme işaret eder. Bu yapı, dairesel veri yapıları
// veya sürekli döngüsel işlemler için idealdir.
struct CNode {
    int data;
    CNode* next;
};

// Listenin başına ekleme işlemi. İlk düğüm oluşturulduğunda kendisine işaret eder.
void insertCNode(CNode*& head, int value) {
    CNode* newNode = new CNode{value, nullptr};
    if (!head) {
        newNode->next = newNode;
        head = newNode;
    } else {
        // Listenin sonuna gidip, yeni düğümü ekliyoruz
        CNode* temp = head;
        while (temp->next != head)
            temp = temp->next;
        temp->next = newNode;
        newNode->next = head;
        head = newNode;  // İsteğe bağlı: yeni düğümü başa alıyoruz.
    }
}

// Dairesel bağlı listeyi yazdıran fonksiyon.
void printCList(CNode* head) {
    if (!head) return;
    CNode* temp = head;
    do {
        cout << temp->data << " -> ";
        temp = temp->next;
    } while (temp != head);
    cout << "(Back to Head)" << endl;
}

/*
 * ====================
 * Main Fonksiyonu
 * ====================
 *
 * Bu fonksiyonda:
 * - Tek yönlü bağlı liste oluşturularak, rastgele eklenen değerler üzerinde önce merge sort
 *   sonra insertion sort algoritması uygulanıp sonuçlar konsola yazdırılır.
 * - Çift yönlü ve dairesel bağlı listeler de örnek veriyle oluşturulup yazdırılır.
 *
 * Bellek yönetimi: Her "new" ile ayrılan bellek, uygun silme işlemleri ile temizlenmelidir.
 * Bu örnekte, dinamik bellek serbest bırakma işlemleri basitlik açısından gösterilmemiştir.
 */
int main() {
    cout << "=== Tek Yönlü Bağlı Liste: Merge Sort & Insertion Sort ===" << endl;
    
    // Tek yönlü bağlı liste oluşturup, örnek veriler ekliyoruz.
    SNode* sList = nullptr;
    insertSNode(sList, 30);
    insertSNode(sList, 10);
    insertSNode(sList, 50);
    insertSNode(sList, 20);
    insertSNode(sList, 40);
    
    cout << "Orijinal Liste: ";
    printSList(sList);
    
    // Merge Sort Uygulaması:
    // Merge sort, bağlı liste üzerinde rekürsif bölme ve birleştirme işlemi yapar.
    SNode* mergeSortedList = mergeSort(sList);
    cout << "Merge Sort Sonucu: ";
    printSList(mergeSortedList);
    
    // Insertion sort için tekrar orijinal karışık listeyi oluşturuyoruz.
    sList = nullptr;
    insertSNode(sList, 30);
    insertSNode(sList, 10);
    insertSNode(sList, 50);
    insertSNode(sList, 20);
    insertSNode(sList, 40);
    
    // Insertion Sort Uygulaması:
    // Her eleman sıralı alt listeye eklenerek doğru pozisyona yerleştirilir.
    SNode* insertionSortedList = insertionSort(sList);
    cout << "Insertion Sort Sonucu: ";
    printSList(insertionSortedList);
    
    cout << "\n=== Çift Yönlü Bağlı Liste ===" << endl;
    DNode* dList = nullptr;
    insertDNode(dList, 30);
    insertDNode(dList, 10);
    insertDNode(dList, 50);
    insertDNode(dList, 20);
    insertDNode(dList, 40);
    cout << "Çift Yönlü Liste: ";
    printDList(dList);
    
    cout << "\n=== Dairesel Bağlı Liste ===" << endl;
    CNode* cList = nullptr;
    insertCNode(cList, 30);
    insertCNode(cList, 10);
    insertCNode(cList, 50);
    insertCNode(cList, 20);
    insertCNode(cList, 40);
    cout << "Dairesel Liste: ";
    printCList(cList);
    
    /*
     * NOT: Bellek ve işlemci yönetimi açısından;
     * - Tek yönlü liste her düğümde bir pointer kullanırken, çift yönlü liste iki pointer (prev, next)
     *   kullanır; bu nedenle çift yönlü liste, bellek tüketimi daha fazladır.
     * - Merge sort, O(n log n) zaman karmaşıklığı ile büyük veri setlerinde verimli bir sıralamadır,
     *   ancak özyinelemeye bağlı olarak ek bellek kullanımı olabilir.
     * - Insertion sort, neredeyse sıralı veri setlerinde etkili olup, en kötü durumda O(n^2) zaman alır.
     */
    
    return 0;
}
