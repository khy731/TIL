#include <avr/io.h>
#include <util/delay.h>

void _delay(int s) {
    int i;
    for(i=0; i<s; i++) {
        _delay_ms(1);
    }
}

void main() {
    DDRA = 0xFF;

    int x = 0b11111110;

    while (1) {
        if (PORTA == 0xFF) x = 0b11111110;

        PORTA = x;
        x = (x << 1) + 1;
        
        _delay(1000);
    }
}