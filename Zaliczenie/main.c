/* Program na zaliczenie przedmiotu Technologie Informacyjne 2 */
#include <stdio.h>
#include <stdlib.h>
#define CARS_MAX 10


struct car {                    //deklaracja struktury opisujacej samochod
    char registration[8];       //nr rejestracyjny
    char company[10];           //marka producenta
    char model[10];             //model samochodu
    int production_year;        //rok produkcji
    int milleage;               //przebieg
};

void add_car(struct car *car_number) {              //funkcja wprowadzajaca samochody
    printf("Podaj numer rejestracyjny: ");
    scanf("%s", (*car_number).registration);
    printf("Podaj marke: ");
    scanf("%s", (*car_number).company);
    printf("Podaj model: ");
    scanf("%s", (*car_number).model);
    printf("Podaj rok produkcji: ");
    scanf("%d", &(*car_number).production_year);
    printf("Podaj przebieg: ");
    scanf("%d", &(*car_number).milleage);
};

void print_car(struct car *car_number) {            //funkcja wyswieltajaca samochdy w strukturze
    printf("Nr rej: %s\t\t", (*car_number).registration);
    printf("%s %s\t\t", (*car_number).company, (*car_number).model);
    printf("%d rok\t", (*car_number).production_year);
    printf("%d km \n", (*car_number).milleage);
};

/*int get_prduction_year(struct car *car_number) {  //funkcja wydobywajaca i zwracajaca rok produkcji
    return (*car_number).production_year;
}
*/
int save_to_file(struct car *car_number){           //eksport bazdy do plku csv
    FILE *fptr;
    fptr = fopen("cars_export.csv", "a");
    if(fptr == NULL){
        fclose(fptr);
        return 1;
    }
    fprintf( fptr,"%s;%s;%s;%d;%d;\n",          //zapisanie w jednym wierszu całej struktury
        (*car_number).registration,
        (*car_number).company,
        (*car_number).model,
        (*car_number).production_year,
        (*car_number).milleage);                    //każdy rekord zakonczony jest znakiem ';'
    fclose(fptr);
    return 0;
}


int load_from_file(struct car *car_number) {                    //impotr bazy danych z pliku CSV, kazdy rekord musi byc zakonczony ;
    FILE *fptr;
    fptr = fopen("cars_import.csv", "r");                         //zabezpieczenie przed bledem
    if(fptr == NULL){
        return 1;
     }

        char temp_car_data [50];
        int line = 0;
        do {
            if (fgets(temp_car_data, sizeof(temp_car_data), fptr) != '\0') {
                printf("Wczytano wiersz %d: %s", line, temp_car_data);
                {
                    int i = 0, stop = 0;
                    char csv_separator = ';';
                    do {                                                    //pętla odczytująca numer rejestracyjny
                        if (temp_car_data[i] != csv_separator) {
                            car_number[line].registration[i] = temp_car_data[i];   //i przypisująca znak po znaku do struktury
                            i = i + 1;
                        } else {                                            //zakończenie odczytywania
                            stop = 1;
                            car_number[line].registration[i] = '\0';               //wpisanie '\0' na końcu rekordu
                        }
                    } while (stop != 1);
                    i=i+1;
                    stop = 0;
                    int j = 0;
                    do {                                                    //pętla odczytująca marke samochodu
                        if (temp_car_data[i] != csv_separator) {
                            car_number[line].company[j] = temp_car_data[i];   //i przypisująca znak po znaku do struktury
                            i = i + 1;
                            j++;
                        } else {                                            //zakończenie odczytywania
                            stop = 1;
                            car_number[line].company[j] = '\0';               //wpisanie '\0' na końcu rekordu
                        }
                    } while (stop != 1);
                    i++;
                    stop = 0;
                    j=0;
                    do {                                                    //pętla odczytująca model samochodu
                        if (temp_car_data[i] != csv_separator) {
                            car_number[line].model[j] = temp_car_data[i];   //i przypisująca znak po znaku do struktury
                            i = i + 1;
                            j++;
                        } else {                                            //zakończenie odczytywania
                            stop = 1;
                            car_number[line].model[j] = '\0';               //wpisanie '\0' na końcu rekordu
                        }
                    } while (stop != 1);
                    stop = 0;
                    i = i + 1;                                              //przesunięcie odczytu o 1, zeby nie odczytac ';'
                    car_number[line].production_year = 0;                   //pętla odczytująca rok produkcji
                    do {
                        if (temp_car_data[i] != csv_separator) {
                            car_number[line].production_year = 10*car_number[line].production_year + temp_car_data[i] - '0';
                            i = i + 1;                                      //odczytuje kolejno cyfry i generuje rok produkcji
                        } else
                            stop = 1;                                       //zakonczenie odczytywania
                    } while (stop != 1);
                    i = i + 1;
                    stop = 0;
                    car_number[line].milleage = 0;                   //pętla odczytująca rok produkcji
                    do {
                        if (temp_car_data[i] != csv_separator) {
                            car_number[line].milleage = 10*car_number[line].milleage + temp_car_data[i] - '0';
                            i = i + 1;                                      //odczytuje kolejno cyfry i generuje rok produkcji
                        } else
                            stop = 1;                                       //zakonczenie odczytywania
                    } while (stop != 1);
                }
                line++;                                                     //inkrementacja w celu odczytania kolejnej linii
            } else {
                printf("\n");
                break;                                                      // Przerwij, jeśli nie ma więcej linii
            }
        } while (temp_car_data[line] != '\0');

    fclose(fptr);

    return line;
}

int main(void) {
    struct car car_list[CARS_MAX];
    int Count_cars = 0;             //zmienna do zlicza ilosci aktualnie wprowadzonych samochodow
    int menu_option = 0;
    do {
        printf("REJEST SAMOCHODOW, samochodow w bazie: %d\n", Count_cars);
        printf("1. Wyswietl samochody w rejestrze\n");
        printf("2. Dodaj samochod do rejestru\n");
        printf("3. Eskportuj dane do pliku cars_export.csv\n");
        printf("4. Importuj dane z pliku cars_import.csv\n");
        printf("5. Wyjscie z programu\n\n");
        printf("Wybierz opcje: ");

        scanf("%d", &menu_option);

        switch(menu_option) {
            case 1:
                for (int i = 0; i < Count_cars; i++) {
                    print_car(&car_list[i]);
                }
            break;
            case 2:
                printf("\n");
                if (Count_cars < CARS_MAX) {
                    add_car(&car_list[Count_cars]);
                    Count_cars++;
                }else {
                    printf("Za duzo samochodow\n");
                }
            break;
            case 3:
                FILE *fptr;
                fptr = fopen("cars_export.csv", "w");     //tworzenie pustego pliku
                fclose(fptr);                                           // cars_export.csv do którego będą eksporotwane dane
                for (int i = 0; i < Count_cars; i++) {
                    save_to_file(&car_list[i]);
                }
            break;
            case 4:
                printf("\n");
                Count_cars = load_from_file(&car_list[0]);
            if (Count_cars > CARS_MAX) {
                printf("Wczytano za duzo samochodow, wyjscie z programu\n");
                menu_option = 5;
            }

            break;
            case 5:
                printf("Koniec programu \n");
            break;
        }
    } while (menu_option != 5);
   return 0;
}