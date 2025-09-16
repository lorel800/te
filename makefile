TARGET = te
CXX = g++
CXXFLAGS = -fdiagnostics-color=always -finput-charset=utf-8 -g
LDFLAGS = -lncursesw
SRCDIR = .
TEXTDIR = textEditor
SRC_FILES = $(SRCDIR)/main.cpp
TEXT_FILES = $(TEXTDIR)/display.cpp $(TEXTDIR)/fileio.cpp $(TEXTDIR)/statusbar.cpp $(TEXTDIR)/editor.cpp
SOURCES = $(SRC_FILES) $(TEXT_FILES)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
$(TEXTDIR)/%.o: $(TEXTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
BINDIR ?= /usr/bin
install: all
	install -s $(TARGET) $(BINDIR)/
uninstall:
	rm -f $(BINDIR)/$(TARGET)
clean:
	rm -f $(TARGET) $(OBJECTS)
.PHONY: all clean install uninstall