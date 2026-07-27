# Detecta Windows/Linux
ifeq ($(OS), Windows_NT)
    #CXX = g++ -std=c++23 
    #CXXFLAGS = -Iinclude -MMD -MP -O0 -g0 -pipe
    #LDFLAGS = -Llib-mingw-w64 -lglfw3dll -lopengl32 -lgdi32 -lwinmm -mconsole
    #OUT = build/program.exe
    #MKDIR = if not exist build mkdir build
    #RM = rmdir /s /q build
    #CP_ASSETS = copy lib-mingw-w64\glfw3.dll build\ && xcopy /E /I /Y shaders build\shaders

    # to use with w64devkit with the C++26
    CXX = g++ -std=c++26 -freflection
    CXXFLAGS = -Iinclude -MMD -MP -O0 -g0 -pipe
    LDFLAGS = -Llib-mingw-w64 -lglfw3dll -lopengl32 -lgdi32 -lwinmm -mconsole
    OUT = build/SkyWar.exe
    MKDIR = mkdir -p build
    RM = rm -r build
    CP_ASSETS = cp lib-mingw-w64/glfw3.dll build/
else
    CXX = g++
    CXXFLAGS = -Iinclude -MMD -MP -O0 -g0 -pipe
    LDFLAGS = -lglfw -lGL -ldl
    OUT = build/program.out
    MKDIR = mkdir -p build
    RM = rm -rf build
    CP_ASSETS = cp -r shaders build/
endif

# Arquivos fonte
SOURCES = $(wildcard src/*.cpp) $(wildcard src/imgui/*.cpp)
SOURCES += src/glad.c
# Gera lista de objetos: cada .cpp ou .c vira um .o na pasta build, com o mesmo nome base
OBJECTS = $(addprefix build/, $(notdir $(SOURCES:.cpp=.o)))
OBJECTS := $(OBJECTS:.c=.o)

# Dependências automáticas
DEPENDS = $(OBJECTS:.o=.d)

all: build_dir compile copy_assets

build_dir:
	$(MKDIR)

# Regra genérica para .cpp -> .o
build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# NOVA REGRA: Regra genérica para os .cpp que estão em src/imgui/
build/%.o: src/imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra específica para glad.c (único arquivo .c)
build/glad.o: src/glad.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Inclui dependências
-include $(DEPENDS)

compile: $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(OUT)

copy_assets:
	$(CP_ASSETS)

clean:
	$(RM)

.PHONY: all clean copy_assets


