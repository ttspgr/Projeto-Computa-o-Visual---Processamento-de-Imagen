CC = gcc
CFLAGS = -Wall -I/opt/homebrew/include -I.
LDFLAGS = -L/opt/homebrew/lib -lSDL3 -lSDL3_image -lSDL3_ttf

TARGET = projeto1
SRCS = main.c src/image_loader.c src/grayscale.c src/histogram.c src/image_saver.c src/gui.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
