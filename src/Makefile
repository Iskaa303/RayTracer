# Define the link target.
linkTarget = game

# Define libraries that we need,
LIBS = -IC:/sdk/sdl2/x86_64-w64-mingw32/include -LC:/sdk/sdl2/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -mwindows -static-libgcc -static-libstdc++ 

# Define flags.
# CFLAGS = -std=c++17 -pg
CFLAGS = -std=c++17

# Define the object files that we need to use.
objects = main.o \
					CApp.o \
					$(patsubst %.cpp,%.o,$(wildcard ./RayTrace/*.cpp))
					
# Define the rebuildables.
rebuildables = $(objects) $(linkTarget)

# Rule to actually perform the build.
$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)
	
# Rule to create the .o files.
%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

.PHONEY:
clean:
	rm $(rebuildables)