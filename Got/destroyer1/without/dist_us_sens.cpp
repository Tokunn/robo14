/////////////////////////////////////////////////////
//�����g�Z���T�p�N���X
//����͖��g�p

  //�R���X�g���N�^
  us_senser::us_senser(){};
  us_senser::us_senser(int p_pin){
    sens_pin = p_pin;
  };

  //�����𓾂�
  int us_senser::getDistance(){

    //�p���X�o�͐ݒ�
    pinMode(sens_pin,OUTPUT);
    digitalWrite(sens_pin,LOW);

    //�p���X���o�͂���
    digitalWrite(sens_pin,HIGH);
    delayMicroseconds(2);
    digitalWrite(sens_pin,LOW);

    //�p���X��M�ݒ�
    delayMicroseconds(5);
    pinMode(sens_pin,INPUT);

//    //�p���X����M����
    t = pulseIn(sens_pin,HIGH,US_TIMEOUT);

    dst = t * SOS_TIME / 2;    //��M�����p���X�̒�������ɋ����𓾂�
    return dst;                //������Ԃ�
  };

/////////////////////////////////////////////////////
//���{�b�g�{�̕��Ə��Ƃ̋����𑪂�N���X
//����͖��g�p

  //�R���X�g���N�^
  dist_sens::dist_sens(){}
  dist_sens::dist_sens(int p_pin){
    uss  = us_senser(p_pin);    //�����g�Z���T
    dist = 0;                   //���{�b�g�ƒn�ʂƂ̋���
  }

  //�������v�Z����
  void dist_sens::calcDistance(double p_theta_x
                              ,double p_theta_y
                              ){

    //�Z���T�l��胍�{�b�g�ƒn�ʂƂ̋����𓾂�
    dist = (double)uss.getDistance();

    //�X���ɂ��덷��␳����
    dist = dist * sin(p_theta_x);          //x�����̌X��
    dist = dist * sin(p_theta_y);          //y�����̌X��
  }

  //������Ԃ�
  double dist_sens::getDistance(){
    return dist;
  };

