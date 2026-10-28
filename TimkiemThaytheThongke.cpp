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

/* Thay the tat ca "cu" bang "moi" tren mot dong, tra ve so lan thay */
static int thayTrenMotDong(char **dong, const char *cu, const char *moi) {
    if (dong == NULL || *dong == NULL || cu == NULL || moi == NULL || cu[0] == '\0')
        return 0;

    size_t lenCu = strlen(cu);
    size_t lenMoi = strlen(moi);
    size_t lenGoc = strlen(*dong);
    size_t soLan = 0;
    const char *p = *dong;

    /* Dem so lan xuat hien cua chuoi cu (khong chong lan). */
    while ((p = strstr(p, cu)) != NULL) {
        soLan++;
        p += lenCu;
    }
    if (soLan == 0) return 0;
    
      /* Tinh kich thuoc moi, bao gom ky tu ket thuc '\0'. */
    size_t lenMoiTong;
    if (lenMoi >= lenCu) {
        size_t themMoi = soLan * (lenMoi - lenCu);
        if (themMoi > (size_t)-1 - lenGoc - 1) return 0;
        lenMoiTong = lenGoc + themMoi;
    } else {
        lenMoiTong = lenGoc - soLan * (lenCu - lenMoi);
    }

    char *ketQua = (char *)bnMalloc(lenMoiTong + 1);
    if (ketQua == NULL) return 0;

    const char *src = *dong;
    char *dst = ketQua;
    const char *timThay;
    while ((timThay = strstr(src, cu)) != NULL) {
        size_t doDaiTruoc = (size_t)(timThay - src);
        memcpy(dst, src, doDaiTruoc);
        dst += doDaiTruoc;
        memcpy(dst, moi, lenMoi);
        dst += lenMoi;
        src = timThay + lenCu;
    }
    strcpy(dst, src);

    bnFree(*dong);
    *dong = ketQua;
    return (int)soLan;
}

void thayTheTatCa(VanBan *vb) {
    char cu[256], moi[256];
    clearScreen();
    printf("Chuoi can thay: ");
    if (!fgets(cu, sizeof(cu), stdin)) return;
    cu[strcspn(cu, "\n")] = '\0';

    printf("Thay bang     : ");
    if (!fgets(moi, sizeof(moi), stdin)) return;
    moi[strcspn(moi, "\n")] = '\0';

    if (!cu[0]) {
        printf("Chuoi can thay khong duoc de trong. Nhan phim bat ky...\n");
        _getch();
        return;
    }
    
    int tong = 0;
    for (int i = 0; i < vb->nLines; i++)
        tong += thayTrenMotDong(&vb->lines[i], cu, moi);
    if (tong > 0) vb->daSua = 1;
    printf("Da thay %d vi tri. Nhan phim bat ky...\n", tong);
    _getch();
}

void thongKe(const VanBan *vb) {
    int soKyTu = 0, soTu = 0;

    for (int i = 0; i < vb->nLines; i++) {
        const unsigned char *s = (const unsigned char *)vb->lines[i];
        int trongTu = 0;

        soKyTu += (int)strlen((const char *)s);

        /* Mot tu bat dau khi gap ky tu khong phai khoang trang
           sau mot khoang trang hoac o dau dong. */
        while (*s) {
            if (isspace(*s)) {
                trongTu = 0;
            } else if (!trongTu) {
                soTu++;
                trongTu = 1;
            }
            s++;
        }
    }

    clearScreen();
    printf("So dong : %d\nSo ky tu: %d\nSo tu   : %d\n",
           vb->nLines, soKyTu, soTu);
    printf("Nhan phim bat ky...\n");
    _getch();
}
