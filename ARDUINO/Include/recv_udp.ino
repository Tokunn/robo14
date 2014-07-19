#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


class RecvUDP {
    public:
        //void set_addr( byte *mac_addr, int *ip_addr );
        //void set_port( int loclaport );
        void start();
        void get( char *command );

    private:
        //byte *__mac;
        //int *__ip;
        int __port = 4000;
        char __packetBuffer[ UDP_TX_PACKET_MAX_SIZE ];
        int __packetSize;
        EthernetUDP __Udp;
        IPAddress ip( 172, 16, 14, 200 );
        byte __mac[] = { 0x80, 0xA2, 0xDA, 0x0F, 0x88, 0x32 };
};

/*void RecvUDP::set_addr( byte *mac_addr, int *ip_addr ) {
    __mac = mac_addr;
    __ip = ip_addr;
}

void RecvUDP::set_port( int localport ) {
    __port = localport;
}*/

void RecvUDP::start() {
    //IPAddress ip( *__ip );
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
