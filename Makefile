CC = gcc
CFLAGS = -Wall -I.
LDFLAGS = -lSDL3 -lSDL3_image -lSDL3_ttf

ifeq ($(OS),Windows_NT)
    TARGET = projeto1.exe
    RM = del /Q /F
else
    TARGET = projeto1
    RM = rm -f
endif

# Adiciona os caminhos do Homebrew apenas se for macOS
ifeq ($(shell uname -s 2>/dev/null),Darwin)
    CFLAGS += -I/opt/homebrew/include
    LDFLAGS += -L/opt/homebrew/lib
endif

SRCS = main.c src/image_loader.c src/grayscale.c src/histogram.c src/image_saver.c src/gui.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	-$(RM) $(TARGET)
