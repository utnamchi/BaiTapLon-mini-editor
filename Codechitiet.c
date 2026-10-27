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
