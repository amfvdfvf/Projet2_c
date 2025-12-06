#include <gtk/gtk.h>
#include "page2.h"

#include <stdio.h>
#include <string.h>

// Définition de la structure
struct article {
    char title[100];
    char id_produit[50];
    char reference[50];
    int alerte_min;
    int quantite;
    char categorie[50];
    char image_path[200];
};

// Tableau d'articles de test
struct article inventaire[] = {
    {
        .title = "Clavier Mécanique RGB",
        .id_produit = "PROD-9876",
        .reference = "KBM-001A",
        .alerte_min = 5,
        .quantite = 12,
        .categorie = "Périphériques",
        .image_path = "/img/periph/kbm001a.png"
    },
    {
        .title = "Souris Sans Fil Ergonomique",
        .id_produit = "PROD-5432",
        .reference = "MOUSE-45B",
        .alerte_min = 10,
        .quantite = 8,
        .categorie = "Périphériques",
        .image_path = "/img/periph/mouse45b.jpg"
    },
    {
        .title = "Écran LED 27 pouces 4K",
        .id_produit = "PROD-1122",
        .reference = "MON-27-4K",
        .alerte_min = 3,
        .quantite = 3,
        .categorie = "Moniteurs",
        .image_path = "/img/monitors/mon274k.webp"
    },
    {
        .title = "Câble HDMI 2.1 (2m)",
        .id_produit = "PROD-3344",
        .reference = "CAB-HDMI-02",
        .alerte_min = 20,
        .quantite = 45,
        .categorie = "Câblage",
        .image_path = "/img/cables/hdmi2m.png"
    },
    {
        .title = "Disque Dur Externe 2To",
        .id_produit = "PROD-6677",
        .reference = "HDD-EXT-2T",
        .alerte_min = 5,
        .quantite = 0,
        .categorie = "Stockage",
        .image_path = "/img/storage/hddext2t.png"
    },
    {
        .title = "Disque Dur Externe 20To",
        .id_produit = "PROD-6677",
        .reference = "HDD-EXT-2T",
        .alerte_min = 5,
        .quantite = 0,
        .categorie = "Stockage",
        .image_path = "/img/storage/hddext2t.png"
    }
};

void create_page2(GtkWidget *box2) {
    GtkWidget *grid;
    char buffer[50];

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 2);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 2);
    gtk_widget_set_margin_start(grid, 10);
    gtk_widget_set_margin_top(grid, 10);

    const char *headers[] = { "Image", "Nom articles", "Quantité", "Modifier" };

    for (int col = 0; col < 4; col++) {
        GtkWidget *label = gtk_label_new(headers[col]);
        gtk_widget_set_hexpand(label, TRUE);

        GtkWidget *frame = gtk_frame_new(NULL);
        gtk_widget_set_hexpand(frame, TRUE);
        gtk_frame_set_child(GTK_FRAME(frame), label);
        gtk_widget_add_css_class(frame, "header");

        gtk_grid_attach(GTK_GRID(grid), frame, col, 0, 1, 1);
    }

    // faire un limd de nb d'atice par page pour faire un pagination aussi c'est plus propre
    int nb_articles = sizeof(inventaire) / sizeof(inventaire[0]);
    for (int row = 0; row < nb_articles; row++) {
        GtkWidget *label_img = gtk_label_new(inventaire[row].image_path); // faire que l'image s'affiche dans un box est qu'il y est un trin de coul de l'iamge selon le stocke est la limit configurer 
        gtk_widget_set_hexpand(label_img, TRUE);
        GtkWidget *frame_img = gtk_frame_new(NULL);
        gtk_widget_set_hexpand(frame_img, TRUE);
        gtk_frame_set_child(GTK_FRAME(frame_img), label_img);
        gtk_widget_add_css_class(frame_img, "cell");
        gtk_grid_attach(GTK_GRID(grid), frame_img, 0, row + 1, 1, 1);

        GtkWidget *label_nom = gtk_label_new(inventaire[row].title);
        gtk_widget_set_hexpand(label_nom, TRUE);
        GtkWidget *frame_nom = gtk_frame_new(NULL);
        gtk_widget_set_hexpand(frame_nom, TRUE);
        gtk_frame_set_child(GTK_FRAME(frame_nom), label_nom);
        gtk_widget_add_css_class(frame_nom, "cell");
        gtk_grid_attach(GTK_GRID(grid), frame_nom, 1, row + 1, 1, 1);

        snprintf(buffer, sizeof(buffer), "%d", inventaire[row].quantite);
        GtkWidget *label_qty = gtk_label_new(buffer);
        gtk_widget_set_hexpand(label_qty, TRUE);
        GtkWidget *frame_qty = gtk_frame_new(NULL);
        gtk_widget_set_hexpand(frame_qty, TRUE);
        gtk_frame_set_child(GTK_FRAME(frame_qty), label_qty);
        gtk_widget_add_css_class(frame_qty, "cell");
        gtk_grid_attach(GTK_GRID(grid), frame_qty, 2, row + 1, 1, 1);

        GtkWidget *btn_modify = gtk_button_new_with_label("Modifier");
        gtk_widget_set_hexpand(btn_modify, TRUE);
        GtkWidget *frame_btn = gtk_frame_new(NULL);
        gtk_widget_set_hexpand(frame_btn, TRUE);
        gtk_frame_set_child(GTK_FRAME(frame_btn), btn_modify); // faire que ca ajtoeu l'id de l'ari cocme ca ca fait un page personaliser pour modfier l'article
        gtk_widget_add_css_class(frame_btn, "cell");
        gtk_grid_attach(GTK_GRID(grid), frame_btn, 3, row + 1, 1, 1);
    }

    gtk_box_append(GTK_BOX(box2), grid);
}