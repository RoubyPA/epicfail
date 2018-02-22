OPT=-Wall
CFLAGS=`pkg-config --libs --cflags glib-2.0 gobject-2.0`

all: dice_demo

dice_demo: Dice.o dice_demo.o
	gcc $(OPT) dice_demo.o Dice.o -o dice $(CFLAGS)

Dice.o: ../src/dice/Dice.c
	gcc $(OPT) -c ../src/dice/Dice.c -o Dice.o $(CFLAGS)

dice_demo.o: dice_demo.c
	gcc $(OPT) -c dice_demo.c -o dice_demo.o $(CFLAGS)

clean:
	rm *.o -v
