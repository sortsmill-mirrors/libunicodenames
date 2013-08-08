/*
 * The example program of the uninm_find_blocks_db(3) manpage.
 *
 * Prints the block start and end points and their names.
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
