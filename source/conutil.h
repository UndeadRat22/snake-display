#include <stdio.h>
#include <unistd.h>   //_getch*/
#include <termios.h>  //_getch*/

#include <iostream>
#include <sys/select.h>

char getch(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;
 };


char getch(int timeout)
{
    fd_set read_set;
    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);
    struct timeval tv = { 0, timeout };
    if (select(STDIN_FILENO + 1, &read_set, NULL, NULL, &tv) < 0)
        return -1;
    char c;
    if (FD_ISSET(STDIN_FILENO, &read_set))
    {
        //std::cin >> c;
        c = getch();
        return c;
    }
    return -1;
};