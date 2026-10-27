/* ===================================================
 * 3. HIEN THI
 * =================================================== */
void gotoxy(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clearScreen(void) { system("cls"); }

void hienThi(const VanBan *vb) {
    clearScreen();
    printf("=== MINI TEXT EDITOR | File: %s%s ===\n",
        vb->tenFile[0] ? vb->tenFile : "(chua dat ten)", vb->daSua ? " *" : "");
    printf("Ctrl+S Luu | Ctrl+O Mo | Ctrl+F Tim | Ctrl+R Thay | Ctrl+K Xoa dong | Ctrl+T Thong ke | Ctrl+Q Thoat\n");
    printf("----------------------------------------------------------------------------------------------------\n");
      /* TODO: neu van ban dai hon man hinh -> chi in cac dong trong cua so cuon */
    int dongBatDau = vb->offDong;
    int manHinhDong = (vb->manHinhDong > 0) ? vb->manHinhDong : 20;
    int dongKetThuc = dongBatDau + manHinhDong;
    if (dongKetThuc > vb->nLines) {
        dongKetThuc = vb->nLines;
    }

    for (int i = dongBatDau; i < dongKetThuc; i++) {
        printf("%3d| %s\n", i + 1, vb->lines[i]);
    }

    if (vb->thongBao[0]) {                         /* thong bao o dong cuoi */
        gotoxy(0, 3 + manHinhDong);
        printf("[%.70s]", vb->thongBao);
    }

    /* Dat con tro: 3 dong tieu de, 5 ky tu '%3d| ' */
    gotoxy(5 + (vb->cur.cot - vb->offCot), 3 + (vb->cur.dong - vb->offDong));
}

/* ===================================================
 * 4. FILE .txt
 * =================================================== */
int luuFile(VanBan *vb, const char *ten) {
    FILE *f = fopen(ten, "w");
    if (!f) return 0;
    for (int i = 0; i < vb->nLines; i++)
        fprintf(f, "%s\n", vb->lines[i]);
    fclose(f);
    strncpy(vb->tenFile, ten, sizeof(vb->tenFile) - 1);
    vb->daSua = 0;
    return 1;
}

int moFile(VanBan *vb, const char *ten) {
    FILE *f = fopen(ten, "r");
    if (!f) return 0;
    /* Xoa noi dung cu, khoi tao lai */
    giaiPhong(vb);
    khoiTao(vb);
    xoaDong(vb, 0);          /* bo dong rong khoi tao; xoaDong se tu them lai neu rong */
    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), f)) {
        // (ghi chu)
        size_t len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[--len] = '\0';
        }
        // (ghi chu)
        themDong(vb, vb->nLines, buffer);
    }

    // (ghi chu)
    if (vb->nLines == 0) {
        themDong(vb, 0, "");
    }

    fclose(f);
    strncpy(vb->tenFile, ten, sizeof(vb->tenFile) - 1);
    vb->daSua = 0;
    vb->cur.dong = vb->cur.cot = 0;
    return 1;
}
