C=gcc
CFLAGS=-c -Wall
GLFLAGS=-lglut -lGL -lGLU -lm
SOURCES=particle.c particles_OpenGL.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=particles_OpenGL

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(GLFLAGS) -o $@

.c:.o 
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)