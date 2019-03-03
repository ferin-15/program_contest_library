int pos = 0;
vector<ll> in(n), out(n), rev(n);
function<void(int,int)> euler = [&](int v, int p) {
  rev[pos] = v;
  in[v] = pos++;
  for(auto to: g[v]) {
    if(to == p) continue;
    euler(to, v);
  }
  out[v] = pos;
};
euler(0, -1);