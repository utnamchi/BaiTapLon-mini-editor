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
