#include "recv_udp.h"
#include <math.h>

#define MOTOR_CNT 4

extern int tire, cata, updown;

int VAL_LEFT_FRONT = 0, VAL_LEFT_REAR = 1, VAL_RIGT_FRONT = 2, VAL_RIGT_REAR = 3;
int CMD_LEFT_FRONT = 1, CMD_LEFT_REAR = 2, CMD_RIGT_FRONT = 3, CMD_RIGT_REAR = 4;

int m_pin_lf[] = { 2, 3 };
int m_pin_lr[] = { 4, 5 };
int m_pin_rf[] = { 6, 7 };
int m_pin_rr[] = { 8, 9 };

void setup()
{
    UDP_setup();
    Serial.begin( 9600 );
}


void make_pwm( int* p_gamepad, int* pwm_val )
{
    pwm_val[ VAL_LEFT_FRONT ] = 255 - ( abs( p_gamepad[ CMD_LEFT_FRONT ] ) * 25 );
    pwm_val[ VAL_LEFT_REAR ] = 255 - ( abs( p_gamepad[ CMD_LEFT_REAR ] ) * 25 );
    pwm_val[ VAL_RIGT_FRONT ] = 255 - ( abs( p_gamepad[ CMD_RIGT_FRONT ] ) * 25 );
    pwm_val[ VAL_RIGT_REAR ] = 255 - ( abs( p_gamepad[ CMD_RIGT_REAR ] ) * 25 );
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


void drive_demae( int* pwm_val, boolean* rotate )
{
    if ( rotate[ VAL_LEFT_FRONT ] ) {       // LF
        analogWrite( m_pin_lf[0], pwm_val[ VAL_LEFT_FRONT ] );
        analogWrite( m_pin_lf[1], 255 );
    }
    else if ( !rotate[ VAL_LEFT_FRONT ] ) {
        analogWrite( m_pin_lf[0], 255 );
        analogWrite( m_pin_lf[1], pwm_val[ VAL_LEFT_FRONT ] );
    }

    if ( rotate[ VAL_LEFT_REAR ] ) {        // LR
        analogWrite( m_pin_lr[0], pwm_val[ VAL_LEFT_REAR ] );
        analogWrite( m_pin_lr[1], 255 );
    }
    else if ( !rotate[ VAL_LEFT_REAR ] ) {
        analogWrite( m_pin_lr[0], 255 );
        analogWrite( m_pin_lr[1], pwm_val[ VAL_LEFT_REAR ] );
    }

    if ( rotate[ VAL_RIGT_FRONT ] ) {       // RF
        analogWrite( m_pin_rf[0], pwm_val[ VAL_RIGT_FRONT ] );
        analogWrite( m_pin_rf[1], 255 );
    }
    else if ( !rotate[ VAL_RIGT_FRONT ] ) {
        analogWrite( m_pin_rf[0], 255 );
        analogWrite( m_pin_rf[1], pwm_val[ VAL_RIGT_FRONT ] );
    }

    if ( rotate[ VAL_RIGT_REAR ] ) {       // RR
        analogWrite( m_pin_rr[0], pwm_val[ VAL_RIGT_REAR ] );
        analogWrite( m_pin_rr[1], 255 );
    }
    else if ( !rotate[ VAL_RIGT_REAR ] ) {
        analogWrite( m_pin_rr[0], 255 );
        analogWrite( m_pin_rr[1], pwm_val[ VAL_RIGT_REAR ] );
    }
}

void loop()
{
    int p_gamepad[] = { tire, 0, 0, 0, 0 };
    int pwm_val[] = { 0, 0, 0, 0 };
    boolean rotate[] = { true, true, true, true };

    get_command( p_gamepad );

    make_pwm( p_gamepad, pwm_val );
    check_rotate( p_gamepad, rotate );

    drive_demae( pwm_val, rotate );

    delay( 30 );
}