# Điều khiển LED bằng nút nhấn – ESP32-S3 + OneButton

Dự án PlatformIO gồm các ví dụ điều khiển LED bằng nút nhấn, dùng thư viện [OneButton](https://github.com/mathertel/OneButton) và thư viện `LED` (thư mục `lib/LED`). Mỗi ví dụ là một **môi trường (env)** riêng trong `platformio.ini`, nên chỉ cần chọn env là chạy được, không phải sửa code.

## Phần cứng

- Board: **ESP32-S3 DevKitC-1 N16R8** (16 MB flash, 8 MB PSRAM)
- 2 LED, 2 điện trở 1k Ω
- 1 nút nhấn
- Test board, dây cắm

## Cấu trúc dự án

```
iot_tuan2/
├── lib/LED/LED.h        # Lớp LED: on(), off(), flip(), blink(ms), loop()
├── src/
│   ├── blink.cpp        # LED nhấp nháy
│   ├── doublePush.cpp   # 1 nút điều khiển 1 LED
│   └── twoLeds.cpp      # 1 nút điều khiển 2 LED
└── platformio.ini       # Mỗi ví dụ = 1 env
```

Mỗi env dùng `build_src_filter` để chỉ biên dịch đúng file của nó, và dùng `build_flags` để khai báo chân GPIO:

| Env | File | Chân sử dụng |
|---|---|---|
| `blink` | `blink.cpp` | LED: GPIO4 |
| `double_push` | `doublePush.cpp` | LED: GPIO4, nút: GPIO0 (nút BOOT trên board) |
| `two_leds` | `twoLeds.cpp` | LED1: GPIO4, LED2: GPIO6, nút: GPIO5 |

## Chức năng

## `blink`
LED nhấp nháy với chu kỳ 500 ms.

## `double_push`
- **Single click:** bật/tắt LED
- **Double click:** LED nhấp nháy 200 ms

## `two_leds`
Một nút nhấn điều khiển hai LED:

| Thao tác | Chức năng |
|---|---|
| **Double click** | Chuyển LED đang được điều khiển (LED1 ⇄ LED2). LED được chọn sẽ sáng, LED còn lại tắt |
| **Single click** | Bật/tắt LED đang được điều khiển |
| **Giữ nút** | LED đang được điều khiển nhấp nháy 200 ms một lần |

Khi khởi động, chương trình chọn LED1 và LED1 sáng. Đang nhấp nháy mà single click thì LED dừng nhấp nháy và tắt.

## Cách chạy

1. Ở thanh trạng thái phía dưới, bấm vào ô chọn môi trường (mặc định hiện `Default (iot_tuan2)`), rồi chọn env cần chạy, ví dụ `env:two_leds`.
2. Bấm **Upload** (→).

> Nếu để `Default`, PlatformIO sẽ build và nạp **lần lượt tất cả env**, và board sẽ chạy env nạp cuối cùng. Vì vậy cần chọn đúng env trước khi nạp.

Có thể dùng dòng lệnh:
```bash
pio run -e two_leds -t upload
```

Tham khảo: 
- https://docs.platformio.org/en/latest/projectconf/sections/env/options/build/build_src_filter.html
- https://docs.platformio.org/en/latest/projectconf/sections/env/index.html

## Thư viện sử dụng

- [mathertel/OneButton](https://github.com/mathertel/OneButton) `^2.6.1`: nhận diện click, double click, giữ nút
- `lib/LED/LED.h`: lớp điều khiển LED không chặn (non-blocking), tác giả Nguyen Anh Tuan
