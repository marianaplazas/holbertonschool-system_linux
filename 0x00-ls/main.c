#include "lslib.h"
/**
 *
 *
 */
int main(int argc, char *argv[])
{
	DIR *mydir;
	struct dirent *myfile;
	struct stat mystat;
	char *directory = ".";
	if (argc > 1)
	{
		directory = argv[1];
		mydir = opendir(argv[1]);
	}
	else
		mydir = opendir(directory);
	char buf[512];
	while((myfile = readdir(mydir)) != NULL)
	{
		sprintf(buf, "%s/%s", directory, myfile->d_name);
		//stat(buf, &mystat);
		//printf("%zu",mystat.st_size);
		printf("%s\n", myfile->d_name);
	}
	closedir(mydir);
}
