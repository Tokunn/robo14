#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = { 0x80, 0xA2, 0xDA, 0x0F, 0x88, 0x32 };
IPAddress ip( 172, 16, 14, 200 );

unsigned int localPort = 4000;

char packetBuffer[ UDP_TX_PACKET_MAX_SIZE ];

EthernetUDP Udp;

void setup() {
    Ethernet.begin( mac, ip );
    Udp.begin( localPort );
    Serial.begin( 9600 );
}

void loop() {
    int packetSize = Udp.parsePacket();
    if( packetSize ) {
        Udp.read( packetBuffer, UDP_TX_PACKET_MAX_SIZE );
        Serial.println( packetBuffer );
    }
}
