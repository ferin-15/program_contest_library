/**
* @file EERTREE.cpp
* @brief EERTREE
* @detail verify: 未
* @author ferin
*/

// BEGIN CUT
struct PalindromicTree{
  struct node{
    map<char,int> nxt;
    int len,suf,hei,app,cnt;
  };
  string s;
  vector<node> v;
  vector<int> ord;
  int n,suff;
  PalindromicTree(){}
  PalindromicTree(string s_){init(s_);build();}
  bool addchar(int pos){
    char ch=s[pos];
    int cur=suff;
    while(1){
      if(pos-1-v[cur].len>=0&&s[pos-1-v[cur].len]==ch) break;
      cur=v[cur].suf;
    }
    if(v[cur].nxt.count(ch)){
      suff=v[cur].nxt[ch];
      v[suff].cnt++;
      return false;
    }
    suff=n++;
    v[suff].len=v[cur].len+2;
    v[suff].app=pos-v[suff].len+1;
    v[suff].cnt=1;
    v[cur].nxt[ch]=suff;

    if(v[suff].len==1){
      v[suff].suf=1;
      v[suff].hei=1;
      return true;
    }
    while(1){
      cur=v[cur].suf;
      if(pos-1-v[cur].len>=0&&s[pos-1-v[cur].len]==ch){
	      v[suff].suf=v[cur].nxt[ch];
	      break;
      }
    }
    v[suff].hei=v[v[suff].suf].hei+1;
    return true;
  }

  void init(string s_){
    s=s_;
    v.clear();
    v.resize(s.length()+10);

    n=2;
    suff=1;
    v[0].app=v[1].app=-1;
    v[0].len=-1;v[1].len=0;
    v[0].suf=v[1].suf=0;
    v[0].hei=v[1].hei=0;
  }

  void calcOrder(){
    ord.clear();
    ord.push_back(0);
    ord.push_back(1);
    for(int i=0;i<(int)ord.size();i++){
      for(auto &p:v[ord[i]].nxt) ord.push_back(p.second);
    }
  }

  void calcCount(){
    assert(ord.size());
    for(int i=(int)ord.size()-1;i>=0;i--){
      v[v[ord[i]].suf].cnt+=v[ord[i]].cnt;
    }
    v[0].cnt=v[1].cnt=0;
  }

  void build(){
    for(int i=0;i<(int)s.size();i++) addchar(i);
    calcOrder();
    calcCount();
  }
};