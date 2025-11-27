#include "addarticles.h"

void generate_random_string(char *str, int length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    srand(time(NULL));
    
    for (int i = 0; i < length; i++) {
        int random_index = rand() % (sizeof(charset) - 1);
        str[i] = charset[random_index];
    }
    str[length] = '\0';
}

int veriAjoutarticle(struct article *a){

    const char* nom = a->nom;
    const char* reference = a->reference;
    const char* id_produit = a->id_produit;
    int alerte_min = a->alerte_min;
    int quantite = a->quantite;

    if (strlen(nom) == 0) {
        printf("Le nom du produit ne peut pas etre vide.\n");
        return -1;
    }

    if(strcspn(nom, "!@#$%^&*()+=[]{}|;:'\",.<>?/`~ ") != strlen(nom)) {
        printf("Le nom du produit contient des caracteres invalides.\n");
        return -4;
    }

    if (strlen(reference) == 0) {
        //gen aleatoirement la reference
        generate_random_string(a->reference, 10);
    }

    if(strlen(id_produit) == 0 || strcspn(id_produit,"!@#$%^&*()+=[]{}|;:'\",.<>?/`~ ") != strlen(id_produit)){
        //gen aleatoirement l'id produit
        generate_random_string(a->id_produit, 10);
    }

    if (alerte_min < 0) {
        printf("Le niveau d'alerte minimum ne peut pas etre negatif.\n");
        return -2;
    }

    if (quantite < 0) {
        printf("La quantite ne peut pas etre negative.\n");
        return -3;
    }

    strcpy(a->nom, nom);
    strcpy(a->reference, reference);
    strcpy(a->id_produit, id_produit);
    a->alerte_min = alerte_min;
    a->quantite = quantite;

    return 1;
}