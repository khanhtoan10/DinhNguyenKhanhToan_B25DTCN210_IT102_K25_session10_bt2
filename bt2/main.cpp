#include <stdio.h>
#include <string.h>

#define MAX_VE 50

struct VeSuKien {
    int maVe;
    char tenSuKien[50];
    char loaiVe[20];
    float giaGoc;
    int isEarlyBird;
    int daCheckIn;
};

int timVeTheoMa(const struct VeSuKien dsVe[], int soLuongVe, int maVe);
int themVe(struct VeSuKien dsVe[], int soLuongVe, struct VeSuKien veMoi);
void hienThiDanhSach(const struct VeSuKien dsVe[], int soLuongVe);
int checkInVe(struct VeSuKien dsVe[], int soLuongVe, int maVe);
int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe);

int main() {
    struct VeSuKien dsVe[MAX_VE];
    int soLuongVe = 0;

    printf("=== HE THONG QUAN LY & SOAT VE TU DONG TICKETBOX ===\n\n");

    struct VeSuKien v1 = {1001, "Live Concert VIBE 2025", "VIP", 2000000.0f, 1, 0};
    struct VeSuKien v2 = {1002, "Live Concert VIBE 2025", "Zone A", 1200000.0f, 0, 0};
    struct VeSuKien v3 = {1003, "Live Concert VIBE 2025", "GA", 800000.0f, 1, 0};

    soLuongVe = themVe(dsVe, soLuongVe, v1);
    soLuongVe = themVe(dsVe, soLuongVe, v2);
    soLuongVe = themVe(dsVe, soLuongVe, v3);

    printf("1. Khoi tao danh sach 3 ve ban dau:\n");
    hienThiDanhSach(dsVe, soLuongVe);

    printf("\n2. Thu nghiem phat hanh them 1 ve moi:\n");
    struct VeSuKien v4 = {1004, "Live Concert VIBE 2025", "VIP", 2500000.0f, 1, 0};
    soLuongVe = themVe(dsVe, soLuongVe, v4);
    hienThiDanhSach(dsVe, soLuongVe);

    printf("\n3 & 4. Thuc hien quet ma QR check-in thanh cong cho ve 1001:\n");
    checkInVe(dsVe, soLuongVe, 1001);

    printf("\n5. Thu nghiem quet lai ma ve 1001 (Duplicate QR Scan):\n");
    checkInVe(dsVe, soLuongVe, 1001);

    printf("\n6. Thuc hien huy 1 ve theo ma (Huy ve 1002):\n");
    soLuongVe = huyVe(dsVe, soLuongVe, 1002);

    printf("\n7. Thu nghiem huy ve khong ton tai (Ma 9999):\n");
    soLuongVe = huyVe(dsVe, soLuongVe, 9999);

    printf("\n8. Hien thi lai toan bo danh sach sau cac thao tac:\n");
    hienThiDanhSach(dsVe, soLuongVe);

    return 0;
}

int timVeTheoMa(const struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    for (int i = 0; i < soLuongVe; i++) {
        if (dsVe[i].maVe == maVe) {
            return i;
        }
    }
    return -1;
}

int themVe(struct VeSuKien dsVe[], int soLuongVe, struct VeSuKien veMoi) {
    if (soLuongVe >= MAX_VE) {
        printf("[LOI]: Tran bo nhieu (Overflow)! Khong the phat hanh them ve.\n");
        return soLuongVe;
    }

    if (veMoi.isEarlyBird == 1) {
        veMoi.giaGoc = veMoi.giaGoc * 0.85f;
    }

    dsVe[soLuongVe] = veMoi;
    printf("[THANH CONG]: Da them ve ma %d vao he thong.\n", veMoi.maVe);
    return soLuongVe + 1;
}

void hienThiDanhSach(const struct VeSuKien dsVe[], int soLuongVe) {
    if (soLuongVe == 0) {
        printf("[THONG BAO]: Danh sach ve hien dang trong (Underflow).\n");
        return;
    }

    printf("--- DANH SACH VE HIEN TAI (%d ve) ---\n", soLuongVe);
    for (int i = 0; i < soLuongVe; i++) {
        printf("STT: %d | Ma: %d | Su kien: %s | Khu vuc: %-7s | Gia thanh toan: %.0f VND | Check-in: %s\n",
               i + 1, dsVe[i].maVe, dsVe[i].tenSuKien, dsVe[i].loaiVe, dsVe[i].giaGoc,
               dsVe[i].daCheckIn == 1 ? "Da check-in" : "Chua check-in");
    }
}

int checkInVe(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    int index = timVeTheoMa(dsVe, soLuongVe, maVe);
    if (index == -1) {
        printf("[LOI CHECK-IN]: Ma ve %d khong ton tai trong he thong!\n", maVe);
        return 0;
    }

    if (dsVe[index].daCheckIn == 1) {
        printf("[CANH BAO GIAN LAN]: Ve ma %d da duoc check-in truoc do!\n", maVe);
        return 0;
    }

    dsVe[index].daCheckIn = 1;
    printf("[THANH CONG]: Check-in thanh công cho ma ve %d.\n", maVe);
    return 1;
}

int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    if (soLuongVe == 0) {
        printf("[LOI HUY VE]: Danh sach rong (Underflow), khong the thuc hien huy.\n");
        return soLuongVe;
    }

    int index = timVeTheoMa(dsVe, soLuongVe, maVe);
    if (index == -1) {
        printf("[LOI HUY VE]: Khong tim thay ma ve %d de huy!\n", maVe);
        return soLuongVe;
    }

    for (int i = index; i < soLuongVe - 1; i++) {
        dsVe[i] = dsVe[i + 1];
    }

    printf("[THANH CONG]: Da huy va xoa ve ma %d khoi he thong.\n", maVe);
    return soLuongVe - 1;
}
