# IoT Tuần 2 – Điều khiển LED bằng nút nhấn (ESP32-S3 + OneButton)

Dự án PlatformIO gồm các bài tập điều khiển LED bằng nút nhấn, dùng thư viện [OneButton](https://github.com/mathertel/OneButton) và lớp `LED` (thư mục `lib/LED`). Tất cả các bài nằm chung trong một project. Mỗi bài là một **môi trường (env)** riêng trong `platformio.ini`, nên không cần copy code qua lại giữa các file.

## ⚠️ Lưu ý về phần cứng

Đề bài yêu cầu dùng **ESP32 DevKit loại 30 chân**. Do không có board này, em dùng **ESP32-S3 DevKitC-1 N16R8** (16 MB flash, 8 MB PSRAM). Vì vậy có một số khác biệt:

| | ESP32 30 chân (theo đề) | ESP32-S3 N16R8 (đang dùng) |
|---|---|---|
| LED built-in | LED đơn ở GPIO2 | LED RGB WS2812 (GPIO48 hoặc GPIO38 tùy phiên bản), **không bật/tắt bằng `digitalWrite` thông thường được** |
| Nút BOOT | GPIO0 | GPIO0 |
| Cấu hình PIO | `board = esp32dev` | `board = esp32-s3-devkitc-1`, thêm cấu hình PSRAM/flash 16 MB |

Vì LED built-in của S3 là LED RGB, em thay bằng **2 LED ngoài** cắm trên test board (GPIO4 và GPIO6). Cách chuyển sang board 30 chân có ở [cuối file](#chạy-trên-esp32-loại-30-chân).

## Cấu trúc dự án

```
iot_tuan2/
├── lib/LED/LED.h        # Lớp LED: on(), off(), flip(), blink(ms), loop()
├── src/
│   ├── blink.cpp        # Bài 1: LED nhấp nháy
│   ├── doublePush.cpp   # Bài 2: 1 nút điều khiển 1 LED
│   └── twoLed.cpp       # Bài 3: 1 nút điều khiển 2 LED (bài tập về nhà)
└── platformio.ini       # Mỗi bài = 1 env
```

Mỗi env dùng `build_src_filter` để chỉ biên dịch đúng file của bài đó, và dùng `build_flags` để khai báo chân GPIO:

| Env | File | Chân sử dụng |
|---|---|---|
| `blink` | `blink.cpp` | LED: GPIO4 |
| `double_push` | `doublePush.cpp` | LED: GPIO4, nút: GPIO0 (BOOT) |
| `two_leds` | `twoLed.cpp` | LED1: GPIO4, LED2: GPIO6, nút: GPIO5 |

## Các bài tập

### Bài 1 – `blink`
LED ở GPIO4 nhấp nháy với chu kỳ 500 ms.

### Bài 2 – `double_push`
Dùng nút BOOT có sẵn trên board:
- **Single click:** bật/tắt LED
- **Double click:** LED nhấp nháy 200 ms

### Bài 3 – `two_leds` (bài tập về nhà)
Một nút nhấn ngoài điều khiển hai LED:

| Thao tác | Chức năng |
|---|---|
| **Double click** | Chuyển LED đang được điều khiển (LED1 ⇄ LED2). LED được chọn sẽ sáng, LED còn lại tắt |
| **Single click** | Bật/tắt LED đang được điều khiển |
| **Giữ nút** | LED đang được điều khiển nhấp nháy 200 ms một lần |

Khi khởi động, chương trình chọn LED1 và LED1 sáng. Đang nhấp nháy mà single click thì LED dừng nhấp nháy và tắt.

## Sơ đồ nối dây (bài 3)

```
GPIO4 ──[220Ω]──▶|── GND     (LED1)
GPIO6 ──[220Ω]──▶|── GND     (LED2)
GPIO5 ──[ nút nhấn ]── GND
```

- LED tích cực mức cao (`LED_ACT=HIGH`): chân dài (+) nối về phía GPIO qua điện trở 220–330 Ω, chân ngắn (−) nối GND.
- Nút nhấn tích cực mức thấp (`BTN_ACT=LOW`): một đầu nối GPIO, một đầu nối GND. OneButton tự bật điện trở kéo lên nội nên không cần điện trở ngoài.

## Cách chạy

1. Cài VS Code và extension **PlatformIO IDE**.
2. Clone dự án:
   ```bash
   git clone https://github.com/TaThanhHa/iot_tuan2.git
   ```
3. Mở thư mục bằng VS Code.
4. Ở thanh trạng thái phía dưới, bấm vào ô chọn môi trường (mặc định hiện `Default (iot_tuan2)`), rồi chọn bài cần chạy, ví dụ `env:two_leds`.
5. Bấm **Upload** (→). PlatformIO tự tải thư viện OneButton.

> Nếu để `Default`, PlatformIO sẽ build và nạp **lần lượt cả 3 bài**, và board sẽ chạy bài nạp cuối cùng. Vì vậy cần chọn đúng env trước khi nạp.

Có thể dùng dòng lệnh:
```bash
pio run -e two_leds -t upload
```

## Chạy trên ESP32 loại 30 chân

1. Thay section `[env]` trong `platformio.ini` bằng:
   ```ini
   [env]
   platform = espressif32
   framework = arduino
   board = esp32dev
   lib_deps =
       mathertel/OneButton @ ^2.6.1
   build_flags =
   ```
   Các dòng `board_build.arduino.memory_type`, `board_upload.flash_size` và cờ `-DBOARD_HAS_PSRAM` chỉ dành cho S3 N16R8, nên cần bỏ đi.
2. Đổi chân trong `[env:two_leds]`. Trên ESP32 thường, **GPIO6–11 nối với bộ nhớ flash và không được dùng**. Gợi ý:
   ```ini
   -DLED_PIN_1=2     ; LED built-in
   -DLED_PIN_2=4     ; LED ngoài
   -DBTN_PIN=18      ; nút ngoài
   ```
   Cách này dùng được LED built-in (GPIO2) đúng như đề bài.

## Thư viện sử dụng

- [mathertel/OneButton](https://github.com/mathertel/OneButton) `^2.6.1`: nhận diện click, double click, giữ nút
- `lib/LED/LED.h`: lớp điều khiển LED không chặn (non-blocking), tác giả Nguyen Anh Tuan
