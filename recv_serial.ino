void setup()
{
    Serial.begin(9600);
    pinMode(8, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(8, LOW);
    digitalWrite(6, HIGH);
}


void recv_str(char *buf)
{
    if (Serial.read() == '$') {
        int i = 0;
        for(int i = 0; i < 11; i++) {
            buf[i] = Serial.read();
        }
        buf[11] = '\0';
    }
}


void loop()
{
    char str[12] = "s0s0s0s0000";
    if (Serial.available()) {
        recv_str(str);
    }

    if (str[0] != 's') {
        digitalWrite(8, HIGH);
        digitalWrite(6, LOW);
    }
    else {
        digitalWrite(8, LOW);
        digitalWrite(6, HIGH);
    }

    delay(50);
        
}
