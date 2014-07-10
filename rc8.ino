int fro_rea[] = {3, 4};
int lef_rig[] = {6, 7};
int speed[] = {9, 10, 11};


boolean fb_dec[3][2] = {{LOW, LOW}, {HIGH, LOW}, {LOW, HIGH}};
boolean lr_dec[3][2] = {{LOW, LOW}, {HIGH, LOW}, {LOW, HIGH}};
boolean speed_dec[5][3] = {{LOW , LOW , LOW },
                         {HIGH, LOW , HIGH},
                         {HIGH, LOW , LOW },
                         {HIGH, HIGH, HIGH},
                         {HIGH, HIGH, LOW }};


void setup()
{
  for (int i = 0; i < 2; i++){
    pinMode(fro_rea[i], OUTPUT);
  }
  for (int i = 0; i < 2; i++){
    pinMode(lef_rig[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++){
    pinMode(speed[i], OUTPUT);
  }
  Serial.begin(9600);
}


void recv_str(char *buf)
{
  int i = 0;
  char c;
  while (1) {
    if (Serial.available()) {
      c = Serial.read();
      buf[i] = c;
      if (i == 2) break;
      i++;
    }
  }
  buf[3] = '\0';
}


void make_list(char *buf, int *list)
{
  switch(buf[0]){
    case '0':
      list[0] = 0;
      break;
    case 'f':
      list[0] = 1;
      break;
    case 'b':
      list[0] = 2;
      break;
    default:
      list[0] = 0;
      break;
  }
  switch(buf[1]){
    case 's':
      list[1] = 0;
      break;
    case 'l':
      list[1] = 1;
      break;
    case 'r':
      list[1] = 2;
      break;
    default:
      list[1] = 0;
      break;
  }
  switch(buf[2]){
    case '1':
      list[2] = 0;
      break;
    case '2':
      list[2] = 1;
      break;
    case '3':
      list[2] = 2;
      break;
    case '4':
      list[2] = 3;
      break;
    case '5':
      list[2] = 4;
      break;
    case '6':
      list[2] = 5;
      break;
    default:
      list[2] = 0;
      break;
  }
}


void action(int *list)
{
  for (int i = 0; i < 2; i++){
    digitalWrite(fro_rea[i], fb_dec[list[0]][i]);
  }
  for (int i = 0; i < 2; i++){
    digitalWrite(lef_rig[i], lr_dec[list[1]][i]);
  }
  for (int i = 0; i < 3; i++){
    digitalWrite(speed[i], speed_dec[list[2]][i]);
  }
}


void loop()
{
  if (Serial.available()){
    char str[4];
    recv_str(str);

    int list[3];
    make_list(str, list);

    action(list);
  }
  else{
    int list[3] = {0, 0, 0};
    action(list);
  }
}
