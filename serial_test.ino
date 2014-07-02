void setup()
{
    Serial.begin(9600);
    pinMode(8, OUTPUT);
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

    if (str[0] != 's') {
        digitalWrite(8, HIGH);
    }
    else {
        digitalWrite(8, LOW);
    }
        
}
