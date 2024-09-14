# Check if SDL2 is installed
SDL2_CHECK := $(shell pkg-config --exists sdl2 && echo installed || echo not-installed)
SDL2_IMAGE_CHECK := $(shell pkg-config --exists SDL2_image && echo installed || echo not-installed)
SDL2_TTF_CHECK := $(shell pkg-config --exists SDL2_ttf && echo installed || echo not-installed)

define n


endef

define ERR_STR
$(error Missing dependencies!$nOn Ubuntu, try this command:$nsudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev$n)
endef

ifeq ($(SDL2_CHECK), not-installed)
$(ERR_STR)
endif

ifeq ($(SDL2_IMAGE_CHECK), not-installed)
$(ERR_STR)
endif

ifeq ($(SDL2_TTF_CHECK), not-installed)
$(ERR_STR)
endif

all:
	g++ -I include -o VisualSort src/* -lSDL2 -lSDL2_image -lSDL2_ttf -pthread

clean:
	rm VisualSort
