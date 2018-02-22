#ifndef DICE_H
#define DICE_H

#include <glib-object.h>

#define TYPE_DICE            (Dice_get_type ())
#define DICE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DICE, Dice))
#define DICE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_DICE, DiceClass))
#define IS_DICE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DICE))
#define IS_DICE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_DICE))
#define DICE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DICE, DiceClass))

typedef struct _Dice Dice;
typedef struct _DiceClass DiceClass;

struct _Dice
{
  /*public*/ GObject parent;
  
  /*public*/ int value;
};

struct _DiceClass
{
  GObjectClass parent;
};

/*public*/ GType Dice_get_type (void);
/*public*/ int Dice_set_value (Dice *self, int value);
/*public*/ int Dice_roll (Dice *self);

#endif /* DICE_H */
