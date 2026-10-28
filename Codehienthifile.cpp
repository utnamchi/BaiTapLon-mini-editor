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
    