BUILD_PATH=build

all: Application

Application: autogen src/makefile
	BUILD_PATH=../$(BUILD_PATH) PREFIX=$(PREFIX) make -C src/

autogen:
	mkdir -p $(BUILD_PATH)/

run:
	EF_DIR=./data $(BUILD_PATH)/epicfail

install: Application
	cp $(BUILD_PATH)/epicfail $(PREFIX)/bin/
	mkdir -p $(PREFIX)/share/epicfail/
	cp -r data/* $(PREFIX)/share/epicfail/

clean:
	BUILD_PATH=../$(BUILD_PATH) make -C src/ clean
