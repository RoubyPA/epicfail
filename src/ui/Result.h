#ifndef RESULT_H
#define RESULT_H

#include <glib-object.h>
#include <gtk/gtk.h>

#include "../config/Config.h"

#define TYPE_RESULT            (Result_get_type ())
#define RESULT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_RESULT, Result))
#define RESULT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_RESULT, ResultClass))
#define IS_RESULT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_RESULT))
#define IS_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_RESULT))
#define RESULT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_RESULT, ResultClass))

typedef struct _Result Result;
typedef struct _ResultClass ResultClass;

struct _Result
{
  /*public*/ GObject parent;
  
  /*public*/ Config *conf;
  
  /*public*/ char *title;
  /*public*/ GtkWidget *window;
  /*public*/ GtkWidget *m_vbox;
  /*public*/ GtkWidget *label;
  /*public*/ GtkWidget *image;
};

struct _ResultClass
{
  GObjectClass parent;
};

/*public*/ GType Result_get_type (void);
/*public*/ void Result_init (Result *, Config *);
/*public*/ void Result_create (Result *);
/*public*/ void Result_update_with_dice_result (Result *, int, int);
/*public*/ void Result_show (Result *);

#endif /*RESULT_H*/
