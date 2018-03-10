#include "Application.h"
#include "../error/error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HEIGHT 200
#define WIDTH 400

#define IMG_FORMAT "%s/d%.3d.png"

typedef struct _on_click_data on_click_data;
struct _on_click_data {
  Application *self;
  Dice *dice;
};

/*private*/ static void on_quit (GtkWidget *w, gpointer data);
/*private*/ static void Application_init_0 (Application *self);
/*private*/ static void Application_init_alloc (Application *self);
/*private*/ static void Application_show (Application *self);
/*private*/ static void Application_new_window (Application *self);
/*private*/ static void Application_create_menu (Application *self);
/*private*/ static void Application_connect (Application *self);
/*private*/ static void Application_create_buttons (Application *self);
/*private*/ static void Application_button_connect (Application *self, Dice *dice, int index);

/******************************************************************************
 * Public methode                                                             *
 ******************************************************************************/

/*public*/ GType
Application_get_type (void)
{
  static GType type = 0;

  if (type == 0)
  {
    static const GTypeInfo info = {
      sizeof (ApplicationClass), /* class_size */
      NULL,                      /* base_init */
      NULL,                      /* base_finalize */
      NULL,                      /* class_init */
      NULL,                      /* class_finalize */
      NULL,                      /* class_data */
      sizeof (Application),      /* instance_size */
      0,                         /* n_preallocs */
      NULL,                      /* instance_init */
      NULL                       /* value_table */
    };
    type = g_type_register_static (G_TYPE_OBJECT, "Application", &info, 0);
  }
  return type;
}

/*public*/ void
Application_init (Application *self, int argc, char **argv, char **env)
{
  Application_init_0 (self);

  /* init Config */
  self->conf = g_object_new (TYPE_CONFIG, NULL);
  Config_init (self->conf, argc, argv, env);
  
  /* init About window */
  self->about = g_object_new (TYPE_ABOUT, NULL);
  About_init (self->about, self->conf);
  About_create (self->about);
  
  /* init Result window */
  self->result = g_object_new (TYPE_RESULT, NULL);
  Result_init (self->result, self->conf);
  Result_create (self->result);

  self->pref = g_object_new (TYPE_PREFERENCE, NULL);
  Preference_init (self->pref, self->conf);
  Preference_create (self->pref);
  
  self->title = self->conf->dico.App_title;
}

/*public*/ void
Application_create (Application *self)
{
  Application_new_window (self);
  Application_create_menu (self);
  Application_create_buttons (self);
  Application_connect (self);
  Application_show (self);
}

/*public*/ void
Application_finalize (Application *self)
{
  Config_finalize (self->conf);
  g_object_unref (self->conf);
}

/******************************************************************************
 * Private methode                                                            *
 ******************************************************************************/

/*private*/ static void
on_click (GtkWidget *w, gpointer data)
{
  on_click_data *oc_data = (on_click_data *)data;
  Application *self = oc_data->self;
  Dice *dice = oc_data->dice;

  if (dice != NULL)
    {
      Result_show (self->result);  
      Result_update_with_dice_result (self->result,
				      dice->value,
				      Dice_roll (dice)); 
    }
  else
    {
      Preference_show (self->pref);  
    }
}

/*private*/ static void
menu_on_click (GtkWidget *w, gpointer data)
{
  Application *self = data;

  About_show (self->about);
}

/*private*/ static void
on_quit (GtkWidget *w, gpointer data)
{
    gtk_main_quit();
}

/*private*/ static void
Application_init_0 (Application *self)
{
  int i;

  self->title = NULL;

  self->window = NULL;
  self->m_hbox = NULL;
  self->l_vbox = NULL;
  self->r_vbox = NULL;
  self->menu_bar = NULL;
  self->menu_item = NULL;

  for (i = 0 ; i <= MAX_DICE_NUM ; i++)
    {
      self->buttons[i].dice = NULL;
      self->buttons[i].button = NULL;
      self->buttons[i].image = NULL;
    }

  Application_init_alloc (self);
}

/*private*/ static void
Application_init_alloc (Application *self)
{
  //self->title = malloc (32);
}

/*private*/ static void
Application_show (Application *self)
{
  gtk_widget_show_all(self->window);
}

/*private*/ static void
Application_new_window (Application *self)
{ 
  self->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title (GTK_WINDOW(self->window), self->title);
  gtk_window_set_default_size (GTK_WINDOW(self->window),
			       HEIGHT, WIDTH);
  gtk_window_set_resizable (GTK_WINDOW(self->window), FALSE);

  self->m_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  self->m_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  self->l_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  self->r_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
}

/*private*/ static void
Application_create_menu (Application *self)
{
  gtk_container_add(GTK_CONTAINER(self->window), self->m_vbox);

  self->menu_bar = gtk_menu_bar_new ();
  self->menu_item = gtk_menu_item_new_with_label (self->conf->dico.App_menu_about);

  gtk_menu_shell_append(GTK_MENU_SHELL(self->menu_bar), self->menu_item);
  gtk_box_pack_start(GTK_BOX(self->m_vbox),
		     self->menu_bar, FALSE, FALSE, 0);

  g_signal_connect(G_OBJECT(self->menu_item), "activate",
		   G_CALLBACK(menu_on_click), (gpointer)self);
}

/*private*/ static void
Application_create_buttons (Application *self)
{
  int index = -1;
  int dice_num[] = {4, 6, 8, 10, 12, 20, 100, 0, -1};
  char *path = malloc(256);
  char *buffer = malloc(256);
  MALLOC_TEST_ERROR(path);
  MALLOC_TEST_ERROR(buffer);

  strcpy (path, (const char *)Config_get_confdir (self->conf));
  strcat (path, "/");
  strcat (path, (const char *)Config_get_theme (self->conf));
  
  gtk_container_add(GTK_CONTAINER(self->m_vbox), self->m_hbox);
  gtk_container_add(GTK_CONTAINER(self->m_hbox), self->l_vbox);
  gtk_container_add(GTK_CONTAINER(self->m_hbox), self->r_vbox);

  while (dice_num[++index] >= 0)
    {
      self->buttons[index].button = gtk_button_new ();
  
      sprintf (buffer, IMG_FORMAT, path, dice_num[index]);
      self->buttons[index].image = gtk_image_new_from_file (buffer);
   
      gtk_box_pack_start (GTK_BOX (index%2 == 0 ? self->l_vbox: self->r_vbox),
  			  self->buttons[index].button,
  			  FALSE, TRUE, 0);
      gtk_container_add (GTK_CONTAINER (self->buttons[index].button),
  			 self->buttons[index].image);

      if (dice_num[index] > 0)
	{
	  self->buttons[index].dice = g_object_new (TYPE_DICE, NULL);
	  if (Dice_set_value (self->buttons[index].dice, dice_num[index]) == -1)
	    ef_error ("Dice init");
	  
	  Application_button_connect (self, self->buttons[index].dice, index);
	}
      else
	{
	  Application_button_connect (self, NULL, index);
	}
	
    }
  
  free (buffer);
}

/*private*/ static void
Application_connect (Application *self)
{
  g_signal_connect( G_OBJECT(self->window), "delete-event",
                    G_CALLBACK(on_quit), (gpointer)self);
}

/*private*/ static void
Application_button_connect (Application *self, Dice *dice, int index)
{
  on_click_data *data = malloc (sizeof (on_click_data));
  MALLOC_TEST_ERROR(data);

  data->self = self;
  data->dice = dice;

  g_signal_connect(G_OBJECT(self->buttons[index].button), "clicked",
		   G_CALLBACK(on_click), (gpointer)data);
 }
