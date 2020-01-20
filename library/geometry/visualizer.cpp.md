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


# :warning: geometry/visualizer.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed7daeb157cd9b31e53896ad3c771a26">geometry</a>
* <a href="{{ site.github.repository_url }}/blob/master/geometry/visualizer.cpp">View this file on GitHub</a>
    - Last commit date: 2019-07-14 12:12:28+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "geometry/visualizer.cpp"
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

