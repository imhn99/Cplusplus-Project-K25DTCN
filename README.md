# README: Hệ thống Quản lý Người dùng và Ví Điểm

## Mục tiêu dự án

Xây dựng hệ thống quản lý người dùng với chức năng ví điểm và bảo mật OTP, cho phép user và admin tương tác với hệ thống theo các quyền hạn khác nhau.

## Chức năng chính

### Đăng nhập / Đăng ký / Đăng xuất

- Người dùng chọn đăng nhập hoặc đăng ký tài khoản.
- Có thể thoát chương trình từ menu chính.
- Đăng xuất quay lại menu chính.

### Với user

1. **Xem thông tin cá nhân**: Hiển thị username, email, role, số dư, mã ví.
2. **Xem số dư ví**: Xem điểm hiện tại trong ví.
3. **Chuyển điểm (OTP)**: Chuyển điểm sang ví người khác sau khi xác thực OTP.
4. **Đổi mật khẩu (OTP)**: Đổi mật khẩu với xác thực OTP.
5. **Đổi thông tin cá nhân (OTP)**: Đổi email với xác thực OTP.
6. **Nạp điểm (OTP + mã giao dịch)**: Gửi yêu cầu nạp điểm với mã giao dịch, chờ admin xác nhận.
7. **Đăng xuất**: Trở về menu chính.

### Với admin

1. **Xem thông tin tất cả thành viên**: Bao gồm mã ví, số dư.
2. **Xem ví tổng**: Số dư và mã ví tổng.
3. **Nạp điểm vào ví tổng**: Thêm điểm vào ví tổng.
4. **Nạp điểm cho thành viên**: Xác nhận mã giao dịch, trừ điểm từ ví tổng để cộng cho user.
5. **Đăng xuất**: Trở về menu chính.

## Nhiệm vụ của từng thành viên

- **Thành viên 1**: Xây dựng module UserManager (đăng ký, đăng nhập, đổi mật khẩu, đổi thông tin cá nhân, lưu file users.db).
- **Thành viên 2**: Xây dựng module WalletManager (quản lý ví, điểm, ví tổng, chuyển điểm, lưu file wallets.db).
- **Thành viên 3**: Xây dựng module OtpManager (tạo, xác thực OTP, bảo mật giao dịch).
- **Thành viên 4**: Tích hợp hệ thống, viết main.cpp, xử lý menu, luồng chương trình, đóng gói và test.

## Các file chính

- `main.cpp`: Điều khiển luồng chính, menu user/admin.
- `UserManager.*`: Xử lý người dùng.
- `WalletManager.*`: Quản lý ví, điểm.
- `OtpManager.*`: Sinh và xác thực OTP.

## Yêu cầu

- **C++17** trở lên.

## Cách cài C++17 theo hệ điều hành

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install g++
g++ --version
```

Hãy đảm bảo version >= 7.

### Fedora / CentOS / RHEL

```bash
sudo dnf install gcc-c++
g++ --version
```

### macOS (với Homebrew)

```bash
brew install gcc
g++-13 --version  # Hoặc g++ tương ứng
```

### Windows

- Cài đặt MinGW-w64: [https://winlibs.com/](https://winlibs.com/)
- Hoặc dùng WSL để chạy môi trường Linux.

## Cách build & chạy

```bash
g++ -std=c++17 main.cpp UserManager.cpp WalletManager.cpp OtpManager.cpp -o app
./app
```

## Ghi chú

- Dữ liệu được lưu ở `users.db`, `wallets.db`, `topups.db`.
- Mỗi giao dịch quan trọng yêu cầu OTP để tăng bảo mật.

## Nguồn tham khảo

- [https://cplusplus.com/](https://cplusplus.com/)
- [https://en.cppreference.com/](https://en.cppreference.com/)
- Tài liệu GCC: [https://gcc.gnu.org/](https://gcc.gnu.org/)
- Hướng dẫn MinGW: [https://winlibs.com/](https://winlibs.com/)

