struct dice {
  mt19937 mt;
  dice() {
    random_device rd;
    mt = mt19937(rd());
  }
  int operator()(int x) { return this->operator()(0, x - 1); }
  int operator()(int x, int y) {
    uniform_int_distribution<int> dist(x, y);
    return dist(mt);
  }
} rnd;