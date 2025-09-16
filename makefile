# Имя исполняемого файла
TARGET = te

# Компилятор
CXX = g++

# Флаги компилятора
CXXFLAGS = -fdiagnostics-color=always -finput-charset=utf-8 -g -I$(WPTEXTDIR)

# Флаги линкера
LDFLAGS = -lncursesw

# Директории с исходными файлами
SRCDIR = .
TEXTDIR = textEditor

# Список исходных файлов
SRC_FILES = $(wildcard $(SRCDIR)/main.cpp)
TEXT_FILES = $(wildcard $(TEXTDIR)/display.cpp $(TEXTDIR)/fileio.cpp $(TEXTDIR)/statusbar.cpp $(TEXTDIR)/editor.cpp)
SOURCES = $(SRC_FILES) $(TEXT_FILES)

# Список объектных файлов
OBJECTS = $(SOURCES:.cpp=.o)

# Директория для установки исполняемого файла
# По умолчанию используется /usr/bin. Для установки в другую директорию,
# например /usr/local/bin, можно вызвать: make install BINDIR=/usr/local/bin
BINDIR = /usr/bin

# Правило по умолчанию
all: $(TARGET)

# Правило для создания исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Правило для компиляции каждого cpp файла в объектный
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для установки исполняемого файла в системную директорию
install: all
	install -s $(TARGET) $(BINDIR)/

# Правило для удаления исполняемого файла из системной директории
uninstall:
	rm -f $(BINDIR)/$(TARGET)

# Правило для очистки скомпилированных файлов
clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean install uninstall
