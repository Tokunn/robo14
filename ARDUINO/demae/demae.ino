#include "recv_udp.h"
#include <math.h>

#define MOTOR_CNT 4

extern int tire, cata, updown;

int VAL_LEFT = 0, VAL_RIGT = 1;
int CMD_LEFT = 1, CMD_RIGT = 2;

int m_pin_lf[] = { 2, 3 };
int m_pin_ll[] = { 4, 5 };
int m_pin_rf[] = { 6, 7 };
int m_pin_rl[] = { 8, 9 };

void setup()
{
    UDP_setup();
    Serial.begin( 9600 );
}


void make_pwm( int* p_gamepad, int* pwm_val )
{
    pwm_val[ VAL_LEFT ] = 255 - ( abs( p_gamepad[ CMD_LEFT ] ) * 25 );
    pwm_val[ VAL_RIGT ] = 255 - ( abs( p_gamepad[ CMD_RIGT ] ) * 25 );
}


void check_rotate( int* p_gamepad, boolean* rotate )
{
    if ( p_gamepad[ CMD_LEFT ] >= 0 ) {
        rotate[ VAL_LEFT ] = true;
    }
    else {
        rotate[ VAL_LEFT ] = false;
    }

    if ( p_gamepad[ CMD_RIGT ] >= 0 ) {
        rotate[ VAL_RIGT ] = true;
    }
    else {
        rotate[ VAL_RIGT ] = false;
    }
}


void drive_demae( int* pwm_val, boolean* rotate )
{
    if ( rotate[ VAL_LEFT ] ) {
        analogWrite( m_pin_lf[0], pwm_val[ VAL_LEFT ] );
        analogWrite( m_pin_lf[1], 255 );

        analogWrite( m_pin_ll[0], pwm_val[ VAL_LEFT ] );
        analogWrite( m_pin_ll[1], 255 );
    }
    else if ( !rotate[ VAL_LEFT ] ) {
        analogWrite( m_pin_lf[0], 255 );
        analogWrite( m_pin_lf[1], pwm_val[ VAL_LEFT ] );

        analogWrite( m_pin_ll[0], 255 );
        analogWrite( m_pin_ll[1], pwm_val[ VAL_LEFT ] );
    }
    if ( rotate[ VAL_RIGT ] ) {
        analogWrite( m_pin_rf[0], pwm_val[ VAL_RIGT ] );
        analogWrite( m_pin_rf[1], 255 );

        analogWrite( m_pin_rl[0], pwm_val[ VAL_RIGT ] );
        analogWrite( m_pin_rl[1], 255 );
    }
    else if ( !rotate[ VAL_RIGT ] ) {
        analogWrite( m_pin_rf[0], 255 );
        analogWrite( m_pin_rf[1], pwm_val[ VAL_RIGT ] );

        analogWrite( m_pin_rl[0], 255 );
        analogWrite( m_pin_rl[1], pwm_val[ VAL_RIGT ] );
    }
}


void debug_print( int* pwm_val, boolean* rotate )
{
    Serial.print( pwm_val[0] );

    Serial.print( pwm_val[1] );

    Serial.println( "" );
}


void loop()
{
    int p_gamepad[] = { tire, 0, 0 };
    int pwm_val[] = { 0, 0 };
    boolean rotate[] = { true, true };

    get_command( p_gamepad );

    make_pwm( p_gamepad, pwm_val );
    check_rotate( p_gamepad, rotate );

    drive_demae( pwm_val, rotate );
    //debug_print( pwm_val );

    delay( 30 );
}
