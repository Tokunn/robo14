//PID制御クラスのソースファイル

#include <arduino.h>
#include <math.h>
#include "onctPID2014.h"

 onctPID2014::onctPID2014(){};
 onctPID2014::onctPID2014(double p_kp,double p_ki,double p_kd,double p_target){
  //変数を初期化
  diff1      = 0;
  diff2      = 0;
  kp         = p_kp;    //比例定数
  ki         = p_ki;    //積分定数
  kd         = p_kd;    //微分定数
  integral   = 0;       //積分値
  target_val = p_target;
};

//最大値と最小値を制限する
double onctPID2014::math_limit(double rtn_val,double min_val,double max_val){
  if     (rtn_val > max_val) return max_val;
  else if(rtn_val < min_val) return min_val;
  else                       return rtn_val;
}

//PID制御の目標値を設定する
void onctPID2014::setTargetVal(int p_val){
  if(p_val != target_val){
    clr_integral();
  }
  target_val = p_val;
}

//PID処理本体
double onctPID2014::pid(int sensor_val){

  double p,i,d;

  //diff1が古い値
  //diff2が新しい値

  diff1   = diff2;
  diff2   = target_val - sensor_val;              //目標値と現在値の差を得る
  integral += (diff2 + diff1) / 2.0 * DELTA_T;    //積分値を蓄積する

  p = kp * diff2;                                 //比例値を得る
  i = ki * integral;                              //積分値を得る
  d = kd * (diff2 - diff1) / DELTA_T;             //微分値を得る

  //一定幅の間で出力値を返す
  return fabs(math_limit(p + i + d, MAX_DRIVE_VAL, MIN_DRIVE_VAL));

};

//積分値をリセットする
void onctPID2014::clr_integral(){
  integral = 0;
}

