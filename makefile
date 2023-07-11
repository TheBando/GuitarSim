CC = g++

CFLAGS = -Wall
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OBJ= CircularBuffer.o StringSound.o $(TARGET).o
DEPS=
LIBS=
TARGET= KSGuitarSim

all: $(TARGET)

$(TARGET): $(OBJ)
	g++ $(OBJ) -o $(TARGET) $(LFLAGS) $(CFLAGS)

KSGuitarSim.o: KSGuitarSim.cpp
	g++ -c KSGuitarSim.cpp

StringSound.o: StringSound.cpp
	g++ -c StringSound.cpp

CircularBuffer.o: CircularBuffer.cpp
	g++ -c CircularBuffer.cpp

clean:
	rm $(OBJ)
