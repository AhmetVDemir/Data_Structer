/*
    Diziye eleman eklemek veya diziden eleman çıkarmak, elemanların yerlerini değiştirmek (kaydırmak) gerektirir. 
    Statik dizilerde bu işlem, belirli bir indisteki elemanı eklemek için o indeksten sonraki tüm elemanların 
    sağa kaydırılması veya silme durumunda sola kaydırılması şeklinde yapılır. Dinamik dizilerde ise yukarıdaki gibi
    insertArray gibi fonksiyonlarla eleman eklenebilir; fakat burada örnek olarak sabit boyutlu bir dizi üzerinde ekleme ve
     silme işlemlerini göstereceğiz.

     Bellek ve İşlemci Yönetimi:

    Bellek: Sabit boyutlu dizilerde, tüm elemanlar ardışık bellek adreslerinde saklanır. Ekleme ve silme işlemleri sırasında, belirli bir konumdan itibaren veriler kaydırılır. Dinamik dizilerde (önceki bölümdeki gibi) ekleme yapıldığında, ek kapasite kontrolü ve gerekirse yeniden tahsis işlemi yapılır.
    İşlemci: İşlemci, döngüler kullanarak elemanların taşınması işlemini gerçekleştirir. Her kaydırma, bir bellek okuma ve yazma işlemi gerektirir. Bu işlemler, CPU’nun bellek erişim hızına bağlı olarak gerçekleşir.

*/


#include <stdio.h>

// Dizide eleman ekleme: Belirli bir index'e ekleme işlemi
// n: dizinin mevcut eleman sayısı (dizinin boyutunu değiştiren referans)
void insertAt(int arr[], int *n, int index, int value) {
    // index ve sonrasındaki elemanları sağa kaydır
    for (int i = *n; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    (*n)++;  // Eleman sayısını güncelle
}

// Diziden eleman çıkarma: Belirli bir index'teki elemanı silme
void deleteAt(int arr[], int *n, int index) {
    // index'ten itibaren elemanları sola kaydır
    for (int i = index; i < (*n) - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*n)--;  // Eleman sayısını güncelle
}

int main() {
    int arr[20] = {1, 2, 3, 4, 5}; // Sabit boyutlu dizi örneği
    int n = 5;  // Şu anki eleman sayısı

    // Örnek: 2. index'e (0 bazlı) 99 ekleyelim
    insertAt(arr, &n, 2, 99);
    printf("Eleman ekleme sonrası: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Örnek: 4. index'teki elemanı silelim
    deleteAt(arr, &n, 4);
    printf("Eleman silme sonrası: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
