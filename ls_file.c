#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<stdlib.h>

int main()
{
struct stat st;
struct passwd *pw;
struct group *gr;
if(stat("sample.txt",&st) < 0)
{
printf("stat error");
}

if(S_ISREG(st.st_mode))
printf("-");
else if(S_ISDIR(st.st_mode))
printf("d");
else if(S_ISCHR(st.st_mode))
printf("c");
else if(S_ISBLK(st.st_mode))
printf("b");
else if(S_ISFIFO(st.st_mode))
printf("p");
else if(S_ISLNK(st.st_mode))
printf("L");
else if(S_ISSOCK(st.st_mode))
printf("s");

    char perms[100];

    perms[0] = (S_IRUSR & st.st_mode) ? 'r' : '-';
    perms[1] = (S_IWUSR & st.st_mode) ? 'w' : '-';
    perms[2] = (S_IXUSR & st.st_mode) ? 'x' : '-';
    perms[3] = (S_IRGRP & st.st_mode) ? 'r' : '-';
    perms[4] = (S_IWGRP & st.st_mode) ? 'w' : '-';
    perms[5] = (S_IXGRP & st.st_mode) ? 'x' : '-';
    perms[6] = (S_IROTH & st.st_mode) ? 'r' : '-';
    perms[7] = (S_IWOTH & st.st_mode) ? 'w' : '-';
    perms[8] = (S_IXOTH & st.st_mode) ? 'x' : '-';
    perms[9] = '\0';

printf("%s",perms);
printf(" %ld ",(long)st.st_nlink );
pw = getpwuid(st.st_uid);
gr = getgrgid(st.st_gid);
printf(" %s ",pw->pw_name );
printf(" %s ",gr->gr_name );
printf(" %lld ",(long long)st.st_size );
printf(" %s ",ctime(&st.st_ctime));
printf("\n");
}
