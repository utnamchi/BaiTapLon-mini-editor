///KIEM TRA VAN BAN HOP LE 
static int vanBanHopLe(const VanBan *vb) {
    if (vb == NULL) return 0;
    if (vb->lines == NULL) return 0;
    if (vb->cur.dong < 0 || vb->cur.dong >= vb->nLines) return 0;
    if (vb->lines[vb->cur.dong] == NULL) return 0;
    return 1;
}
