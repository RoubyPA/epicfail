#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#include "Config.h"

#include "../error/error.h"

#define CONFIG_LANG_SIZE 3
#define CONFIG_THEME_NAME_MAX_SIZE 32
#define CONFIG_PATH_MAX_SIZE 256
#define CONFIG_STD_STRING_SIZE 32
#define CONFIG_LONG_STRING_SIZE 1024

#define CONFIG_FORMAT "%s = %s\n"
#define CONFIG_FILE "/epicfail.conf"

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
/*private*/ static void Config_read_config (Config *);

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
  
  Config_init_dir (self);
  Config_read_config (self);
  
  Config_set_lang (self);
}

/*public*/ const char *
Config_get_confdir (Config *self)
{
  return (const char *)self->dir;
}

/*public*/ const char *
Config_get_theme (Config *self)
{
  return (const char *)self->theme;
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
Config_save_file (Config *self)
{
  FILE *conf = NULL;
  char *path = NULL;

  path = malloc (CONFIG_PATH_MAX_SIZE);
  MALLOC_TEST_ERROR (path);
  
  strcpy (path, self->dir);
  strcat (path, CONFIG_FILE);
  
  conf = fopen (path, "w+");
  if (conf == NULL)
    ef_error ("open config file");

  fprintf (conf, "# Epicfail configuration file !\n");
  fprintf (conf, "# DO NOT EDIT !\n");
  
  fprintf (conf, "lang = %s\n", self->lang);
  fprintf (conf, "theme = %s\n", self->theme);

  fclose (conf);
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
  self->dico.App_menu_about = NULL;

  self->dico.About_title = NULL;
  self->dico.About_label = NULL;
  self->dico.About_button = NULL;

  self->dico.Result_title = NULL;
  self->dico.Result_label = NULL;
  self->dico.Result_button = NULL;

  self->dico.Preference_title = NULL;
  self->dico.Preference_label = NULL;
  self->dico.Preference_theme_label = NULL;
  self->dico.Preference_lang_label = NULL;
  self->dico.Preference_button = NULL;

  Config_lang_alloc (self);  
}

/*private*/ static void
Config_lang_alloc (Config *self)
{
  self->dico.App_title = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.App_title);
  
  self->dico.App_menu_about = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.App_menu_about);

  
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

  
  self->dico.Preference_title = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.Preference_title);

  self->dico.Preference_label = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.Preference_label);

  self->dico.Preference_theme_label = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.Preference_theme_label);

  self->dico.Preference_lang_label = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.Preference_lang_label);

  self->dico.Preference_button = malloc(CONFIG_STD_STRING_SIZE);
  MALLOC_TEST_ERROR (self->dico.Preference_button);

}

/*private*/ static void
Config_read_config (Config *self)
{
  char *path = NULL;
  char *name = NULL;
  char *value = NULL;
  char *buffer = NULL;
  FILE *conf = NULL;

  path = malloc (CONFIG_PATH_MAX_SIZE);
  MALLOC_TEST_ERROR (path);
  buffer = malloc (CONFIG_PATH_MAX_SIZE);
  MALLOC_TEST_ERROR (buffer);
  name = malloc (CONFIG_PATH_MAX_SIZE);
  MALLOC_TEST_ERROR (name);
  value = malloc (CONFIG_PATH_MAX_SIZE);
  MALLOC_TEST_ERROR (value);

  strcpy (path, self->dir);
  strcat (path, CONFIG_FILE);
  
  conf = fopen (path, "r");
  if (conf == NULL)
    ef_error ("fopen");

  while (fgets (buffer, CONFIG_PATH_MAX_SIZE, conf) != NULL)
    {
      if (buffer[0] == '#')
	continue;
      
      sscanf (buffer, CONFIG_FORMAT, name, value);

      if (strcmp (name, "lang") == 0)
	strcpy (self->lang, value);
      else if (strcmp (name, "theme") == 0)
	strcpy (self->theme, value);
      else
	printf ("[WARNING] Unknow config name \"%s\"\n", name);
    }

  fclose (conf);
  free (buffer);
  free (name);
  free (value);
  free (path);
}

/*private*/ static void
Config_set_lang (Config *self)
{
  strcpy (self->dico.App_title, "Epicfail (Alpha)");
  strcpy (self->dico.App_menu_about, "About");

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
  
  strcpy (self->dico.Preference_title, "Epicfail - Setting");
  strcpy (self->dico.Preference_label, "Setting");
  strcpy (self->dico.Preference_theme_label, "Theme");
  strcpy (self->dico.Preference_lang_label, "Language");
  strcpy (self->dico.Preference_button, "Save");
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
  free (self->dico.App_menu_about);
  
  free (self->dico.About_title);
  free (self->dico.About_label);
  free (self->dico.About_button);

  free (self->dico.Result_title);
  free (self->dico.Result_label);
  free (self->dico.Result_button);

  free (self->dico.Preference_title);
  free (self->dico.Preference_label);
  free (self->dico.Preference_theme_label);
  free (self->dico.Preference_lang_label);
  free (self->dico.Preference_button);
}
