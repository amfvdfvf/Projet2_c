#include <gtk/gtk.h>
#include <string.h>
#include "addarticles.h"

typedef struct {
    GtkEntry *entry_nom;
    GtkEntry *entry_id_produit;
    GtkEntry *entry_reference;
    GtkEntry *entry_alerte_min;
    GtkEntry *entry_quantite;
    GtkDropDown *dropdown;
    GtkWidget *window;
} SaveData;


void button_create_article(GtkWidget *widget, gpointer article_data){
    (void)widget;
    SaveData *data = (SaveData *)article_data;

    struct article article = {0};

    strcpy(article.nom, gtk_editable_get_text(GTK_EDITABLE(data->entry_nom)));
    strcpy(article.id_produit, gtk_editable_get_text(GTK_EDITABLE(data->entry_id_produit)));
    strcpy(article.reference, gtk_editable_get_text(GTK_EDITABLE(data->entry_reference)));
    article.alerte_min = atoi(gtk_editable_get_text(GTK_EDITABLE(data->entry_alerte_min)));
    article.quantite = atoi(gtk_editable_get_text(GTK_EDITABLE(data->entry_quantite)));
    strcpy(article.categorie, gtk_drop_down_get_selected_item(GTK_DROP_DOWN(data->dropdown)));

    veriAjoutarticle(&article);

    printf("Article ajouté avec succès !\n");
    gtk_window_close(GTK_WINDOW(data->window));
    
    g_free(data);

}

void on_image_chosen(GObject *source, GAsyncResult *res, gpointer user_data) {
    GtkPicture *picture = GTK_PICTURE(user_data);
    GtkFileDialog *dialog = GTK_FILE_DIALOG(source);
    GError *error = NULL;

    GFile *file = gtk_file_dialog_open_finish(dialog, res, NULL);
    if (!file) return;

    gtk_picture_set_file(picture, file);

    char *path_image = g_file_get_path(file);

    printf("%s", path_image);

    const char *dest_folder = "C:/users/ambro/Desktop/Projet2_c/images/";

    if (g_mkdir_with_parents(dest_folder, 0755) != 0) {
        printf("Erreur lors de la crea du dossier images\n");
        g_object_unref(file);
        return;
    }

    char name_image[100];
    generate_random_string(name_image, 20);
    strcat(name_image, ".png");
    
    //save le passe a un endroit pour le save en bdd est si pas de sauvegarde supprimer l'image


    gchar *dest_path = g_build_filename(dest_folder, name_image, NULL);

    GFile *dest = g_file_new_for_path(dest_path);
    
    g_file_copy(file, dest, G_FILE_COPY_OVERWRITE, NULL, NULL, NULL, &error);
    
    if (error) {
        printf("Erreur copie image: %s\n", error->message);
        g_error_free(error);
    } else {
        printf("Image copiée\n");
    }

    g_free(path_image);
    g_free(dest_path);
    g_object_unref(dest);
    g_object_unref(file);

}

void on_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWindow *window = GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(button)));
    GtkPicture *picture = GTK_PICTURE(user_data);

    GtkFileDialog *dialog = gtk_file_dialog_new();

    gtk_file_dialog_open(
        dialog,
        window,
        NULL,  
        on_image_chosen,
        picture
    );
}


void button_add_articles(GtkWidget *widget, gpointer user_data) {
    (void)widget;
    GtkApplication *app = GTK_APPLICATION(user_data);

    GtkWidget *new_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(new_window), "Ajout d'articles");
    gtk_window_set_default_size(GTK_WINDOW(new_window), 400, 300);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(new_window), box);

    GtkWidget *label = gtk_label_new("Ajouter un article");
    gtk_box_append(GTK_BOX(box), label);

    struct article p = {0};

    GtkWidget *box_image = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(box), box_image);

    GtkWidget *button = gtk_button_new_with_label("Choisir une image");
    gtk_box_append(GTK_BOX(box_image), button);
    GtkWidget *picture = gtk_picture_new();
    gtk_picture_set_can_shrink(GTK_PICTURE(picture), TRUE);
    gtk_box_append(GTK_BOX(box_image), picture);

    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), picture);

    //Nom       
    GtkWidget *label_nom= gtk_label_new("Nom produit :");
    gtk_box_append(GTK_BOX(box), label_nom);
    GtkWidget *entry_nom = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_nom), "Ex: Nom du produit");
    gtk_editable_set_text(GTK_EDITABLE(entry_nom), p.nom);
    gtk_box_append(GTK_BOX(box), entry_nom);

    //id prod gen automatiquement si null
    GtkWidget *label_id_produit= gtk_label_new("Id produit :");
    gtk_box_append(GTK_BOX(box), label_id_produit);
    GtkWidget *entry_id_produit = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_id_produit), "Ex: ID du produit");
    gtk_editable_set_text(GTK_EDITABLE(entry_id_produit), p.id_produit);
    gtk_box_append(GTK_BOX(box), entry_id_produit);

    //reference
    GtkWidget *label_id_reference= gtk_label_new("Id reference :");
    gtk_box_append(GTK_BOX(box), label_id_reference);
    GtkWidget *entry_id_reference = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_id_reference), "Ex: id ref");
    gtk_editable_set_text(GTK_EDITABLE(entry_id_reference), p.reference);
    gtk_box_append(GTK_BOX(box), entry_id_reference); 

    
    //Alerte min
    GtkWidget *label_alerte_min= gtk_label_new("Alerte min :");
    gtk_box_append(GTK_BOX(box), label_alerte_min);
    GtkWidget *entry_alerte_min = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_alerte_min), "Ex: Seuil d'alerte pour le stock 0 égale Nul");
    gtk_editable_set_text(GTK_EDITABLE(entry_alerte_min), "");
    gtk_box_append(GTK_BOX(box), entry_alerte_min);

    //quantite si 0 c'est jsute la creation de l'article
    GtkWidget *label_quantite= gtk_label_new("Quantite :");
    gtk_box_append(GTK_BOX(box), label_quantite);
    GtkWidget *entry_quantite = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_quantite), "Ex: Quantite initiale 0 creation d'article");
    gtk_editable_set_text(GTK_EDITABLE(entry_quantite), "");
    gtk_box_append(GTK_BOX(box), entry_quantite);

    //ajoute pour dire la categorire du produit liste deroulante faire que plus tard elle soit recupere de la bdd est peut etre crée par le user
    GtkWidget *label_categorie = gtk_label_new("Catégorie :");
    gtk_box_append(GTK_BOX(box), label_categorie);

    const char *categories[] = {"Électronique", "Vêtements", "Alimentation", "Autre", NULL};
    GtkStringList *list = gtk_string_list_new(categories);
    GtkWidget *dropdown = gtk_drop_down_new(G_LIST_MODEL(list), NULL);
    gtk_box_append(GTK_BOX(box), dropdown);

    //faire le bouton de sauvegarde et recuperer les donnees plus tard

     GtkWidget *save_button = gtk_button_new_with_label("Créer l'article");


    SaveData *data = malloc(sizeof(SaveData));
    data->entry_nom = GTK_ENTRY(entry_nom);
    data->entry_id_produit = GTK_ENTRY(entry_id_produit);
    data->entry_reference = GTK_ENTRY(entry_id_reference);
    data->entry_alerte_min = GTK_ENTRY(entry_alerte_min);
    data->entry_quantite = GTK_ENTRY(entry_quantite);
    data->dropdown = GTK_DROP_DOWN(dropdown);
    data->window = new_window;
    
    g_signal_connect(save_button, "clicked", G_CALLBACK(button_create_article), data);
    gtk_box_append(GTK_BOX(box), save_button);

    GtkWidget *back_button = gtk_button_new_with_label("Retour");
    g_signal_connect_swapped(back_button, "clicked", G_CALLBACK(gtk_window_close), new_window);
    gtk_box_append(GTK_BOX(box), back_button);
    gtk_window_present(GTK_WINDOW(new_window));
}
