CC=g++
CPPFLAGS=-std=c++1y -Wall -g
MAIN=main.o
EXECUTABLE=bin/raytracer
INCLDIR=include/
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.cc = $(CC) $(DEPFLAGS) $(CPPFLAGS) -I$(INCLDIR) -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all: CPPFLAGS += -O2
all: $(EXECUTABLE)

game: CPPFLAGS += -DGAME
game: all

debug: CPPFLAGS += -g
debug: $(EXECUTABLE)

prof: CPPFLAGS += -pg -O2
prof: $(EXECUTABLE)

$(EXECUTABLE): obj/$(MAIN) $(OBJ_FILES)
		$(CC) $(CPPFLAGS) -o $@ $^

obj/%.o : src/%.cpp $(DEPDIR)/%.d
		$(COMPILE.cc) $(OUTPUT_OPTION) $<
		$(POSTCOMPILE)

clean:
		rm -f $(OBJ_FILES) $(MAIN) $(EXECUTABLE)
		rm -rf $(DEPDIR)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(addprefix .d/,$(notdir $(CPP_FILES:.cpp=.d)))
