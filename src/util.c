/*
 * =====================================================================================
 *
 *       Filename:  util.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/30/13 09:31:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <jnxc_headers/jnxfile.h>
#define FILEPATH "/.dnoted/dnoted.conf"
typedef struct kvp_node{
	char *key;
	char *value;
	struct kvp_node *next;
}kvp_node;
char *get_cwd(void)
{
	char *path = malloc(1023 *sizeof(char));
	char* ret = getcwd(path,1024);
	if(ret == NULL)
	{
		perror("get_cwd: ");
		exit(1);
	}
}
char *file_path(void)
{
	char *buffer = malloc(2048 *sizeof(char));
	bzero(buffer,2048 * sizeof(char));
	char *parent_dir = getenv("HOME");
	strncpy(buffer,parent_dir,strlen(parent_dir));
	strncat(buffer,FILEPATH,strlen(FILEPATH));
	return buffer;
}
void write_message(char *message)
{
	char *write_path = file_path();
	char *cwd = get_cwd();
#ifdef DEBUG
	printf("Write path %s\n",write_path);
	printf("CWD %s\n",cwd);
	printf("Message %s\n",message);
#endif
	/*-----------------------------------------------------------------------------
	 *  Write into the file path
	 *-----------------------------------------------------------------------------*/
	char payload[2048];
	strncpy(payload,cwd,strlen(cwd));
	strncat(payload,"=",1);
	strncat(payload,message,strlen(message));
#ifdef DEBUG
	printf("Payload %s\n",payload);
#endif
	FILE *fp = fopen(write_path,"a");
	if(fp == NULL)
	{
		perror("write_message: ");
		exit(1);
	}
	int size = strlen(payload);
	fwrite(payload,size,1,fp);
	//Adding end of line
	fwrite("\n",1,1,fp);
	fclose(fp);

	free(write_path);
	free(cwd);
}

kvp_node *pull_kvp_from_file(char *path)
{
	char *delimiter = "=";
	FILE *fp;
	if((fp = fopen(path,"r+")) == NULL)
	{
		perror("pull_kvp_from_file: ");
		exit(1);
	}
	kvp_node *list = NULL, **nextp = &list;
	char buffer[1024];
	while(fgets(buffer,sizeof buffer, fp) != NULL)
	{
		char *key = strtok(buffer,delimiter);
		char *value = strtok(NULL,delimiter);
		if(value == NULL) { continue; }
		kvp_node* node;
		node = malloc(sizeof(kvp_node));
		node->key = malloc(strlen(key) + 1);
		node->value = malloc(strlen(value) +1);
		strcpy(node->key,key);
		strcpy(node->value,value);
		if(node->value[strlen(node->value)-1] == '\n'){
			node->value[strlen(node->value) -1] = 0;
		}
		node->next = NULL;
		*nextp = node;
		nextp = &node->next;
	}
	return list;
}
void delete_message(void)
{
	char *cwd = get_cwd();
	char *write_path = file_path();
	
	kvp_node *head = pull_kvp_from_file(write_path);	

	while(head)
	{
		printf("Key %s Value %s\n",head->key,head->value);
		if(strcmp(head->key,cwd) != 0)
		{
			//add it to our new file
			FILE *fp;
			if((fp = fopen("dnoted.temp","w")) == NULL)
			{
				perror("delete_message: ");
				exit(1);
			}
			//Create a payload similar to write_message	
			char payload[2048];
			strncpy(payload,head->key,strlen(head->key));
			strncat(payload,"=",1);
			strncat(payload,head->value,strlen(head->value));		
			
			int size = strlen(payload);
			fwrite(payload,size,1,fp);
			//Adding end of line
			fwrite("\n",1,1,fp);
			fclose(fp);
		}
		head = head->next; 
	}

	/*-----------------------------------------------------------------------------
	 *   now we removed the original write_path
	 *-----------------------------------------------------------------------------*/
	remove(write_path);	
	/*-----------------------------------------------------------------------------
	 *  Replace with our new conf file
	 *-----------------------------------------------------------------------------*/
	system("mv dnoted.temp $HOME/.dnoted/dnoted.conf");
	free(write_path);
	free(cwd);
}
void read_message()
{
	char *write_path = file_path();
	char *cwd = get_cwd();

	kvp_node *head = pull_kvp_from_file(write_path);	

	while(head)
	{
		if(strcmp(head->key,cwd) == 0)
		{
			printf("dnoted says: %s\n",head->value);
		}	
		head = head->next;
	}	
	free(write_path);
	free(cwd);
}
