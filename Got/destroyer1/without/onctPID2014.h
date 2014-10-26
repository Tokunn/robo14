//PID制御クラスのヘッダファイル

#include <arduino.h>
#include "params.h"

#ifndef onct_PID2014
#define onct_PID2014

//積分計算用インターバルタイム
#define DELTA_T 20              //[ms]

class onctPID2014{
  private:
    int    diff1;         //入力値と目標値の差
    int    diff2;         //入力値と目標値の差
    double integral;      //積分値
    double kp;            //比例パラメータ
    double ki;            //積分パラメータ
    double kd;            //微分パラメータ
    int    target_val;    //目標値

    //関数

    //リミッタ
    double math_limit(double rtn_val    //入力値
                     ,double min_val    //最小値
                     ,double max_val    //最大値
                     );

  public:
    //関数
    //コンストラクタ
    onctPID2014();
    onctPID2014(double p_kp        //比例パラメータ
               ,double p_ki        //積分パラメータ
               ,double p_kd        //微分パラメータ
               ,double p_target    //目標値
               );

    double pid(int sensor_val);      //PID野郎
    void   setTargetVal(int p_val);  //setter:目標値
    void   clr_integral();           //積分値をリセットする
};
#endif

