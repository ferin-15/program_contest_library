---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: memo/Dice.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d504a5ea65b088497578bdd812714d51">memo</a>
* <a href="{{ site.github.repository_url }}/blob/master/memo/Dice.cpp">View this file on GitHub</a>
    - Last commit date: 2018-09-27 01:44:20+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "memo/Dice.cpp"
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

