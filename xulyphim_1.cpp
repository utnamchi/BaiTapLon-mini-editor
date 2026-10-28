void xuLyPhim(VanBan *vb, int *thoat) {
    int k = _getch();

    if (k == 0 || k == KEY_EXT) {                 /* phim mo rong */
        int k2 = _getch();
        int len = (int)strlen(vb->lines[vb->cur.dong]);
        switch (k2) {
            case KEY_UP:
                if (vb->cur.dong > 0) vb->cur.dong--;
                break;
            case KEY_DOWN:
                if (vb->cur.dong < vb->nLines - 1) vb->cur.dong++;
                break;
            case KEY_LEFT:
                if (vb->cur.cot > 0) vb->cur.cot--;
                else if (vb->cur.dong > 0) {      /* ve cuoi dong truoc */
                    vb->cur.dong--;
                    vb->cur.cot = (int)strlen(vb->lines[vb->cur.dong]);
                }
                break;
             case KEY_RIGHT:
                if (vb->cur.cot < len) vb->cur.cot++;
                else if (vb->cur.dong < vb->nLines - 1) { vb->cur.dong++; vb->cur.cot = 0; }
                break;
            case KEY_DEL : {
	    	char *dong= vb->lines[vb->cur.dong];
	    	int len = strlen(dong);
	    	
	    	if(vb->cur.cot < len )
	    		memmove(dong + vb->cur.cot ,dong + vb->cur.cot+1, len-vb->cur.cot);
	    		
	    	else if(vb->cur.dong <vb->nLines -1){
	    		strcat(dong, vb->lines[vb->cur.dong+1]); //noi tiep dong nay vao sau dong kia
	    		xoaDong(vb, vb->cur.dong+1);
			}
			vb->daSua=1;
			break;
		}
        }
        /* Gioi han cot theo do dai dong moi */
        len = (int)strlen(vb->lines[vb->cur.dong]);
        if (vb->cur.cot > len) vb->cur.cot = len;
        return;
    }

    switch (k) {
        case KEY_ENTER:  xuongDong(vb);                    break;
        case KEY_BACK:   xoaKyTuTruocCon(vb);              break;
        case KEY_TAB:    chenTab(vb);          			   break;
        case KEY_CTRL_K: xoaDong(vb, vb->cur.dong);        break;
        case KEY_CTRL_T: thongKe(vb);                      break;
        case KEY_CTRL_F: timChuoi(vb);                     break;
        case KEY_CTRL_R: thayTheTatCa(vb);                 break;
        case KEY_CTRL_S: {
            char ten[260];
            if (vb->tenFile[0]) strcpy(ten, vb->tenFile);
            else {
                clearScreen();
                printf("Ten file (vd: baitap.txt): ");
                fgets(ten, sizeof(ten), stdin);
                ten[strcspn(ten, "\n")] = '\0';
            }
            if (ten[0]) luuFile(vb, ten);
            break;
        }
        case KEY_CTRL_O: {
            char ten[260];
            clearScreen();
            printf("Ten file can mo: ");
            fgets(ten, sizeof(ten), stdin);
            ten[strcspn(ten, "\n")] = '\0';
            if (!moFile(vb, ten)) { printf("Khong mo duoc file!\n"); _getch(); }
            break;
        }
        case KEY_CTRL_Q: {
    		if (vb->daSua) {
        		char ch;
        		printf("Luu truoc khi thoat? (y/n): ");
        		ch = _getch();

        		if (ch == 'y' || ch == 'Y') {
            		char ten[260];
					strcpy(ten, vb->tenFile);
				
					if (ten[0] == '\0') {
               			printf("\nTen file: ");
                		fgets(ten, sizeof(ten), stdin);
                		ten[strcspn(ten, "\n")] = '\0';
            		}

            		if (ten[0] == '\0') {
                		printf("Ten file khong duoc de trong!");
                		_getch();
            		}
            		else if (luuFile(vb, ten)) {
                		*thoat = 1;
            		}
            		else {
               			printf("Khong luu duoc file!");
                		_getch();
            		}
        		}
        		else if (ch == 'n' || ch == 'N') {
            		*thoat = 1;
        		}
        		break;
    		}
    		else {
           		*thoat = 1;
            	break;
    		}
    	}
    	default:
            if (k >= 32 && k < 127) chenKyTu(vb, (char)k);   /* ky tu in duoc */
            break;
	}
}
