#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


class RecvUdp
{
    public:
        void UDP_setup();
        void get_command( int *command );

    private:
        void convert_command( char *packetBuffer, int *command );

    private:
        EthernetUDP Udp;
        char packetBuffer[ UDP_TX_PACKET_MAX_SIZE ];

        byte mac[6];
        const uint8_t[5] ip_add;
        int tire, cata, updown;
        unsigned int localport;
        IPAddress ip( 172, 16, 14, 200 );
};

void RecvUdp::UDP_setup( byte *mac, uint8_t *addr, unsigned int localport )
{
    for ( int i = 0; i < sizeof( addr ); i++ ) {
        ip_addr[i] = addr[i];
    }
    IPAddress ip( ip_add );
    Ethernet.begin( mac, ip );
    Udp.begin( localPort );
}
