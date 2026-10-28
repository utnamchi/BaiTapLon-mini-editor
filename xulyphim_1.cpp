void xuLyPhim(VanBan *vb, int *thoat) {
    int k = _getch();

    if (k == 0 || k == KEY_EXT) {                 /* phim mo rong */
        int k2 = _getch();
        int len = (int)strlen(vb->lines[vb->cur.dong]);
        switch (k2) {
            case KEY_UP:
                if (vb->cur.dong > 0) vb->cur.dong--;
                break;
            case KEY_DOWN:
                if (vb->cur.dong < vb->nLines - 1) vb->cur.dong++;
                break;
            case KEY_LEFT:
                if (vb->cur.cot > 0) vb->cur.cot--;
                else if (vb->cur.dong > 0) {      /* ve cuoi dong truoc */
                    vb->cur.dong--;
                    vb->cur.cot = (int)strlen(vb->lines[vb->cur.dong]);
                }
                break;
