#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


/*****************Netwok Settings*****************/

int tire = 0, cata = 1, updown = 2;
byte mac[] = { 0x80, 0xA2, 0xDA, 0x0F, 0x88, 0x32 };
IPAddress ip( 172, 16, 14, 200 );
unsigned int localPort = 4000;

char packetBuffer[ UDP_TX_PACKET_MAX_SIZE ];
EthernetUDP Udp;

/*****************Netword Settings End************/
/*****************Network Functions***************/

void UDP_setup() {
    Ethernet.begin( mac, ip );
    Udp.begin( localPort );
}

void get_command( int *command ) {
    if( Udp.parsePacket() ) {
        Udp.read( packetBuffer, UDP_TX_PACKET_MAX_SIZE );
        convert_command( packetBuffer, command );
        //Serial.println( packetBuffer );
    }
}

void convert_command( char *packetBuffer, int *command ) {
    int VALUE_ID = 0;
    int VALUE_LEFT = 2;
    int VALUE_RIGT = 4;
    int COM_ID = 0;
    int COM_LEFT = 1;
    int COM_RIGT = 2;

    switch( packetBuffer[ VALUE_ID ] ) {
        case '$':
            command[ COM_ID ] = tire;    break;
        case '%':
            command[ COM_ID ] = cata;    break;
        case '&':
            command[ COM_ID ] = updown;  break;
    }

    char temp_left[ 2 ];
    char temp_rigt[ 2 ];
    temp_left[ 0 ] = packetBuffer[ VALUE_LEFT ];
    temp_rigt[ 0 ] = packetBuffer[ VALUE_RIGT ];
    temp_left[ 1 ] = temp_rigt[ 1 ] = '\0';

    command[ COM_LEFT ] = atoi( temp_left );
    command[ COM_RIGT ] = atoi( temp_rigt );

    if( packetBuffer[ VALUE_LEFT - 1 ] == 'B' ) {
        command[ COM_LEFT ] *= -1;
    }
    if( packetBuffer[ VALUE_RIGT - 1 ] == 'B' ) {
        command[ COM_RIGT ] *= -1;
    }
}

/******************Netword Functions End***********/


/*
void setup() {
    UDP_setup();
    Serial.begin(9600);
}

void loop() {
    int command[] = { tire, 0, 0 };
    get_command( command );

    Serial.print( command[ 0 ] );
    Serial.print( command[ 1 ] );
    Serial.print( command[ 2 ] );
    Serial.print( "\n" );
}
*/
