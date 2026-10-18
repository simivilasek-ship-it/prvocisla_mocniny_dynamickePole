#include <stdio.h>
#include <stdlib.h>
#define VSTUPNI_SOUBOR "cisla.txt"
#define VYSTUPNI_SOUBOR "vystup.txt"

typedef struct {
    int zaklad;
    int exponent;
}ZAZNAM;

void Kontrola_otevreni(FILE* soubor, const char* SOUBOR) {
    if (soubor == NULL) {
        printf("Soubor %s se nepodarilo otevrit.\n", SOUBOR);
        exit(EXIT_FAILURE);
    }
}


void Kontrola_zavreni( FILE* soubor, const char* SOUBOR) {
    if (fclose(soubor)!= 0) {
        printf("Soubor %s se nepodarilo spravne zavrit.\n", SOUBOR);
        exit(EXIT_FAILURE);
    }

}


ZAZNAM *read_file(int * count) {
    int i = 0;
    ZAZNAM *tmp_zaznamy = NULL;
    ZAZNAM *zaznamy = NULL;

    FILE *soubor = fopen(VSTUPNI_SOUBOR, "r");
    Kontrola_otevreni(soubor, VSTUPNI_SOUBOR);

    zaznamy = (ZAZNAM *) malloc(sizeof(ZAZNAM));
    if (zaznamy == NULL) {
        printf("Chyba vytvoreni pameti\n");
        exit(EXIT_FAILURE);
    }


    while (fscanf(soubor,"%d %d", &zaznamy[i].zaklad, &zaznamy[i].exponent)==2) {
        i++;
        tmp_zaznamy = (ZAZNAM *) realloc(zaznamy, (i + 1) *sizeof(ZAZNAM));

        if (tmp_zaznamy != NULL) {
            zaznamy = tmp_zaznamy;
        }else {
            free(zaznamy);
            printf("Error (re)allocting memory, program will end.\n");
            exit(EXIT_FAILURE);
        }

    }
    Kontrola_zavreni(soubor, VSTUPNI_SOUBOR);
    *count = i;
    return zaznamy;




}


float Mocnina(int zaklad, int exponent) {
    float vysledek = 1.0f;
    for (int i = 0; i < exponent;i++) {
        vysledek *=zaklad;
    }
    return vysledek;
}


int JePrvocislo(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;


    }
    return 1;
}

void Tisk_hlavicky_obrazovka(void) {
    printf("VYPIS CISEL\n");
    printf("Vypis cisel ze souboru %s\n",VSTUPNI_SOUBOR);
    printf("----------------------------------------\n");
    printf("poradi  zaklad  exponent    mocnina\n");
    printf("----------------------------------------\n");
}



void Tisk_hlavicky_soubor(FILE*f) {
    fprintf(f,"Vypis cisel s prvociselnym zakladem ze seoboru %s\n",VSTUPNI_SOUBOR);
    fprintf(f,"------------------------------------\n");
    fprintf(f,"poradi   zaklad  exponent    mocnina\n");
    fprintf(f,"------------------------------------\n");
}


int main(void) {
    int pocet =0;

    ZAZNAM * zaznamy = read_file(&pocet);

    FILE *souborvystup = fopen(VYSTUPNI_SOUBOR, "w");
    Kontrola_otevreni(souborvystup, VYSTUPNI_SOUBOR);

    Tisk_hlavicky_obrazovka();
    Tisk_hlavicky_soubor(souborvystup);


    int poradi_soubor = 0;

    for (int i = 0; i < pocet; i++) {
        int zaklad = zaznamy[i].zaklad;
        int exponent = zaznamy[i].exponent;
        float vysledekMocnina = Mocnina(zaklad, exponent);

        printf("%4d.  %6d  %8d %10.0f\n", i + 1, zaklad, exponent, vysledekMocnina);
        if (JePrvocislo(zaklad)) {
            poradi_soubor++;
            fprintf(souborvystup,"%4d. %6d %8d %10.0f\n", poradi_soubor, zaklad, exponent, vysledekMocnina);
        }
    }


    Kontrola_zavreni(souborvystup, VYSTUPNI_SOUBOR);
    free(zaznamy);
    printf("\n Byl vytvoren soubor %s.\n", VYSTUPNI_SOUBOR);
    return 0;
}
