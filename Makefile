CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./include
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/ebank

.PHONY: all clean run

all: $(TARGET)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

$(TARGET): $(OBJDIR) $(BINDIR) $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)
	@echo "Build successful! Executable: $@"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	@rm -rf $(OBJDIR) $(BINDIR)
	@echo "Cleaned up build files"

help:
	@echo "Available targets:"
	@echo "  all   - Build the project"
	@echo "  run   - Build and run the project"
	@echo "  clean - Remove build files"
	@echo "  help  - Show this help message"
