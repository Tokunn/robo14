//加速度センサの値から角度を得るクラス

#ifndef ACC_SENS4
#define ACC_SENS4

//補正値
#define V_OFFSET (1023/2)      //オフセット電圧(0Gあたりの出力電圧)
#define V_1G     (1023/5)      //1Gあたりの出力振幅
#define DELTAT_STP 10         //モータを一時停止する時間[ms]

//クラス定義
class acc_sens4{
  private:
    int    xy_pin;                        //xyの値を返すセンサピン
    int    z_pin;                         //zの値を返すセンサピン
    int    xy;                            //xyのセンサ値
    int    z;                             //zのセンサ値
    double theta;                         //xy-z間の角度[rad]
    double theta_d;                       //xy-z間の角度[deg]
    double theta_b;                       //直前のx-z間の角度[rad]

    void   read_sens_val();               //加速度センサの値を読み取る

  public:
    acc_sens4();                          //空コンストラクタ
    acc_sens4(int p_xy_pin                 //コンストラクタ
             ,int p_z_pin
             );

    //xy方向の角度を返す
    double rtn_theta();                   //x-z間の角度[rad]を返す
    double rtn_theta_d();                 //x-z間の角度[deg]を返す
    double rtn_theta_b();                 //直前のx-z間の角度[rad]を返す

    //角度を計算する
    void   write_theta();                 //計算により、xy-z間の角度を得る

};
#endif

