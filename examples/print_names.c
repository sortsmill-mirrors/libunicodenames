/*
 * The example program of the uninm_find_names_db(3) manpage.
 *
 * Prints names and annotations corresponding to code points 0 to 999.
 *
 * Compile with
 *
 *    cc -o print_names `pkg-config --cflags libunicodenames` \
 *      print_names.c `pkg-config --libs libunicodenames`
 */

#include <libunicodenames.h>
#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char **argv)
{
  unsigned int codepoint;
  char *dbfile;
  uninm_names_db db;
  const char *name, *annot;

  dbfile = uninm_find_names_db (NULL);
  if (dbfile == NULL)
    exit (1);
  db = uninm_names_db_open (dbfile);
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
