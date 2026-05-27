#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INT_SIZE 1000
#define MAX_WORDS 50000
#define MAX_LENGTH 100
#define SHOW_DATA 10


//fungsi bantuan untuk swap data
void swapInt(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapString(char a[][MAX_LENGTH], int i, int j) {
    char temp[MAX_LENGTH];
    strcpy(temp, a[i]);
    strcpy(a[i], a[j]);
    strcpy(a[j], temp);
}

void generateRandomData(int arr[]) {
    for (int i = 0; i < INT_SIZE; i++) {
        arr[i] = rand() % 10000;
    }
}

void shuffleInt(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swapInt(&arr[i], &arr[j]);
    }
}

void shuffleString(char words[][MAX_LENGTH], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swapString(words, i, j);
    }
}

void printIntData(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printStringData(char words[][MAX_LENGTH], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", words[i]);
    }
}

//MENU SORTING DASAR

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swapInt(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        swapInt(&arr[minIndex], &arr[i]);
    }
}

//MENU ADVANCE SORTING 

void merge(char words[][MAX_LENGTH], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char L[n1][MAX_LENGTH];
    char R[n2][MAX_LENGTH];

    for (int i = 0; i < n1; i++) {
        strcpy(L[i], words[left + i]);
    }

    for (int j = 0; j < n2; j++) {
        strcpy(R[j], words[mid + 1 + j]);
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(words[k], L[i]);
            i++;
        } else {
            strcpy(words[k], R[j]);
            j++;
        }
        k++;
    }

    while (i < n1) {
        strcpy(words[k], L[i]);
        i++;
        k++;
    }

    while (j < n2) {
        strcpy(words[k], R[j]);
        j++;
        k++;
    }
}

void mergeSort(char words[][MAX_LENGTH], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(words, left, mid);
        mergeSort(words, mid + 1, right);
        merge(words, left, mid, right);
    }
}

int partition(char words[][MAX_LENGTH], int low, int high) {
    char pivot[MAX_LENGTH];
    strcpy(pivot, words[high]);

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(words[j], pivot) < 0) {
            i++;
            swapString(words, i, j);
        }
    }

    swapString(words, i + 1, high);
    return i + 1;
}

void quickSort(char words[][MAX_LENGTH], int low, int high) {
    if (low < high) {
        int pi = partition(words, low, high);

        quickSort(words, low, pi - 1);
        quickSort(words, pi + 1, high);
    }
}

void shellSort(char words[][MAX_LENGTH], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char temp[MAX_LENGTH];
            strcpy(temp, words[i]);

            int j;
            for (j = i; j >= gap && strcmp(words[j - gap], temp) > 0; j -= gap) {
                strcpy(words[j], words[j - gap]);
            }

            strcpy(words[j], temp);
        }
    }
}

//MENU FILE DATASET

int loadWords(char words[][MAX_LENGTH], const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("File tidak ditemukan!\n");
        return 0;
    }

    int count = 0;

    while (fscanf(file, "%99s", words[count]) != EOF && count < MAX_WORDS) {
        count++;
    }

    fclose(file);
    return count;
}

//MENU SORTING DASAR

void sortingDasar() {
    int pilihan;
    int data[INT_SIZE];

    do {
        printf("\n===== SORTING DASAR =====\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Kembali\n");
        printf("Pilih metode : ");
        scanf("%d", &pilihan);

        if (pilihan >= 1 && pilihan <= 3) {
            generateRandomData(data);
            shuffleInt(data, INT_SIZE);

            printf("\nData Sebelum Sorting:\n");
            printIntData(data, SHOW_DATA);

            clock_t start = clock();

            switch (pilihan) {
                case 1:
                    bubbleSort(data, INT_SIZE);
                    printf("\nMenggunakan Bubble Sort\n");
                    break;
                case 2:
                    insertionSort(data, INT_SIZE);
                    printf("\nMenggunakan Insertion Sort\n");
                    break;
                case 3:
                    selectionSort(data, INT_SIZE);
                    printf("\nMenggunakan Selection Sort\n");
                    break;
            }

            clock_t end = clock();
            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

            printf("\nData Setelah Sorting:\n");
            printIntData(data, SHOW_DATA);

            printf("\nWaktu Eksekusi : %.6f detik\n", time_taken);
        }

    } while (pilihan != 4);
}

//MENU ADVANCE SORTING 

void advanceSorting() {
    int pilihan;
    static char words[MAX_WORDS][MAX_LENGTH];

    int totalWords = loadWords(words, "sorting_string.txt");

    if (totalWords == 0) {
        return;
    }

    do {
        printf("\n===== ADVANCE SORTING =====\n");
        printf("1. Merge Sort\n");
        printf("2. Quick Sort\n");
        printf("3. Shell Sort\n");
        printf("4. Kembali\n");
        printf("Pilih metode : ");
        scanf("%d", &pilihan);

        if (pilihan >= 1 && pilihan <= 3) {
            shuffleString(words, totalWords);

            printf("\nData Sebelum Sorting:\n");
            printStringData(words, SHOW_DATA);

            clock_t start = clock();

            switch (pilihan) {
                case 1:
                    mergeSort(words, 0, totalWords - 1);
                    printf("\nMenggunakan Merge Sort\n");
                    break;
                case 2:
                    quickSort(words, 0, totalWords - 1);
                    printf("\nMenggunakan Quick Sort\n");
                    break;
                case 3:
                    shellSort(words, totalWords);
                    printf("\nMenggunakan Shell Sort\n");
                    break;
            }

            clock_t end = clock();
            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

            printf("\nData Setelah Sorting:\n");
            printStringData(words, SHOW_DATA);

            printf("\nWaktu Eksekusi : %.6f detik\n", time_taken);
        }

    } while (pilihan != 4);
}

//MAIN
int main() {
    srand(time(NULL));

    int pilihan;

    do {
        printf("\n===== MENU UTAMA =====\n");
        printf("1. Sorting Dasar\n");
        printf("2. Advance Sorting\n");
        printf("3. Keluar\n");
        printf("Pilih menu : ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                sortingDasar();
                break;
            case 2:
                advanceSorting();
                break;
            case 3:
                printf("\nProgram selesai.\n");
                break;
            default:
                printf("\nPilihan tidak valid!\n");
        }

    } while (pilihan != 3);

    return 0;
}
