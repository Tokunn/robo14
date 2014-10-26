/////////////////////////////////////////////////////
//超音波センサ用クラス
//今回は未使用

  //コンストラクタ
  us_senser::us_senser(){};
  us_senser::us_senser(int p_pin){
    sens_pin = p_pin;
  };

  //距離を得る
  int us_senser::getDistance(){

    //パルス出力設定
    pinMode(sens_pin,OUTPUT);
    digitalWrite(sens_pin,LOW);

    //パルスを出力する
    digitalWrite(sens_pin,HIGH);
    delayMicroseconds(2);
    digitalWrite(sens_pin,LOW);

    //パルス受信設定
    delayMicroseconds(5);
    pinMode(sens_pin,INPUT);

//    //パルスを受信する
    t = pulseIn(sens_pin,HIGH,US_TIMEOUT);

    dst = t * SOS_TIME / 2;    //受信したパルスの長さを基に距離を得る
    return dst;                //距離を返す
  };

/////////////////////////////////////////////////////
//ロボット本体部と床との距離を測るクラス
//今回は未使用

  //コンストラクタ
  dist_sens::dist_sens(){}
  dist_sens::dist_sens(int p_pin){
    uss  = us_senser(p_pin);    //超音波センサ
    dist = 0;                   //ロボットと地面との距離
  }

  //距離を計算する
  void dist_sens::calcDistance(double p_theta_x
                              ,double p_theta_y
                              ){

    //センサ値よりロボットと地面との距離を得る
    dist = (double)uss.getDistance();

    //傾きによる誤差を補正する
    dist = dist * sin(p_theta_x);          //x方向の傾き
    dist = dist * sin(p_theta_y);          //y方向の傾き
  }

  //距離を返す
  double dist_sens::getDistance(){
    return dist;
  };

