/////////////////////////////////////////////////////
//超音波センサ用クラス
//dist_sensクラス内部で使用

//定数はリアルガチプログラム内バックアップ版を参照のこと

#define SOS_TIME (348 * 0.001)  //[mm]

class us_senser{
  private:
    int dst;      //距離[mm]
    int t;        //パルスの反射時間[μs]
    int sens_pin;

  public:
    us_senser();
    us_senser(int p_pin);
    int getDistance();
};

/////////////////////////////////////////////////////
//ロボット本体部と床との距離を測るクラス

class dist_sens{
  private:
    //変数
//    int       sens_pin;        //センサが接続されているピン番号
//    int       sens_val;        //センサ値
//    double    sens_vale;       //電圧
    double    dist;            //距離(計算値)[mm]
    us_senser uss;             //超音波センサ用
    //関数

  public:
    //関数

    //コンストラクタ
    dist_sens();
    dist_sens(int p_pin);

    //距離を返す
    void calcDistance(double p_theta_x
                     ,double p_theta_y
                     );
    double getDistance();
};

