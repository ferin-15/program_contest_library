#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A&lang=jp"
#include "../memo/macro.hpp"
#include "../math/runtime_modint.cpp"
#include "../math/finite_field_matrix.cpp"

signed main(void) {
    MOD = (1LL<<61)-1;
    ll n;
    cin >> n;

    matrix mat(2, 2);
    mat.get(0, 0) = 1, mat.get(0, 1) = 1;
    mat.get(1, 0) = 1, mat.get(1, 1) = 0;
    mat = pow(mat, n); 

    cout << mat.get(0, 0) << endl;

    return 0;
}