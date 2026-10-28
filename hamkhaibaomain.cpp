//ham khai bao main
int main(void) {
    VanBan vb;
    memset(&vb, 0, sizeof(vb));
    khoiTao(&vb);
    int thoat = 0;
    while (!thoat) {
        hienThi(&vb);
        xuLyPhim(&vb, &thoat);
    }
    giaiPhong(&vb);
    clearScreen();
    bnBaoCaoRoRi();       /* phai bao cao 0 khoi ro ri khi nop bai */
    printf("Nhan phim bat ky de dong...\n");
    _getch();
    return 0;
}
