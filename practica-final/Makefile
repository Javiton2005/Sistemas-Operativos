# Variables
CC = gcc
CFLAGS = -I. -IListas
LDFLAGS = -lpthread
OBJDIR = obj
SRCDIR = .
BINDIR = .
TARGET_BANCO = banco
TARGET_USUARIO = usuario
TARGET_MONITOR = monitor

# Archivos fuente
SRCS_BANCO := $(wildcard $(SRCDIR)/banco.c) \
        $(wildcard $(SRCDIR)/usuarios/*.c) \
		$(wildcard $(SRCDIR)/transacciones/*.c) \
        $(wildcard $(SRCDIR)/comun/*.c) \
        $(wildcard $(SRCDIR)/login/*.c) \

SRCS_USUARIO := $(wildcard $(SRCDIR)/usuario.c) \
        $(wildcard $(SRCDIR)/comun/*.c) \
        $(wildcard $(SRCDIR)/funciones/*.c) \
				$(wildcard $(SRCDIR)/usuarios/*.c) \
				$(wildcard $(SRCDIR)/transacciones/*.c)

SRCS_MONITOR := $(wildcard $(SRCDIR)/monitor.c) \
        $(wildcard $(SRCDIR)/comun/*.c) \
				$(wildcard $(SRCDIR)/usuarios/*.c) \
				$(wildcard $(SRCDIR)/transacciones/*.c)

# Archivos objeto para banco y usuario
OBJS_BANCO := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS_BANCO))
OBJS_USUARIO := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS_USUARIO))
OBJS_MONITOR := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS_MONITOR))

# Reglas
all: $(TARGET_BANCO) $(TARGET_USUARIO) $(TARGET_MONITOR)

# Regla para compilar 'banco'
$(TARGET_BANCO): $(OBJS_BANCO)
	$(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)

# Regla para compilar 'usuario'
$(TARGET_USUARIO): $(OBJS_USUARIO)
	$(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)

# Regla para compilar 'usuario'
$(TARGET_MONITOR): $(OBJS_MONITOR)
	$(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)

# Reglas de compilación para cada .c (compatible con subcarpetas)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(BINDIR)/$(TARGET_BANCO) $(BINDIR)/$(TARGET_USUARIO)

.PHONY: all clean
