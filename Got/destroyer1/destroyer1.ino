
//【最終版】小山小僧が角材をまたぐためのプログラム(半独立系)
//for Arduino MEGA
#include <math.h>

#include "motor_drives5.h"      //モータ制御
#include "dist_sens.h"          //測距センサ

#include "params.h"             //パラメータ一覧

#define LEG 4    //脚の本数
#define reverse_val(x) (-1 * x)
//変数
motor_drives4 mt_leg[LEG];     //脚伸縮用モータ
blockFinders  bfs;             //角材検知用センサユニット(赤外線)
int           leg_sts;         //脚の伸縮ステータス
int           ir_pins[][IR_SENSES][IR_VAL_TYPES] = {
                                                       { {IR_PIN_FF, IR_VAL_FF ,IR_LED_FF} ,{IR_PIN_FR, IR_VAL_FR ,IR_LED_FR} }
                                                      ,{ {IR_PIN_MF, IR_VAL_MF ,IR_LED_MF} ,{IR_PIN_MR, IR_VAL_MR ,IR_LED_MR} }
                                                      ,{ {IR_PIN_RF, IR_VAL_RF ,IR_LED_RF} ,{IR_PIN_RR, IR_VAL_RR ,IR_LED_RR} }
                                                   };

//boolean       control_mode = true;        //制御モード(true:オート false:マニュアル)
boolean       control_flg[2]  = {false,true};
destroy_led   d_led = destroy_led(DESTROY_LED1,DESTROY_LED2);  //ピンは逆でも可
void setup(){
Serial.begin(9600);

  pinMode(MODE_PIN       ,INPUT);         //制御モード(自動/手動)識別用
  pinMode(MANUAL_FRNT_PIN,INPUT);         //手動モード時の前脚ステータス
  pinMode(MANUAL_BACK_PIN,INPUT);         //手動モード時の後脚ステータス

  //センサ
  bfs        = blockFinders(ir_pins);                //赤外線センサユニット
  leg_sts    = bfs.getLegStatus();                   //脚の状態

  //モータ設定初期化
  mt_leg[0]  = motor_drives4(MT_PIN_RF_A  ,MT_PIN_RF_B);//右前脚モータ
  mt_leg[1]  = motor_drives4(MT_PIN_LF_A  ,MT_PIN_LF_B);//左前脚モータ
  mt_leg[2]  = motor_drives4(MT_PIN_RB_A  ,MT_PIN_RB_B);//右後脚モータ
  mt_leg[3]  = motor_drives4(MT_PIN_LB_A  ,MT_PIN_LB_B);//左後脚モータ

  //モータドライバ充電
  for(int i = 0;i < LEG;i++){
    mt_leg[i].motor_charge();
  }
  delay(W_UP_WAIT_TIME_1);

  //脚状態初期化
  for(int i = 0;i < LEG;i++){
    mt_leg[i].motor_ini();
  }
  delay(W_UP_WAIT_TIME_2);

  //モータを止める
  for(int i = 0;i < LEG;i++){
    mt_leg[i].motor_stop();
  }
  Serial.println("Wake up ");
  ///////////////////////////////////////////
}

//脚の状態確認用
inline void legsts_view(int sts){
  if(sts == FULL_SHRINK){
    //Serial.print("Front:UP    Rear:UP");
  }
  else if(sts == FRNT_STRECH){
    //Serial.print("Front:DOWN  Rear:UP");
  }
  else if(sts == BACK_STRECH){
    //Serial.print("Front:UP    Rear:DOWN");
  }
  else if(sts == FULL_STRECH){
    //Serial.print("Front:DOWN  Rear:DOWN");
  }
  else{
    //Serial.print("Err");
  }
}


void loop(){
//Serial.print("[");
//Serial.print(digitalRead(MODE_PIN));
//Serial.print(":");
//Serial.print(digitalRead(MANUAL_FRNT_PIN));
//Serial.print(":");
//Serial.print(digitalRead(MANUAL_BACK_PIN));
//Serial.print("]");
  //モードチェック
//  if(digitalRead(MODE_PIN) == MANUAL_MODE && !control_flg){//マニュアルモード切替(オルタネート)
//    control_mode = !control_mode;
//    control_flg  = true;
//  }
//  else{
//    control_flg  = false;
//  }
  control_flg[1] = control_flg[0];
  control_flg[0] = digitalRead(MODE_PIN);
  bfs.blockFinding();

//  if(control_mode){
  if(control_flg[0] == AUTO_MODE){  //自動制御モード[妖精モード](通常時/通信途絶時)

    //モード切替直後
    if(control_flg[1] != control_flg[0]){
      bfs.unitClear();    //全センサユニットを初期化
      d_led.led_stop();   //モード識別ランプを消灯
    }

    //角材対応
    bfs.blockFinding();                //角材検知
    leg_sts = bfs.getLegStatus();      //脚の状態を得る

//legsts_view(leg_sts);//動作チェック用

    //各脚の伸縮を決める
    if(leg_sts == FULL_STRECH){//クローラを使わない場合
      for(int i = 0;i < LEG;i++){
        mt_leg[i].setTargetVal(reverse_val(MAX_DRIVE_VAL));    //全脚伸ばす
      }
    }
    else{//クローラを使う場合
      if(leg_sts == FRNT_STRECH){//前輪＋クローラ
        //前輪伸ばす
        mt_leg[0].setTargetVal(reverse_val(MAX_DRIVE_VAL));
        mt_leg[1].setTargetVal(reverse_val(MAX_DRIVE_VAL));
        //後輪収納
        mt_leg[2].setTargetVal(MAX_DRIVE_VAL);
        mt_leg[3].setTargetVal(MAX_DRIVE_VAL);
      }
      else if(leg_sts == BACK_STRECH){//クローラ＋後輪
        //前輪収納
        mt_leg[0].setTargetVal(MAX_DRIVE_VAL);
        mt_leg[1].setTargetVal(MAX_DRIVE_VAL);
        //後輪伸ばす
        mt_leg[2].setTargetVal(reverse_val(MAX_DRIVE_VAL));
        mt_leg[3].setTargetVal(reverse_val(MAX_DRIVE_VAL));
      }
      else if(leg_sts == FULL_SHRINK){//クローラのみ
        //全輪収納
        for(int i = 0;i < LEG;i++){
          mt_leg[i].setTargetVal(MAX_DRIVE_VAL);
        }
      }
    }

//Serial.println("");
  }

  else if(control_flg[0] == MANUAL_MODE){//マニュアルモード[デストロイモード](非常時/坂道運転時)
//Serial.print("[000000]");

//    bfs.destroy_marker();
    d_led.led_ctrl();
    //前脚コントロール
    if     (digitalRead(MANUAL_FRNT_PIN) == MANUAL_STRECH){//伸ばす
      mt_leg[0].setTargetVal(reverse_val(MAX_DRIVE_VAL));
      mt_leg[1].setTargetVal(reverse_val(MAX_DRIVE_VAL));
//Serial.print("[111111]");
    }
    else if(digitalRead(MANUAL_FRNT_PIN) == MANUAL_SHRINK){//収納
      mt_leg[0].setTargetVal(MAX_DRIVE_VAL);
      mt_leg[1].setTargetVal(MAX_DRIVE_VAL);
//Serial.print("[222222]");
    }
    //後脚コントロール
    if     (digitalRead(MANUAL_BACK_PIN) == MANUAL_STRECH){//伸ばす
      mt_leg[2].setTargetVal(reverse_val(MAX_DRIVE_VAL));
      mt_leg[3].setTargetVal(reverse_val(MAX_DRIVE_VAL));
//Serial.print("[333333]");
    }
    else if(digitalRead(MANUAL_BACK_PIN) == MANUAL_SHRINK){//収納
      mt_leg[2].setTargetVal(MAX_DRIVE_VAL);
      mt_leg[3].setTargetVal(MAX_DRIVE_VAL);
//Serial.print("[444444]");
    }
//Serial.println("");
  }

  //各脚を伸縮する
  for(int i = 0;i < LEG;i++){
    mt_leg[i].motor_drive();//右前脚
  }

}

