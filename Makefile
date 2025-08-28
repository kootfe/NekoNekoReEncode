SRC = $(wildcard *.c)
OBK = $(SRC:.c=.o)
TARGET = app
CC = gcc
LIBS = glfw3 leif libclipboard cglm xcb gl

CFLAGS = -Wall -Wextra $(shell pkg-config --cflags $(LIBS))
LDFLAGS = $(shell pkg-config --libs $(LIBS))

all: $(TARGET)

# Link all object files to create the target
$(TARGET): $(OBK)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -lm -c $< -o $@

clean:
	rm -f $(OBK) $(TARGET)

