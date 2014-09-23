#include <Servo.h>
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

Servo myservo;
Servo myservo2;

void setup()
{
    UDP_setup();
    Serial.begin( 9600 );
    pinMode(9, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(3, OUTPUT);
    myservo.attach(9);
    myservo.write(90);
    myservo2.attach(3);
    myservo2.write(90);
}


int calc_pwm( int p_gamepad_value ) 
{
    int plumi_p_gamepad = p_gamepad_value * -1;
    int ratio_p_gamepad = plumi_p_gamepad * 6;
    int origin190_p_gamepad = ratio_p_gamepad + 190;
    return origin190_p_gamepad;
}


void drive_tire( int* p_gamepad )
{
    if (p_gamepad[ CMD_LEFT_REAR ] >= 5) {
        myservo.write(50);
    }
    else if (p_gamepad[ CMD_LEFT_REAR ] <= -5) {
        myservo.write(140);
    }
    else {
        myservo.write(90);
    }
    if (p_gamepad[ CMD_RIGT_REAR ] >= 5) {
        myservo2.write(50);
    }
    else if (p_gamepad[ CMD_RIGT_REAR ] <= -5) {
        myservo2.write(140);
    }
    else {
        myservo2.write(90);
    }

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

    if (p_gamepad[0] == tire || p_gamepad[0] == cata) {
        drive_tire( p_gamepad );
    }

    delay( 30 );
}
