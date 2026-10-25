#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/sysmacros.h>

void generate_error_msg(const char *msg, const char *arg){
    int length = strlen(arg) + strlen(msg);
    char buff[length];
    snprintf(buff, length -1, msg,arg);
    buff[length -1] ='\0';
    perror(buff);
}

int main(int argc, char *argv[])
{
    if(argc != 3){
        printf("Error: the mycp command accept 2 arguments source and destination.\n");
        return 1;
    }

    struct stat source_stat;
    int st;
    if ((st = stat(argv[1], &source_stat)) == -1) {
        generate_error_msg("mycp: cannot stat '%s'", argv[1]);
        return 1;
    }

    int source_fd;
    if ((source_fd = open(argv[1], O_RDONLY)) == -1) {
        generate_error_msg("mycp : cannot open '%s' for read", argv[1]);
        return 1;
    }

    int dest_fd;
    if ((dest_fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC,source_stat.st_mode)) == -1) {
        generate_error_msg("mycp: cannot open '%s' for write", argv[2]);
        close(source_fd);
        return 1;
    }

    int rd_bytes = -1;
    char buff[1024];
    while ((rd_bytes = read(source_fd,buff, 1023)) > 0) {
        buff[rd_bytes] = '\0';
        int wr_bytes = write(dest_fd, buff, rd_bytes);
        if (wr_bytes == -1){
            generate_error_msg("mycp: cannot write to '%s'", argv[2]);
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (rd_bytes == -1) {
        generate_error_msg("mycp : cannot read '%s'", argv[1]);
        return 1;
    }

    close(source_fd);
    close(dest_fd);
    return 0;
}
