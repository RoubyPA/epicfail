#ifndef APPLICATION_H
#define APPLICATION_H

#include <glib-object.h>
#include <gtk/gtk.h>

#include "../config/Config.h"
#include "../dice/Dice.h"
#include "About.h"
#include "Result.h"
#include "Preference.h"

#define TYPE_APPLICATION            (Application_get_type ())
#define APPLICATION(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_APPLICATION, Application))
#define APPLICATION_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_APPLICATION, ApplicationClass))
#define IS_APPLICATION(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_APPLICATION))
#define IS_APPLICATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_APPLICATION))
#define APPLICATION_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_APPLICATION, ApplicationClass))

#define MAX_DICE_NUM 10
  
typedef struct _dice_button dice_button;
struct _dice_button {
  Dice *dice;
  GtkWidget *button;
  GtkWidget *image;
};

typedef struct _Application Application;
typedef struct _ApplicationClass ApplicationClass;

struct _Application
{
  /*public*/ GObject parent;

  /*public*/ Config *conf;
  /*public*/ About *about;
  /*public*/ Result *result;
  /*public*/ Preference *pref;
  
  /*public*/ char *title;
  /*public*/ GtkWidget *window;
  /*public*/ GtkWidget *m_vbox;
  /*public*/ GtkWidget *m_hbox;
  /*public*/ GtkWidget *l_vbox;
  /*public*/ GtkWidget *r_vbox;
  /*public*/ GtkWidget *menu_bar;
  /*public*/ GtkWidget *menu_item;

  /*public*/ dice_button buttons[MAX_DICE_NUM];
};

struct _ApplicationClass
{
  GObjectClass parent;
};

/*public*/ GType Application_get_type (void);
/*public*/ void Application_init (Application *, int, char **, char **);
/*public*/ void Application_create (Application *);
/*public*/ void Application_finalize (Application *);

#endif /*APPLICATION_H*/
