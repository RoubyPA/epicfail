#ifndef CONFIG_H
#define CONFIG_H

#include <glib-object.h>

#define TYPE_CONFIG            (Config_get_type ())
#define CONFIG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_CONFIG, CONFIG))
#define CONFIG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_CONFIG, ConfigClass))
#define IS_CONFIG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_CONFIG))
#define IS_CONFIG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_CONFIG))
#define CONFIG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_CONFIG, ConfigClass))

typedef struct _wordlist wordlist;
struct _wordlist
{
  char *App_title;
  char *App_menu_name;
  char *App_menu_pref;
  char *App_menu_about;
  char *App_menu_theme;
  char *App_menu_lang;

  char *About_title;
  char *About_label;
  char *About_button;

  char *Result_title;
  char *Result_label;
  char *Result_button;
};

typedef struct _Config Config;
typedef struct _ConfigClass ConfigClass;

struct _Config
{
  /*public*/ GObject parent;

  /*public*/ char **argv;
  /*public*/ char **env;
  
  /*public*/ char *dir;
  /*public*/ char *lang;
  /*public*/ char *theme;

  /*public*/ wordlist dico;
};

struct _ConfigClass
{
  GObjectClass parent;
};

/*public*/ GType Config_get_type (void);
/*public*/ void Config_init (Config *, int, char **, char **);
/*public*/ void Config_change_lang (Config *);
/*public*/ void Config_change_theme (Config *);
/*public*/ void Config_finalize (Config *);

#endif /*CONFIG_H*/
