build:
	g++ -std=c++17 -Wall -I deps/SDL2/include -I include -L deps/SDL2/lib/x64 -lSDL2 -lSDL2main -o app main.cpp src/*.cpp -lmingw32 -lSDL2main -lSDL2

run:
	./sdl_app

build_and_run:
	g++ -std=c++17 -Wall -I deps/SDL2/include -I include -L deps/SDL2/lib/x64 -lSDL2 -lSDL2main -o app main.cpp src/*.cpp -lmingw32 -lSDL2main -lSDL2
	./sdl_app

clean:
	rm sdl_app
