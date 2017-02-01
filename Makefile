#########################################################################
# Kane Catt - 4/26/2016                                                 #
# Universal Makefile                                                    #
#                                                                       #
# Can be used with any project. Set up to compile an arbitrary amount   #
# of files in a project that can be in any directory within the         #
# base project directory. Specify the directories that the source       #
# files are contained using the SRC_DIR variable and you can change     #
# the location the object files are placed with the BUILD_DIR variable. #                                                   
#                                                                       #
# University of Evansville                                              #
#########################################################################

SRC_DIR    := src src/objects src/utils src/include src/interface src/ext/glad
BUILD_DIR  := build build/objects build/utils build/include build/interface build/ext/glad
SRC        := $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.cpp))
OBJ        := $(patsubst src/%.cpp, build/%.o, $(SRC))

BACKUPS    := *~ src/*~
EXECUTABLE := test
FLAGS      := -std=c++14 -c -Wall -g
INCLUDES   := $(addprefix -I,$(SRC_DIR)) -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
INCDIR     := 
XLIBS      := -std=c++14
CC         := g++

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CC) $$< -o $$@ $(INCLUDES) $(FLAGS) 
endef

.PHONY: all checkdirs clean

all: checkdirs $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $^ -o $@ -I$(INCDIR) $(INCLUDES) $(XLIBS) 

$(OBJDIR)/%.o: %.cpp %.h
	$(CC) $(FLAGS) $< -o $@

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR) $(BACKUPS) $(EXECUTABLE)

$(foreach bdir, $(BUILD_DIR), $(eval $(call make-goal, $(bdir))))