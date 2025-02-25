# Makefile para compilar un archivo con nombre variable y soporte para pthread
# Uso: make FILE=nombre_archivo (sin extensión)

# Variables
CC = gcc
LDFLAGS = -pthread

# Si no se especifica FILE, usar 'programa' como valor predeterminado
FILE ?= programa

# Regla principal
all: $(FILE)

# Patrón para compilar cualquier .c en un ejecutable con el mismo nombre
$(FILE): ./src/$(FILE).c
	$(CC) -o $@ $< $(LDFLAGS)

# Limpiar archivos compilados
clean:
	rm -f $(FILE)

.PHONY: all clean
