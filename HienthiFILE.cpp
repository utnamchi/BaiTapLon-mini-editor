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