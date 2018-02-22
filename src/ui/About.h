#ifndef ABOUT_H
#define ABOUT_H

#include <glib-object.h>
#include <gtk/gtk.h>

#include "../config/Config.h"
#include "../error/error.h"

#define TYPE_ABOUT            (About_get_type ())
#define ABOUT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_ABOUT, About))
#define ABOUT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_ABOUT, AboutClass))
#define IS_ABOUT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_ABOUT))
#define IS_ABOUT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_ABOUT))
#define ABOUT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_ABOUT, AboutClass))

typedef struct _About About;
typedef struct _AboutClass AboutClass;

struct _About
{
  /*public*/ GObject parent;

  /*public*/ Config *conf;
  
  /*public*/ char *title;
  /*public*/ GtkWidget *window;
  /*public*/ GtkWidget *m_vbox;
  /*public*/ GtkWidget *label;
  /*public*/ GtkWidget *image;
};

struct _AboutClass
{
  GObjectClass parent;
};

/*public*/ GType About_get_type (void);
/*public*/ void About_init (About *, Config *);
/*public*/ void About_create (About *);
/*public*/ void About_show (About *);

#endif /*ABOUT_H*/
