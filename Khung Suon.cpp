#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

//MaPhim
#define KEY_ENTER   13
#define KEY_BACK    8
#define KEY_CTRL_S  19   // luu file   
#define KEY_CTRL_O  15   //mo file    
#define KEY_CTRL_F  6    //tim chuoi  
#define KEY_CTRL_R  18   //thay the   
#define KEY_CTRL_K  11   //xoa dong   
#define KEY_CTRL_T  20   //thong ke   
#define KEY_CTRL_Q  17   // thoat      
#define KEY_EXT     224  // phim mo rong (mui ten)
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_LEFT    75
#define KEY_RIGHT   77
#define KEY_DEL     83
//ConTro
typedef struct {
    int dong;
    int cot;
} ConTroViTri;

typedef struct {
    char **lines;
    int nLines;
    int capacity;        
    ConTroViTri cur;
    char tenFile[260];
    int daSua;           
} VanBan;

//TenKhaiBao
void khoiTao(VanBan *vb);
void giaiPhong(VanBan *vb);
void themDong(VanBan *vb, int viTri, const char *noiDung);
void xoaDong(VanBan *vb, int viTri);
void chenKyTu(VanBan *vb, char c);
void xoaKyTuTruocCon(VanBan *vb);     
void xuongDong(VanBan *vb);            
void hienThi(const VanBan *vb);
void xuLyPhim(VanBan *vb, int *thoat);
int  luuFile(VanBan *vb, const char *ten);
int  moFile(VanBan *vb, const char *ten);
void timChuoi(VanBan *vb);
void thayTheTatCa(VanBan *vb);
void thongKe(const VanBan *vb);
void gotoxy(int x, int y);
void clearScreen(void);



int main() {
	printf("hello word");
	
	
	return 0;
	
	
}
