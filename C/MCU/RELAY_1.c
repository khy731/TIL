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
    PORTB = 0x01;

    while (1) {
        _delay(500);
        PORTB = 0x00;

        _delay(500);
        PORTB = 0x01;
    }
}