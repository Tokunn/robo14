void setup()
{
    Serial.begin(9600);
}


void recv_str(char *buf)
{
    int i = 0;
    while (true) {
        if (Serial.available()) {
            buf[i] = Serial.read();
            if (i > 7) break;
            i++;
        }
    }
    buf[9] = '\0';
}


void some_action(char *str)
{
    Serial.println(str);
}


void loop()
{
    if (Serial.available() > 0) {
        char str[10];
        recv_str(str);
        some_action(str);
    }

    else {
        char str[10] = "s0n0s0n00";
        some_action(str);
    }
}
