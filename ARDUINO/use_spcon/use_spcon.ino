#include "recv_udp.h"
#include <math.h>

#define MOTOR_CNT 4

extern int tire, cata, updown;

int VAL_LEFT_FRONT = 0, VAL_LEFT_REAR = 1, VAL_RIGT_FRONT = 2, VAL_RIGT_REAR = 3;
int CMD_LEFT_FRONT = 1, CMD_LEFT_REAR = 2, CMD_RIGT_FRONT = 3, CMD_RIGT_REAR = 4;

int m_pin_lf = 3;
int m_pin_lr = 5;
int m_pin_rf = 6;
int m_pin_rr = 9;

int m_pin_ud = 10;
int m_pin_oc = 11;


void setup()
{
    UDP_setup();
    Serial.begin( 9600 );
}


int calc_pwm( int p_gamepad_value ) 
{
    int plumi_p_gamepad = p_gamepad_value * -1;
    int ratio_p_gamepad = plumi_p_gamepad * 6;
    int origin190_p_gamepad = ratio_p_gamepad + 190;
    return origin190_p_gamepad;
}


void make_pwm( int* p_gamepad, int* pwm_val )
{
    pwm_val[ VAL_LEFT_FRONT ] = calc_pwm( p_gamepad[ CMD_LEFT_FRONT ] );
    pwm_val[ VAL_LEFT_REAR  ] = calc_pwm( p_gamepad[ CMD_LEFT_REAR  ] );
    pwm_val[ VAL_RIGT_FRONT ] = calc_pwm( p_gamepad[ CMD_RIGT_FRONT ] );
    pwm_val[ VAL_RIGT_REAR  ] = calc_pwm( p_gamepad[ CMD_RIGT_REAR  ] );
}


void drive_tire( int* pwm_val )
{
    analogWrite( m_pin_lf, pwm_val[ VAL_LEFT_FRONT ] );
    analogWrite( m_pin_lr, pwm_val[ VAL_LEFT_REAR  ] );
    analogWrite( m_pin_rf, pwm_val[ VAL_RIGT_FRONT ] );
    analogWrite( m_pin_rr, pwm_val[ VAL_LEFT_REAR  ] );
}

void loop()
{
    static int p_gamepad[] = { tire, 0, 0, 0, 0 };
    static int p_gamepad_t[] = { tire, 0, 0, 0, 0 };
    static int p_gamepad_c[] = { cata, 0, 0, 0, 0 };
    int pwm_val[] = { 0, 0, 0, 0 };

    int miss_catch_udp_count = get_command( p_gamepad );    // Get command and miss_catch_udp_count

    if (miss_catch_udp_count > 5) {
        for (int i = 0; i < sizeof(p_gamepad); i++ ) {
            p_gamepad[i] = p_gamepad_t[i];
        }
    }

    if (p_gamepad[0] == tire ) {
        make_pwm( p_gamepad, pwm_val );
        drive_tire( pwm_val );
    }

    delay( 30 );
}
