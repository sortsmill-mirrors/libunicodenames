/*
 * The example program of the uninm_find_blocks_db(3) manpage.
 *
 * Prints the start points, end points, and names of the Unicode
 * blocks.
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
  size_t numblocks, i;
  unsigned int start, end;
  char *dbfile;
  uninm_blocks_db db;
  const char *name;

  setlocale (LC_ALL, "");
  dbfile = uninm_find_blocks_db (NULL);
  if (dbfile == NULL)
    exit (1);
  db = uninm_blocks_db_open (dbfile);
  free (dbfile);
  if (db == NULL)
    exit (1);
  numblocks = uninm_num_blocks (db);
  for (i = 0; i < numblocks; i++)
    {
      start = uninm_block_start (db, i);
      end = uninm_block_end (db, i);
      name = uninm_block_name (db, i);
      if (name == NULL)
	exit (2);
      printf ("--\ni: %u\nstart: %d\nend: %d\nblock name: %s\n",
	      (unsigned int) i, start, end, name);
    }
  uninm_blocks_db_close (db);
}
