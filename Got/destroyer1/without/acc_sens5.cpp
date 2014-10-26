//加速度センサの値から角度を得るクラス

//まっすぐな状態が0度、+-90度で計算する

#include <arduino.h>
#include <math.h>
#include "acc_sens5.h"

  //コンストラクタ
  acc_sens4::acc_sens4(){};
  acc_sens4::acc_sens4(int p_xy_pin
                      ,int p_z_pin
                      ){
    xy_pin = p_xy_pin;            //センサに接続されたピンを指定する
    z_pin  = p_z_pin;             //センサに接続されたピンを指定する
  }

  //加速度センサの値を読み取る
  void acc_sens4::read_sens_val(){
    xy = analogRead(xy_pin);
    z  = analogRead(z_pin);
  }

  //計算により、xy-z間の角度を得る
  void acc_sens4::write_theta(){

    read_sens_val();          //加速度センサの値を読み取る
    theta_b = theta;          //直前のx角度を保持

    //下処理
    xy       -= V_OFFSET;
    z        -= V_OFFSET;
    theta     = 0.0;
    theta_d   = 0.0;

    //分母が 0 でない場合
    //角度[rad][deg]を得る
    if(xy != 0){
      theta   = atan2((double)z,(double)xy);// -HALF_PI;   //x-z間の角度[rad]を得る
      theta_d = theta * 180 / PI;                       //x-z間の角度[deg]を得る
    }
  }

  //xy-z間の角度[rad]を返す
  double acc_sens4::rtn_theta(){
    return theta;
  }

  //直前のxy-z間の角度[rad]を返す
  double acc_sens4::rtn_theta_b(){
    return theta_b;
  }
  //xy-z間の角度[deg]を返す
  double acc_sens4::rtn_theta_d(){
    return theta_d;
  };

