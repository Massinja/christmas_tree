CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SOURCES = my_christmas_tree.c
OBJFILES = $(SOURCES:.c=.o)
TARGET = my_tree
all: $(TARGET)


$(TARGET): $(OBJFILES) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)


.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJFILES)
