#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "Config.h"

#include "../error/error.h"

#define CONFIG_LANG_SIZE 3
#define CONFIG_THEME_NAME_MAX_SIZE 32
#define CONFIG_PATH_MAX_SIZE 256
#define CONFIG_STD_STRING_SIZE 32
#define CONFIG_LONG_STRING_SIZE 1024

#ifndef PREFIX
#define DEFAULT_CONFIG_PATH "/share/epicfail"
#else
#define DEFAULT_CONFIG_PATH PREFIX "/share/epicfail"
#endif

/*private*/ static void Config_init_0 (Config *);
/*private*/ static void Config_init_alloc (Config *);
/*private*/ static void Config_lang_init_0 (Config *);
/*private*/ static void Config_lang_alloc (Config *);
/*private*/ static void Config_set_lang (Config *);
/*private*/ static void Config_init_dir (Config *);
/*private*/ static void Config_finalize_free (Config *);

/******************************************************************************
 * Public method                                                              *
 ******************************************************************************/

/*public*/ GType
Config_get_type (void)
{
  static GType type = 0;

  if (type == 0)
  {
    static const GTypeInfo info = {
      sizeof (ConfigClass), /* class_size */
      NULL,                 /* base_init */
      NULL,                 /* base_finalize */
      NULL,                 /* class_init */
      NULL,                 /* class_finalize */
      NULL,                 /* class_data */
      sizeof (Config),      /* instance_size */
      0,                    /* n_preallocs */
      NULL,                 /* instance_init */
      NULL                  /* value_table */
    };
    type = g_type_register_static (G_TYPE_OBJECT, "Config", &info, 0);
  }
  return type;
}

/*public*/ void
Config_init (Config *self, int argc, char **argv, char **env)
{
  self->argv = argv;
  self->env = env;

  Config_init_0 (self);
  Config_lang_init_0 (self);
  Config_set_lang (self);
  Config_init_dir (self);
}

/*public*/ void
Config_change_lang (Config *self)
{
  
}

/*public*/ void
Config_change_theme (Config *self)
{
  
}

/*public*/ void
Config_finalize (Config *self)
{
  Config_finalize_free (self);
}

/******************************************************************************
 * Private method                                                             *
 ******************************************************************************/

/*private*/ static void
Config_init_0 (Config *self)
{
  self->dir = NULL;
  self->lang = NULL;
  self->theme = NULL;

  Config_init_alloc (self);
}

/*private*/ static void
Config_init_alloc (Config *self)
{
  self->dir = malloc(CONFIG_PATH_MAX_SIZE);
  MALLOC_TEST_ERROR (self->dir)
  
  self->lang = malloc(CONFIG_LANG_SIZE);
  MALLOC_TEST_ERROR (self->lang)
  
  self->theme = malloc(CONFIG_THEME_NAME_MAX_SIZE);
  MALLOC_TEST_ERROR (self->theme)
}

/*private*/ static void
Config_lang_init_0 (Config *self)
{
  self->dico.App_title = NULL;
  self->dico.App_menu_name = NULL;
  self->dico.App_menu_pref = NULL;
  self->dico.App_menu_about = NULL;
  self->dico.App_menu_theme = NULL;
  self->dico.App_menu_lang = NULL;

  self->dico.About_title = NULL;
  self->dico.About_label = NULL;
  self->dico.About_button = NULL;

  self->dico.Result_title = NULL;
  self->dico.Result_label = NULL;
  self->dico.Result_button = NULL;

  Config_lang_alloc (self);  
}

/*private*/ static void
Config_lang_alloc (Config *self)
{
  self->dico.App_title = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.App_title);
  
  self->dico.App_menu_name = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.App_menu_name);
  
  self->dico.App_menu_pref = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.App_menu_pref);
  
  self->dico.App_menu_about = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.App_menu_about);
  
  self->dico.App_menu_theme = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.App_menu_theme);
    
  self->dico.App_menu_lang = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.App_menu_lang);

  
  self->dico.About_title = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.About_title);
    
  self->dico.About_label = malloc(CONFIG_LONG_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.About_label);
  
  self->dico.About_button = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.About_button);

  
  self->dico.Result_title = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.Result_title);
    
  self->dico.Result_label = malloc(CONFIG_LONG_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.Result_label);
  
  self->dico.Result_button = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.Result_button);
}

/*private*/ static void
Config_set_lang (Config *self)
{
  strcpy (self->dico.App_title, "Epicfail (Alpha)");
  strcpy (self->dico.App_menu_name, "File");
  strcpy (self->dico.App_menu_pref, "Preference");
  strcpy (self->dico.App_menu_about, "About");
  strcpy (self->dico.App_menu_theme, "Theme");
  strcpy (self->dico.App_menu_lang, "Language");

  strcpy (self->dico.About_title , "Epicfail - About");
  strcpy (self->dico.About_button, "Quit");
  strcpy (self->dico.About_label, "<span font_desc=\"bold\">Epicfail</span> "
	  "is a <a href=\"https://www.gnu.org/philosophy/free-sw.html\">free software</a>,\n"
	  "you have the freedom to run,\n"
	  "copy, distribute, study,\n"
	  "change and improve the software.\n"
	  "<span font_desc=\"italic\">This program comes with absolutely no warranty.</span>\n\n"
	  "Version: v0.2.1\n"
	  "License: <a href=\"https://www.gnu.org/licenses/gpl-3.0.txt\">GPLv3</a>\n"
	  "Sources: <span font_desc=\"italic\"><a href=\"https://github.com/RoubyPA/epicfail/\">"
	  "https://github.com/RoubyPA/epicfail/</a></span>\n");

  strcpy (self->dico.Result_title , "Epicfail - Result");
  strcpy (self->dico.Result_button, "Quit");
  strcpy (self->dico.Result_label, "No result...");
}

/*private*/ static void
Config_init_dir (Config *self)
{
  char *buffer;
  
  buffer = getenv("EF_DIR");
  
  if (buffer == NULL)
    self->dir = DEFAULT_CONFIG_PATH;
  else
    self->dir = buffer;
}


/*private*/ static void
Config_finalize_free (Config *self)
{ 
  free (self->dico.App_title);
  free (self->dico.App_menu_name);
  free (self->dico.App_menu_pref);
  free (self->dico.App_menu_about);
  free (self->dico.App_menu_theme);
  free (self->dico.App_menu_lang);
  
  free (self->dico.About_title);
  free (self->dico.About_label);
  free (self->dico.About_button);

  free (self->dico.Result_title);
  free (self->dico.Result_label);
  free (self->dico.Result_button);
}
