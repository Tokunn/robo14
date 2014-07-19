#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

void UDP_setup();
    byte mac[] = { 0x80, 0xA2, 0xDA, 0x0F, 0x88, 0x32 };
    IPAddress ip( 172, 16, 14, 200 );

    unsigned int localPort = 4000;

    char packetBuffer[ UDP_TX_PACKET_MAX_SIZE ];

    EthernetUDP Udp;

    Ethernet.begin( mac, ip );
    Udp.begin( localPort );
}

void get_command( int *command ) {
    if( Udp.parsePacket() ) {
        Udp.read( packetBuffer, UDP_TX_PACKET_MAX_SIZE );
        Serial.println( packetBuffer );
    }
}
