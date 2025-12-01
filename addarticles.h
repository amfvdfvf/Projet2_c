#ifndef ADDARTICLES_H
#define ADDARTICLES_H

#include <gtk/gtk.h>
#include <time.h>


struct article {
    char nom[100];
    char reference[100];
    char id_produit[100];
    int alerte_min;
    int quantite;
    char categorie[100];
};

void button_add_articles(GtkWidget *widget, gpointer user_data);
//metre les fonction pour crée l'aticle et les verifications
int veriAjoutarticle(struct article *a);

void generate_random_string(char *str, int length);


#endif // ADDARTICLES_H
