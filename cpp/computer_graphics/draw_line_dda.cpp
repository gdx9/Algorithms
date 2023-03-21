// only int version
void drawLineDda(int x1, int y1, int x2, int y2) {
    int l, dx, dy;

    int xr = abs(x2 - x1);
    int yr = abs(y2 - y1);

    if (xr > yr) l = xr;
    else l = yr;

    int px = (x1 << 12) + (1 << 11);
    int py = (y1 << 12) + (1 << 11);
    int ex = (x2 << 12) + (1 << 11);
    int ey = (y2 << 12) + (1 << 11);

    if (l != 0) {
        dx = (ex - px) / l;
        dy = (ey - py) / l;
    } else {
        dx = 0;
        dy = 0;
    }

    for (int i = 0; i <= l; i++) {
        // here: draw point (px >> 12), (py >> 12)

        px += dx;
        py += dy;
    }

}
