/* =====================================================
 *  5. TIM KIEM / THAY THE / THONG KE
 * ===================================================== */
void timChuoi(VanBan *vb) {
    char mau[256];
    clearScreen();
    printf("Nhap chuoi can tim: ");
    if (!fgets(mau, sizeof(mau), stdin)) return;
    mau[strcspn(mau, "\n")] = '\0';
    if (!mau[0]) {
        printf("Chuoi tim kiem khong duoc de trong. Nhan phim bat ky...\n");
        _getch();
        return;
    }

    int soLan = 0;
    for (int i = 0; i < vb->nLines; i++) {
        const char *p = vb->lines[i];
        while ((p = strstr(p, mau)) != NULL) {
            printf("Dong %d, cot %d\n", i + 1,
                   (int)(p - vb->lines[i]) + 1);
            soLan++;
            p += strlen(mau); /* Tim cac lan xuat hien khong chong lan */
        }
    }
    if (soLan == 0) printf("Khong tim thay chuoi \"%s\".\n", mau);
    printf("Tong cong: %d lan. Nhan phim bat ky...\n", soLan);
    _getch();
}
