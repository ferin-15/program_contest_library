struct visualizer {
    struct Col { int r, g, b; };
    FILE* fp;
    R off, f;
    // uには座標の最大値, dには最小値を入れる
    visualizer(string s, R u, R d=0) : off(d), f(1000/(u-d)) {
        fp = fopen(s.c_str(), "w");
        fprintf(
            fp,
            "<html><head><script>"
            "onload = function draw() {"
            "var cv = document.getElementById('c');"
            "var ct = cv.getContext('2d');"
        );
    }
    R norm(R x) { return (x - off) * f; }
    void set_col(Col c) {
        fprintf(fp, "ct.fillStyle = \"rgb(%d, %d, %d)\";", c.r, c.g, c.b);
        fprintf(fp, "ct.strokeStyle = \"rgb(%d, %d, %d)\";", c.r, c.g, c.b);
    }
    void line(L l, Col col = {0, 0, 0}) {
        set_col(col);
        fprintf(fp,
        "ct.beginPath();"
        "ct.moveTo(%Lf, %Lf);"
        "ct.lineTo(%Lf, %Lf);"
        "ct.closePath();"
        "ct.stroke();",
        norm(l.first.real()), norm(l.first.imag()), norm(l.second.real()), norm(l.second.imag()));
    }
    void point(P p, Col col = {0, 0, 0}) {
        set_col(col);
        fprintf(fp,
            "ct.beginPath();"
            "ct.arc(%Lf, %Lf, 2, 0, Math.PI * 2, true);"
            "ct.fill();",
            norm(p.real()), norm(p.imag())
        );
    }
    void circle(C c, Col col = {0, 0, 0}) {
        set_col(col);
        fprintf(fp,
            "ct.beginPath();"
            "ct.arc(%Lf, %Lf, %Lf, 0, Math.PI * 2, true);"
            "ct.stroke();",
            norm(c.c.real()), norm(c.c.imag()), norm(c.r)
        );
    }
    ~visualizer() {
        fprintf(
            fp,
            "}</script></head><body>"
            "<canvas id=\"c\" width=\"1000\" height=\"1000\">"
            "</canvas></body></html>"
        );
        fclose(fp);
    }
};
