#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* denumire;
    float pret;
    int garantieLuni;
} Dispozitiv;

Dispozitiv citireDispozitiv() {
    Dispozitiv d;
    char buffer[100];

    printf("ID: ");
    scanf("%d", &d.id);
    getchar();

    printf("Denumire: ");
    fgets(buffer, 100, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    d.denumire = (char*)malloc(strlen(buffer) + 1);
    strcpy(d.denumire, buffer);

    printf("Pret: ");
    scanf("%f", &d.pret);

    printf("Garantie (luni): ");
    scanf("%d", &d.garantieLuni);

    return d;
}

float pretCuTVA(Dispozitiv d) {
    return d.pret * 1.19f;
}

void modificaPret(Dispozitiv* d, float nouPret) {
    if (d != NULL)
        d->pret = nouPret;
}

void afisareDispozitiv(Dispozitiv d) {
    printf("ID: %d\n", d.id);
    printf("Denumire: %s\n", d.denumire);
    printf("Pret: %.2f\n", d.pret);
    printf("Garantie: %d luni\n", d.garantieLuni);
}

int main() {
    Dispozitiv d = citireDispozitiv();
    afisareDispozitiv(d);

    printf("\nPret cu TVA: %.2f\n", pretCuTVA(d));

    modificaPret(&d, 299.99f);
    printf("\nDupa modificare pret:\n");
    afisareDispozitiv(d);

    free(d.denumire);

    return 0;
}
