#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct car {
    char *brand;
    char *numar;
    char *combustibil;
    double consum;
    int km;
};

int statistica(struct car *ptr, int N, char *tip) {
    int numar = 0;
    for (int i = 0; i < N; i++) {
        if (strcmp(ptr[i].combustibil, tip) == 0) numar++;
    }
    return numar;
}
int numar_corect(struct car *ptr, int i) {
    int length = strlen(ptr[i].numar);  // lungimea numarului masinii curente
    for (int j = length - 1; j > length - 4; j--) {
        if (isalpha(ptr[i].numar[j]) ==
            0)  // daca cel putin una nu e litera , exit
            return 0;
    }
    for (int j = length - 4; j > length - 6; j--) {
        if (isdigit(ptr[i].numar[j]) ==
            0)  // daca cel putin urm 2 nu sunt cifre , exit
            return 0;
    }
    int nr_cifre = 2, nr_litere = 0,
        first = 0;  // daca am ajuns pana aici ,
                   // inseamna ca s-au gasit deja 2 cifre
    for (int j = length - 6; j >= 0; j--) {
        if (isdigit(ptr[i].numar[j]) != 0 &&
            first == 0) {  // daca urm e cifra si nu am avut litera inainte ,
                           // s-au epuizat cifrele posibile
            nr_cifre++;
            if (nr_cifre > 3) return 0;
        } else if (isdigit(ptr[i].numar[j]) != 0 &&
                   first == 1)  // e cifra dar avem litera inainte
            return 0;
         // daca e litera
        if (isalpha(ptr[i].numar[j]) != 0 && nr_litere <= 2) { 
            first = 1;  // am gasit prima litera deci nu mai avem voie cu cifre
            nr_litere++;
            if (nr_litere > 2) return 0;
        }
    }
    return 1;
}

void consum_si_suma(struct car *ptr, int N, int i, double *suma,
                    double *suma_consum) {
    *suma = 0;
    *suma_consum = 0;
    for (int j = 0; j < N; j++) {  // pt fiecare masina din struct
       // daca brandul curent corespunde cu brandul trimis 
        if (strcmp(ptr[i].brand, ptr[j].brand) == 0) {  
            // calculam consumul si suma
            double consum_masina =
                (ptr[j].consum * ptr[j].km) / 100; 
            *suma_consum += consum_masina;
            if (strcmp(ptr[j].combustibil, "benzina") == 0 ||
                strcmp(ptr[j].combustibil, "hibrid") == 0)
                *suma += consum_masina * 8.02;
            if (strcmp(ptr[j].combustibil, "motorina") == 0)
                *suma += consum_masina * 9.29;
        }
    }
}
int main() {
    char *pct;
    pct = (char *)malloc(sizeof(char));
    int N;  // nr de masini
    scanf("%d", &N);
    struct car *ptr;
    // alocam memorie structurii
    ptr = (struct car *)malloc(N * sizeof(struct car));
    // alocam memorie pentru string-uri
    for (int i = 0; i < N; i++) {
        char brand[20], numar[20], combustibil[20];  // string-uri auxiliare
        scanf("%s %s %s %lf %d", brand, numar, combustibil, &(ptr + i)->consum,
              &(ptr + i)->km);
        ptr[i].brand = malloc(strlen(brand) + 1);
        ptr[i].numar = malloc(strlen(numar) + 1);
        ptr[i].combustibil = malloc(strlen(combustibil) + 1);
        strcpy(ptr[i].brand, brand);
        strcpy(ptr[i].numar, numar);
        strcpy(ptr[i].combustibil, combustibil);
    }

    getchar();
    scanf("%c", pct);
    // cerinta 1
    if (*pct == 'a') {
        int nr_benzina = statistica(ptr, N, "benzina");
        int nr_motorina = statistica(ptr, N, "motorina");
        int nr_hibrid = statistica(ptr, N, "hibrid");
        int nr_electric = statistica(ptr, N, "electric");
        printf("benzina - %d\n", nr_benzina);
        printf("motorina - %d\n", nr_motorina);
        printf("hibrid - %d\n", nr_hibrid);
        printf("electric - %d\n", nr_electric);
    }

    double suma, suma_consum;
    // cerinta 2
    if (*pct == 'b') {
        int i, j;
        for (i = 0; i < N; i++) {
            for (j = 0; j < i; j++) {
                if (strcmp(ptr[i].brand, ptr[j].brand) == 0) break;
            }
            if (i == j) {
                consum_si_suma(ptr, N, i, &suma_consum, &suma);
                printf("%s a consumat %.2lf - %.2lf lei\n", ptr[i].brand, suma,
                       suma_consum);
            }
        }
    }
    // cerinta 3
    if (*pct == 'c') {
        int gasit = 1;  // presupunem ca toate numerele sunt corecte
        for (int i = 0; i < N; i++) {
            if (numar_corect(ptr, i) == 0) {
                printf("%s cu numarul %s: numar invalid\n", ptr[i].brand,
                       ptr[i].numar);
                gasit = 0;
            }
        }
        if (gasit == 1) printf("Numere corecte!\n");
    }
    // eliberam memoria

    for (int i = 0; i < N; i++) {
        free(ptr[i].brand);
        free(ptr[i].numar);
        free(ptr[i].combustibil);
    }
    free(ptr);
}