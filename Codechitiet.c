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
