BUILD_PATH=build

all: Application

Application: autogen src/makefile
	BUILD_PATH=../$(BUILD_PATH) make -C src/

autogen:
	mkdir -p $(BUILD_PATH)/

run:
	EF_DIR=./data $(BUILD_PATH)/epicfail

clean:
	BUILD_PATH=../$(BUILD_PATH) make -C src/ clean
