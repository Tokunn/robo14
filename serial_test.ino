#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);


void setup()
{
    Serial.begin(9600);
    lcd.print("Standby");
}


void recv_str(char *buf)
{
    if (Serial.available()) {
        if (Serial.read() == '$') {
            int i = 0;
            for(int i = 0; i < 9; i++) {
                buf[i] = Serial.read();
            }
            buf[9] = '\0';
        }
    }
}


void loop()
{
    char str[10] = "s0n0s0n00";
    recv_str(str);
    lcd.print(str);
}
