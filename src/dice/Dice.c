#include "Dice.h"

#include "../error/error.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*public*/ GType
Dice_get_type (void)
{
  static GType type = 0;

  if (type == 0)
  {
    static const GTypeInfo info = {
      sizeof (DiceClass), /* class_size */
      NULL,               /* base_init */
      NULL,               /* base_finalize */
      NULL,               /* class_init */
      NULL,               /* class_finalize */
      NULL,               /* class_data */
      sizeof (Dice),      /* instance_size */
      0,                  /* n_preallocs */
      NULL,               /* instance_init */
      NULL                /* value_table */
    };
    type = g_type_register_static (G_TYPE_OBJECT, "Dice", &info, 0);
  }
  return type;
}

/*public*/ int
Dice_set_value (Dice *self, int value)
{
  if (self == NULL)
    return -1;

  self->value = value;
  
  return self->value;
}

/*public*/ int
Dice_roll (Dice *self)
{
  int ret = 0;
  float tmp = 0;

  srand (time (NULL) + rand ());

  if(self->value < 2)
    {
      ef_error("roll");
      ret = -1;
    }
  else
    {
      tmp = (float)rand () / (float)RAND_MAX;
      ret = (int)(tmp * self->value)+1;
    }

  return ret;
}
