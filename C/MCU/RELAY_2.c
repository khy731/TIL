#include <avr/io.h>
#include <util/delay.h>

void _delay(int s)
{
    int i;
    for (i = 0; i < s; i++)
    {
        _delay_ms(1);
    }
}

void main()
{
    DDRA = 0xFF;
    DDRB = 0xFF;

    // (ON, ON)
    PORTA = 0x01;
    PORTB = 0x00;

    while (1)
    {
        // (ON, OFF)
        _delay(1000);
        PORTA = 0x01;
        PORTB = 0x01;

        // (OFF, ON)
        _delay(1000);
        PORTA = 0x00;
        PORTB = 0x00;

        // (OFF, OFF)
        _delay(1000);
        PORTA = 0x00;
        PORTB = 0x01;

        // (ON, ON)
        _delay(1000);
        PORTA = 0x01;
        PORTB = 0x00;
    }
}