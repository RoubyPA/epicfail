all: Application

Application: autogen src/makefile
	make -C src/

autogen:
	mkdir -p ./build/bin

run:
	EF_DIR=./data ./build/bin/epicfail

clean:
	make -C src/ clean
