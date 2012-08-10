/*
  semtool.c - simple semaphore manipulation utility.

  always takes a single argument, the name of a semaphore (with leading slash)
  when called as:
     semcreate - creates the named semaphore (whether or not it already exists)
     semdelete - deletes the named semaphore
     semwait -   waits on the named semaphore
     sempost -   posts the named semaphore
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int
main (int argc, char *argv[]) {
  int rv;
  sem_t *sem;

  if (argc == 2) {

    if (0 == strcmp(argv[0], "semcreate")) {
      sem = sem_open(argv[1], O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO, 0);
      if (sem == SEM_FAILED) {
	fprintf(stderr, "Error: unable to create semaphore %s.  Errno=%d\n", argv[1], errno);
	return 1;
      }
      sem_close(sem);
      return 0;
    } else if (0 == strcmp(argv[0], "semdelete")) {
      rv = sem_unlink(argv[1]);
      if (rv != 0) {
	fprintf(stderr, "Error: unable to delete semaphore %s.  Errno=%d\n", argv[1], errno);
	return 1;
      }
      return 0;
    } else if (0 == strcmp(argv[0], "semwait")) {
      sem = sem_open(argv[1], 0);
      if (sem == SEM_FAILED) {
	fprintf(stderr, "Error: unable to open semaphore %s for waiting.  Errno=%d\n", argv[1], errno);
	return 1;
      }
      rv = sem_wait(sem);
      sem_close(sem);
      if (rv) {
	fprintf(stderr, "Error: waiting for semaphore %s returned errno=%d\n", argv[1], errno);
	return 1;
      }
      return 0;
    } else if (0 == strcmp(argv[0], "sempost")) {
      sem = sem_open(argv[1], 0);
      if (sem == SEM_FAILED) {
	fprintf(stderr, "Error: unable to open semaphore %s for posting.  Errno=%d\n", argv[1], errno);
	return 1;
      }
      rv = sem_post(sem);
      sem_close(sem);
      if (rv) {
	fprintf(stderr, "Error: posting semaphore %s returned errno=%d\n", argv[1], errno);
	return 1;
      }
      return 0;
    } 
    puts ("Usage:\n"
	  "\n"
	  "semcreate /SEMNAME - create a named semaphore\n"
	  "semdelete /SEMNAME - delete a named semaphore\n"
	  "semwait /SEMNAME - wait for someone to post to named semaphore\n"
	  "sempost /SEMNAME - post a named semaphore\n"
	  );
  }
}    
