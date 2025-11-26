#include <gtk/gtk.h>
#include <string.h>
#include "params.h"
#include "extract_parms.h"

// Structure pour passer les données à la fonction callback
typedef struct {
    GtkEntry *entry_height;
    GtkEntry *entry_width;
    GtkEntry *entry_sound;
    GtkWidget *window;
} SaveData;

static void on_save_button_clicked(GtkWidget *widget, gpointer user_data) {
    (void)widget;
    SaveData *data = (SaveData *)user_data;
    
    struct parms p = {0};
    p.height = atoi(gtk_editable_get_text(GTK_EDITABLE(data->entry_height)));
    p.width = atoi(gtk_editable_get_text(GTK_EDITABLE(data->entry_width)));
    strcpy(p.sound, gtk_editable_get_text(GTK_EDITABLE(data->entry_sound)));
    
    updatefichier("parms.txt", &p);
    
    printf("Paramètres sauvegardés !\n");
    gtk_window_close(GTK_WINDOW(data->window));
    
    g_free(data);
}

void button_parms(GtkWidget *widget, gpointer user_data) {
    (void)widget;
    GtkApplication *app = GTK_APPLICATION(user_data);

    GtkWidget *new_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(new_window), "Parametres");
    gtk_window_set_default_size(GTK_WINDOW(new_window), 400, 300);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(new_window), box);

    struct parms p = {0};
    read_config("parms.txt", &p);

    GtkWidget *label = gtk_label_new("Paramètres");
    gtk_box_append(GTK_BOX(box), label);

    // Label et Entry pour Hauteur
    GtkWidget *label_height = gtk_label_new("Hauteur :");
    gtk_box_append(GTK_BOX(box), label_height);
    GtkWidget *entry_height = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(entry_height), g_strdup_printf("%d", p.height));
    gtk_box_append(GTK_BOX(box), entry_height);

    // Label et Entry pour Largeur
    GtkWidget *label_width = gtk_label_new("Largeur :");
    gtk_box_append(GTK_BOX(box), label_width);
    GtkWidget *entry_width = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(entry_width), g_strdup_printf("%d", p.width));
    gtk_box_append(GTK_BOX(box), entry_width);

    // Label et Entry pour Son
    GtkWidget *label_sound = gtk_label_new("Son :");
    gtk_box_append(GTK_BOX(box), label_sound);
    GtkWidget *entry_sound = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(entry_sound), p.sound);
    gtk_box_append(GTK_BOX(box), entry_sound);

    // Bouton Sauvegarder
    GtkWidget *save_button = gtk_button_new_with_label("Sauvegarder");
    
    // Préparer les données pour le callback
    SaveData *data = malloc(sizeof(SaveData));
    data->entry_height = GTK_ENTRY(entry_height);
    data->entry_width = GTK_ENTRY(entry_width);
    data->entry_sound = GTK_ENTRY(entry_sound);
    data->window = new_window;
    
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_button_clicked), data);
    gtk_box_append(GTK_BOX(box), save_button);

    GtkWidget *back_button = gtk_button_new_with_label("Retour");
    g_signal_connect_swapped(back_button, "clicked", G_CALLBACK(gtk_window_close), new_window);
    gtk_box_append(GTK_BOX(box), back_button);
    gtk_window_present(GTK_WINDOW(new_window));
}