高専ロボコン・ロボットプログラム（通信）
=======================================

NITOyC 2014 RoboconProject

概要
-----
高専機構・NHKが主催する高専ロボコンの通信組プログラムです。  

機能
----
接続したゲームパッドから値を読み込み、接続されているArduino（その他の機器）へとシリアル通信でコマンドを送信します。  


動作環境
--------
・Raspberrypi (その他のPC)  
・Raspbian (その他のOS)  
・Python2.7  
・Pygame
・LogicoolGamepad F710  (そのほかのゲームパッド)  
・Arduino Mega (その他のマイコンボード)  
※（）内のでも代用が可能です。  
基本的にゲームパッドとPython類があればどんな環境でも動きます。  

使い方
------
PythonとPygameが入っているPCで実行してください。  
robo14/demae.pyとrobo14/uketori.pyがメインプログラムです。  
robo14/get_gamepad.pyはゲームパッドの値を読み込んで扱いやすい形に変換するためのクラスです。  
ゲームパッドとArduinoを接続してrobo14/demae.pyまたはrobo14/uketori.pyを実行してください。  

編集方法
--------
ゲームパッドの信号の読み取りとコマンドへの変換はSerial_write()クラスで行います。  
serial_update()メソッドで更新処理を行いますので、新しい関数はここで呼び出してください。  
```lang
def serial_update(self, F710):
        self.serial_command = ['$', 'f', '0', 'n', '0', 's', '0', 'n', '0', '0', '0', '0']

        self.make_serial_direction(F710, "tire")
        self.make_serial_direction(F710, "catarpillar")
        self.make_serial_level(F710)
        self.make_serial_updown(F710)
```


作成者アカウント
----------------
https://twitter.com/KTokunn  

作成者サイト
-------------
http://tokunn.hateblo.jp/  
