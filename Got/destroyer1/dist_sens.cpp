//各種測距センサ用クラス

#include <arduino.h>
#include <math.h>
#include "dist_sens.h"
#include "params.h"

//////////////////////////////////////////////////////////
//blockFinderUnitクラス
//測距センサ1ペア分の管理用

//コンストラクタ
 blockFinderUnit::blockFinderUnit(){};
 blockFinderUnit::blockFinderUnit(int p_pins[][IR_VAL_TYPES]){

  pinF    = p_pins[IR_FRNT][BFU_OUTPUT];     //前側センサの接続ピン
  pinB    = p_pins[IR_BACK][BFU_OUTPUT];     //後側センサの接続ピン
  pinFval = p_pins[IR_FRNT][BFU_VALUE];      //前側センサの調整用ピン
  pinBval = p_pins[IR_BACK][BFU_VALUE];      //後側センサの調整用ピン
  pinFled = p_pins[IR_FRNT][BFU_LED];        //前側センサのインジケータランプ
  pinBled = p_pins[IR_BACK][BFU_LED];        //後側センサのインジケータランプ
//  flg[0]  = false;                           //前側センサの反応状態
//  flg[1]  = false;                           //後側センサの反応状態
//  i[0]    = 0;                               //角材カウンタ(now)
//  i[1]    = 0;                               //角材カウンタ(old)
//  sts[0]  = 0;                               //センサユニットのステータス(直近)(now)
//  sts[1]  = 10;                              //センサユニットのステータス(直近)(old)
//  bsts[0] = 10;                              //センサユニットのステータス(遷移)(now)
//  bsts[1] = 10;                              //センサユニットのステータス(遷移)(old)
//  way_flg = false;                           //角材を見つけたときのロボットの移動方向
  unitClear();                               //各種値の初期化

  //センサ調整用
  pinMode(pinFled,OUTPUT);
  pinMode(pinBled,OUTPUT);
  digitalWrite(pinFled,LOW);
  digitalWrite(pinBled,LOW);
}

//角材検知機能本体
void blockFinderUnit::block_finder(){
  flg[IR_FRNT] = getSts(pinF,pinFval);
  flg[IR_BACK] = getSts(pinB,pinBval);
  digitalWrite(pinFled,flg[IR_FRNT]);
  digitalWrite(pinBled,flg[IR_BACK]);

  sts[1] = sts[0];
  if     (flg[0]&&flg[0]!=flg[1]) sts[0] = IR_FRNT_ON;  //前側センサのみ反応あり
  else if(flg[0]&&flg[1])         sts[0] = IR_BOTH_ON;  //両方のセンサに反応あり
  else if(flg[1]&&flg[0]!=flg[1]) sts[0] = IR_BACK_ON;  //後側センサのみ反応あり
  else                            sts[0] = IR_BOTH_OFF;  //反応なし

  if(sts[0] != sts[1]){//ステータスが変わったとき
    i[1] = i[0];  //角材の数の変化を控えておく
    if( sts[0] == IR_BACK_ON
    && bsts[0] == IR_BOTH_ON
    && bsts[1] == IR_FRNT_ON){//前→後(増)
      i[0]++;
//      way_flg = true;
    }
    else if(sts[0] == 1 && bsts[0] == 2 && bsts[1] == 3){//後→前(減)
      i[0]--;
//      way_flg = false;
    }
    //ステータスが何から何に変わったか控えておく
    bsts[1] = bsts[0];
    bsts[0] = sts[0];
  }
Serial.print("(");
Serial.print(bsts[0]);
Serial.print(":");
Serial.print(bsts[1]);
Serial.print(")");
}

boolean blockFinderUnit::getSts(int p_pin                  //赤外線センサ
                               ,int p_pin_val              //感度調整用ボリューム
                               ){
  tmp_sens_val = analogRead(p_pin);      //センサ値を得る
  tmp_val_val  = analogRead(p_pin_val);  //しきい値を得る


  //センサの値を丸める
  tmp_val_val  /= IR_SENSITIV_VAL;
  tmp_val_val  *= IR_SENSITIV_VAL;

  //調整ボリュームの値を丸める
  tmp_val_val  /= IR_SENSITIV_VAL;
  tmp_val_val  *= IR_SENSITIV_VAL;
  tmp_val_val  += (IR_SENSITIV_VAL/2);
//Serial.print("[");
//Serial.print(tmp_sens_val);
//Serial.print(tmp_val_val);
//Serial.print("]");

  if     (tmp_sens_val >  tmp_val_val) return true;        //角材あり
  else if(tmp_sens_val <= tmp_val_val) return false;       //なし
}

//センサユニットのステータスを返す
int blockFinderUnit::getUnitStatus(){
  return sts[0];
}

//またいだ角材数を返す
int blockFinderUnit::getBlkCnt(){
  return i[0];
}

//角材上でロボットが動いた方向を返す
boolean blockFinderUnit::getWayFlg(){

  if(bsts[0] < bsts[1]) way_flg = false;  //後退時
  else                  way_flg = true;   //前進時

  return way_flg;
}

//角材検知ユニットのデータを初期化する
void blockFinderUnit::unitClear(){
  flg[0]  = false;                           //前側センサの反応状態
  flg[1]  = false;                           //後側センサの反応状態
  i[0]    = 0;                               //角材カウンタ(now)
  i[1]    = 0;                               //角材カウンタ(old)
  sts[0]  = 0;                               //センサユニットのステータス(直近)(now)
  sts[1]  = 10;                              //センサユニットのステータス(直近)(old)
  bsts[0] = 10;                              //センサユニットのステータス(遷移)(now)
  bsts[1] = 10;                              //センサユニットのステータス(遷移)(old)
  way_flg = false;                           //角材を見つけたときのロボットの移動方向
}

//マニュアルモード時にセンサ調整用LEDを互い違いに点灯させる
void blockFinderUnit::destroy_marker(boolean p_mt_led){
    digitalWrite(pinFled,!p_mt_led);
    digitalWrite(pinBled, p_mt_led);
}

//移動方向フラグを設定する
void blockFinderUnit::set_wayFlg(boolean p_flg){
  way_flg = p_flg;
}

//////////////////////////////////////////////////////////
//blockFindersクラス
//センサユニット3個を1グループとして連動管理する

//コンストラクタ
 blockFinders::blockFinders(){};
 blockFinders::blockFinders(int p_pins[][IR_SENSES][IR_VAL_TYPES]){

  //センサユニット初期化
  bfu[0] = blockFinderUnit(p_pins[0]);
  bfu[1] = blockFinderUnit(p_pins[1]);
  bfu[2] = blockFinderUnit(p_pins[2]);

  //脚部伸縮フラグ
  leg_flg[FRNT_LEGS] = true;
  leg_flg[BACK_LEGS] = true;

  leg_sts            = FULL_STRECH;
 }

//角材探知、脚伸縮ロジック本体
//戻り値：
//  0:両方伸ばす
//  1:前だけ縮める
//  2:両方縮める
//  3:後だけ縮める
void blockFinders::blockFinding(){
  //角材の有無を調べる
  for(int i = 0;i<3;i++){
    bfu[i].block_finder();
  }

//各位置の通過本数を見る
Serial.print("[");
Serial.print(bfu[0].getBlkCnt());
Serial.print("][");
Serial.print(bfu[1].getBlkCnt());
Serial.print("][");
Serial.print(bfu[2].getBlkCnt());
Serial.print("]");

//Serial.print("(");
//Serial.print(bfu[0].getWayFlg());
//Serial.print(")(");
//Serial.print(bfu[1].getWayFlg());
//Serial.print(")(");
//Serial.print(bfu[2].getWayFlg());
//Serial.print(")");

  //進入向きフラグ設定
  if(bfu[0].getBlkCnt() == bfu[1].getBlkCnt() && bfu[1].getBlkCnt() == bfu[2].getBlkCnt()){
    if(bfu[0].getUnitStatus() == 1 && bfu[1].getUnitStatus() == 0 && bfu[2].getUnitStatus() == 0){//前進で角材を越え始めた場合
      set_wayFlg(GO_FWRD);
    }
    else if(bfu[0].getUnitStatus() == 0 && bfu[1].getUnitStatus() == 0 && bfu[2].getUnitStatus() == 1){//後進で角材を越え始めた場合
      set_wayFlg(GO_BACK);
    }
  }

  //またいでいる途中の角材が無い場合
  if((bfu[0].getBlkCnt() == bfu[1].getBlkCnt() && bfu[1].getBlkCnt() == bfu[2].getBlkCnt())
  && (bfu[0].getUnitStatus() == 0 && bfu[1].getUnitStatus() == 0 && bfu[2].getUnitStatus() == 0)){
    //全脚を伸ばす
    leg_flg[FRNT_LEGS] = true;
    leg_flg[BACK_LEGS] = true;
  }
  else{

    //前脚を縮めるフラグ
    if(
      (bfu[0].getUnitStatus() >  0 && bfu[0].getBlkCnt() == bfu[1].getBlkCnt() &&  bfu[0].getWayFlg())    //前部センサの条件
    ||(bfu[1].getUnitStatus() == 1 && bfu[0].getBlkCnt() >  bfu[1].getBlkCnt() && !bfu[1].getWayFlg())    //重心部センサの条件
    ){
      leg_flg[FRNT_LEGS] = false;
    }

    //前脚を伸ばすフラグ
    else if(
      (bfu[0].getUnitStatus() == 0 && bfu[0].getBlkCnt() == bfu[1].getBlkCnt())   //前部センサの条件
    ||(bfu[0].getUnitStatus() >  0 && bfu[0].getBlkCnt() == bfu[1].getBlkCnt() && !bfu[0].getWayFlg())    //前部センサの条件
    ||(bfu[1].getUnitStatus() == 1 && bfu[0].getBlkCnt() >  bfu[1].getBlkCnt() &&  bfu[1].getWayFlg())    //重心部センサの条件
    ){
      leg_flg[FRNT_LEGS] = true;
    }
  
    //後脚を縮めるフラグ
    if(
      (bfu[2].getUnitStatus() >  0 && bfu[1].getBlkCnt() == bfu[2].getBlkCnt() && !bfu[2].getWayFlg())   //後部センサの条件
    ||(bfu[1].getUnitStatus() == 3 && bfu[1].getBlkCnt() >  bfu[2].getBlkCnt() &&  bfu[1].getWayFlg())   //重心部センサの条件
    ){
      leg_flg[BACK_LEGS] = false;
    }

    //後脚を伸ばすフラグ
    else if(
//      (bfu[2].getUnitStatus() >  1 && bfu[1].getBlkCnt() >= bfu[2].getBlkCnt())   //後部センサの条件
      (bfu[2].getUnitStatus() == 3 && bfu[1].getBlkCnt() == bfu[2].getBlkCnt())   //後部センサの条件
    ||(bfu[1].getUnitStatus() >  1 && bfu[1].getBlkCnt() >  bfu[2].getBlkCnt() && !bfu[2].getWayFlg())   //重心部センサの条件
    ||(bfu[2].getUnitStatus() == 3 && bfu[1].getBlkCnt() == bfu[2].getBlkCnt() &&  bfu[2].getWayFlg())   //後部センサの条件
    ){
      leg_flg[BACK_LEGS] = true;
    }
  }
  //フラグを基にステータスを設定する
  if(     !leg_flg[FRNT_LEGS] && !leg_flg[BACK_LEGS]) leg_sts = FULL_SHRINK;  //全脚縮める
  else if( leg_flg[FRNT_LEGS] && !leg_flg[BACK_LEGS]) leg_sts = FRNT_STRECH;  //前脚のみ伸ばす
  else if(!leg_flg[FRNT_LEGS] &&  leg_flg[BACK_LEGS]) leg_sts = BACK_STRECH;  //後脚のみ伸ばす
  else                                                leg_sts = FULL_STRECH;  //全脚伸ばす
//Serial.print("[[");
//Serial.print(leg_sts);
//Serial.print("]]");
};

//脚の伸縮ステータスを得る
int blockFinders::getLegStatus(){
  return leg_sts;
}

//全センサユニットの値を初期化する
void blockFinders::unitClear(){
  for(int i=0;i<IR_UNITS;i++){
    bfu[i].unitClear();
  }
}

//マニュアルモード時にセンサ調整用LEDを点滅させる
void blockFinders::destroy_marker(){
  mt_t_tmp = millis();
  if(mt_t + D_TIME < mt_t_tmp){
    mt_t = mt_t_tmp;
    mt_led = !mt_led;
    bfu[0].destroy_marker(mt_led);
    bfu[1].destroy_marker(mt_led);
    bfu[2].destroy_marker(mt_led);
  }
}

//移動方向フラグを設定する
void blockFinders::set_wayFlg(boolean p_flg){
  bfu[0].set_wayFlg(p_flg);
  bfu[1].set_wayFlg(p_flg);
  bfu[2].set_wayFlg(p_flg);
}

//コンストラクタ
 destroy_led::destroy_led(int p_led1,int p_led2){
  led1 = p_led1;
  led2 = p_led2;
}
//LEDチカチカ
void destroy_led::led_ctrl(){
   mt_t_tmp = millis();
  if(mt_t + D_TIME < mt_t_tmp){
    mt_t = mt_t_tmp;
    mt_led = !mt_led;
    digitalWrite(led1, mt_led);
    digitalWrite(led2,!mt_led);
  }
}
void destroy_led::led_stop(){
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
}

