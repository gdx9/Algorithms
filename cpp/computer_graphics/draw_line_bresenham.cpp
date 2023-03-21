void drawLineBresenham(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy; // error value by x and y axes

    while(true){
        // here: draw point x0 y0

        int e2 = err << 1; // err * 2
        if (e2 >= dy) { // error by xy + error x > 0
            if (x0 == x1)
                break;
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) { // error by xy + error y < 0
            if (y0 == y1)
                break;
            err += dx;
            y0 += sy;
        }
    }
}
