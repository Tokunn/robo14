//各種測距センサ用クラス

#include <arduino.h>

#ifndef DIST_SENS
#define DIST_SENS

//前後脚の識別添え字
#define FRNT_LEGS  0        //添え字[前脚]
#define BACK_LEGS  1        //添え字[後脚]

//測距センサ類接続用添え字
#define BFU_OUTPUT 0         //添え字[センサ本体]
#define BFU_VALUE  1         //添え字[調整用ボリューム]
#define BFU_LED    2         //添え字[LED]

//四脚全体のステータス
#define FULL_SHRINK    2     //全脚縮める
#define FRNT_STRECH    3     //前脚のみ伸ばす
#define BACK_STRECH    1     //後脚のみ伸ばす
#define FULL_STRECH    0     //全脚伸ばす

//赤外線センサユニット識別添え字
#define IR_FRNT        0     //測距センサ(前側)
#define IR_BACK        1     //測距センサ(後側)

//赤外線センサユニットのステータス
#define IR_BOTH_OFF    0     //両センサOFF
#define IR_FRNT_ON     1     //前側センサのみON
#define IR_BOTH_ON     2     //後側センサのみON
#define IR_BACK_ON     3     //両センサON

//配列添え字
#define IR_UNITS       3     //赤外線センサのユニット数(3セット)
#define IR_SENSES      2     //連動する赤外線センサ1ユニット分の個数(ペア)
#define IR_VAL_TYPES   3     //赤外線センサに関するパラメタ数(信号線、しきい値、パイロットランプ)

#define D_TIME       500     //マニュアルモード時のランプ点滅間隔[ms]

//進行方向の識別用
#define GO_FWRD     true     //前進
#define GO_BACK    !GO_FWRD  //後進

/////////////////////////////////////////////////////
//blockFinderUnitクラス
//測距センサ1ペア分の管理用
//blockFindersクラス内部で使用

//センサユニットのステータス
//0:全センサOFF
//1:前側センサのみON
//2:全センサON
//3:後側センサのみON

class blockFinderUnit{

  private:
    int          pinF;             //前側センサ接続ピン
    int          pinB;             //後側センサ接続ピン
    int          pinFval;          //前側センサ調整ボリューム用ピン
    int          pinBval;          //後側センサ調整ボリューム用ピン
    int          pinFled;          //前側センサ調整LED用ピン
    int          pinBled;          //後側センサ調整LED用ピン
    boolean      flg[2];           //各センサの反応状態
    int          i[2];             //角材カウンタ
    int          sts[2];           //センサユニットのステータス(直近)
    int          bsts[2];          //センサユニットのステータス(遷移)
    boolean      way_flg;          //最後に角材を見つけた際の移動方向 true:前進、false:後退
    int          tmp_sens_val;     //赤外線センサの値を入れる
    int          tmp_val_val;      //センサ調整用ボリュームの値を入れる
    //個別のセンサのステータスを返す
    boolean getSts(int p_pin       //センサ接続ピン
                  ,int p_pin_val   //センサしきい値調整用ピン
                  );
  public:
    //コンストラクタ
    blockFinderUnit();
    blockFinderUnit(int p_pins[][IR_VAL_TYPES]);

    void    block_finder();                     //角材検知機能(本体)
    int     getUnitStatus();                    //センサユニットのステータスを返す
    int     getBlkCnt();                        //またいだ角材数を返す
    boolean getWayFlg();                        //角材上でのロボットの移動方向を返す
    void    unitClear();                        //センサユニットの各種値を初期化する
    void    destroy_marker(boolean p_led);      //マニュアルモード時にセンサ調整用LEDを点滅させる
    void    set_wayFlg(boolean p_flg);          //センサユニットの移動方向フラグを設定する
};

//////////////////////////////////////////////////////////
//blockFindersクラス
//角材を探し出す処理
//センサユニット3個を1グループとして連動管理する

class blockFinders{

  private:
    blockFinderUnit bfu[3];                     //センサユニット
    boolean         leg_flg[2];                 //前後脚の伸縮状態フラグ true:伸、false:縮
    int             leg_sts;                    //脚の伸縮ステータス 0:全伸、1:後伸、2:全縮、3:前伸
    unsigned int    mt_t;                       //マニュアルモード時のランプ点滅用
    unsigned int    mt_t_tmp;                   //マニュアルモード時のランプ点滅用
    boolean         mt_led;                     //マニュアルモード時のランプ点滅用

    void            set_wayFlg(boolean p_flg);  //センサユニットの移動方向フラグを設定する

  public:

    //コンストラクタ
    blockFinders();
    blockFinders(int p_pin[][IR_SENSES][IR_VAL_TYPES]);
    void            blockFinding();             //角材探知、脚伸縮ロジック本体
    int             getLegStatus();             //各脚のステータスを得る
    void            unitClear();                //センサユニットの値をクリアする
    void            destroy_marker();           //マニュアルモード時にセンサ調整用LEDを点滅させる
};

//マニュアルモード時LED点滅用
class destroy_led{
  private:
    unsigned long int mt_t;
    unsigned long int mt_t_tmp;
    boolean           mt_led;
    int               led1;
    int               led2;
  public:
    destroy_led();
    destroy_led(int p_led1, int p_led2);
    void led_ctrl();
    void led_stop();
};

#endif

