    #include <stdio.h>
#include <string.h>

struct TicketZone {
    int zone_id;
    char zone_name[50];
    float ticket_price;
    int total_capacity;
    int sold_tickets;
};

struct QrCheckIn {
    char qr_code[20];
    int zone_id;
    int is_used;
};

int findZoneById(struct TicketZone zones[], int total_zones, int zone_id);
int findQrByCode(struct QrCheckIn qrs[], int total_qrs, const char* qr_code);
float calculatePrice(float base_price, int quantity, int is_early_bird);
int bookTickets(struct TicketZone zones[], int total_zones, int zone_id, int quantity, int is_early_bird, float* total_cost);
int checkInQR(struct QrCheckIn qrs[], int total_qrs, const char* qr_code);

int main() {
    struct TicketZone zones[5] = {
        {1, "VIP", 2000000, 50, 48},  
        {2, "Zone A", 1000000, 100, 10} 
    };
    int total_zones = 2;

    struct QrCheckIn qrs[5] = {
        {"QR_VIP_001", 1, 0}, 
        {"QR_ZOA_001", 2, 1}  
    };
    int total_qrs = 2;

    float cost = 0;

    printf("=== KIEM THU MODULE BAN VE ===\n");

    printf("\n1. Test mua ve thanh cong (Early Bird): ");
    if (bookTickets(zones, total_zones, 2, 2, 1, &cost)) {
        printf("Thanh cong! Tong tien: %.0f VND\n", cost);
    }

    printf("\n2. Test mua vuot han muc 4 ve/don (Loi 1): ");
    bookTickets(zones, total_zones, 2, 5, 0, &cost);

    printf("\n3. Test mua so luong am (Loi 1): ");
    bookTickets(zones, total_zones, 2, -1, 0, &cost);

    printf("\n4. Test tran dung luong (Loi 2 - VIP con 2 cho, mua 3 ve): ");
    bookTickets(zones, total_zones, 1, 3, 0, &cost);

    printf("\n5. Test ma khu vuc khong ton tai (Loi 3): ");
    bookTickets(zones, total_zones, 99, 2, 0, &cost);

    printf("\n6. Test mang rong (Loi 5): ");
    bookTickets(zones, 0, 1, 2, 0, &cost);


    printf("\n\n=== KIEM THU MODULE CHECK-IN ===\n");

    printf("\n7. Test check-in thanh cong: ");
    checkInQR(qrs, total_qrs, "QR_VIP_001");

    printf("\n8. Test check-in trung lap (Loi 4 - Quet lai ma vua xai): ");
    checkInQR(qrs, total_qrs, "QR_VIP_001");

    printf("\n9. Test check-in ma da dung tu truoc (Loi 4): ");
    checkInQR(qrs, total_qrs, "QR_ZOA_001");

    printf("\n10. Test check-in ma khong ton tai (Loi 3): ");
    checkInQR(qrs, total_qrs, "QR_FAKE_999");

    printf("\n11. Test mang QR rong (Loi 5): ");
    checkInQR(qrs, 0, "QR_VIP_001");

    return 0;
}

int findZoneById(struct TicketZone zones[], int total_zones, int zone_id) {
    for (int i = 0; i < total_zones; i++) {
        if (zones[i].zone_id == zone_id) {
            return i;
        }
    }
    return -1;
}

int findQrByCode(struct QrCheckIn qrs[], int total_qrs, const char* qr_code) {
    for (int i = 0; i < total_qrs; i++) {
        if (strcmp(qrs[i].qr_code, qr_code) == 0) {
            return i;
        }
    }
    return -1;
}

float calculatePrice(float base_price, int quantity, int is_early_bird) {
    float total = base_price * quantity;
    if (is_early_bird == 1) {
        total = total * 0.85f;
    }
    return total;
}

int bookTickets(struct TicketZone zones[], int total_zones, int zone_id, int quantity, int is_early_bird, float* total_cost) {
    if (total_zones <= 0) {
        printf("[Tu choi]: He thong khu vuc ve dang rong.\n");
        return 0;
    }

    if (quantity < 1 || quantity > 4) {
        printf("[Tu choi]: So luong ve (%d) khong hop le. Chi duoc mua 1-4 ve.\n", quantity);
        return 0;
    }

    int idx = findZoneById(zones, total_zones, zone_id);
    if (idx == -1) {
        printf("[Tu choi]: Ma khu vuc %d khong ton tai tren he thong.\n", zone_id);
        return 0;
    }

    if (zones[idx].sold_tickets + quantity > zones[idx].total_capacity) {
        printf("[Tu choi]: Khu vuc %s da het cho (Con lai: %d).\n", 
               zones[idx].zone_name, 
               zones[idx].total_capacity - zones[idx].sold_tickets);
        return 0;
    }

    zones[idx].sold_tickets += quantity;
    *total_cost = calculatePrice(zones[idx].ticket_price, quantity, is_early_bird);
    
    return 1;
}

int checkInQR(struct QrCheckIn qrs[], int total_qrs, const char* qr_code) {
    if (total_qrs <= 0) {
        printf("[Tu choi]: He thong QR dang rong.\n");
        return 0;
    }

    int idx = findQrByCode(qrs, total_qrs, qr_code);
    if (idx == -1) {
        printf("[Tu choi]: Ma QR %s khong ton tai.\n", qr_code);
        return 0;
    }

    if (qrs[idx].is_used == 1) {
        printf("[Tu choi - GIAN LAN]: Ma QR %s da duoc su dung truoc do!\n", qr_code);
        return 0;
    }

    qrs[idx].is_used = 1;
    printf("[Hop le]: Check-in thanh cong cho ma %s.\n", qr_code);
    return 1;
}