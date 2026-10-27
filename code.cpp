//khoi tao van ban  
void khoiTao(VanBan *vb) {
    if (!vb) return;
    vb->capacity = 16;
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
    vb->manHinhDong = 1000 ;
    //luon dam bao van ban co 1 dong trong  
    themDong(vb, 0, "");          /* luon co it nhat 1 dong */
    if (vb->nLines == 0) {        /* themDong that bai: khong the chay tiep */
        printf("Het bo nho!\n");
        bnFree(vb->lines);
        vb->lines = NULL;
        exit(1);
    }
    vb->daSua = 0;                /* van ban moi chua bi sua */
}

