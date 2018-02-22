#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "../src/dice/Dice.h"

int
usage (char *prog)
{
  printf ("Usage: %s <dice value>\n", prog);
  exit (EXIT_FAILURE);
}

int
main (int argc, char **argv)
{
  int i;
  int value;
  Dice *d = NULL;

  if (argc < 2)
    usage (argv[0]);

  if ((value = atoi(argv[1])) == 0)
    usage (argv[0]);
  
  d = g_object_new (TYPE_DICE, NULL);
  if (d == NULL)
    perror ("g_object_new");
  
  value = Dice_set_value (d, value);
  printf ("Dice value = %d\n", value);

  for (i = 0 ; i < 5 ; i++)
    {
      value = Dice_roll (d);
      printf ("Roll => %d\n", value);    
    }
  
  g_object_unref (d);
  return 0;
}
