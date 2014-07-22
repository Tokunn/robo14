#include "recv_udp.h"

extern int tire, cata, updown;

void setup() {
    UDP_setup();
    Serial.begin( 9600 );
}

void loop() {
    int command[] = { tire, 0, 0 };
    get_command( command );

    Serial.print( command[ 0 ] );
    Serial.print( command[ 1 ] );
    Serial.print( command[ 2 ] );
    Serial.print( "\n" );
}
