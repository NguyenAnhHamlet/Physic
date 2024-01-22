CC = g++ 

INC_DIRS=include 
TAR_DIRS = bin
SRC_DIRS = src
OBJ_DIRS = obj
TAR_NAME = ${MAKECMDGOALS}

DEP_FLAGS = -MMD -MP
INC_FLAGS = -I${INC_DIRS} -I/usr/include/SDL2/
LD_FLAGS = -lSDL2
CXXFLAGS = $(DEP_FLAGS) $(INC_FLAGS) $(LD_FLAGS)

CPP_FILES = $(wildcard $(SRC_DIRS)/*.cpp)
CPP_FILES += ${TAR_NAME}.cpp
OBJ_FILES = $(patsubst $(SRC_DIRS)/%.cpp,$(OBJ_DIRS)/%.o,$(CPP_FILES))
DEP_FILES = $(patsubst $(OBJ_DIRS)/%.o,$(DEP_DIRS)/%.d,$(OBJ_FILES))

$(OBJ_DIRS)/%.o : $(SRC_DIRS)/%.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS) 

.DEFAULT : all
all : $(OBJ_FILES)
	$(CC) -o $(TAR_DIRS)/$(TAR_NAME) $^ $(CXXFLAGS)

test_SAH : $(OBJ_FILES)
	$(CC) -o $(TAR_DIRS)/test_SAH $^ $(CXXFLAGS)

test_BVH : $(OBJ_FILES)
	$(CC) -o $(TAR_DIRS)/test_BVH $^ $(CXXFLAGS)
	

.PHONY : clean
clean : 
	rm -f ${OBJ_DIRS}/* ${TAR_DIRS}/*