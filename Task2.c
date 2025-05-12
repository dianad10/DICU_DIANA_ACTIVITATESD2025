#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* denumire;
    float pret;
    int garantieLuni;
} Dispozitiv;

Dispozitiv initializare(int id, const char* denumire, float pret, int garantie) {
    Dispozitiv d;
    d.id = id;
    d.denumire = (char*)malloc(strlen(denumire) + 1);
    strcpy(d.denumire, denumire);
    d.pret = pret;
    d.garantieLuni = garantie;
    return d;
}

void afisare(Dispozitiv d) {
    printf("ID: %d | Denumire: %s | Pret: %.2f | Garantie: %d luni\n", d.id, d.denumire, d.pret, d.garantieLuni);
}

void afisareVector(Dispozitiv* vector, int nrElemente) {
    for (int i = 0; i < nrElemente; i++) {
        afisare(vector[i]);
    }
}

Dispozitiv* copiazaDupaGarantie(Dispozitiv* vector, int nrElemente, int garantieMinima, int* dimNou) {
    Dispozitiv* vectorNou = (Dispozitiv*)malloc(nrElemente * sizeof(Dispozitiv));
    *dimNou = 0;
    for (int i = 0; i < nrElemente; i++) {
        if (vector[i].garantieLuni >= garantieMinima) {
            vectorNou[*dimNou] = initializare(vector[i].id, vector[i].denumire, vector[i].pret, vector[i].garantieLuni);
            (*dimNou)++;
        }
    }
    return vectorNou;
}

Dispozitiv* copiazaDupaPret(Dispozitiv* vector, int nrElemente, float pretMaxim, int* dimNou) {
    Dispozitiv* vectorNou = (Dispozitiv*)malloc(nrElemente * sizeof(Dispozitiv));
    *dimNou = 0;
    for (int i = 0; i < nrElemente; i++) {
        if (vector[i].pret <= pretMaxim) {
            vectorNou[*dimNou] = initializare(vector[i].id, vector[i].denumire, vector[i].pret, vector[i].garantieLuni);
            (*dimNou)++;
        }
    }
    return vectorNou;
}

Dispozitiv* concateneazaVectori(Dispozitiv* v1, int dim1, Dispozitiv* v2, int dim2, int* dimFinal) {
    *dimFinal = dim1 + dim2;
    Dispozitiv* rezultat = (Dispozitiv*)malloc((*dimFinal) * sizeof(Dispozitiv));
    for (int i = 0; i < dim1; i++) {
        rezultat[i] = initializare(v1[i].id, v1[i].denumire, v1[i].pret, v1[i].garantieLuni);
    }
    for (int i = 0; i < dim2; i++) {
        rezultat[dim1 + i] = initializare(v2[i].id, v2[i].denumire, v2[i].pret, v2[i].garantieLuni);
    }
    return rezultat;
}

void dezalocare(Dispozitiv** vector, int* dim) {
    if (vector != NULL && *vector != NULL) {
        for (int i = 0; i < *dim; i++) {
            free((*vector)[i].denumire);
        }
        free(*vector);
        *vector = NULL;
        *dim = 0;
    }
}

int main() {
    int dim = 5;
    Dispozitiv* vector = (Dispozitiv*)malloc(dim * sizeof(Dispozitiv));
    vector[0] = initializare(1, "Laptop", 3500.0f, 24);
    vector[1] = initializare(2, "Telefon", 2200.0f, 12);
    vector[2] = initializare(3, "Boxa", 450.0f, 6);
    vector[3] = initializare(4, "Monitor", 800.0f, 36);
    vector[4] = initializare(5, "Mouse", 120.0f, 3);

    printf("Vector original:\n");
    afisareVector(vector, dim);

    int dimGarantie;
    Dispozitiv* garantii = copiazaDupaGarantie(vector, dim, 12, &dimGarantie);
    printf("\nDispozitive cu garantie >= 12 luni:\n");
    afisareVector(garantii, dimGarantie);

    int dimPret;
    Dispozitiv* ieftine = copiazaDupaPret(vector, dim, 1000.0f, &dimPret);
    printf("\nDispozitive cu pret <= 1000:\n");
    afisareVector(ieftine, dimPret);

    int dimConcat;
    Dispozitiv* total = concateneazaVectori(garantii, dimGarantie, ieftine, dimPret, &dimConcat);
    printf("\nVector concatenat:\n");
    afisareVector(total, dimConcat);

    dezalocare(&vector, &dim);
    dezalocare(&garantii, &dimGarantie);
    dezalocare(&ieftine, &dimPret);
    dezalocare(&total, &dimConcat);

    return 0;
}
