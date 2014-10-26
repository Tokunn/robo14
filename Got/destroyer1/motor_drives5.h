//モータ駆動クラスのヘッダファイル

#include <arduino.h>

#ifndef MOTOR_DRIVES4
#define MOTOR_DRIVES4

//クラス定義
class motor_drives4{
  private:
    //変数
    int           outa_pin;                  //モータドライバ用ピン
    int           outb_pin;                  //モータドライバ用ピン
    int           now_val;                   //現在の値
    int           old_val;                   //直前の値
    unsigned long tm_stops;                  //ブレーキをかけ始めた時刻
    unsigned long sign_turn_time;            //モータの回転方向が逆転した時刻
    boolean       sign_turn_flg;             //モータの回転方向が逆転を判断するためのフラグ 反転時:true、非反転時:false
    unsigned long tmp_tm;                    //
    //関数
    boolean isStop();                        //モータを止めるべきか判定する
//    boolean chk_turn_mode();                 //モータの回転方向(信号)が逆転したかチェックする
    int     drive_val(double p_val);         //モータの制御量を決める
    void    motor_turn();                    //モータを回す

  public:
    //関数
    //コンストラクタ
    motor_drives4();
    motor_drives4(int    p_outa_pin          //モータ用ピン
                 ,int    p_outb_pin          //モータ用ピン
                 );

    void motor_charge();                     //モータドライバ起動時チャージ用
    void motor_ini();                        //モータドライバ起動時チャージ用
    void motor_drive();                      //モータを制御する
    void motor_stop();                       //モータを止める(ブレーキ) 
    void setTargetVal(double p_val);         //目標値をセットする

};
#endif

