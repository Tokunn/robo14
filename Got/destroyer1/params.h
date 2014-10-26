//必要なパラメータをまとめたヘッダファイル

#ifndef PARAMS
#define PARAMS

#define DESTROY_LED1           30        //マニュアルモード時の車幅灯LED
#define DESTROY_LED2           32        //マニュアルモード時の車幅灯LED

#define W_UP_WAIT_TIME_1      500        //起動時待ち時間(モータドライバ充電時間)
#define W_UP_WAIT_TIME_2     2000        //起動時待ち時間(ロボットの物理的な立ち上がり時間)
#define IR_SENSITIV_VAL        30        //角材検知調整ボリュームの感度(分解能)

#define MAX_DRIVE_VAL         250        //モータ最大出力時の信号値
#define MIN_DRIVE_VAL           0        //モータ最小出力時の信号値
#define STOP_VAL                0        //モータにブレーキをかけるときの値
#define BASE_VAL         STOP_VAL        //モータ入力値を計算するための基準値
#define INI_DRIVE_VAL         255        //起動時入力値

#define DRIVE_WAIT_TIME        20        //モータの信号が反転してから実際に回り出すまでのウェイトタイム[ms]
#define DRIVE_STOP_TIME  W_UP_WAIT_TIME_2        //モータを回す(脚を伸縮する)時間[ms]

//赤外線センサ(角材検知用)
#define IR_PIN_FF              A0        //前部ユニット(前)
#define IR_PIN_FR              A1        //前部ユニット(後)
#define IR_PIN_MF              A2        //重心部ユニット(前)
#define IR_PIN_MR              A3        //重心部ユニット(後)
#define IR_PIN_RF              A4        //後部ユニット(前)
#define IR_PIN_RR              A5        //後部ユニット(後)

#define IR_VAL_FF              A8        //前部ユニット(前)調整ボリューム
#define IR_VAL_FR              A9        //前部ユニット(後)調整ボリューム
#define IR_VAL_MF             A10        //重心部ユニット(前)調整ボリューム
#define IR_VAL_MR             A11        //重心部ユニット(後)調整ボリューム
#define IR_VAL_RF             A12       //後部ユニット(前)調整ボリューム
#define IR_VAL_RR             A13       //後部ユニット(後)調整ボリューム

#define IR_LED_FF              53        //前部ユニット(前)調整用パイロットランプ
#define IR_LED_FR              51        //前部ユニット(後)調整用パイロットランプ
#define IR_LED_MF              49        //重心部ユニット(前)調整用パイロットランプ
#define IR_LED_MR              47        //重心部ユニット(後)調整用パイロットランプ
#define IR_LED_RF              45       //後部ユニット(前)調整用パイロットランプ
#define IR_LED_RR              43       //後部ユニット(後)調整用パイロットランプ

//脚伸縮用モータ
//左前脚
#define MT_PIN_LF_A             2
#define MT_PIN_LF_B             3

//左後脚
#define MT_PIN_LB_A             4
#define MT_PIN_LB_B            13

//右前脚
#define MT_PIN_RF_A             5
#define MT_PIN_RF_B             6

//右後脚
#define MT_PIN_RB_A            11
#define MT_PIN_RB_B            12

//非常用(マニュアルモード時用設定)

#define AUTO_MODE             LOW    //オートモード
#define MANUAL_MODE    !AUTO_MODE    //マニュアルモード

#define MANUAL_STRECH         LOW    //伸びている状態
#define MANUAL_SHRINK        HIGH    //収納状態

#define MODE_PIN               22    //操作モード設定ピン
#define MANUAL_FRNT_PIN        24    //前脚ステータス
#define MANUAL_BACK_PIN        26    //後脚ステータス

#endif

