#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = { 0x80, 0xA2, 0xDA, 0x0F, 0x88, 0x32 };
IPAddress ip( 172, 16, 14, 200 );
unsigned int localPort = 4000;
char packetBuffer[ UDP_TX_PACKET_MAX_SIZE ];
EthernetUDP Udp;

void UDP_setup();
void get_command( int *command );

void setup() {
    UDP_setup();
    Serial.begin(9600);
}

void loop() {
    int tire = 0, cata = 1, updown = 2;

    int command[] = { tire, 0, 0 };
    get_command( command );
}

void UDP_setup() {
    Ethernet.begin( mac, ip );
    Udp.begin( localPort );
}

void get_command( int *command ) {
    if( Udp.parsePacket() ) {
        Udp.read( packetBuffer, UDP_TX_PACKET_MAX_SIZE );
        Serial.println( packetBuffer );
    }
}
