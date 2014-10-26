/////////////////////////////////////////////////////
//�����g�Z���T�p�N���X
//dist_sens�N���X�����Ŏg�p

//�萔�̓��A���K�`�v���O�������o�b�N�A�b�v�ł��Q�Ƃ̂���

#define SOS_TIME (348 * 0.001)  //[mm]

class us_senser{
  private:
    int dst;      //����[mm]
    int t;        //�p���X�̔��ˎ���[��s]
    int sens_pin;

  public:
    us_senser();
    us_senser(int p_pin);
    int getDistance();
};

/////////////////////////////////////////////////////
//���{�b�g�{�̕��Ə��Ƃ̋����𑪂�N���X

class dist_sens{
  private:
    //�ϐ�
//    int       sens_pin;        //�Z���T���ڑ�����Ă���s���ԍ�
//    int       sens_val;        //�Z���T�l
//    double    sens_vale;       //�d��
    double    dist;            //����(�v�Z�l)[mm]
    us_senser uss;             //�����g�Z���T�p
    //�֐�

  public:
    //�֐�

    //�R���X�g���N�^
    dist_sens();
    dist_sens(int p_pin);

    //������Ԃ�
    void calcDistance(double p_theta_x
                     ,double p_theta_y
                     );
    double getDistance();
};

