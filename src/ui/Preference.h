#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <glib-object.h>
#include <gtk/gtk.h>

#include "../config/Config.h"
#include "../error/error.h"

#define TYPE_PREFERENCE            (Preference_get_type ())
#define PREFERENCE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_PREFERENCE, Preference))
#define PREFERENCE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_PREFERENCE, PreferenceClass))
#define IS_PREFERENCE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_PREFERENCE))
#define IS_PREFERENCE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_PREFERENCE))
#define PREFERENCE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_PREFERENCE, PreferenceClass))

#define MAX_RADIO_BTN 15

typedef struct _Preference Preference;
typedef struct _PreferenceClass PreferenceClass;

struct _Preference
{
  /*public*/ GObject parent;

  /*public*/ Config *conf;

  /*public*/ char *title;
  
  /*public*/ GtkWidget *window;
  /*public*/ GtkWidget *main_vbox;
  /*public*/ GtkWidget *label;
  /*public*/ GtkWidget *hbox;
  
  /*public*/ GtkWidget *theme_vbox;
  /*public*/ GtkWidget *theme_label;
  /*public*/ GSList    *theme_group;
  /*public*/ GtkWidget *theme_radio[MAX_RADIO_BTN];

  /*public*/ GtkWidget *lang_vbox;
  /*public*/ GtkWidget *lang_label;
  /*public*/ GSList    *lang_group;
  /*public*/ GtkWidget *lang_radio[MAX_RADIO_BTN];

  /*public*/ GtkWidget *save;
  /*public*/ GtkWidget *about;
};

struct _PreferenceClass
{
  GObjectClass parent;
};

/*public*/ GType Preference_get_type (void);
/*public*/ void Preference_init (Preference *, Config *);
/*public*/ void Preference_create (Preference *);
/*public*/ void Preference_show (Preference *);
/*public*/ void Preference_hide (Preference *);

#endif /*PREFERENCE_H*/
