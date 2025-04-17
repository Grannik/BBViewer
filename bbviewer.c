#include <stdio.h>
#include <unistd.h>
#include <termios.h>

void enableRawMode() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty);
}

void disableRawMode() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty);
}

int main() {
    enableRawMode();

    char buf[3];
    while (1) {
        ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
        if (n == 1 && buf[0] == 'q') break;

        // Печатаем все полученные байты
        printf("Read %zd bytes: ", n);
        for (ssize_t i = 0; i < n; i++) {
            printf("%d ", (unsigned char)buf[i]);
        }
        printf("\n");
        fflush(stdout);
    }

    disableRawMode();
    return 0;
}
