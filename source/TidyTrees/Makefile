# OBJS specifies which files to compile as part of the project
OBJS = main.c

# CC specifies which compiler we're using
CC = gcc
# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I/usr/local/include

# LIBRARY_PATHS specifies the additional library paths we'll need and GL_LIBS specifies path for OpenGL Libraries
LIBRARY_PATHS = -L/usr/local/lib

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -framework OpenGL -framework GLUT -lglfw3 -lglew -lSOIL

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Application

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
