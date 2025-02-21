/*

C dilinde diziler sabit boyutludur. Ancak, bellek üzerinde dinamik olarak
boyutlandırılabilen diziler oluşturmak için malloc ve realloc fonksiyonları kullanılır.
Dinamik diziler, eleman ekledikçe yeniden boyutlandırılarak bellekteki yerlerini günceller.
Bu yaklaşım, dizinin eleman sayısının çalışma zamanında değişmesine olanak tanır. 
Bellek, heap (yığın) bölgesinde ayrılır ve işlemci dizinin elemanlarına indis numarası ile (random access) hızlıca erişir.

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;      // Elemanların tutulduğu bellek bloğu
    size_t used;     // Kullanılan eleman sayısı
    size_t size;     // Ayrılan toplam kapasite
} DynamicArray;

// Dinamik diziyi başlat
void initArray(DynamicArray *a, size_t initialSize) {
    a->array = (int *)malloc(initialSize * sizeof(int));
    if(a->array == NULL) {
        fprintf(stderr, "Bellek ayirma hatası!\n");
        exit(1);
    }
    a->used = 0;
    a->size = initialSize;
}

// Dizinin sonuna eleman ekle; kapasite dolduğunda iki katına çıkar.
void insertArray(DynamicArray *a, int element) {
    if (a->used == a->size) {
        a->size *= 2;
        a->array = (int *)realloc(a->array, a->size * sizeof(int));
        if(a->array == NULL) {
            fprintf(stderr, "Bellek yeniden tahsis hatası!\n");
            exit(1);
        }
    }
    a->array[a->used++] = element;
}

// Dinamik diziyi serbest bırakır
void freeArray(DynamicArray *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

int main() {
    DynamicArray a;
    initArray(&a, 5);  // Başlangıç kapasitesi 5

    
    for (int i = 0; i < 10; i++) {
        insertArray(&a, i);
    }


    printf("Dinamik Dizi Elemanları: ");
    for (int i = 0; i < a.used; i++) {
        printf("%d ", a.array[i]);
    }
    printf("\n");

    freeArray(&a);
    return 0;
}

/*
Bellek ve İşlemci Yönetimi:

Bellek: malloc ile başlangıçta belirli bir blok (örneğin 5 elemanlık) heap’te ayrılır. 
Eleman ekleme sırasında kapasite dolduğunda, realloc kullanılarak dizinin kapasitesi iki katına çıkarılır. 
Böylece bellek yeniden düzenlenir.
İşlemci: İşlemci, dizi elemanlarına indisler üzerinden doğrudan erişir. 
Yeni eleman eklerken, mevcut elemanların sayısını (indx) günceller; ayrıca realloc sırasında veriler yeni bellek bölgesine kopyalanır.

*/