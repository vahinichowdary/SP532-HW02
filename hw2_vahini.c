#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

char *filetype(unsigned char type)
{
    char *str;
    switch (type)
    {
    case DT_BLK:
        str = "block device";
        break;
    case DT_CHR:
        str = "character device";
        break;
    case DT_DIR:
        str = "directory";
        break;
    case DT_FIFO:
        str = "named pipe (FIFO)";
        break;
    case DT_LNK:
        str = "symbolic link";
        break;
    case DT_REG:
        str = "regular file";
        break;
    case DT_SOCK:
        str = "UNIX domain socket";
        break;
    case DT_UNKNOWN:
        str = "unknown file type";
        break;
    default:
        str = "UNKNOWN";
    }
    return str;
}

/* FUNCTION POINTER */
int fun(int a)
{
    return a;
}

/* For Regular */
int recursive(DIR *parentDir, char *path)
{
    struct dirent *dirent;
    int count = 1;
    char *duplicatePath = (char *)malloc(2000);

    parentDir = opendir(path);
    if (parentDir == NULL)
    {
        printf("Error opening directory '%s'\n", dirent->d_name);
        exit(-1);
    }
    while ((dirent = readdir(parentDir)) != NULL)
    {
        if (dirent->d_type == DT_DIR)
        {
            if (strcmp(dirent->d_name, ".") == 0 || (strcmp(dirent->d_name, "..") == 0))
            {
                continue;
            }

            strcpy(duplicatePath, path);
            duplicatePath = strcat(duplicatePath, "/");
            duplicatePath = strcat(duplicatePath, dirent->d_name);
            printf("[%d] %s (%s)\n", count, dirent->d_name, filetype(dirent->d_type));
            count++;
            recursive(parentDir, duplicatePath);
        }
        if (dirent->d_type != DT_DIR)
        {
            printf("    ");
            printf("[%d] %s (%s)\n", count, dirent->d_name, filetype(dirent->d_type));
            count++;
        }
    }
    closedir(parentDir);
    return 0;
}

/* For -S */
int recursiveS(DIR *parentDir, char *path)
{
    struct stat buf;
    struct dirent *dirent;
    int count = 1;
    char *duplicatePath = (char *)malloc(2000);
    parentDir = opendir(path);
    if (parentDir == NULL)
    {
        printf("Error opening directory '%s'\n", dirent->d_name);
        exit(-1);
    }
    while ((dirent = readdir(parentDir)) != NULL)
    {
         strcpy(duplicatePath, path);
            duplicatePath = strcat(duplicatePath, "/");
            duplicatePath = strcat(duplicatePath, dirent->d_name);
            lstat(duplicatePath, &buf);
	    int n = buf.st_mode;
	    int bcount =0;
        while (n != 0) {
	    n /= 10;
	    ++bcount;
	    } 
	    char *filemode = (char *)malloc(bcount+2);
	    char *filepermission = (char *)malloc(11);
	    //itoa(buf.st_mode,filemode,10);
	    snprintf(filemode,bcount+2,"%o",buf.st_mode);
        if (dirent->d_type == DT_DIR)
	{
		strcpy(filepermission,"d");
	}
	else
	{
		strcpy(filepermission,"-");
	}
	n=2;
	    while(n>=0)
	    {
		switch(filemode[strlen(filemode)-(n+1)]){
		case '0':
		strcat(filepermission,"---");
		break;
		case '1':
		strcat(filepermission,"--x");
		break;
		case '2':
		strcat(filepermission,"-w-");
		break;
		case '3':
		strcat(filepermission,"-wx");
		break;
		case '4':
		strcat(filepermission,"r--");
		break;
		case '5':
		strcat(filepermission,"r-x");
		break;
		case '6':
		strcat(filepermission,"rw-");
		break;
		case '7':
		strcat(filepermission,"rwx");
		break;
		}
		n--;
	    }
        if (dirent->d_type == DT_DIR)
        {
            if (strcmp(dirent->d_name, ".") == 0 || (strcmp(dirent->d_name, "..") == 0))
            {
                continue;
            }
//            printf("[%d] %s (%lld)\n", count, dirent->d_name, (long long)buf.st_size);
	    printf("[%d] %s %s (%lld) %s %s\n", count, dirent->d_name,filetype(dirent->d_type), (long long)buf.st_size,filepermission,ctime(&buf.st_atime));
            count++;
            recursiveS(parentDir, duplicatePath);
        }
        if (dirent->d_type != DT_DIR)
        {
	
            printf("    ");
            printf("[%d] %s %s (%lld) %s %s\n", count, dirent->d_name,filetype(dirent->d_type), (long long)buf.st_size,filepermission,ctime(&buf.st_atime));
            count++;
        }
    }
    closedir(parentDir);
    return 0;
}

/* For -s */
int recursives(DIR *parentDir, char *path, int size)
{
    struct stat buf;
    struct dirent *dirent;
    int count = 1;
    char *duplicatePath = (char *)malloc(2000);

    parentDir = opendir(path);
    if (parentDir == NULL)
    {
        printf("Error opening directory '%s'\n", dirent->d_name);
        exit(-1);
    }
    while ((dirent = readdir(parentDir)) != NULL)
    {
	strcpy(duplicatePath, path);
            duplicatePath = strcat(duplicatePath, "/");
            duplicatePath = strcat(duplicatePath, dirent->d_name);
	    lstat(duplicatePath, &buf);
        if (dirent->d_type == DT_DIR)
        {
            if (strcmp(dirent->d_name, ".") == 0 || (strcmp(dirent->d_name, "..") == 0))
            {
                continue;
            }
            printf("[%d] %s\n", count, dirent->d_name);
            count++;
            recursives(parentDir, duplicatePath, size);
        }
        if (dirent->d_type != DT_DIR)
        {
            lstat(dirent->d_name, &buf);
            if (size >= (long long)buf.st_size)
            {
                printf("    ");
                printf("[%d] %s (%lld)\n", count, dirent->d_name,(long long)buf.st_size);
                count++;
            }
        }
    }
    closedir(parentDir);
    return 0;
}

/* for -f */
int recursivef(DIR *parentDir, char *path, char *sub,int sub1)
{
    struct dirent *dirent;
    int count = 1;
    char *duplicatePath = (char *)malloc(2000);
    char *contain = (char *)malloc(2000);

    parentDir = opendir(path);
    if (parentDir == NULL)
    {
        printf("Error opening directory '%s'\n", dirent->d_name);
        exit(-1);
    }
    while ((dirent = readdir(parentDir)) != NULL && sub1>=0)
    {
        if (dirent->d_type == DT_DIR)
        {
            if (strcmp(dirent->d_name, ".") == 0 || (strcmp(dirent->d_name, "..") == 0))
            {
                continue;
            }
            strcpy(duplicatePath, path);
            duplicatePath = strcat(duplicatePath, "/");
            duplicatePath = strcat(duplicatePath, dirent->d_name);
            contain = strstr(dirent->d_name, sub);
            if (contain)
            {
                printf("[%d] %s\n", count, dirent->d_name);
                count++;
            }
            recursivef(parentDir, duplicatePath, sub,sub1-1);
        }
        if (dirent->d_type != DT_DIR)
        {
            contain = strstr(dirent->d_name, sub);
            if (contain)
            {
                printf("    ");
                printf("[%d] %s\n", count, dirent->d_name);
                count++;
            }
        }
    }
    closedir(parentDir);
    return 0;
}

/* for -t */
int recursivet(DIR *parentDir, char *path, char *sub)
{
    struct dirent *dirent;
    int count = 1;
    char *duplicatePath = (char *)malloc(2000);
    char *contain = (char *)malloc(2000);

    parentDir = opendir(path);
    if (parentDir == NULL)
    {
        printf("Error opening directory '%s'\n", dirent->d_name);
        exit(-1);
    }
    while ((dirent = readdir(parentDir)) != NULL)
    {	
        if (dirent->d_type == DT_DIR)
        {
            if (strcmp(dirent->d_name, ".") == 0 || (strcmp(dirent->d_name, "..") == 0))
            {
                continue;
            }
            strcpy(duplicatePath, path);
            duplicatePath = strcat(duplicatePath, "/");
            duplicatePath = strcat(duplicatePath, dirent->d_name);
            if (strcmp(sub,"d")==0)
            {
                printf("[%d] %s\n", count, dirent->d_name);
                count++;
            }
            recursivet(parentDir, duplicatePath, sub);
        }
        if (dirent->d_type != DT_DIR && strcmp(sub,"f")==0)
        {
                {
                printf("    ");
                printf("[%d] %s\n", count, dirent->d_name);
                count++;
            }
        }
    }
    closedir(parentDir);
    return 0;
}

int main(int argc, char *argv[])
{
    DIR *parentDir;
    char *path, *sub;
    int opt, size,sub1=9999;

    while ((opt = getopt(argc, argv, "S S: s: f: t:")) != -1)
    {
        switch (opt)
        {
        case 'S':
	        	
            /*if (optarg == NULL)
            {
                parentDir = opendir(".");
                path = ".";
                if (parentDir == NULL)
                {
                    printf("Error opening directory '%s'\n", path);
                    exit(-1);
                }
                recursiveS(parentDir, path);		
		return 0;
            }
            else
            {
                parentDir = opendir(optarg);
                path = optarg;
                if (parentDir == NULL)
                {
                    printf("Error opening directory '%s'\n", path);
                    exit(-1);
                }
                recursiveS(parentDir, path);
		return 0;
            }*/
		parentDir = opendir(".");
            path = ".";
            if (parentDir == NULL)
            {
                printf("Error opening directory '%s'\n", path);
                exit(-1);
            }
            //size = atoi(optarg);
	    for(;optind<argc;optind++){
		parentDir = opendir(argv[optind]);
		path=argv[optind];
            if (parentDir == NULL)
            {
                printf("Error opening directory '%s'\n", path);
                exit(-1);
            }

	    }
	    recursiveS(parentDir, path);	
	    return 0;
            break;
        case 's':
            parentDir = opendir(".");
            path = ".";
            if (parentDir == NULL)
            {
                printf("Error opening directory '%s'\n", path);
                exit(-1);
            }
            size = atoi(optarg);
	    for(;optind<argc;optind++){
		parentDir = opendir(argv[optind]);
		path=argv[optind];
            if (parentDir == NULL)
            {
                printf("Error opening directory '%s'\n", path);
                exit(-1);
            }

	    }	
            recursives(parentDir, path, size);
	    return 0;
            break;
        case 'f':
            parentDir = opendir(".");
            path = ".";
            if (parentDir == NULL)
            {
                printf("Error opening directory '%s'\n", path);
                exit(-1);
            }
            sub = optarg;
	    for(;optind<argc;optind++){
		sub1 = atoi(argv[optind]);
	    }
	    if (sub1 == 9999)
	    {
		printf("Enter the depth\n");
		exit(-1);
	    }
	    if (optind<argc)
	    {
		parentDir = opendir(argv[++optind]);
		path=argv[optind];
           	 if (parentDir == NULL)
	            {	
        	        printf("Error opening directory '%s'\n", path);
                	exit(-1);
           	    }
	    }
            recursivef(parentDir, path, sub, sub1);
	    return 0;
            break;
        
	case 't':
            parentDir = opendir(".");
            path = ".";
            if (parentDir == NULL)
            {
                printf("Error opening directory '%s'\n", path);
                exit(-1);
            }
            sub = optarg;
	    if (optind<argc)
	    {
		parentDir = opendir(argv[++optind]);
		path=argv[optind];
           	 if (parentDir == NULL)
	            {	
        	        printf("Error opening directory '%s'\n", path);
                	exit(-1);
           	    }
	    }
//	    printf("%s %d\n",sub,sub1);
            recursivet(parentDir, path, sub);
	    return 0;
            break;
		
        }
	
    }

//    USED FUCNTION POINTER HERE 
    int (*fun_ptr)(int) = &fun;
    if (argc < (*fun_ptr)(2))
    {
        parentDir = opendir(".");
        path = ".";
    }
    else
    {
        parentDir = opendir(argv[1]);
        path = argv[1];
    }
    if (parentDir == NULL)
    {
        printf("Error opening directory '%s'\n", argv[1]);
        exit(-1);
    }
    recursive(parentDir, path); 
    return 0;
}