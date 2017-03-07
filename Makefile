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

# Suppress display of executed commands.
$(VERBOSE).SILENT:

SRC_DIR    := src src/objects src/utils src/include src/interface src/ext src/ext/glad src/ext/nanovg src/ext/KHR
BUILD_DIR  := build build/objects build/utils build/include build/interface build/ext/glad build/ext/nanovg build/ext/KHR
SRC        := $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.cpp))
OBJ        := $(patsubst src/%.cpp, build/%.o, $(SRC))

BACKUPS    := *~ src/*~
EXECUTABLE := test
FLAGS      := -std=c++14 -c -Wall -g -Wno-deprecated -Wl,-rpath=./src/lib
INCLUDES   := $(addprefix -I,$(SRC_DIR)) -lglfw3 -lGL -lGLU -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl -L./src/lib/ -lnanogui -L./src/lib/nfd -lnfd
INCDIR     := 
XLIBS      := -std=c++14 -Wl,-rpath=./src/lib
CC         := g++
GTK        := -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/mirclient -I/usr/include/mircommon -I/usr/include/mircookie -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng12 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0


vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	@echo "Generating file $$@"
	$(CC) $$< -o $$@ $(INCLUDES) $(FLAGS) $(GTK)
endef

.PHONY: all checkdirs clean

all: checkdirs $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	@echo "Generating executable $@"
	$(CC) $^ -o $@ -I$(INCDIR) $(INCLUDES) $(XLIBS) $(GTK)

$(OBJDIR)/%.o: %.cpp %.h
	$(CC) $(FLAGS) $(GTK) $< -o $@ 

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR) $(BACKUPS) $(EXECUTABLE)

$(foreach bdir, $(BUILD_DIR), $(eval $(call make-goal, $(bdir))))