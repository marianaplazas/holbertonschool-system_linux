#include "hls.h"

/**
 * print_file_long - prints a single file according to options
 * @param: the parameter struct
 * @file: the file to print
 * @sizes: print field widths
 */
void print_file_long(Param *param, File *file, size_t *sizes)
{
	struct passwd *usr = getpwuid(file->stat.st_uid);
	struct group *grp = getgrgid(file->stat.st_gid);

	(void)param;
	printf("%c%c%c%c%c%c%c%c%c%c %-*lu ",
		is_dir(file) ? 'd' : S_ISLNK(file->stat.st_mode) ? 'l' : '-',
		RUSR, WUSR, XUSR, RGRP, WGRP, XGRP, ROTH, WOTH, XOTH,
		(int)sizes[0], file->stat.st_nlink);

	if (usr)
		printf("%-*s ", (int)sizes[1], usr->pw_name);
	else
		printf("%*u ", (int)sizes[1], file->stat.st_uid);

	if (grp)
		printf("%-*s ", (int)sizes[2], grp->gr_name);
	else
		printf("%*u ", (int)sizes[2], file->stat.st_gid);
	printf("%*lu %s %s", (int)sizes[3],
		file->stat.st_size, sprint_time(file), base_name(file->name));
	if (S_ISLNK(file->stat.st_mode))
	{
		char buf[256] = {0};

		readlink(file->name, buf, 256);
		printf(" -> %s", buf);
	}
	printf("\n");
}


/**
 * get_long_format_field_sizes - for alignment
 * @param: the parameter struct
 * @sizes: the array to fill with field widths
 * @omit_dirs: true if ignore dirs
 */
void get_long_format_field_sizes(Param *param, size_t *sizes, int omit_dirs)
{
	size_t i, len;
	struct passwd *usr;
	struct group *grp;
	struct File *file;

	for (i = 0; i < param->files_i; i++)
	{
		file = &param->files[i];
		if (!omit_dirs || !is_dir(file))
		{
			usr = getpwuid(file->stat.st_uid);
			grp = getgrgid(file->stat.st_gid);

			len = _strlen(convert_number(file->stat.st_nlink, 10, 0));
			sizes[0] = MAX(sizes[0], len);

			len = _strlen(usr ? usr->pw_name :
				convert_number(file->stat.st_uid, 10, 0));
			sizes[1] = MAX(sizes[1], len);

			len = _strlen(grp ? grp->gr_name :
				convert_number(file->stat.st_gid, 10, 0));
			sizes[2] = MAX(sizes[2], len);

			len = _strlen(convert_number(file->stat.st_size, 10, 0));
			sizes[3] = MAX(sizes[3], len);
		}
	}
}
