OPT=-Wall -g
CFLAGS=`pkg-config --libs --cflags gobject-2.0 gtk+-3.0`

all: Application

Application: error.o Config.o About.o Result.o Application.o main.o Dice.o
	gcc $(OPT) main.o error.o About.o Config.o Result.o Dice.o Application.o -o ../build/bin/epicfail $(CFLAGS)

Application.o: ui/Application.c
	gcc $(OPT) -c ui/Application.c -o Application.o $(CFLAGS)

About.o: ui/About.c
	gcc $(OPT) -c ui/About.c -o About.o $(CFLAGS)

Result.o: ui/Result.c
	gcc $(OPT) -c ui/Result.c -o Result.o $(CFLAGS)

Config.o: config/Config.c
	gcc $(OPT) -c config/Config.c -o Config.o $(CFLAGS)

error.o: error/error.c
	gcc $(OPT) -c error/error.c -o error.o $(CFLAGS)

main.o: main.c
	gcc $(OPT) -c main.c -o main.o $(CFLAGS)

Dice.o: dice/Dice.c
	gcc $(OPT) -c dice/Dice.c -o Dice.o $(CFLAGS)

clean:
	rm *.o -v
