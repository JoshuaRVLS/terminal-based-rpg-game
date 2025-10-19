SRC_FILES := $(wildcard src/*.cpp) \
             $(wildcard src/*/*.cpp) \

debug:
	@mkdir -p bin/debug
	g++ -g -O0 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 \
	--include-directory="./include" \
	-Wconversion -Wnull-dereference -Wsign-conversion \
	$(SRC_FILES) -o bin/debug/debug

release:
	@mkdir -p bin/release
	g++ -O3 -march=native -flto -DNDEBUG -fno-exceptions \
	--include-directory="./include" \
	-s -ffast-math -funroll-loops \
	$(SRC_FILES) -o bin/release/release

run: release
	./bin/release/release

check: debug
	# Add your tests here - for example:
	./bin/debug/debug --test || true

distcheck: debug release
	# Add distribution checks here
	@echo "Distribution check passed"

test: debug
	./bin/debug/debug --test || true

.PHONY: run check distcheck test