#include "extract_parms.h"

void to_uppercase(char *s)
{
    while (*s != '\0') {
        *s = toupper(*s);
        ++s;
    }
}

void read_config(const char *filename, struct parms *p)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Impossible d'ouvrir le fichier");
        return;
    }

    char line[256];

    while (fgets(line, sizeof line, f)) {
        line[strcspn(line, "\n")] = '\0';

        char *eq = strchr(line, '=');
        if (!eq) continue;

        *eq = '\0';
        char *key   = line;
        char *value = eq + 1;

        while (*value == ' ') value++;

        if (strcmp(key, "height") == 0) {
            p->height = atoi(value);
        }
        else if (strcmp(key, "width") == 0) {
            p->width = atoi(value);
        }
        else if (strcmp(key, "sound") == 0) {
            strncpy(p->sound, value, sizeof p->sound - 1);
        }
    }

    if (!(strcmp(p->sound, "ON") == 0 || strcmp(p->sound, "OFF") == 0)) {
        strcpy(p->sound, "OFF");
    }

    fclose(f);
}

void updatefichier(char *filename, struct parms *p)
{
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Impossible d'ouvrir le fichier");
        return;
    }

    to_uppercase(p->sound);

    if (strcmp(p->sound, "ON") != 0 && strcmp(p->sound, "OFF") != 0) {
        strcpy(p->sound, "OFF");
    }

    if (p->height <= 0) p->height = 1024;
    if (p->width <= 0) p->width = 1820;

    float ratio = (float)p->width / (float)p->height;
    printf("le ratio est de %f\n", ratio);

    if (ratio < 1.6f || ratio > 2.0f) {
        printf("pb ratio correction faite\n");
        p->height = 2160;
        p->width  = 3840;
    }

    fprintf(f, "height= %d\n", p->height);
    fprintf(f, "width= %d\n", p->width);
    fprintf(f, "sound= %s\n", p->sound);

    fclose(f);
}
