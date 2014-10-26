//計算により得た値を基に1個のモータを回すクラス
#include <arduino.h>
#include <math.h>
#include "motor_drives5.h"
#include "params.h"

  //コンストラクタ
  motor_drives4::motor_drives4(){};
  motor_drives4::motor_drives4(int    p_outa_pin        //モータ用ピン
                              ,int    p_outb_pin        //モータ用ピン
                              ){
    outa_pin      = p_outa_pin;                         //モータドライバに接続するピンを設定
    outb_pin      = p_outb_pin;                         //モータドライバに接続するピンを設定
    sign_turn_flg = false;
  };

  //モータの制御量を決める
  int motor_drives4::drive_val(double p_val){
//    return (int)pid_xy.pid(p_val);
    return p_val;
  }

  //モータを止める(ブレーキ)
  void motor_drives4::motor_stop(){
    analogWrite(outa_pin,STOP_VAL);
    analogWrite(outb_pin,STOP_VAL);
  }

  //モータドライバ充電
  void motor_drives4::motor_charge(){
    analogWrite(outa_pin,INI_DRIVE_VAL);
    analogWrite(outb_pin,INI_DRIVE_VAL);
  }

  //脚を強制的に伸ばす
  void motor_drives4::motor_ini(){
    analogWrite(outa_pin,BASE_VAL);
    analogWrite(outb_pin,INI_DRIVE_VAL);
  }

  //モータを回転させる
  void motor_drives4::motor_turn(){

    if(now_val >= 0){//脚を縮める
      analogWrite(outa_pin,drive_val(abs(BASE_VAL - now_val)) );
      analogWrite(outb_pin,BASE_VAL);
Serial.print("[UP NOW]");
    }
    else{//脚を伸ばす
      analogWrite(outa_pin,BASE_VAL);
      analogWrite(outb_pin,drive_val(abs(BASE_VAL - now_val)) );
Serial.print("[DOWN NOW]");
    }
  }

  //モータを止めるべきか判定する
  boolean motor_drives4::isStop(){
    tmp_tm = millis();
    if(sign_turn_flg){          //モータの回転方向(入力信号)が逆転した場合
      sign_turn_time = millis();  //逆転した時刻を得る
      sign_turn_flg  = false;
    }
    //止めるべき時刻でない
    if((tmp_tm >= (sign_turn_time + DRIVE_WAIT_TIME))    //逆転してから一定時間待った後
    && (tmp_tm <= (sign_turn_time + DRIVE_STOP_TIME))    //逆転してから脚を伸ばし切った/縮め切ったと思われる時間経っていない
     ){
       return false;         //止めない
     }
     else{
       return true;           //止める
     }
  }

  //モータを制御する
  void motor_drives4::motor_drive(){

    //モータを止める場合
    if(isStop()){
      motor_stop();                 //モータを止める
    }

    //モータを回す場合
    else{
      motor_turn();                 //モータを回す
    }
  }

  //PID処理の目標値を再設定する
  void motor_drives4::setTargetVal(double p_val){
    old_val = now_val;              //変更直前の値を取っておく
    now_val = p_val;                //現在の値を更新する
    if(old_val != now_val){
      sign_turn_flg = true;    //反転したとき
    }
    else{
      sign_turn_flg = false;   //反転していないとき
    }
  };

