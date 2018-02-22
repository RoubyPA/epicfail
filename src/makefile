CC=gcc

OPT=-Wall -g -pedantic
CFLAGS=`pkg-config --cflags gobject-2.0 gtk+-3.0`
LDFLAGS=`pkg-config --libs gobject-2.0 gtk+-3.0`

APP_OBJ=error.o \
	Config.o \
	About.o \
	Result.o \
	Application.o \
	main.o \
	Dice.o

all: Application

Application: $(APP_OBJ)
	$(CC) $(OPT) $(BUILD_PATH)/main.o $(BUILD_PATH)/error.o \
			$(BUILD_PATH)/About.o $(BUILD_PATH)/Config.o \
			$(BUILD_PATH)/Result.o $(BUILD_PATH)/Dice.o \
			$(BUILD_PATH)/Application.o -o $(BUILD_PATH)/epicfail $(LDFLAGS)

Application.o: ui/Application.c
	$(CC) $(OPT) -c ui/Application.c -o $(BUILD_PATH)/Application.o $(CFLAGS)

About.o: ui/About.c
	$(CC) $(OPT) -c ui/About.c -o $(BUILD_PATH)/About.o $(CFLAGS)

Result.o: ui/Result.c
	$(CC) $(OPT) -c ui/Result.c -o $(BUILD_PATH)/Result.o $(CFLAGS)

Config.o: config/Config.c
	$(CC) $(OPT) -c config/Config.c -o $(BUILD_PATH)/Config.o $(CFLAGS)

error.o: error/error.c
	$(CC) $(OPT) -c error/error.c -o $(BUILD_PATH)/error.o $(CFLAGS)

main.o: main.c
	$(CC) $(OPT) -c main.c -o $(BUILD_PATH)/main.o $(CFLAGS)

Dice.o: dice/Dice.c
	$(CC) $(OPT) -c dice/Dice.c -o $(BUILD_PATH)/Dice.o $(CFLAGS)

clean:
	rm $(BUILD_PATH)/*.o -v
