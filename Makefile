TARGET = rich.exe
SRC:=$(wildcard ./*.c)
OBJ:=$(patsubst ./%.c, ./%.o, $(SRC))
HEADER:=$(wildcard ./*.h)
#OBJ = main.o map.o command_exec.o command_parser.o playerMove.o initialize.o dump.o judge.o action.o tools.o building.o
#HEADER = common.h map.h command_exec.h command_parser.h playerMove.h initialize.h dump.h judge.h action.h tools.h building.h

all:$(TARGET)

$(TARGET):$(OBJ)
	gcc $(OBJ) -o $(TARGET)

%.o:%.c $(HEADER)
	gcc -c $< -o $@

.PHONY:clean
clean:
	rm *.o *.exe