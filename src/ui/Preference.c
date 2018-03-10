#include "Preference.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CONF_FORMAT "%s = %s\n"

#define HEIGHT 140
#define WIDTH 140

/*private*/ static void Preference_on_quit (GtkWidget *w, gpointer data);
/*private*/ static void Preference_init_0 (Preference *self);
/*private*/ static void Preference_new_window (Preference *self);
/*private*/ static void Preference_connect (Preference *self);

/******************************************************************************
 * Public methode                                                             *
 ******************************************************************************/

/*public*/ GType
Preference_get_type (void)
{
  static GType type = 0;

  if (type == 0)
  {
    static const GTypeInfo info = {
      sizeof (PreferenceClass), /* class_size */
      NULL,                /* base_init */
      NULL,                /* base_finalize */
      NULL,                /* class_init */
      NULL,                /* class_finalize */
      NULL,                /* class_data */
      sizeof (Preference),      /* instance_size */
      0,                   /* n_preallocs */
      NULL,                /* instance_init */
      NULL                 /* value_table */
    };
    type = g_type_register_static (G_TYPE_OBJECT, "Preference", &info, 0);
  }
  return type;
}


/*public*/ void
Preference_init (Preference *self, Config *conf)
{
  Preference_init_0 (self);

  self->conf = conf;
  self->title = self->conf->dico.Preference_title;
}

/*public*/ void
Preference_create (Preference *self)
{
  Preference_new_window (self);
  Preference_connect (self);
  Preference_show (self);
  Preference_hide (self);
}

/*public*/ void
Preference_show (Preference *self)
{
  gtk_widget_show_all(self->window);
}

/*public*/ void
Preference_hide (Preference *self)
{
  gtk_widget_hide (self->window);
}

/******************************************************************************
 * Private method                                                             *
 ******************************************************************************/

/*private*/ static void
Preference_on_quit (GtkWidget *w, gpointer data)
{
  Preference *self = (Preference *)data;

  self->window = w;
  Preference_hide (self);
}

/*private*/ void
Preference_save_setting (GtkWidget *w, gpointer data)
{
  int i = 0;
  gchar *label = NULL;
  Preference *self = (Preference *)data;

  label = malloc(256);
  MALLOC_TEST_ERROR (label);
  
  while (self->lang_radio[i] != NULL)
    {
      if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(self->lang_radio[i])))
	{
	  strcpy (self->conf->lang,
		  gtk_button_get_label (GTK_BUTTON(self->lang_radio[i])));
	  break;
	}
      i++;
    }

  i = 0;

  while (self->theme_radio[i] != NULL)
    {
      if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(self->theme_radio[i])))
	{
	  strcpy (self->conf->theme,
		  gtk_button_get_label (GTK_BUTTON(self->theme_radio[i])));
	  break;
	}      
      i++;
    }

  Config_save_file (self->conf);

  Preference_hide (self);
}

/*private*/ void
Preference_list_theme (Preference *self)
{
  int i = 0;
  char *buffer = NULL;
  DIR *conf = NULL;
  struct dirent *element = NULL;

  buffer = malloc (256);
  MALLOC_TEST_ERROR (buffer);
  strcpy (buffer, (const char *)Config_get_confdir(self->conf));
  
  conf = opendir (buffer);
  if (conf == NULL)
    ef_error ("Fail to load conf dir");

  errno = 0;
  while ((element = readdir (conf)) != NULL && errno == 0)
    {
      if (element->d_type != DT_DIR)
	continue;

      if (element->d_name[0] == '.')
	continue;
      
      if (strcmp (element->d_name, "lang") == 0)
	continue;

      self->theme_radio[i] = gtk_radio_button_new_with_label (self->theme_group, element->d_name);
      self->theme_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON(self->theme_radio[i]));

      gtk_box_pack_start (GTK_BOX (self->theme_vbox),
			  self->theme_radio[i],
			  FALSE, TRUE, 0);

      if (strcmp (element->d_name, self->conf->theme) == 0)
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(self->theme_radio[i]),
				      TRUE);
	
      i++;
    }
  
  closedir (conf);
  free (buffer);
}

/*private*/ void
Preference_list_lang (Preference *self)
{
  int i = 0;
  char *buffer = NULL;
  DIR *conf = NULL;
  struct dirent *element = NULL;

  buffer = malloc (256);
  MALLOC_TEST_ERROR (buffer);
  
  strcpy (buffer, (const char *)Config_get_confdir(self->conf));
  strcat (buffer, "/lang/");
  
  conf = opendir (buffer);
  if (conf == NULL)
    ef_error ("Fail to load conf dir");

  errno = 0;
  while ((element = readdir (conf)) != NULL && errno == 0)
    {      
      if (element->d_type != DT_REG)
	continue;

      if (element->d_name[0] == '.')
	continue;

      self->lang_radio[i] = gtk_radio_button_new_with_label (self->lang_group, element->d_name);
      self->lang_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON(self->lang_radio[i]));

      gtk_box_pack_start (GTK_BOX (self->lang_vbox),
			  self->lang_radio[i],
			  FALSE, TRUE, 0);

      if (strcmp (element->d_name, self->conf->lang) == 0)
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(self->lang_radio[i]),
				      TRUE);
	
      i++;
    }

  closedir (conf);
  free (buffer);
}

/*private*/ static void
Preference_init_0 (Preference *self)
{
  self->title = NULL;
  
  self->window = NULL;
  self->main_vbox = NULL;
  self->label = NULL;
  self->hbox = NULL;
  
  self->theme_vbox = NULL;
  self->theme_label = NULL;
  self->theme_group = NULL;

  self->lang_vbox = NULL;
  self->lang_label = NULL;
  self->lang_group = NULL;

  self->save = NULL;
  self->about = NULL;
}

/*private*/ static void
Preference_new_window (Preference *self)
{
  self->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position (GTK_WINDOW (self->window), GTK_WIN_POS_CENTER);
  gtk_window_set_title (GTK_WINDOW (self->window), self->conf->dico.Preference_title);
  gtk_window_set_default_size (GTK_WINDOW (self->window),
			       HEIGHT,
			       WIDTH);

  self->main_vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (self->window), self->main_vbox);
  
  self->label = gtk_label_new (self->conf->dico.Preference_label);
  gtk_label_set_justify (GTK_LABEL (self->label), GTK_JUSTIFY_CENTER);
  gtk_box_pack_start (GTK_BOX (self->main_vbox),
  		      self->label,
  		      FALSE, TRUE, 0);

  self->hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_start (GTK_BOX (self->main_vbox),
  		      self->hbox,
  		      FALSE, TRUE, 0);
    
  self->theme_vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start (GTK_BOX (self->hbox),
  		      self->theme_vbox,
  		      FALSE, TRUE, 0);

  self->theme_label = gtk_label_new (self->conf->dico.Preference_theme_label);
  gtk_label_set_justify (GTK_LABEL (self->theme_label), GTK_JUSTIFY_CENTER);
  gtk_box_pack_start (GTK_BOX (self->theme_vbox),
  		      self->theme_label,
  		      FALSE, TRUE, 0);

  Preference_list_theme (self);

  self->lang_vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start (GTK_BOX (self->hbox),
  		      self->lang_vbox,
  		      FALSE, TRUE, 0);

  self->lang_label = gtk_label_new ("Lang");
  gtk_label_set_justify (GTK_LABEL (self->lang_label), GTK_JUSTIFY_CENTER);
  gtk_box_pack_start (GTK_BOX (self->lang_vbox),
  		      self->lang_label,
  		      FALSE, TRUE, 0);

  Preference_list_lang (self);

  self->save = gtk_button_new_with_label ("Save");
  gtk_box_pack_start (GTK_BOX (self->main_vbox),
  		      self->save,
  		      FALSE, TRUE, 0);
}

/*private*/ static void
Preference_connect (Preference *self)
{
  g_signal_connect( G_OBJECT(self->window), "delete-event",
                    G_CALLBACK(Preference_on_quit), (gpointer)self);

  g_signal_connect( G_OBJECT(self->save), "clicked",
                    G_CALLBACK(Preference_save_setting), (gpointer)self);
}
