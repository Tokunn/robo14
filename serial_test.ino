void setup()
{
    Serial.begin(9600);
}


void recv_str(char *buf, int count)
{
    int i = 0;
    while (true) {
        if (Serial.available()) {
            buf[i] = Serial.read();
            if (i > (count - 2)) break;
            i++;
        }
    }
    buf[(count - 1)] = '\0';
    Serial.println(buf);
}


void some_action(char *str)
{
    Serial.println(str);
}


void main_()
{
    if (Serial.available() > 0) {
        char str[10];
        recv_str(str, 10);
        some_action(str);
    }

    else {
        char str[10] = "s0n0s0n00";
        some_action(str);
    }
}


void loop()
{
    while (true) {
        Serial.print('S');

        if (Serial.available() > 0) {
            char str_sync;
            str_sync = Serial.read();
            Serial.println(str_sync);

            if (str_sync == 'O') {
                Serial.print('A');
                main_();
            }
        }
        delay(100);
    }
}
