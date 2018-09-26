struct Dice{
  //top, front, right, left, back, bottom
  int side[6];
  Dice(){}
  Dice(int s[]){
    for(int i=0; i<6; ++i) side[i] = s[i];
  }

  void rotate(int op){
    int tmp = ' ';
    //右に倒す
    if(op==0){
      tmp = side[0];
      side[0] = side[3];
      side[3] = side[5];
      side[5] = side[2];
      side[2] = tmp;
    }

    //前に倒す
    if(op==1){
      tmp = side[0];
      side[0] = side[4];
      side[4] = side[5];
      side[5] = side[1];
      side[1] = tmp;
    }

    //左に倒す
    if(op==2){
      tmp = side[0];
      side[0] = side[2];
      side[2] = side[5];
      side[5] = side[3];
      side[3] = tmp;
    }

    //後ろに倒す
    if(op==3){
      tmp = side[0];
      side[0] = side[1];
      side[1] = side[5];
      side[5] = side[4];
      side[4] = tmp;
    }

    //topとbottomを軸に右回転
    if(op==4){
      tmp = side[1];
      side[1] = side[2];
      side[2] = side[4];
      side[4] = side[3];
      side[3] = tmp;
    }

    //topとbottomを軸に左回転
    if(op==5){
      tmp = side[1];
      side[1] = side[3];
      side[3] = side[4];
      side[4] = side[2];
      side[2] = tmp;
    }
  }
};

//24通りのサイコロを生成する
Dice initDice, dice[24];
void makeDice(){
  int tmpNum[] = {1,2,3,4,5,6};
  initDice = Dice(tmpNum);

  for(int i=0; i<24; ++i){
    if(i==4) initDice.rotate(1);
    if(i==8) initDice.rotate(1);
    if(i==12)initDice.rotate(1);
    if(i==16){
      initDice.rotate(1);
      initDice.rotate(0);
    }
    if(i==20){
      initDice.rotate(2);
      initDice.rotate(2);
    }
    initDice.rotate(4);
    dice[i] = initDice;
  }
}

// d[top][front] front, right, back, left
// 問題のdiceの設定とあっているか確認すること！！！！！
int d[6][6][4] = {
  {{-1, -1, -1, -1}, {2, 4, 5, 3}, {3, 2, 4, 5}, {4, 5, 3, 2}, {5, 3, 2, 4}, {-1, -1, -1, -1}}
  ,{{1, 3, 6, 4}, {-1, -1, -1, -1}, {3, 6, 4, 1}, {4, 1, 3, 6}, {-1, -1, -1, -1}, {6, 4, 1, 3}}
  ,{{1, 5, 6, 2}, {2, 1, 5, 6}, {-1,-1,-1,-1}, {-1,-1,-1,-1}, {5, 6, 2, 1}, {6, 2, 1, 5}}
  ,{{1, 2, 6, 5}, {2, 6, 5, 1}, {-1,-1,-1,-1}, {-1,-1,-1,-1}, {5, 1, 2, 6}, {6, 5, 1, 2}}
  ,{{1, 4, 6, 3}, {-1,-1,-1,-1}, {3, 1, 4, 6}, {4, 6, 3, 1}, {-1,-1,-1,-1}, {6, 3, 1, 4}}
  ,{{-1,-1,-1,-1}, {2, 3, 5, 4}, {3, 5, 4, 2}, {4, 2, 3, 5}, {5, 4, 2, 3}, {-1,-1,-1,-1}}};
