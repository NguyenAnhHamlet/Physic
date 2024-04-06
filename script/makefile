CC = g++ 

INC_DIRS= ../include 
TAR_DIRS = ../bin
SRC_DIRS = ../src
OBJ_DIRS = ../obj
TAR_NAME = ${MAKECMDGOALS}

DEP_FLAGS = -MMD -MP
INC_FLAGS = -I${INC_DIRS} -I/usr/include/SDL2/
LD_FLAGS = -lSDL2
CXXFLAGS = $(DEP_FLAGS) $(INC_FLAGS) $(LD_FLAGS)

CPP_FILES = $(wildcard $(SRC_DIRS)/**/*.cpp)
CPP_FILES += ../main/${TAR_NAME}.cpp

OBJ_FILES += $(OBJ_DIRS)/${TAR_NAME}.o
OBJ_FILES += $(patsubst $(SRC_DIRS)/base/%.cpp,$(OBJ_DIRS)/%.o,$(wildcard $(SRC_DIRS)/base/*.cpp))
OBJ_FILES += $(patsubst $(SRC_DIRS)/bvh/%.cpp,$(OBJ_DIRS)/%.o,$(wildcard $(SRC_DIRS)/bvh/*.cpp))
OBJ_FILES += $(patsubst $(SRC_DIRS)/collision/%.cpp,$(OBJ_DIRS)/%.o,$(wildcard $(SRC_DIRS)/collision/*.cpp))
OBJ_FILES += $(patsubst $(SRC_DIRS)/common/%.cpp,$(OBJ_DIRS)/%.o,$(wildcard $(SRC_DIRS)/common/*.cpp))
OBJ_FILES += $(patsubst $(SRC_DIRS)/force/%.cpp,$(OBJ_DIRS)/%.o,$(wildcard $(SRC_DIRS)/force/*.cpp))
OBJ_FILES += $(patsubst $(SRC_DIRS)/gjk/%.cpp,$(OBJ_DIRS)/%.o,$(wildcard $(SRC_DIRS)/gjk/*.cpp))
OBJ_FILES += $(patsubst $(SRC_DIRS)/interaction/%.cpp,$(OBJ_DIRS)/%.o,$(wildcard $(SRC_DIRS)/interaction/*.cpp))
OBJ_FILES += $(patsubst $(SRC_DIRS)/render/%.cpp,$(OBJ_DIRS)/%.o,$(wildcard $(SRC_DIRS)/render/*.cpp)) 

DEP_FILES = $(patsubst $(OBJ_DIRS)/%.o,$(DEP_DIRS)/%.d,$(OBJ_FILES))

$(OBJ_DIRS)/${TAR_NAME}.o : ../main/${TAR_NAME}.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS) 

$(OBJ_DIRS)/%.o : $(SRC_DIRS)/**/%.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS) 

test_SAH : $(OBJ_FILES)
	$(CC) -g -o $(TAR_DIRS)/test_SAH $^ $(CXXFLAGS)

test_BVH : $(OBJ_FILES)
	@echo "object file : $(OBJ_FILES)"
	$(CC) -g -o $(TAR_DIRS)/test_BVH $^ $(CXXFLAGS)

test_Falling: $(OBJ_FILES)
	$(CC) -g -o $(TAR_DIRS)/test_Falling $^ $(CXXFLAGS)

test_falling2: $(OBJ_FILES)
	$(CC) -g -o $(TAR_DIRS)/test_falling2 $^ $(CXXFLAGS)

main : $(OBJ_FILES)
	$(CC) -o $(TAR_DIRS)/main $^ $(CXXFLAGS)

.PHONY : clean
clean : 
	rm -f ${OBJ_DIRS}/* ${TAR_DIRS}/*