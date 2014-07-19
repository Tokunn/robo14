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
        Serial.println( packetBuffer );
    }
}

void convert_command( char packetBuffer, int command ) {
    VALUE_ID = 0;
    VALUE_LEFT = 2;
    VALUE_RIGT = 4;
    COM_ID = 0;
    COM_LEFT = 1;
    COM_RIGT = 2;

    switch( packetBuffer[ VALUE_ID ] ) {
        case '$':
            command[ COM_ID ] = tire;    break;
        case '%':
            command[ COM_ID ] = cata;    break;
        case '&':
            command[ COM_ID ] = updown;  break;
    }
    command[ COM_LEFT ] = atoi( packetBuffer[ VALUE_LEFT ] );
    command[ COM_RIGT ] = atoi( packetBuffer[ VALUE_RIGT ] );

    if( packetBuffer[ VALUE_LEFT - 1 ] == 'B' ) {
        command[ COM_LEFT ] *= -1;
    }
    if( packetBuffer[ VALUE_RIGT - 1 ] == 'B' ) {
        command[ COM_RIGT ] *= -1;
    }
}

/******************Netword Functions End***********/



void setup() {
    UDP_setup();
    Serial.begin(9600);
}

void loop() {
    int command[] = { tire, 0, 0 };
    get_command( command );
    Serial.println( "\t\t%d\t%d\t%d", command[ 0 ], command[ 1 ], command[ 2 ] );
}
