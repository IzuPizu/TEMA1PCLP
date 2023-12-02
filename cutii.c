#include <stdbool.h>
#include <stdio.h>

void afisare(int l[], int k) {  // afiseaza ciclul
    for (int i = 0; i < k - 1; i++) {
        printf("%d ", l[i]);
    }
    printf("%d", l[k - 1]);
    printf("\n");
}
int win(int v[], int P) {
    bool gasit;
    int c;
    for (int i = 1; i <= P; i++) {  // contor pt prizonieri
        gasit = false;              // inca nu a gasit cutia cu numarul sau
        c = i;  //  prizonierul (i) deschide cutia numarul (i)
        for (int j = 1; j <= P / 2; j++) {  // nr de cutii deschise

            if (i ==
                v[c]) {  // daca valoarea din interiorul cutiei = nr prizonier
                gasit = true;
                break;
            } else
                c = v[c];  // urm cutie ce urmeaza sa fie deschisa
        }
        if (gasit == false) return 0;
    }
    if (gasit == true)
        return 1;  // toti prizonierii si-au gasit numarul
    else
        return 0;
}

int main() {
    int P, v[501];
    scanf("%d", &P);  // citim numarul de prizonieri
    for (int i = 1; i <= P; i++)
        scanf("%d", &v[i]);  // citim continutul cutiilor

    if (win(v, P) == 1)  // daca prizonierii castiga
        printf("Da\n");
    else
        printf("Nu\n");  // daca prizonierii pierd

    // cicluri
    int c, l[501], k;
    int vizitat[501] = {0};
    int found;
    for (int i = 1; i <= P; i++) {
        found = 0;
        k = 0;
        c = i;                     // nr cutiei curente
        while (vizitat[c] != 1) {  // cat timp nu cutia nu a mai fost deschisa
            found = 1;
            vizitat[c] = 1;
            // memoram intr un vector elementele ciclului candidat
            l[k] = c;
            k++;
            c = v[c];  // nr urmatoarei cutii ce va fi deschisa
        }
        // cand se termina while-ul inseamna ca s a ajuns la o cutie deja
        // vizitata=> am gasit un ciclu
        if (found == 1) {
            afisare(l, k);
        }
    }
    return 0;
}