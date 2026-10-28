/*
 * DT17 - Mini Text Editor tren Console (Windows)
 * Bien dich: gcc mini_text_editor.c -o editor.exe
 *
 * Cau truc du lieu:
 *   char **lines : mang 2 chieu dong, moi dong la 1 chuoi malloc rieng
 *   int nLines   : so dong hien co
 *   ConTroViTri  : vi tri con tro (dong, cot)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

/* ---------- Ma phim ---------- */
#define KEY_ENTER   13
#define KEY_BACK    8
#define KEY_CTRL_S  19   /* luu file   */
#define KEY_CTRL_O  15   /* mo file    */
#define KEY_CTRL_F  6    /* tim chuoi  */
#define KEY_CTRL_R  18   /* thay the   */
#define KEY_CTRL_K  11   /* xoa dong   */
#define KEY_CTRL_T  20   /* thong ke   */
#define KEY_CTRL_Q  17   /* thoat      */
#define KEY_EXT     224  /* phim mo rong (mui ten) */
#define KEY_UP      72
#define KEY_DOWN    80
#define SO_KHOANG_TRANG_TAB 4
#define MAX_THONG_BAO 80
#define KEY_LEFT    75
#define KEY_RIGHT   77
#define KEY_DEL     83
#define KEY_TAB     9 

/* ---------- Struct ---------- */
typedef struct {
    int dong;
    int cot;
} ConTroViTri;

typedef struct {
    char **lines;
    int nLines;
    int capacity;        /* so o con tro da cap phat cho lines */
    ConTroViTri cur;
    char tenFile[260];
    int daSua;           /* co thay doi chua luu */
    int offDong;
    int offCot;
    int manHinhDong;
    char thongBao[MAX_THONG_BAO];   /* thong bao ngan cho nguoi dung */
} VanBan;

/* ---------- Tien khai bao ---------- */
void khoiTao(VanBan *vb);
void giaiPhong(VanBan *vb);
void themDong(VanBan *vb, int viTri, const char *noiDung);
void xoaDong(VanBan *vb, int viTri);
void chenKyTu(VanBan *vb, char c);
void xoaKyTuTruocCon(VanBan *vb);      /* Backspace */
void xuongDong(VanBan *vb);            /* Enter: tach dong */
void hienThi(const VanBan *vb);
void xuLyPhim(VanBan *vb, int *thoat);
int  luuFile(VanBan *vb, const char *ten);
int  moFile(VanBan *vb, const char *ten);
void timChuoi(VanBan *vb);
void thayTheTatCa(VanBan *vb);
void thongKe(const VanBan *vb);
void gotoxy(int x, int y);
void clearScreen(void);
void *bnMalloc(size_t soByte);
void *bnRealloc(void *p, size_t soByte);
void  bnFree(void *p);
int   bnBaoCaoRoRi(void);
void  datThongBao(VanBan *vb, const char *noiDung);
/* ---------- Ham boc bo nho: dung bnMalloc/bnRealloc/bnFree thay cho malloc/realloc/free ---------- */
static int g_soCapPhat = 0;       /* dem so lan cap phat thanh cong */
static int g_soGiaiPhong = 0;     /* dem so lan giai phong          */

void *bnMalloc(size_t soByte) {
    void *p = malloc(soByte);
    if (p) g_soCapPhat++;
    return p;
}

void *bnRealloc(void *p, size_t soByte) {
    void *q;
    if (soByte == 0) {                         /* realloc(p, 0) = giai phong */
        if (p) { free(p); g_soGiaiPhong++; }
        return NULL;
    }
    q = realloc(p, soByte);
    if (q && p == NULL) g_soCapPhat++;         /* realloc(NULL, n) = cap phat moi */
    return q;
}

void bnFree(void *p) {
    if (p) { free(p); g_soGiaiPhong++; }
}

/* In bao cao; tra ve so khoi bi ro ri (0 = tot) */
int bnBaoCaoRoRi(void) {
    int roRi = g_soCapPhat - g_soGiaiPhong;
    printf("Cap phat: %d | Giai phong: %d\n", g_soCapPhat, g_soGiaiPhong);
    if (roRi != 0) printf("CANH BAO RO RI BO NHO: %d khoi\n", roRi);
    else           printf("Khong ro ri bo nho.\n");
    return roRi;
}

/* Luu thong bao ngan (hienThi se in o dong cuoi). NULL = xoa thong bao. */
void datThongBao(VanBan *vb, const char *noiDung) {
    if (!vb) return;
    if (!noiDung) { vb->thongBao[0] = '\0'; return; }
    strncpy(vb->thongBao, noiDung, MAX_THONG_BAO - 1);
    vb->thongBao[MAX_THONG_BAO - 1] = '\0';
}




int main (){
	printf("Hello UTC2");
	
	
	
	
} 
