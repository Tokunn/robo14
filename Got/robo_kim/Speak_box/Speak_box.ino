#define INTERVAL 7000

//please input message
char* voice_msg[] = { "konnnichiwa",
                      "suxtukarisamukunaxtutekimasitane", 
                      "nixtukoudesyugyouwosimasgita",
                      "oisiiosobadayo",
                      "tennpurasobamoosusumedesu",
                      "oxtutoxtuto abunakaxtuta",
                      
                      
                      "END"         //for count message number
                     };


//-----------Start function defintion-------------

//count message number
int get_length( char** string ) {
    
    int i=0;
    while( string[i] != "END" ) {
        i++;
    }
    
    return i;
}
//-----------End function defintion---------------


void setup() {
    
    Serial.begin( 9600 );
    Serial.print( "?" );        //ATP3011 start command mode
   
}


void loop() {
     
    int msg_number = get_length( voice_msg );
    
    for( int i=0; i<msg_number; i++ ) {
        Serial.println( voice_msg[i] );        //send message for ATP3011
        delay( INTERVAL );
    }
}
    
