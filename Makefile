CC=gcc-12
C_FLAGS= -std=c99 
MAIN=sicemu
TEST_ARGS=bin/test.rom

reset:
	rm -rf ./bin/$(MAIN)
	mkdir -p ./bin

compile: reset
	$(CC) $(C_FLAGS) -o bin/$(MAIN) src/*.c

test: compile
	bin/$(MAIN) $(TEST_ARGS)

format:
	clang-format -i src/*.c