CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRCDIR = src
INCDIR = includes
OBJDIR = obj
BINDIR = bin
# Automatically finds all .cpp files in src/ directory
# Without wildcard, you'd have to manually list every file:
# SOURCES = src/main.cpp src/player.cpp src/bullet.cpp ...
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/centipede
all: $(TARGET)
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@
clean:
	rm -rf $(OBJDIR) $(BINDIR)
run: $(TARGET)
	./$(TARGET)
# This declares that `all`, `clean`, and `run` are phony targets (fake targets)
# Make will always run these commands, even if files with those names exist
.PHONY: all clean run