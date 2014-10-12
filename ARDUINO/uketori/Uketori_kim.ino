#include "recv_udp.h"
#include <math.h>

#define MOTOR_CNT 4

#define DRIVER_BASIS 0
#define SPEED_ARM 250

#define SPEED_HAND 100


extern int tire, arm;

int VAL_LEFT_FRONT = 0, VAL_LEFT_REAR = 1, VAL_RIGT_FRONT = 2, VAL_RIGT_REAR = 3;
int CMD_LEFT_FRONT = 1, CMD_LEFT_REAR = 2, CMD_RIGT_FRONT = 3, CMD_RIGT_REAR = 4;

int m_pin_lf[] = { 2, 3 };
int m_pin_lr[] = { 4, 5 };
int m_pin_rf[] = { 6, 7 };
int m_pin_rr[] = { 8, 9 };


int m_pin_arm[]  = { 11, 12 };
int m_pin_hand[] = { 44, 46 };



void setup()
{    
    init_driver();
    delay( 200 );
        
    //turn stop arm and hand  
    faststop( m_pin_arm );
    faststop( m_pin_hand );

    UDP_setup();
    Serial.begin( 9600 );
}



//--------------------Start function defintion--------------------
void make_pwm( int* p_gamepad, int* pwm_val )
{
    /* for old driver
    pwm_val[ VAL_LEFT_FRONT ] = 255 - ( abs( p_gamepad[ CMD_LEFT_FRONT ] ) * 25 );
    pwm_val[ VAL_LEFT_REAR ] = 255 - ( abs( p_gamepad[ CMD_LEFT_REAR ] ) * 25 );
    pwm_val[ VAL_RIGT_FRONT ] = 255 - ( abs( p_gamepad[ CMD_RIGT_FRONT ] ) * 25 );
    pwm_val[ VAL_RIGT_REAR ] = 255 - ( abs( p_gamepad[ CMD_RIGT_REAR ] ) * 25 );
    */
    
    // for new driver
    pwm_val[ VAL_LEFT_FRONT ] =  abs( p_gamepad[ CMD_LEFT_FRONT ] ) * 25 ;
    pwm_val[ VAL_LEFT_REAR ] =  abs( p_gamepad[ CMD_LEFT_REAR ] ) * 25 ;
    pwm_val[ VAL_RIGT_FRONT ] =  abs( p_gamepad[ CMD_RIGT_FRONT ] ) * 25 ;
    pwm_val[ VAL_RIGT_REAR ] =  abs( p_gamepad[ CMD_RIGT_REAR ] ) * 25 ;
}


void faststop( int* m_pin )
{
    analogWrite( m_pin[0], DRIVER_BASIS );
    analogWrite( m_pin[1], DRIVER_BASIS );
}


void init_driver()
{
    for( int i=2; i<=12; i++ ) {
        analogWrite( i, 255 );
    }
    analogWrite( 44, 255 );
    analogWrite( 46, 255 );
    
    delay( 5000 );
}


void check_rotate( int* p_gamepad, boolean* rotate )
{
    if ( p_gamepad[ CMD_LEFT_FRONT ] >= 0 ) {   // LF
        rotate[ VAL_LEFT_FRONT ] = true;
    }
    else {
        rotate[ VAL_LEFT_FRONT ] = false;
    }
    if ( p_gamepad[ CMD_LEFT_REAR ] >= 0 ) {    // LR
        rotate[ VAL_LEFT_REAR ] = true;
    }
    else {
        rotate[ VAL_LEFT_REAR ] = false;
    }
    if ( p_gamepad[ CMD_RIGT_FRONT ] >= 0 ) {   // RF
        rotate[ VAL_RIGT_FRONT ] = true;
    }
    else {
        rotate[ VAL_RIGT_FRONT ] = false;
    }
    if ( p_gamepad[ CMD_RIGT_REAR ] >= 0 ) {   // RR
        rotate[ VAL_RIGT_REAR ] = true;
    }
    else {
        rotate[ VAL_RIGT_REAR ] = false;
    }
}  
    


void drive_uketori( int* pwm_val, boolean* rotate )
{
    if ( rotate[ VAL_LEFT_FRONT ] ) {       // LF
        analogWrite( m_pin_lf[0], pwm_val[ VAL_LEFT_FRONT ] );
        analogWrite( m_pin_lf[1], DRIVER_BASIS );
    }
    else if ( !rotate[ VAL_LEFT_FRONT ] ) {
        analogWrite( m_pin_lf[0], DRIVER_BASIS );
        analogWrite( m_pin_lf[1], pwm_val[ VAL_LEFT_FRONT ] );
    }

    if ( rotate[ VAL_LEFT_REAR ] ) {        // LR
        analogWrite( m_pin_lr[0], pwm_val[ VAL_LEFT_REAR ] );
        analogWrite( m_pin_lr[1], DRIVER_BASIS );
    }
    else if ( !rotate[ VAL_LEFT_REAR ] ) {
        analogWrite( m_pin_lr[0], DRIVER_BASIS );
        analogWrite( m_pin_lr[1], pwm_val[ VAL_LEFT_REAR ] );
    }

    if ( rotate[ VAL_RIGT_FRONT ] ) {       // RF
        analogWrite( m_pin_rf[0], pwm_val[ VAL_RIGT_FRONT ] );
        analogWrite( m_pin_rf[1], DRIVER_BASIS );
    }
    else if ( !rotate[ VAL_RIGT_FRONT ] ) {
        analogWrite( m_pin_rf[0], DRIVER_BASIS );
        analogWrite( m_pin_rf[1], pwm_val[ VAL_RIGT_FRONT ] );
    }

    if ( rotate[ VAL_RIGT_REAR ] ) {       // RR
        analogWrite( m_pin_rr[0], pwm_val[ VAL_RIGT_REAR ] );
        analogWrite( m_pin_rr[1], DRIVER_BASIS );
    }
    else if ( !rotate[ VAL_RIGT_REAR ] ) {
        analogWrite( m_pin_rr[0], DRIVER_BASIS );
        analogWrite( m_pin_rr[1], pwm_val[ VAL_RIGT_REAR ] );
    }
}


void action_hand( int* p_gamepad )
{       
    if ( p_gamepad[1] == 1 && p_gamepad[2] == 1 ) {
        faststop( m_pin_hand );
    }
    else {
        //grip seiro
        if ( p_gamepad[1] == 1 ) {
            analogWrite( m_pin_hand[0], SPEED_HAND );
            analogWrite( m_pin_hand[1], DRIVER_BASIS );
            
            Serial.println( "hand" );
        }
        else if (p_gamepad[1] == 0 && p_gamepad[2] == 0) {
              Serial.println( "hand_stop" );
            faststop( m_pin_hand );
        }


        //release seiro
        if ( p_gamepad[2] == 1 ) {
            analogWrite( m_pin_hand[0], DRIVER_BASIS );
            analogWrite( m_pin_hand[1], SPEED_HAND );
        }
        else if (p_gamepad[1] == 0 && p_gamepad[2] == 0) {
            faststop( m_pin_hand );
        }
    }
}


void move_arm( int* p_gamepad )
{
    //arm UP
    if ( p_gamepad[3] == 1 ) {
        analogWrite( m_pin_arm[0], DRIVER_BASIS );
        analogWrite( m_pin_arm[1], SPEED_ARM );
    }
    //arm DOWM
    else if ( p_gamepad[3] == 2 ) {
        analogWrite( m_pin_arm[0], SPEED_ARM );
        analogWrite( m_pin_arm[1], DRIVER_BASIS ); 
    }
    //arm STOP
    else {
        faststop( m_pin_arm );
    }   
}
//------------------End functioin defintion-------------------- 




void loop()
{
    static int p_gamepad[] = { 0, 0, 0, 0, 0 };
  
    static int p_gamepad_t[] = { tire, 0, 0, 0, 0 };
    static int p_gamepad_a[] = { arm, 0, 0, 0, 0 };
    
    
    int pwm_val[] = { 0, 0, 0, 0 };    
    boolean rotate[] = { true, true, true, true };

    
    int miss_catch_udp_count = get_command( p_gamepad );    // Get command and miss_catch_udp_count            
  
    if (miss_catch_udp_count > 5) {
        for (int i = 0; i < sizeof(p_gamepad); i++ ) {
            p_gamepad[i] = p_gamepad_a[i];
        }
    }   
    
    

    if ( p_gamepad[0] == tire ) {
        //Case Command is Drive 
        make_pwm ( p_gamepad, pwm_val );
        check_rotate ( p_gamepad, rotate );

        drive_uketori ( pwm_val, rotate );      
    }
    
    else if ( p_gamepad[0] == arm ) {
        //Case Command is Hand & Arm
        action_hand( p_gamepad );
        move_arm( p_gamepad );
    }

    delay( 30 );
}
