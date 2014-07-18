#include <SPI.h>
#include <Ethernet.h>
#include <Udp.h>

#define LED 9

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x8B, 0x32 };
byte ip[] = { 172, 16, 14, 200 };

unsigned int localPort = 4000;

byte remoteIp[ 4 ];

unsigned int remotePort;

char packetBuffer[ UDP_TX_PACKET_MAX_SIZE ];
char ReplyBuffer[] = "acknowledged";

char cON[] = "on";
char cOFF[] = "off";

void setup() {
    Ethernet.begin( mac, ip );
    Udp.begin( localPort );
    
    PinMode( LED, OUTPUT );
    Serial.begin(9600);
}

void loop() {
    int packetSize = Udp.available();
    if( packetSize ) {
        packetSize = packetSize - 8;
        Serial.print( "Received packet of size" )
        Serial.println( packetSize );

        Udp.readPacket( packetBuffer, UDP_TX_PACKET_MAX_SIZE, remoteIp, remotePort );

        packetBuffer[ packetSize ] = 0;

        if( strcmp( packetBuffer, cON ) == 0 ) {
            digitalWrite( LED, HIGH );
        }
        if( strcmp( packetBuffer, cOFF ) == 0 ) {
            digitalWrite( LED, LOW );
        }
        Serial.print( "Contents:" );
        Serial.println( packetBuffer );

        Udp.sendPacket( ReplyBuffer, remoteIp, remotePort );
    }
    delay(10);
}
