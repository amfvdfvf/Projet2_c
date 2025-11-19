#ifndef EXTRACT_PARMS_H
#define EXTRACT_PARMS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct parms {
    int height;
    int width;
    char sound[10];
};

void to_uppercase(char *s);
void read_config(const char *filename, struct parms *p);
void updatefichier(char *filename, struct parms *p);

#endif // EXTRACT_PARMS_H
