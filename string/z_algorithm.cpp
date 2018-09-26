// z-algotirhm O(|S|)
VI Zalgo(string s) {
  VI v(s.size());
  v[0] = s.size();
  int i = 1, j = 0;
  while (i < s.size()) {
    while (i+j < s.size() && s[j] == s[i+j]) ++j;
    v[i] = j;
    if (j == 0) { ++i; continue;}
    int k = 1;
    while (i+k < s.size() && k+v[k] < j) v[i+k] = v[k], ++k;
    i += k; j -= k;
  }
	return v;
}
