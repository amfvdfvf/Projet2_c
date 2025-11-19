# Compilateur
CC = gcc

# Nom de l'exécutable
EXECUTABLE = app

# Cible par défaut
all: $(EXECUTABLE)

# Compilation directe en une seule commande
$(EXECUTABLE): main.c
	$(CC) main.c -o $(EXECUTABLE) `pkg-config --cflags --libs gtk4`
	@echo "✅ Compilation réussie ! Exécutable : $(EXECUTABLE)"

# Lancer l'app
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Nettoyer
clean:
	rm -f $(EXECUTABLE)

rebuild: clean all

.PHONY: all run clean rebuild

# gcc main.c -o app `pkg-config --cflags --libs gtk4`
# gcc  main.c params.c -o app `pkg-config --cflags --libs gtk4`