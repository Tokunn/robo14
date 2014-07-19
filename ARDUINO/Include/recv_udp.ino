#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


class RecvUDP {
    public:
        void start();
        void get( char *command );

    private:
        char __packetBuffer[ UDP_TX_PACKET_MAX_SIZE ];
        int __packetSize;
        EthernetUDP __Udp;

        int __port = 4000;
        IPAddress ip( 172, 16, 14, 200 );
        byte __mac[] = { 0x80, 0xA2, 0xDA, 0x0F, 0x88, 0x32 };
};

void RecvUDP::start() {
    Ethernet.begin( __mac, ip );
    Udp.begin( __port );
}

void RecvUDP::get( char *command ) {
    if( Udp.parsePacket() ) {
        Udp.read( packetBuffer, UDP_TX_PACKET_MAX_SIZE );
        for (int i = 0; i < sizeof( packetBuffer ); i++ ) {
            command[ i ] = packetBuffer[ i ];
        }
    }
}

void setup() {
}

void loop() {
}
