#include <iostream>
#include <stdlib.h>

using namespace std;

void get_command( int *commad, char *packetBuffer );

int main() {
    int command[] = { 0, 0, 0 };
    char packetBuffer[] = "$S0S0";
    get_command( command, packetBuffer );
}

void get_command( int *command, char *packetBuffer ) {
    char temp[3];
    temp[0] = packetBuffer[2];
    temp[1] = '\0';
    command[ 1 ] = atoi( temp );
}
