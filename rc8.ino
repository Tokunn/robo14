void setup()
{
    Serial.begin(9600);
    pinMode(8, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    digitalWrite(8, HIGH);
    digitalWrite(6, HIGH);
}

void recv_str(char *buf)
{
    if (Serial.read() == '$') {
        int i = 0;
        for(int i = 0; i < 4; i++) {
            buf[i] = Serial.read();
        }
        buf[11] = '\0';
    }
}

void loop()
{
    digitalWrite(10, LOW);
    char str[12] = "s0s0";

    if (Serial.available()) {
        recv_str(str);
    }

    if (str[0] == 'f') {
        digitalWrite(8, HIGH);
        digitalWrite(6, LOW);
    }
    /*else if (str[0] == 'b') {
        digitalWrite(8, LOW);
        digitalWrite(6, HIGH);
    }
    else if (str[0] == 's') {
        digitalWrite(8, LOW);
        digitalWrite(6, LOW);
    }
    else if (str[0] == '0') {
        digitalWrite(8, HIGH);
        digitalWrite(6, HIGH);
    }*/ 
    else {
        digitalWrite(9, HIGH);
    }

    delay(50);
    digitalWrite(10, HIGH);
}
