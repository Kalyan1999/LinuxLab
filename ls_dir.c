#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void printall(struct stat f_stat);

int main()
{

    printf("Give directory name: \n");
    char dname[100];
    scanf("%s",dname);
    DIR *dir=opendir(dname);
    struct dirent* d;
    if(dir)
    while((d=readdir(dir))!=NULL)
    {
     printf("%s ",d->d_name);
     switch(d->d_type)
     {
       case DT_UNKNOWN:printf("unknown");
       break;  //unknown file type
       
       case DT_REG:printf("r");
       break; //regular file
       
       case DT_DIR:printf("d");
       break; //directory file
       
       case DT_FIFO:printf("f");
       break; //fifo file
       
       case DT_SOCK:printf("s");
       break; //socket file
       
       case DT_CHR:printf("c");
       break; //character device
       
       case DT_BLK:printf("b");
       break; //block device
       
       case DT_LNK:printf("l");
       break; //symbolic link
     }
     
       struct stat f_stat;
       stat(d->d_name,&f_stat);
       printall(f_stat);
//prints ->(user,group,other permissions),(no of hard links),(user id),(group id),(size of file),(time of modification)
}
}

void printall(struct stat f_stat)
{
char str[10];
//user
str[0]=f_stat.st_mode&S_IRUSR?'r':'-';
str[1]=f_stat.st_mode&S_IWUSR?'w':'-';
str[2]=f_stat.st_mode&S_IXUSR?'x':'-';
//group
str[3]=f_stat.st_mode&S_IRGRP?'r':'-';
str[4]=f_stat.st_mode&S_IWGRP?'w':'-';
str[5]=f_stat.st_mode&S_IXGRP?'x':'-';
//others
str[6]=f_stat.st_mode&S_IROTH?'r':'-';
str[7]=f_stat.st_mode&S_IWOTH?'w':'-';
str[8]=f_stat.st_mode&S_IXOTH?'x':'-';
str[9]='\0';
printf("%s ",str);

//hard link
printf("%ld ",f_stat.st_nlink);
//group and user id -> include pwd.h and grp.h
struct passwd *pw=getpwuid(f_stat.st_uid);
struct group *gr=getgrgid(f_stat.st_gid);
printf("%s %s ",pw->pw_name,gr->gr_name);
//size of file
printf("%ld ",f_stat.st_size);
//time of modification
printf("%s ",ctime(&f_stat.st_mtime));
}
