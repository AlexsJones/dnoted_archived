/*
 * =====================================================================================
 *
 *       Filename:  dnoted.c
 *
 *    Description:  dnoted is a program for leaving yourself directory messages
 *
 *        Version:  1.0
 *        Created:  05/30/13 09:10:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "util.h"


void usage()
{
  printf("******************************\n");
  printf("*          DNOTED            *\n");
  printf("* Leave messages to yourself *\n");
  printf("* Options:                   *\n");
  printf("* -a [New message]           *\n");
  printf("* -d Deletes current message *\n");
  printf("******************************\n");
  exit(0);
}
int main(int argc, char **argv)
{
  int i;
  while((i = getopt(argc, argv, "a:dhp")) != -1)
  {
    switch(i)
    {
      case 'h':
        usage();
        break;
      case 'a':
        write_message(optarg);
        printf("dnoted added message!\n");
        break;
      case 'd':
        delete_message();
        printf("dnoted cleared everything from this directory!\n");
        break;
      case 'p':
        read_message();
        break;
      default:
        usage();
        break;
    }
  }
  return 0;
}
