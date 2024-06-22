CC=gcc
CFLAGS=-Iinclude
SRCDIR=src
BINDIR=bin
TARGET=$(BINDIR)/main.exe

SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(SOURCES:$(SRCDIR)/%.c=$(BINDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo Linking $@
	@$(CC) $^ -o $@

$(BINDIR)/%.o: $(SRCDIR)/%.c
	@echo Compiling $<
	@if not exist "$(BINDIR)" mkdir "$(BINDIR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo Cleaning
	@IF EXIST "$(BINDIR)\*" del /q /f "$(BINDIR)\*"
	@IF EXIST "$(BINDIR)" rmdir /q /s "$(BINDIR)"
.PHONY: all clean