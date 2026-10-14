BÁO CÁO TÁI CẤU TRÚC HỆ THỐNG (RÚT GỌN)
1. Phân tích I/O

Module Bán vé: Nhận đầu vào là mảng khu vực, ID, số lượng, trạng thái ưu đãi. Trả về tổng tiền và cập nhật số lượng vé đã bán.

Module Soát vé: Nhận đầu vào là mảng QR và mã QR. Trả về trạng thái hợp lệ và cập nhật cờ is_used.

2. Đề xuất & Lựa chọn Giải pháp

Giải pháp A (Hàm nguyên khối): Gộp toàn bộ logic tìm kiếm, tính toán, kiểm tra vào 1 hàm. Dễ sinh lỗi (Spaghetti code), khó bảo trì.

Giải pháp B (Module hóa SRP): Tách nhỏ thành các hàm chuyên biệt: Tìm khu vực (findZoneById), Tìm QR (findQrByCode), Tính tiền (calculatePrice), Bán vé (bookTickets), và Soát vé (checkInQR).

=> Lựa chọn Giải pháp B. Việc tách riêng các hàm tiện ích giúp code mạch lạc, tái sử dụng tốt, dễ dàng bóc tách và chặn đứng triệt để 5 lỗi biên (số lượng sai, tràn sức chứa, sai ID, trùng QR, mảng rỗng) mà không làm phình to hàm chính.
