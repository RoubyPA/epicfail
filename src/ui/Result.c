#include "Result.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../error/error.h"

#define HEIGHT 400
#define WIDTH 300

#define EPICFAIL    0.95
#define FAIL        0.50
#define EPICSUCCESS 0.05

#define IMG_EPICFAIL    "/epicfail.png"
#define IMG_FAIL        "/fail.png"
#define IMG_SUCCESS     "/success.png"
#define IMG_EPICSUCCESS "/epicsuccess.png"

/*private*/ static void on_quit (GtkWidget *w, gpointer data);
/*private*/ static void Result_init_0 (Result *self);
/*private*/ static void Result_hide (Result *self);
/*private*/ static void Result_new_window (Result *self);
/*private*/ static void Result_create_image (Result *self);
/*private*/ static void Result_create_label (Result *self);
/*private*/ static void Result_update_label (Result *self, char *str);
/*private*/ static void Result_connect (Result *self);
/*private*/ static void Result_update_image (Result *self, int dice, int value);

  
/******************************************************************************
 * Public method                                                              *
 ******************************************************************************/

/*public*/ GType
Result_get_type (void)
{
  static GType type = 0;

  if (type == 0)
  {
    static const GTypeInfo info = {
      sizeof (ResultClass), /* class_size */
      NULL,                 /* base_init */
      NULL,                 /* base_finalize */
      NULL,                 /* class_init */
      NULL,                 /* class_finalize */
      NULL,                 /* class_data */
      sizeof (Result),      /* instance_size */
      0,                    /* n_preallocs */
      NULL,                 /* instance_init */
      NULL                  /* value_table */
    };
    type = g_type_register_static (G_TYPE_OBJECT, "Result", &info, 0);
  }
  return type;
}

/*public*/ void
Result_init (Result *self, Config *conf)
{
  Result_init_0 (self);

  self->conf = conf;
  self->title = self->conf->dico.Result_title;
}

/*public*/ void
Result_create (Result *self)
{
  Result_new_window (self);
  Result_connect (self);
  Result_hide (self);
}

/*public*/ void
Result_update_with_dice_result (Result *self, int dice, int value)
{
  char *buffer = malloc (256);
  MALLOC_TEST_ERROR (buffer);

  sprintf (buffer, "\n<span font_desc=\"bold\">%d</span> / %d", value, dice);
  
  Result_update_label(self, buffer);
  Result_update_image(self, dice, value);

  Result_show (self);
  
  free (buffer);
}

/*public*/ void
Result_show (Result *self)
{ 
  gtk_widget_show_all (self->window);
}

/******************************************************************************
 * Private method                                                             *
 ******************************************************************************/

/*private*/ static void
on_quit (GtkWidget *w, gpointer data)
{
  Result *self = data;
  
  self->window = w;
  Result_hide (self);
}

/*private*/ static void
Result_init_0 (Result *self)
{
  self->title = NULL;
  
  self->window = NULL;
  self->m_vbox = NULL;
  self->label = NULL;
  self->image = NULL;
}

/*private*/ static void
Result_hide (Result *self)
{
  gtk_widget_hide (self->window);
}

/*private*/ static void
Result_new_window (Result *self)
{
  self->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title (GTK_WINDOW(self->window), self->title);
  gtk_window_set_position (GTK_WINDOW (self->window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW(self->window),
			       HEIGHT, WIDTH);
  gtk_window_set_resizable (GTK_WINDOW(self->window), FALSE);
  
  self->m_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
  self->label = gtk_label_new ("");

  Result_create_image (self);
  Result_create_label (self);

  gtk_container_add (GTK_CONTAINER (self->window), self->m_vbox);
  gtk_box_pack_start (GTK_BOX (self->m_vbox), self->image,
		      FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (self->m_vbox), self->label,
		      FALSE, TRUE, 0);
}

/*private*/ static void
Result_create_image (Result *self)
{
  char *buffer = malloc (256); /* TODO global macro */
  MALLOC_TEST_ERROR (buffer);

  strcpy(buffer, Config_get_confdir(self->conf));
  strcat(buffer, "/");
  strcat(buffer, Config_get_theme(self->conf));
  strcat(buffer, IMG_EPICFAIL);
    
  self->image = gtk_image_new_from_file (buffer);

  free (buffer);
}

/*private*/ static void
Result_create_label (Result *self)
{
  gchar *buffer;
  
  buffer = g_locale_to_utf8 (self->conf->dico.Result_label, -1, NULL, NULL, NULL);
  gtk_label_set_justify (GTK_LABEL (self->label), GTK_JUSTIFY_CENTER);
  gtk_label_set_markup (GTK_LABEL (self->label), buffer);
}

/*private*/ static void
Result_update_label (Result *self, char *str)
{
  gchar *buffer;
  
  buffer = g_locale_to_utf8 (str, -1, NULL, NULL, NULL);
  gtk_label_set_markup (GTK_LABEL (self->label), buffer);
}

/*private*/ static void
Result_update_image (Result *self, int dice, int value)
{
  float result = 0;
  char *buffer = malloc (256);
  MALLOC_TEST_ERROR (buffer);

  result = (float)value / (float)dice;
  
  strcpy(buffer, Config_get_confdir(self->conf));
  strcat(buffer, "/");
  strcat(buffer, Config_get_theme(self->conf));
  
  if (result <= EPICSUCCESS)
    strcat (buffer, IMG_EPICSUCCESS);
  else if (result <= FAIL)
    strcat (buffer, IMG_SUCCESS);
  else if (result > FAIL && result < EPICFAIL)
    strcat (buffer, IMG_FAIL);
  else
    strcat (buffer, IMG_EPICFAIL);
  
  gtk_image_set_from_file (GTK_IMAGE(self->image),
			   buffer);

  free (buffer);
}

/*private*/ static void
Result_connect (Result *self)
{
  g_signal_connect( G_OBJECT(self->window), "delete-event",
                    G_CALLBACK(on_quit), (gpointer)self);
}
