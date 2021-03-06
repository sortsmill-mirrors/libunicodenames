/*
 * The example program of the uninm_find_names_db(3) manpage.
 *
 * Prints names and annotations corresponding to code points 0 to 999.
 *
 *
 * Copyright (C) 2013 Khaled Hosny and Barry Schwartz
 * 
 * Copying and distribution of this file, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved.  This file is offered as-is,
 * without any warranty.
 */

#include <libunicodenames.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int
main (int argc, char **argv)
{
  unsigned int codepoint;
  char *dbfile;
  uninm_names_db db;
  const char *name, *annot;

  setlocale (LC_ALL, "");
  dbfile = uninm_find_names_db (NULL);
  if (dbfile == NULL)
    exit (1);
  db = uninm_names_db_open (dbfile);
  free (dbfile);
  if (db == NULL)
    exit (1);
  for (codepoint = 0; codepoint <= 999; codepoint++)
    {
      name = uninm_name (db, codepoint);
      annot = uninm_annotation (db, codepoint);
      name = (name == NULL) ? "--none--" : name;
      annot = (annot == NULL) ? "--none--" : annot;
      printf ("--\ncode point: %u\nname: %s\nannotation:\n%s\n",
	      codepoint, name, annot);
    }
  uninm_names_db_close (db);
}
