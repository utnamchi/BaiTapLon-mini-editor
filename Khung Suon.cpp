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
//Phan khoi tao cua Quan
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

//Phan Soan Thao cua TRAN
///KIEM TRA VAN BAN HOP LE 
static int vanBanHopLe(const VanBan *vb) {
    if (vb == NULL) return 0;
    if (vb->lines == NULL) return 0;
    if (vb->cur.dong < 0 || vb->cur.dong >= vb->nLines) return 0;
    if (vb->lines[vb->cur.dong] == NULL) return 0;
    return 1;
}
///CHUAN HOA VI TRI CON TRO 
static int chuanHoaCot(VanBan *vb) {
    int len = (int)strlen(vb->lines[vb->cur.dong]);
    if (vb->cur.cot < 0)   vb->cur.cot = 0;
    if (vb->cur.cot > len) vb->cur.cot = len;
    return vb->cur.cot;
}
///CHEN KY TU TAI VI TRI CON TRO 
void chenKyTu(VanBan *vb, char c) {
    char *dong;        
    char *moi;          
    int len, cot, i;
    if (!vanBanHopLe(vb) || c == '\0') return;
    cot  = chuanHoaCot(vb);
    dong = vb->lines[vb->cur.dong];
    len  = (int)strlen(dong);
    moi = (char *)bnRealloc(dong, len + 2);
    if (moi == NULL) {                       
        datThongBao(vb, "Het bo nho!");
        return;
    }

    for (i = len; i >= cot; i--) {
        moi[i + 1] = moi[i];
    }
    moi[cot] = c;
    vb->lines[vb->cur.dong] = moi;           
    vb->cur.cot = cot + 1;
    vb->daSua = 1;
}

    void chenTab(VanBan *vb) {
    for (int i = 0; i < SO_KHOANG_TRANG_TAB; i++) {
        chenKyTu(vb, ' ');
    }
}
///XUONG DONG TAI VI TRI CON TRO 
    void xuongDong(VanBan *vb) {
    int cot, soDongTruoc;

    if (!vanBanHopLe(vb)) return;

    cot = chuanHoaCot(vb);
    soDongTruoc = vb->nLines;                
     themDong(vb, vb->cur.dong + 1, vb->lines[vb->cur.dong] + cot);
    if (vb->nLines != soDongTruoc + 1) {
        datThongBao(vb, "Khong the tach dong!");
        return;
    }
    vb->lines[vb->cur.dong][cot] = '\0';
    vb->cur.dong++;
    vb->cur.cot = 0;
    vb->daSua = 1;
}
///XOA KY TU TAI VI TRI TRUOC CON TRO 
  void xoaKyTuTruocCon(VanBan *vb) {
    char *dong, *truoc, *moi;
    int cot, len, i;
    int dongTruoc, lenTruoc, lenHienTai;
    if (!vanBanHopLe(vb)) return;
    cot  = chuanHoaCot(vb);
    dong = vb->lines[vb->cur.dong];
    len  = (int)strlen(dong);
    if (cot > 0) {
        for (i = cot - 1; i < len; i++) {
            dong[i] = dong[i + 1];
        }
        vb->cur.cot = cot - 1;
        vb->daSua = 1;
        return;
    }
    if (vb->cur.dong == 0) return;
    dongTruoc  = vb->cur.dong - 1;
    truoc      = vb->lines[dongTruoc];
    lenTruoc   = (int)strlen(truoc);         
    lenHienTai = (int)strlen(dong);
    moi = (char *)bnRealloc(truoc, lenTruoc + lenHienTai + 1);
    if (moi == NULL) {
        datThongBao(vb, "Het bo nho!");
        return;
    }
    strcat(moi, dong);
    vb->lines[dongTruoc] = moi;
    xoaDong(vb, vb->cur.dong);
    vb->cur.dong = dongTruoc;
    vb->cur.cot  = lenTruoc;
    vb->daSua = 1;
}
///XOA KY TU TAI CON TRO 
void xoaKyTuTaiCon(VanBan *vb) {
    char *dong, *ke, *moi;
    int cot, len, i;
    int dongGoc, dongKe, lenKe;
  if (!vanBanHopLe(vb)) return;
    cot  = chuanHoaCot(vb);
    dong = vb->lines[vb->cur.dong];
    len  = (int)strlen(dong);
    if (cot < len) {
        for (i = cot; i < len; i++) {        
            dong[i] = dong[i + 1];
        }
        vb->daSua = 1;
        return;
    }
    if (vb->cur.dong + 1 >= vb->nLines) return;
    dongGoc = vb->cur.dong;
    dongKe  = dongGoc + 1;
    ke      = vb->lines[dongKe];
    lenKe   = (int)strlen(ke);

    moi = (char *)bnRealloc(dong, len + lenKe + 1);
    if (moi == NULL) {
        datThongBao(vb, "Het bo nho!");
        return;
    }
    strcat(moi, ke);                         
    vb->lines[dongGoc] = moi;

    xoaDong(vb, dongKe);
    vb->cur.dong = dongGoc;                  
    vb->cur.cot  = cot;                      
    vb->daSua = 1;
}
///XOA DONG HIEN TAI 
void xoaDongHienTai(VanBan *vb) {
    if (!vanBanHopLe(vb)) return;

    xoaDong(vb, vb->cur.dong);               
    if (vb->cur.dong >= vb->nLines) vb->cur.dong = vb->nLines - 1;
    if (vb->cur.dong < 0) vb->cur.dong = 0;

    vb->cur.cot = 0;
    vb->daSua = 1;
}

//Khai bao hien thi va file cua HIEN
//KHAI BAO HIEN THI
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
//KHAI BAO FILE
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

int main (){
	printf("Hello UTC2");
	
	
	
	
} 
