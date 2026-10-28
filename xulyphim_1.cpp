void xuLyPhim(VanBan *vb, int *thoat) {
    int k = _getch();

    if (k == 0 || k == KEY_EXT) {                 /* phim mo rong */
        int k2 = _getch();
        int len = (int)strlen(vb->lines[vb->cur.dong]);
        switch (k2) {
            case KEY_UP:
                if (vb->cur.dong > 0) vb->cur.dong--;
                break;
