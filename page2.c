#include <gtk/gtk.h>
#include "page2.h"

void create_page2(GtkWidget *box2) {
    GtkWidget *label = gtk_label_new("Ambroise");
    gtk_label_set_markup(GTK_LABEL(label), "<b>Ambroise</b>");
    gtk_box_append(GTK_BOX(box2), label);

    GtkWidget *progress = gtk_progress_bar_new();
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress), 0.5);
    gtk_box_append(GTK_BOX(box2), progress);
}
