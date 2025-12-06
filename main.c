#include "params.h"
#include "extract_parms.h"
#include "addarticles.h"
#include "page2.h"
#include <gtk/gtk.h>

static int counter = 0;

static void on_button_clicked(GtkWidget *widget, gpointer user_data) {
    (void)user_data;
    counter++;
    gtk_button_set_label(GTK_BUTTON(widget), g_strdup_printf("Compteur: %d", counter));
}

static void on_page2_button_clicked(GtkWidget *widget, gpointer user_data) {
    (void)widget;
    GtkStack *stack = GTK_STACK(user_data);
    gtk_stack_set_visible_child_name(stack, "page1");
}

static void on_page1_button_clicked(GtkWidget *widget, gpointer user_data) {
    (void)widget;
    GtkStack *stack = GTK_STACK(user_data);
    gtk_stack_set_visible_child_name(stack, "page2");
}

static void activate(GtkApplication *app, gpointer user_data) {
    (void)user_data;
    
    struct parms p = {0};
    read_config("parms.txt", &p);
    
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "GTK 4 Example");
    gtk_window_set_default_size(GTK_WINDOW(window), p.width, p.height);

    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_window_set_child(GTK_WINDOW(window), stack);

    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(box1, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box1, GTK_ALIGN_CENTER);

    GtkWidget *label1 = gtk_label_new("Menu Principal");
    gtk_box_append(GTK_BOX(box1), label1);

    GtkWidget *button = gtk_button_new_with_label("Compteur: 0");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_box_append(GTK_BOX(box1), button);

    GtkWidget *button2 = gtk_button_new_with_label("Paramètres");
    gtk_widget_set_halign(button2, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button2, GTK_ALIGN_CENTER);
    g_signal_connect(button2, "clicked", G_CALLBACK(button_parms), app);
    gtk_box_append(GTK_BOX(box1), button2);

    GtkWidget *button3 = gtk_button_new_with_label("Ajouter un article");
    gtk_widget_set_halign(button3, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button3, GTK_ALIGN_CENTER);
    g_signal_connect(button3, "clicked", G_CALLBACK(button_add_articles), app);
    gtk_box_append(GTK_BOX(box1), button3);

    GtkWidget *button_page2 = gtk_button_new_with_label("Aller à Page 2");
    gtk_widget_set_halign(button_page2, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button_page2, GTK_ALIGN_CENTER);
    g_signal_connect(button_page2, "clicked", G_CALLBACK(on_page1_button_clicked), stack);
    gtk_box_append(GTK_BOX(box1), button_page2);

    gtk_stack_add_named(GTK_STACK(stack), box1, "page1");

    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(box2, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box2, GTK_ALIGN_CENTER);

    GtkWidget *label2 = gtk_label_new("Ajouter un Article");
    gtk_box_append(GTK_BOX(box2), label2);

    create_page2(box2);

    GtkWidget *button_back = gtk_button_new_with_label("Retour au Menu");
    gtk_widget_set_halign(button_back, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button_back, GTK_ALIGN_CENTER);
    g_signal_connect(button_back, "clicked", G_CALLBACK(on_page2_button_clicked), stack);
    gtk_box_append(GTK_BOX(box2), button_back);

    gtk_stack_add_named(GTK_STACK(stack), box2, "page2");

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "page1");

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.example.GtkApp", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
