#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10



void Generuj_tablice(int *array) {
    int RandValue = 0;
    time_t tt;
    srand(time(&tt));
    for (int i =0; i < SIZE; i++) {
    array[i] = rand() % 99 + 1;
    }
}

void Print_Array(int *array) {
    for (int i =0; i < SIZE; i++) {
        printf("Array[%d] = %d \n", i, array[i]);           //wyswietlanie wartości elementów tablicy
        //printf("*(%p) = %d \n\n", array + i, *(array + i));       //wyswietlanie adresów
    }
}

int Array_minimum(int *array) {
    int minimum = *array;
    for (int i = 1; i < SIZE;++i){
        if (*(array + i) < minimum){
            minimum = *(array + i);
        }
    }
    return minimum;
}

int Array_maximum(int *array) {
    int maximum = *array;
    for (int i = 1; i < SIZE; ++i) {
        if (*(array + i) > maximum) {
            maximum = *(array + i);
        }
    }
    return maximum;
}

float Avarage_array(int *array, int size){
    int sum = 0;
    for (int i = 0; i<SIZE; i++) {
        sum += *(array + i);   // obliczanie sumy
    }
    return (float) sum / size;

}

int Save_array(int array[]) {
    FILE *fptr;
    fptr = fopen("C:\\aisr\\data.txt", "w");

    if  (fptr == NULL){
        return 1;
    }
    for (int i = 0; i < SIZE; ++i) {
        fprintf(fptr,"%d\n", array[i]);
    }
    fclose(fptr);
    return 0;
}


int Read_array(int array[]) {
    char fileLine[100];
    FILE *fptr;
    fptr = fopen("C:\\aisr\\data.txt", "r");

    if  (fptr == NULL){
        return 1;
    }
    for (int i = 0; i < SIZE; ++i) {
        //while(!feof(fptr))
        //{
        //    fgets(fileLine, 100, fptr);

        //}
        fscanf(fptr, "%d", &array[i]);
    }
    fclose(fptr);
    return 0;

}

int main(void) {            //menu programu
    int menu_optiopn = 0;
    int errorCode = 0;
    int array[10]  = {1,2,5, -2, 19, 5, 21, -32,43,1};

     do {
            printf("1. Generuj losowe wartosci do tablicy. \n");
            printf("2. Wyswietl tablice. \n");
            printf("3. Znajdz wartosc najmniejsza. \n");
            printf("4. Znajdz wartosc najwieksza. \n");
            printf("5. Znajdz wartosc srednia \n");
            printf("6. Znajdz mediane \n");
            printf("7. Zapisz tablice do pliku \n");
            printf("8. Wczytaj tablice z pliku \n");
            printf("9. KONIEC \n");

            scanf("%d", &menu_optiopn);

        switch(menu_optiopn) {
            case 1:
                Generuj_tablice(array);
                break;
            case 2:
                Print_Array(array);
                break;
            case 3:
                printf("Wartosc najmniejsza: %d \n", Array_minimum(array));
                break;
            case 4:
                printf("Wartosc najwieksza: %d \n", Array_maximum(array));
                break;
            case 5:
                printf("Wartosc srednia: %f \n", Avarage_array(array, sizeof(array)/sizeof(int)));
                break;
            case 6:
                break;
            case 7:
                printf("Zapisuję tabilice do pliku \n");
            errorCode = Save_array(array);
            if (!errorCode){
                printf("Zapisano \n");
            } else {
                printf("Cos poszlo nie tak \n");
            }
            break;
            case 8:
                printf("Odczytuje tabilice do pliku \n");
            errorCode = Read_array(array);
            if (!errorCode){
                printf("Odczytano \n");
            } else {
                printf("Cos poszlo nie tak \n");
            }

            case 9:
                printf("Koniec programu \n");
                break;

        }


     } while (menu_optiopn != 9);
    return 0;

}