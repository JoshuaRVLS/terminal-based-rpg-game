debug:
	g++ -g -O0 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 \
	--include-directory="./include" \
	-Wconversion -Wnull-dereference -Wsign-conversion \
  src/*.cpp -o bin/debug/debug

release:
	g++ -O3 -march=native -flto -DNDEBUG -fno-exceptions \
	--include-directory="./include" \
    -fno-rtti -s -ffast-math -funroll-loops \
    src/*.cpp -o bin/release/release


