#include <avr/io.h>
#include <util/delay.h>

// 키 패드 값 상수 지정
// KEY 스캔용 1bit + 스캔된 KEY코드값
#define KEY1 0x11;
#define KEY2 0x12;
#define KEY3 0x14;

// 스캔된 KEY코드값 얻기
unsigned char get_key_code()
{
    unsigned char input = 0;

    // PIN : MCU 입력값 예약어
    // 입력신호 중 하위 3비트만을 저장
    input = PINA & 0x07;

    // 채터링 검사 루프
    // 500마이크로sec 간격으로 10회동안 값 검사
    // : 같으면 input 반환, 다르면 0 반환
    for (int i = 0; i < 10; i++)
    {
        _delay_us(500);
        if (input != (PINA & 0x07))
        {
            return 0;
        }
    }
    return input;
}

// 완성된 KEY 코드값
unsigned char key_check()
{
    unsigned char input = 0;
    unsigned char output = 0;

    output = 0x10;
    PORTB = output;         // PB4~7를 각각 KEY_R0~3에 연결
    input = get_key_code(); // 스캔된 KEY 코드값

    if (input != 0) // 신호가 하나라도 들어온 경우
    {
        return (output | input); // 완성된 KEY코드값
                                 // KEY 스캔용 1bit + 스캔된 KEY코드값
    }
    return 0xFF;
}

int main()
{
    unsigned char key_value = 0x00;

    DDRA = 0xF8; // KEY 입력(0x00도 ㄱㅊ) : input PA0~PA2
    DDRB = 0x10; // KEY 스캔(oxFF도 ㄱㅊ) : output PB4
    DDRC = 0xFF; // LED 출력 : PORTC

    PORTC = 0; // LED off

    while (true)
    {
        key_value = key_check();

        switch (key_value) // 눌러진 KEY 검사
        {
        case KEY1:
            PORTC = 0x01;   // LED on
            break;
        case KEY2:
            PORTC = 0x02;   // LED on
            break;
        case KEY3:
            PORTC = 0x04;   // LED on
            break;
        default:            // 아무것도 누르지 않음
            PORTC = 0;      // 모든 LED off
            break;
        }
    }
    return 0;
}