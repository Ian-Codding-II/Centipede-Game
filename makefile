CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
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

# Debug build: Adds AddressSanitizer for runtime checks (e.g., use-after-free in screens).
# Rationale: Run with 'make debug' to catch issues like null Button* in update(); LDFLAGS += -fsanitize=address.
debug: CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer
debug: LDFLAGS += -fsanitize=address
debug: clean all

run-debug: debug
	LSAN_OPTIONS=verbosity=1 ./$(TARGET)  # LeakSanitizer verbose.

# Valgrind target: Runs Memcheck for memory errors (leaks, invalid reads) on built binary.
# Rationale: --full leak-check tracks origins (e.g., Button new without delete in onExit); supp file quiets SFML.
# Assumptions: valgrind.supp in root; --error-exitcode=1 halts on errors; logs to valgrind.log.
valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes \
	         --log-file=valgrind.log --error-exitcode=1 ./$(TARGET)

# This declares that `all`, `clean`, and `run` ... are phony targets (fake targets)
# Make will always run these commands, even if files with those names exist
.PHONY: all clean run debug run-debug valgrind