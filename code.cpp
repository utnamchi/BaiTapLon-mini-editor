/* Khoi tao cac gia tri ban dau cho doi tuong VanBan */
void khoiTao(VanBan *vb) {
    if (!vb) return;
    vb->capacity = 16; /* Khoi tao suc chua mac dinh 16 dong */
    vb->lines = (char **)bnMalloc((size_t)vb->capacity * sizeof(char *));
    if (!vb->lines) { printf("Het bo nho!\n"); exit(1); }
    
    vb->nLines = 0;
    vb->cur.dong = 0;
    vb->cur.cot = 0;
    vb->tenFile[0] = '\0';
    vb->thongBao[0] = '\0';
    vb->daSua = 0;
    vb->offDong = 0;
    vb->offCot = 0;
    vb->manHinhDong = 1000;
    
    /* Luon dam bao van ban moi mo ra co it nhat 1 dong trong */
    themDong(vb, 0, "");
    if (vb->nLines == 0) {
        printf("Het bo nho!\n");
        bnFree(vb->lines);
        vb->lines = NULL;
        exit(1);
    }
    vb->daSua = 0; /* Van ban moi chua bi chinh sua */
}

/* Giai phong toan bo bo nho da cap phat cho van ban */
void giaiPhong(VanBan *vb) {
    if (!vb) return;
    if (vb->lines) {
        /* Giai phong bo nho cua tung chuoi dong */
        for (int i = 0; i < vb->nLines; i++) bnFree(vb->lines[i]);
        /* Giai phong mang con tro dong */
        bnFree(vb->lines);
    }
    vb->lines = NULL;
    vb->nLines = vb->capacity = 0;
}

/* Chen mot dong moi vao vi tri chi dinh trong mang lines */
void themDong(VanBan *vb, int viTri, const char *noiDung) {
    if (!vb || !vb->lines || !noiDung) return;
    if (viTri < 0 || viTri > vb->nLines) return;
    
    /* Mo rong suc chua neu so dong vuot qua capacity hien tai */
    if (vb->nLines >= vb->capacity) {
        int moi = (vb->capacity > 0) ? vb->capacity * 2 : 16;
        char **tmp = (char **)bnRealloc(vb->lines, (size_t)moi * sizeof(char *));
        if (!tmp) { datThongBao(vb, "Het bo nho!"); return; }
        vb->lines = tmp;
        vb->capacity = moi;
    }
    
    /* Cap phat bo nho cho dong moi va sao chep noi dung vao */
    char *dong = (char *)bnMalloc(strlen(noiDung) + 1);
    if (!dong) { datThongBao(vb, "Het bo nho!"); return; }
    strcpy(dong, noiDung);
    
    /* Doi cac dong phia sau xuong 1 vi tri de tao khoang trong */
    for (int i = vb->nLines; i > viTri; i--)
        vb->lines[i] = vb->lines[i - 1];
        
    vb->lines[viTri] = dong;
    vb->nLines++;
    vb->daSua = 1;
}

/* Xoa mot dong tai vi tri viTri trong van ban */
void xoaDong(VanBan *vb, int viTri) {
    if (!vb || !vb->lines) return;
    if (viTri < 0 || viTri >= vb->nLines) return;

    /* Truong hop dac biet: Neu chi con 1 dong duy nhat thi lam trong dong do, khong xoa mang */
    if (vb->nLines == 1) {
        vb->lines[0][0] = '\0';
        vb->cur.dong = 0;
        vb->cur.cot = 0;
        vb->offDong = 0;
        vb->offCot = 0;
        vb->daSua = 1;
        return;
    }

    /* Giai phong dong can xoa */
    bnFree(vb->lines[viTri]);
    
    /* Don cac dong phia sau len 1 vi tri */
    for (int i = viTri; i < vb->nLines - 1; i++)
        vb->lines[i] = vb->lines[i + 1];
        
    vb->nLines--;
    vb->lines[vb->nLines] = NULL; /* Trainh con tro rac */

    /* Dieu chinh toa do con tro soan thao sao cho khong bi vuot qua pham vi moi */
    if (vb->cur.dong >= vb->nLines) vb->cur.dong = vb->nLines - 1;
    if (vb->cur.dong < 0) vb->cur.dong = 0;
    
    int len = (int)strlen(vb->lines[vb->cur.dong]);
    if (vb->cur.cot > len) vb->cur.cot = len;
    
    if (vb->offDong >= vb->nLines) vb->offDong = vb->nLines - 1;
    if (vb->offDong < 0) vb->offDong = 0;
    vb->daSua = 1;
}
