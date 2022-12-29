CC:= gcc
SOURCES:= $(wildcard src/*.c)
OBJECTS:= $(addprefix obj/,$(notdir $(SOURCES:.c=.o)))

CFLAGS:= -c -Wall -isystem /opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2 -isystem /opt/homebrew/Cellar/sdl2_image/2.6.2_1/include/SDL2 -Iinclude
LDFLAGS:= -L/opt/homebrew/Cellar/sdl2/2.26.1/lib -L/opt/homebrew/Cellar/sdl2_image/2.6.2_1/lib
LDLIBS:= -lSDL2 -lSDL2_image

EXECUTABLE:= game

# Instantly runs the game after linking
run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "Linking..."
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
	@echo "Linking for target $(EXECUTABLE) succeeded!"

obj/%.o: src/%.c
	@echo "Compiling:"
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm $(OBJECTS)
	rm game