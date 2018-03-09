CXX=g++
CXXFLAGS=-Wall -O0 -g -std=c++14 -MMD -MP
SRCDIR=src
OBJDIR=build/obj
INCL=include
LIBDIR=lib
LDFLAGS=-g
LDLIBS=-mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lglew32 -lopengl32

RM=rm
RMDIR=rm -r
MKDIR=mkdir -p

OUT=bin/main.exe

SRCS=Main/main.cpp Main/Game.cpp Main/ScaledDeltaTimer.cpp \
	Scene/SceneManager.cpp \
	Render/RenderManager.cpp Render/ShaderProgram.cpp

OBJNAMES := $(SRCS:.cpp=.o)
OBJS := $(addprefix $(OBJDIR)/,$(OBJNAMES))
BUILD_DIRS := $(patsubst %/,%,$(sort $(dir $(OBJS))))

all : $(OUT)

.PHONY: clean all

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp | $(BUILD_DIRS)
	$(CXX) $< -c $(CXXFLAGS) -I$(INCL) -o $@

$(OUT) : $(OBJS)
	$(CXX) $^ $(LDFLAGS) -L$(LIBDIR) $(LDLIBS) -o $(OUT)
	
$(BUILD_DIRS):
	$(MKDIR) "$@"
	
clean :
	$(RM) "$(OUT)"
	$(RMDIR) "$(OBJDIR)"
	
-include $(OBJS:.o=.d)