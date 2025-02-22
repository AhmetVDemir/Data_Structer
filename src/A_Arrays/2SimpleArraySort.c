/*
a) Kabarcık Sıralama (Bubble Sort)
Açıklama:
Kabarcık sıralama, bitişik elemanları karşılaştırarak yer değiştiren basit bir sıralama algoritmasıdır. 
Her geçişte en büyük (veya en küçük) eleman sona doğru "yüzerek" yer alır.
*/
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Her geçişte son i eleman zaten sıralanmış
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Elemanları yer değiştir
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


//------------------------------------

/*
    b) Hızlı Sıralama (Quick Sort)
Açıklama:
Hızlı sıralama, böl ve yönet (divide and conquer) yaklaşımını kullanır. 
Bir pivot eleman seçilir, diziyi pivot etrafında iki alt diziye böler, sonra alt dizileri özyinelemeli olarak sıralar. 
Ortalama durum karmaşıklığı 
𝑂(𝑛log𝑛)
O(nlogn) olarak kabul edilir.

İşlemci ve Bellek Üzerindeki Etkiler:

İşlemci: Döngüler ve özyinelemeli çağrılar işlemci tarafından tekrarlı olarak gerçekleştirilir. Karşılaştırmalar ve takas işlemleri, CPU’nun ALU’sunda (Arithmetic Logic Unit) gerçekleştirilir.
Bellek: Sıralama algoritmaları, dizi elemanlarına doğrudan erişerek (random access) çalışır. Quick Sort’ta özyineleme sırasında ek yığın (stack) alanı kullanılır.
*/
// İki elemanı yer değiştirme fonksiyonu
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Pivot etrafında diziyi bölme
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Pivot olarak son elemanı seçiyoruz
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// QuickSort Fonksiyonu
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Bölme noktası
        quickSort(arr, low, pi - 1);  // Sol alt diziyi sırala
        quickSort(arr, pi + 1, high); // Sağ alt diziyi sırala
    }
}
