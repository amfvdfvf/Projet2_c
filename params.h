#ifndef PARAMS_H
#define PARAMS_H

#include <gtk/gtk.h>

struct params
{
    char width[100];
    char length[100];
    char pseudo[100];
    char sound[100];
};

void button_parms(GtkWidget *widget, gpointer user_data);

#endif // PARAMS_H
