# 🛠 Hướng dẫn sử dụng

Ứng dụng này cho phép bạn tạo dữ liệu số ngẫu nhiên, lưu trữ dưới dạng file nhị phân và quan sát trực quan quá trình sắp xếp của các thuật toán nổi tiếng.

1. Chuẩn bị dữ liệu (Bắt đầu từ đâu?)
   
   Trước khi chọn thuật toán để xem, bạn cần có dữ liệu đầu vào. Bạn có hai lựa chọn tại menu chính:
   - Lựa chọn 130 (Tạo file ngẫu nhiên):
       - Nhập tên file (ví dụ: `test`).
       - Nhập giá trị nhỏ nhất (Min) và lớn nhất (Max) của dãy số.
       - Nhập số lượng phần tử (Amount).
       - Lưu ý: Ứng dụng sẽ tự động lưu dưới dạng `.dat`.
   - Lựa chọn 120 (Chọn file có sẵn):
       - Ứng dụng sẽ liệt kê các file `.dat` hoặc `.bin` trong thư mục hiện hành.
       - Bạn chỉ cần nhập số thứ tự của file để tải dữ liệu vào bộ nhớ.

2. Các thuật toán sắp xếp được hỗ trợ
   
   - Sau khi đã có dữ liệu (hiển thị thông báo "Successfully read/created"), bạn có thể chọn các phím từ 1 đến 7 để bắt đầu xem mô phỏng:
     ```
     Phím   |  Thuật toán     | Đặc điểm mô phỏng
     -------|-----------------|--------------------------------------------------------
     1      |  Bubble Sort    | Chạy từng cặp, đưa số lớn nhất về cuối.
     -------|-----------------|--------------------------------------------------------
     2      |  Selection Sort | Tìm số nhỏ nhất và đưa về đầu.
     -------|-----------------|--------------------------------------------------------
     3      |  Insertion Sort | Chèn dần các số vào vị trí đúng trong mảng đã xếp.
     -------|-----------------|--------------------------------------------------------
     4      |  Merge Sort     | Chia để trị, gộp các mảng con lại với nhau.
     -------|-----------------|--------------------------------------------------------
     5      |  Quick Sort     | Phân đoạn mảng dựa trên phần tử chốt (Pivot).
     -------|-----------------|--------------------------------------------------------
     6      |  Heap Sort      | Xây dựng cấu trúc cây (Heap) để lấy số lớn nhất.
     -------|-----------------|--------------------------------------------------------
     7      |  Bogo Sort      | "Sắp xếp dựa trên nhân phẩm" (xáo trộn ngẫu nhiên).
            |                 | Cảnh báo: Đừng thử với mảng > 7 phần tử trừ khi bạn có quá nhiều thời gian!
    ```
3. Cách đọc biểu đồ
   
   Khi ứng dụng đang chạy mô phỏng, bạn sẽ thấy các thanh biểu đồ dấu # với các màu sắc khác nhau:
   - Xanh lá: Phần tử đã nằm đúng vị trí (đã xong).
   - Đỏ: Các phần tử đang được so sánh với nhau.
   - Vàng: Phần tử đặc biệt (như Pivot trong Quick Sort hoặc Min trong Selection Sort).
   - Xanh dương: Các phần tử còn lại trong mảng.

4. Tùy chỉnh và Lưu kết quả
   
   - Thay đổi tốc độ (Phím 100): Bạn có thể nhập khoảng thời gian trễ (miliseconds). Số càng nhỏ, mô phỏng chạy càng nhanh.
   - Lưu kết quả (Phím 110): Sau khi sắp xếp xong, bạn có thể lưu mảng đã sắp xếp vào một file .dat mới để sử dụng sau này.

⚠️ Lưu ý quan trọng
- Số lượng phần tử: Tốt nhất nên để dưới 30 phần tử. Nếu nhiều hơn, biểu đồ sẽ bị tràn màn hình và khó quan sát.
- Thao tác chuột: KHÔNG nên cuộn chuột (scroll) hoặc thay đổi kích thước cửa sổ Console khi ứng dụng đang vẽ biểu đồ, vì nó sử dụng mã điều khiển con trỏ `(\033[H)`, việc cuộn sẽ làm hình ảnh bị chồng chéo.
- Hệ điều hành: Đoạn mã được tối ưu hóa tốt nhất cho Windows (có sử dụng `system("cls")` và `localtime_s`).
