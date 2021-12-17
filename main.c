#include <pic18f4520.h>
#include "config.h"
#include "bits.h"
#include "io.h"
#include "lcd.h"
#include "ssd.h"
#include "keypad.h"
#include "pwm.h"
#include "atraso.h"

#define L_CLR 0x01

void main() {
    ssdInit();
    lcdInit();
    kpInit();
    pwmInit();


    int tecla, num1, t, temp, operacao, num2, x, y;

    for (;;) {
        lcdString("U=+10   L=-10");
        lcdPosition(1, 0);
        lcdString("D=+100  R=-100");
        for (;;) {
            if (kpReadKey() != temp) {
                temp = kpReadKey();
                if (kpReadKey() != 0) {
                    tecla = kpReadKey();
                    if (tecla == 'U') {
                        num1 += 10;
                    }
                    if (tecla == 'L') {
                        num1 += 100;
                    }
                    if (tecla == 'D') {
                        num1 -= 10;
                    }
                    if (tecla == 'R') {
                        num1 -= 100;
                    }
                    if (tecla == 'S') {
                        pwmSet(100);
                        atraso_ms(250);
                        pwmSet(0);
                        break;
                    }
                }
            }
            ssdDigit((num1 / 1) % 10, 3);
            ssdDigit((num1 / 10) % 10, 2);
            ssdDigit((num1 / 100) % 10, 1);
            ssdDigit((num1 / 1000) % 10, 0);
            ssdUpdate();
            for (t = 0; t < 1000; t++);
            kpDebounce();
        }
        lcdCommand(L_CLR);
        lcdString("U = + L = -");
        lcdPosition(1, 0);
        lcdString("D = * R = /");

        for (;;) {
            if (kpReadKey() != temp) {
                temp = kpReadKey();
                if (kpReadKey() != 0) {
                    tecla = kpReadKey();
                    if (tecla == 'U') {
                        operacao = 0;
                    }
                    if (tecla == 'L') {
                        operacao = 1;
                    }
                    if (tecla == 'D') {
                        operacao = 2;
                    }
                    if (tecla == 'R') {
                        operacao = 3;
                    }
                    if (tecla == 'S') {
                        pwmSet(100);
                        atraso_ms(250);
                        pwmSet(0);
                        break;
                    }
                }
            }
            kpDebounce();
        }
        lcdCommand(L_CLR);
        lcdString("U=+10   L=-10");
        lcdPosition(1, 0);
        lcdString("D=+100  R=-100");
        for (;;) {
            if (kpReadKey() != temp) {
                temp = kpReadKey();
                if (kpReadKey() != 0) {
                    tecla = kpReadKey();
                    if (tecla == 'U') {
                        num2 += 10;
                    }
                    if (tecla == 'L') {
                        num2 += 100;
                    }
                    if (tecla == 'D') {
                        num2 -= 10;
                    }
                    if (tecla == 'R') {
                        num2 -= 100;
                    }
                    if (tecla == 'S') {
                        pwmSet(100);
                        atraso_ms(250);
                        pwmSet(0);
                        break;
                    }
                }
            }

            ssdDigit((num2 / 1) % 10, 3);
            ssdDigit((num2 / 10) % 10, 2);
            ssdDigit((num2 / 100) % 10, 1);
            ssdDigit((num2 / 1000) % 10, 0);
            ssdUpdate();
            for (t = 0; t < 1000; t++);
            kpDebounce();
        }
        switch (operacao) {
            case 0:
                y = "+";
                x = num1 + num2;
                break;
            case 1:
                y = "-";
                x = num1 - num2;
                break;
            case 2:
                y = "*";
                x = num1 * num2;
                break;
            case 3:
                y = "/";
                x = num1 / num2;
                break;
            default:
                break;
        }
        lcdCommand(L_CLR);
        lcdNumber(num1);
        lcdString(y);
        lcdNumber(num2);
        lcdPosition(1, 0);
        lcdString("Resultado=");
        lcdNumber(x);
        for (;;) {
            kpDebounce();
            if (kpReadKey() != temp) {
                temp = kpReadKey();
                if (kpReadKey() != 0) {
                    tecla = kpReadKey();
                    if (tecla == 's') {
                        lcdCommand(L_CLR);
                        num1 = 0;
                        num2 = 0;
                        operacao = -1;
                        break;
                    }
                }
            }
        }
    }
}