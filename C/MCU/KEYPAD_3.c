#include <avr/io.h>
#include <util/delay.h>

// 키 패드 값 상수 지정
// KEY 스캔용 1bit + 스캔된 KEY코드값
#define KEY1 0x11
#define KEY2 0x12;
#define KEY3 0x14;
#define KEY4 0x21;
#define KEY5 0x22;
#define KEY6 0x24;
#define KEY7 0x41;
#define KEY8 0x42;
#define KEY9 0x44;
#define KEY0 0x82;
#define KEYA 0x81; // KEY*
#define KEYB 0x84; // KEY#
#define KEY12 0x13
#define KEY13 0x15
#define KEY123 0x17

// KEY 채터링 검사 함수
unsigned char get_key_code()
{
    unsigned char input = 0;

    // 입력신호 중 하위 3비트만을 저장
    input = PINA & 0x07;

    for (int i = 0; i < 10; i++)
    {
        _delay_us(500);
        if (input != (PINA & 0x07))
            return 0;
    }
    return input;
}

// KEY 입력 체크 -> 최종 값 반환 함수
unsigned char key_check()
{
    unsigned char input = 0;
    unsigned char output = 0;

    output = 0x10;
    PORTB = output;
    input = get_key_code();
    if (input != 0)
        return (output | input);

    output = 0x20;
    PORTB = output;
    input = get_key_code();
    if (input != 0)
        return (output | input);

    output = 0x40;
    PORTB = output;
    input = get_key_code();
    if (input != 0)
        return (output | input);

    output = 0x80;
    PORTB = output;
    input = get_key_code();
    if (input != 0)
        return (output | input);

    return 0xFF;
}

int main()
{
    unsigned char key_value = 0x00;

    DDRA = 0xF8;
    DDRB = 0xF0;
    DDRC = 0xFF;
    DDRD = 0xFF;

    PORTB = 0x00;
    PORTC = 0;    // high
    PORTD = 0xFF; // low

    while (true)
    {
        key_value = key_check();

        if (key_value)

        switch (key_value) // 눌러진 KEY 검사
        {
        case KEY1:
            PORTC = 0x01;
            break;
        case KEY2:
            PORTC = 0x02;
            break;
        case KEY3:
            PORTC = 0x04;
            break;
        case KEY4:
            PORTC = 0x08;
            break;
        case KEY5:
            PORTC = 0x10;
            break;
        case KEY6:
            PORTC = 0x20;
            break;
        case KEY7:
            PORTC = 0x40;
            break;
        case KEY8:
            PORTC = 0x80;
            break;
        case KEY9:
            PORTC = ~0x01;
            break;
        case KEYA:
            PORTC = ~0x02;
            break;
        case KEY0:
            PORTC = ~0x04;
            break;
        case KEYB:
            PORTC = ~0x08;
            break;
        default:
            PORTC = 0;
            break;
        }
    }
    return 0;
}

// 과제 : 동시에 눌러도 ㄱㅊ도록