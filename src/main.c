/*
 * Copyright (C) 2018 Pierre-Antoine Rouby
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "ui/Application.h"

void
usage (char **argv)
{
  printf ("Usage: %s <options>\n", argv[0]);
  printf ("Options:\n");
  printf ("   --en\t English\n");
  printf ("   --fr\t French\n");
  printf ("   -h --help\t Show this help\n");
  printf ("   -v --version\t Version\n");
  exit (EXIT_FAILURE);
}

void
version (void)
{
  printf ("EpicFail: Version 0.2.0 (Alfa)\n");
  printf ("   Build:       %s(%s)\n", __DATE__, __TIME__);
  printf ("   License:     Gnu GPLv3\n");
  printf ("   Source code: <https://github.com/RoubyPA/epicfail>\n");
}

void
options (int argc, char **argv)
{
  int longindex;
  char optchar;
  char *shortopt = "hvef";
  struct option const longopt[] = {
    {"en",      no_argument, NULL, 'e'},
    {"fr",      no_argument, NULL, 'f'},
    {"help",    no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'v'},
    {NULL, 0, NULL, 0}
  };

  while ((optchar = getopt_long(argc, argv, shortopt,
				longopt, &longindex)) != -1)
    {
      switch (optchar)
	{
	case 'h':
	  usage (argv);
	  break;
	case 'v':
	  version ();
	  break;
	case 'e':
	  printf ("Not implemented yet\n");
	  break;
	case 'f':
	  printf ("Not implemented yet\n");
	  break;
	default:
	  printf ("Not implemented yet\n");
	  break;
	}
    }
}

int
main (int argc, char **argv, char **env)
{
  Application *app;

  options (argc, argv);
  
  app = g_object_new (TYPE_APPLICATION, NULL);

  gtk_init(&argc, &argv);
  
  Application_init (app, argc, argv, env);
  Application_create (app);
    
  gtk_main ();

  Application_finalize (app);
  g_object_unref (app);
  
  exit (EXIT_SUCCESS);
}
