#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include<unistd.h>
#include <sys/time.h>
#define ll long long
unsigned int microsecond = 1000000;
char fileNames[6575][105];
char fileData[6575][100372];
void swap_char(char *a, char *b)
{
    char c[1000];
    strcpy(c, a);
    strcpy(a, b);
    strcpy(b, c);
}
void print_str(char *msg)
{
    printf("%s\n", msg);
}
int debug_i, debug_j;
void cut_txt(char *in, char *out)
{
    int i;
    for (i=0; in[i]!='\0'&&in[i]!='.'; i++)
    {
        out[i]=in[i];
    }
    out[i]='\0';
}
void *play_video()
{
    system("mpv video/bad_apple.mp4 &");
}
long timeInMicro(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
int main()
{
    print_str("Opening dir...");
    DIR *d;
    struct dirent *dir;
    d = opendir("ascii_2");
    if (d)
    {
        int file_nr=-1;
        print_str("Reading files name...");
        while ((dir = readdir(d)) != NULL)
        {
            if (file_nr<1) {file_nr++; continue;}
            strcpy(fileNames[file_nr++], dir->d_name);
        }
        closedir(d);
        file_nr--;
        print_str("Sorting file names...");
        for (int i=1; i<file_nr; i++)
        {
            for (int j=i+1; j<=file_nr; j++)
            {
                char fa[1000], fb[1000];
                debug_i=i;
                debug_j=j;
                cut_txt(fileNames[i], fa);
                cut_txt(fileNames[j], fb);
                int ia=atoi(fa), ib=atoi(fb);
                if (ia>ib)
                {
                    swap_char(fileNames[i], fileNames[j]);
                }
            }
        }
        print_str("Reading file content in memory...");
        for (int i=1; i<=file_nr; i++)
        {
            char file_path[1000];
            strcpy(file_path, "ascii_2/");
            strcat(file_path, fileNames[i]);
            FILE *fin=fopen(file_path, "r");
            if (fin==NULL) {
                print_str("Can't open file for reading...");
                return 0;
            }
            int cnt=0;
            while (1)
            {
                char ch=fgetc(fin);
                if (ch==EOF) break;
                fileData[i][cnt++]=ch;
            }
            fclose(fin);
            fileData[i][cnt]='\0';
        }


        print_str("Starting animation...");
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, play_video, NULL);
        usleep(115000);
        system("clear");
        int waitTime=33333;
        ll timp=timeInMicro();
        for (int i=1; i<=file_nr; i++) {
            printf("%s", fileData[i]);
            while (timeInMicro()<timp+waitTime) {
                continue;
            }
            system("clear");
            timp+=waitTime;
        }
    }
    else
    {
        printf("%s\n", "Couldn't open dir...");
        return 0;
    }
    return 0;
}
