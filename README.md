# Mini Text Editor trên Console (Windows)

**Bài tập lớn môn Kỹ thuật lập trình** – Đề tài: *Trình biên tập văn bản đơn giản trên Console (Mini Text Editor)*, viết bằng ngôn ngữ C.

**Trường Đại học Giao thông Vận tải – Phân hiệu tại TP. Hồ Chí Minh – Bộ môn Công nghệ Thông tin**

| | |
|---|---|
| Giảng viên hướng dẫn | ThS. Trần Thị Dung |
| Lớp | CQ.67.CNTT (Khóa 67) |
| Ngày hoàn thành | 08/11/2026 |

## Nhóm thực hiện

| STT | Họ và tên | MSSV |
|:---:|-----------|------|
| 1 | Phan Ngọc Bảo Trân | 6751071080 |
| 2 | Đoàn Lê Thái Phong | 6751071057 |
| 3 | Mai Thu Tuyền | 6751071088 |
| 4 | Lê Minh Quân | 6751071065 |
| 5 | Bùi Minh Hiển | 6751071019 |

---

## 1. Giới thiệu

Mini Text Editor là trình soạn thảo văn bản chạy trực tiếp trên console Windows. Nhóm vận dụng các kiến thức về chuỗi ký tự, con trỏ, cấu trúc dữ liệu, cấp phát bộ nhớ động và xử lý tệp để xây dựng chương trình. Văn bản được lưu trong bộ nhớ dưới dạng mảng con trỏ `char **lines`, mỗi dòng là một chuỗi cấp phát riêng.

## 2. Chức năng

- Soạn thảo nhiều dòng: chèn ký tự, `Enter` tách dòng, `Backspace` và `Delete` (tự nối dòng khi xóa ở đầu hoặc cuối dòng).
- Di chuyển con trỏ bằng các phím mũi tên, có thể đi qua lại giữa các dòng.
- Phím `Tab` chèn 4 khoảng trắng.
- Mở và lưu tệp `.txt`.
- Xóa nguyên một dòng.
- Tìm chuỗi: liệt kê mọi vị trí (dòng, cột) và tổng số lần xuất hiện (không chồng lấn).
- Thay thế tất cả các lần xuất hiện của một chuỗi, hỗ trợ chuỗi mới dài hơn, ngắn hơn hoặc rỗng.
- Thống kê số dòng, số ký tự, số từ.
- Hỏi lưu khi thoát nếu có thay đổi chưa lưu (thanh tiêu đề hiện dấu `*`).
- Theo dõi cấp phát/giải phóng bộ nhớ và cảnh báo rò rỉ khi thoát.

## 3. Phím tắt

| Phím | Chức năng |
|------|-----------|
| `Ctrl + S` | Lưu tệp (hỏi tên tệp nếu chưa đặt) |
| `Ctrl + O` | Mở tệp |
| `Ctrl + F` | Tìm chuỗi |
| `Ctrl + R` | Thay thế tất cả |
| `Ctrl + K` | Xóa dòng hiện tại |
| `Ctrl + T` | Thống kê (dòng / ký tự / từ) |
| `Ctrl + Q` | Thoát (hỏi lưu nếu có thay đổi) |
| `←` `↑` `→` `↓` | Di chuyển con trỏ |
| `Backspace` | Xóa ký tự trước con trỏ |
| `Delete` | Xóa ký tự tại con trỏ |
| `Tab` | Chèn 4 khoảng trắng |
| `Enter` | Xuống dòng |

## 4. Yêu cầu và cách chạy

**Yêu cầu:** Windows và trình biên dịch GCC (MinGW / MinGW-w64). Chương trình dùng `<conio.h>`, `<windows.h>` và lệnh `cls` nên chỉ hướng đến console Windows.

**Biên dịch và chạy:**

```bash
gcc mini-text-eitor-full.c -o mini-text-eitor-full.exe
mini-text-eitor-full.exe
```

## 5. Hướng dẫn sử dụng nhanh

1. Chạy chương trình rồi gõ nội dung trực tiếp.
2. Nhấn `Ctrl + S`, nhập tên tệp (ví dụ `baitap.txt`) để lưu.
3. Nhấn `Ctrl + O` và nhập tên tệp để mở lại.
4. Dùng `Ctrl + F` để tìm, `Ctrl + R` để thay thế, `Ctrl + T` để xem thống kê.
5. Nhấn `Ctrl + Q` để thoát. Nếu có thay đổi chưa lưu, chương trình hỏi `Luu truoc khi thoat? (y/n)`.

## 6. Cấu trúc dữ liệu

```c
typedef struct {
    int dong;   // chỉ số dòng (bắt đầu từ 0)
    int cot;    // chỉ số cột (0 là đầu dòng)
} ConTroViTri;

typedef struct {
    char **lines;       // mảng động, mỗi phần tử là một dòng (chuỗi malloc riêng)
    int nLines;         // số dòng hiện có
    int capacity;       // số ô con trỏ đã cấp phát (gấp đôi khi đầy)
    ConTroViTri cur;    // vị trí con trỏ
    char tenFile[260];  // tên tệp đang mở
    int daSua;          // cờ: có thay đổi chưa lưu
    int offDong, offCot;
    int manHinhDong;
    char thongBao[80];  // thông báo ngắn ở cuối màn hình
} VanBan;
```

- Mảng `lines` được mở rộng bằng `realloc`, tăng gấp đôi dung lượng khi đầy.
- Văn bản luôn có ít nhất 1 dòng: xóa dòng cuối cùng chỉ làm dòng đó rỗng.

## 7. Quản lý bộ nhớ

Mọi thao tác cấp phát đều đi qua các hàm bọc `bnMalloc`, `bnRealloc`, `bnFree` để đếm số lần cấp phát và giải phóng. Khi thoát, chương trình in báo cáo:

```
Cap phat: <n> | Giai phong: <n>
Khong ro ri bo nho.
```

Nếu hai con số không khớp, chương trình in `CANH BAO RO RI BO NHO` kèm số khối bị rò rỉ.

## 8. Tổ chức mã nguồn

| Nhóm | Hàm |
|------|-----|
| Quản lý bộ nhớ | `khoiTao`, `giaiPhong`, `themDong`, `xoaDong` |
| Soạn thảo | `chenKyTu`, `chenTab`, `xuongDong`, `xoaKyTuTruocCon`, `xoaKyTuTaiCon` |
| Hiển thị | `hienThi`, `gotoxy`, `clearScreen` |
| Tệp | `luuFile`, `moFile` |
| Tìm / thay thế / thống kê | `timChuoi`, `thayTheTatCa`, `thongKe` |
| Xử lý phím | `xuLyPhim` |

## 9. Kiểm thử

Nhóm kiểm thử chức năng theo từng thao tác với văn bản nhiều dòng, chuỗi lặp, dòng rỗng, tệp tồn tại và không tồn tại. Một số ca tiêu biểu:

| Chức năng | Thao tác | Kết quả mong đợi |
|-----------|----------|------------------|
| Chèn ký tự / xuống dòng | Gõ `Xin chao`, `Enter`, gõ `Dong thu hai` | Hai dòng hiển thị đúng thứ tự |
| Backspace | `ABCDE`, con trỏ sau `C`, nhấn `Backspace` | Thành `ABDE` |
| Delete | `ABCDE`, con trỏ tại `C`, nhấn `Delete` | Thành `ABDE` |
| Delete cuối dòng | Con trỏ ở cuối dòng có dòng phía dưới | Hai dòng được nối lại |
| Xóa dòng | 3 dòng, con trỏ ở dòng 2, `Ctrl + K` | Dòng 2 bị xóa, các dòng khác giữ nguyên |
| Tìm chuỗi | `xin chao xin chao`, tìm `chao` | 2 lần xuất hiện, đúng dòng và cột |
| Tìm chuỗi không có / rỗng | Tìm `khongco`; hoặc nhấn `Enter` khi nhập chuỗi tìm | Thông báo không tìm thấy / không được để trống |
| Thay chuỗi dài hơn | `toi hoc C`, thay `C` bằng `lap trinh C` | Thay đúng, phần còn lại không đổi |
| Thay chuỗi ngắn hơn | `abc abc`, thay `abc` bằng `x` | Thành `x x` |
| Lưu rồi mở lại | Lưu `kiemthu.txt`, mở lại | Nội dung trùng khớp |
| Mở tệp không tồn tại | Nhập `khong_ton_tai.txt` | Báo `Khong mo duoc file!`, không thoát bất thường |
| Thoát khi chưa lưu | Sửa nội dung rồi `Ctrl + Q` | Hỏi lưu và xử lý đúng lựa chọn |
| Bộ nhớ | Mở, sửa, tìm/thay thế nhiều lần rồi thoát | Báo `Khong ro ri bo nho.` |

Chi tiết đầy đủ các ca kiểm thử nằm trong file báo cáo (Chương 4).

## 10. Hạn chế

- Chỉ chạy trên Windows.
- Chỉ nhận ký tự ASCII in được (mã 32 đến 126), chưa gõ được tiếng Việt có dấu trực tiếp.
- Khi mở tệp, dòng dài hơn 1023 ký tự sẽ bị tách thành nhiều dòng.
- Chưa có cuộn màn hình (số dòng hiển thị tối đa đặt là 1000).
- `Ctrl + O` không hỏi lưu khi văn bản hiện tại có thay đổi chưa lưu.

## 11. Hướng phát triển

- Cải tiến giao diện, cuộn màn hình theo vị trí con trỏ.
- Bổ sung sao chép, cắt, dán, hoàn tác và làm lại (Undo/Redo).
- Hỗ trợ tiếng Việt có dấu (UTF-8) và thống kê ký tự chính xác hơn.
- Nâng cao xử lý tệp: lưu tự động, cảnh báo khi mở tệp mới mà chưa lưu.
- Tăng độ ổn định: hoàn thiện xử lý ngoại lệ và kiểm thử các trường hợp đặc biệt.

## 12. Tài liệu tham khảo

1. B. W. Kernighan, D. M. Ritchie, *The C Programming Language*, 2nd ed., Prentice Hall, 1988.
2. S. Prata, *C Primer Plus*, 6th ed., Addison-Wesley, 2013.
3. Microsoft Learn, `_getch`, `_getwch`; `SetConsoleCursorPosition function`.
4. cppreference.com, *C string and memory library*.
