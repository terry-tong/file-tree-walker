/*
Terry Tong
File Tree Walker
*/

#include <dirent.h> 
#include <stdio.h>
#include <errno.h>
#include "apue.h"



static void dirExplorer(char *, char *, long int *, int *);
int main(int argc, char *argv[]) {
	int result;
	char indent[100] = "";
	long int space = 0;
	int count = 0;
	if (argc != 2)
		err_quit("Usage: ./file-tree-walker <directory>");
	printf("Directory listing of %s:\n", argv[1]);
	printf("\n");
	dirExplorer(argv[1], indent, &space, &count);
	printf("Total space usage: %ld\n", space);
	printf("Total number of files: %d\n", count);
	printf("\n");
	printf("Done.\n");
	return(0);
}

void dirExplorer(char *basePath, char *indent, long int *space, int *count) {
	DIR *d;
	struct dirent *dir;
	struct stat statbuf;
	if ((d = opendir(basePath)) == NULL)
		err_quit("Error: Directory does not exist");
	char filePtr[100] = "";
	char newPath[100] = "";
	char newIndent[100] = "";
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (dir->d_type == DT_REG) {
				printf("%s%s", indent, dir->d_name);
				strcpy(filePtr, basePath);
				strcat(filePtr, "/");
				strcat(filePtr, dir->d_name);
				lstat(filePtr, &statbuf);
				printf(" %ld\n", statbuf.st_size);
				strcpy(filePtr,basePath);
				(*count)++;
				*space += statbuf.st_size;
			}
			if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
				continue;
			}
			if (dir->d_type == DT_DIR) {
				printf("%s%s /\n", indent, dir->d_name);
				strcpy(newPath, basePath);
				strcat(newPath, "/");
				strcat(newPath, dir->d_name);
				strcpy(newIndent, indent);
				strcat(newIndent, "    ");
				
				/* 
				If number and size of folders need to be
				taken into account, please uncomment the code below
				*/
				
				//(*count)++;
				//*space += statbuf.st_size;
				
				dirExplorer(newPath, newIndent, space, count);
				strcpy(newIndent, indent);
			}
		}
		closedir(d);
	}
}
