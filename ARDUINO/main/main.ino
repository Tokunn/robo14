#include "Include/recv_udp.h"

void setup() {
    UDP_setup();
    Serial.begin( 9600 );
}

void loop() {
    int command[] = "$S0S0";
    get_command( command );
}
