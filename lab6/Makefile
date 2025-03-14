
# Makefile para compilar el proyecto

# Variables
CC = gcc
CFLAGS = -I. -IListas 
LDFLAGS = -lpthread
OBJDIR = obj
SRCDIR = .
BINDIR = bin
TARGET = banco

# Archivos fuente (aquí arreglamos el tema de la barra y agregamos bien los paths)
SRCS := $(wildcard $(SRCDIR)/*.c) \
        $(wildcard $(SRCDIR)/banco/*.c) \
        $(wildcard $(SRCDIR)/usuarios/*.c) \
        $(wildcard $(SRCDIR)/comun/*.c) \
	$(wildcard $(SRCDIR)/login/*.c) \
	$(wildcard $(SRCDIR)/funciones/*.c) \
	$(wildcard $(SRCDIR)/monitor/*.c)
# Archivos objeto (y aquí transformamos los .c a .o dentro de obj/)
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Reglas
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Reglas de compilación para cada .c (ahora compatible con subcarpetas)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Necesitas una regla extra para que los .c dentro de `banco/` generen .o en `obj/banco/`
$(OBJDIR)/banco/%.o: $(SRCDIR)/banco/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean

