OBJNAMES=Main/main.o Main/Game.o Ball.o Scene/SceneManager.o Main/ScaledDeltaTimer.o Main/Vector2.o Render/Sprite.o Main/GameComponent.o
OBJDIR=./build/obj
OBJS=$(addprefix $(OBJDIR)/,$(OBJNAMES))
OBJPATHNAMES=$(strip $(subst .,,$(patsubst %/,%,$(dir $(OBJNAMES)))))
OBJPATHS=$(addprefix $(OBJDIR)/,$(OBJPATHNAMES))

SRC=src

CXX=g++
INCL=include/SDL2
LIB=lib
LDFLAGS=
LDLIBS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
CXXFLAGS=-Wall -O0 -g -std=c++14 -m64 -MMD -MP

RM=rmdir /Q /S
MKDIR=mkdir

OUT=bin/main.exe

all : $(OUT)

.PHONY: clean all

$(OBJDIR)/%.o : $(SRC)/%.cpp | $(OBJPATHS)
	$(CXX) $< -c $(CXXFLAGS) -I$(INCL) -o $@

$(OUT) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -L$(LIB) $(LDLIBS) -o $(OUT)
	
$(OBJPATHS):
	$(MKDIR) "$@"
	
clean :
	$(RM) "$(OBJDIR)"
	
-include $(OBJS:.o=.d)