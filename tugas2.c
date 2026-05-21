#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 10000
#define MAX_LEN 50

void generateRandomData(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; 
    }
}

void shuffleInteger(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
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
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void removeNewline(char str[]) {
    str[strcspn(str, "\n")] = '\0';
}

int readStringFile(char filename[], char data[][MAX_LEN]) {
    FILE *file = fopen(filename, "r");
    int count = 0;

    if (file == NULL) {
        printf("Gagal membuka file: %s\n", filename);
        return 0;
    }

    while (count < MAX_WORDS && fgets(data[count], MAX_LEN, file) != NULL) {
        removeNewline(data[count]);

        if (strlen(data[count]) > 0) {
            count++;
        }
    }

    fclose(file);
    return count;
}

void swapString(char a[], char b[]) {
    char temp[MAX_LEN];
    
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

void shuffleString(char data[][MAX_LEN], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swapString(data[i], data[j]);
    }
}

void mergeString(char data[][MAX_LEN], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char L[n1][MAX_LEN];
    char R[n2][MAX_LEN];

    for (int i = 0; i < n1; i++)
        strcpy(L[i], data[left + i]);

    for (int j = 0; j < n2; j++)
        strcpy(R[j], data[mid + 1 + j]);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(data[k], L[i]);
            i++;
        } else {
            strcpy(data[k], R[j]);
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        strcpy(data[k], L[i]);
        i++;
        k++;
    }

    while (j < n2) {
        strcpy(data[k], R[j]);
        j++;
        k++;
    }
}

void mergeSortString(char data[][MAX_LEN], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortString(data, left, mid);
        mergeSortString(data, mid + 1, right);

        mergeString(data, left, mid, right);
    }
}

int partitionString(char data[][MAX_LEN], int low, int high) {
    char pivot[MAX_LEN];
    strcpy(pivot, data[high]);

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(data[j], pivot) <= 0) {
            i++;
            swapString(data[i], data[j]);
        }
    }

    swapString(data[i + 1], data[high]);
    return i + 1;
}

void quickSortString(char data[][MAX_LEN], int low, int high) {
    if (low < high) {
        int pi = partitionString(data, low, high);

        quickSortString(data, low, pi - 1);
        quickSortString(data, pi + 1, high);
    }
}

void shellSortString(char data[][MAX_LEN], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char temp[MAX_LEN];
            strcpy(temp, data[i]);

            int j;
            for (j = i; j >= gap && strcmp(data[j - gap], temp) > 0; j -= gap) {
                strcpy(data[j], data[j - gap]);
            }

            strcpy(data[j], temp);
        }
    }
}
