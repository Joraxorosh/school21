CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
LDFLAGS = -lfcgi
TARGET  = server
SRC     = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
