#include "params.h"
#include <gtk/gtk.h>


static int counter = 0;

static void on_button_clicked(GtkWidget *widget, gpointer user_data) {
    counter++;
    gtk_button_set_label(GTK_BUTTON(widget), g_strdup_printf("Compteur: %d", counter));
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "GTK 4 Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Créer un conteneur box pour centrer les boutons
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), box);

    // Créer le premier bouton
    GtkWidget *button = gtk_button_new_with_label("Compteur: 0");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_box_append(GTK_BOX(box), button);

    // dCréer le deuxième bouton
    GtkWidget *button2 = gtk_button_new_with_label ("Cliquez‑moi slt !");
    gtk_widget_set_halign (button2, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (button2, GTK_ALIGN_CENTER);
    g_signal_connect(button2, "clicked", G_CALLBACK(button_parms), app);
    gtk_box_append(GTK_BOX(box), button2);


    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.example.GtkApp", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
