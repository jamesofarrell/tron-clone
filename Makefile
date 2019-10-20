#OBJS specifies which files to compile as part of the project
OBJS = Controller.cpp  Field.cpp  main.cpp  Model.cpp  Player.cpp  View.cpp

#CC specifies which compiler we're using
CC = mipsel-gcw0-linux-uclibc-g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -std=c++11 `sdl2-config --cflags`
#
#  #LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS =  -lSDL2_ttf -lSDL2_image `sdl2-config --libs`

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = tron-clone.elf

#This is the target that compiles our executable
all : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
