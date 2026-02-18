# Tên trình biên dịch
CXX = g++

# Các tùy chọn biên dịch: chuẩn C++17 và bật cảnh báo lỗi 
CXXFLAGS = -std=c++17 -Wall -I.

# Tên file thực thi đầu ra [cite: 269]
TARGET = main

# Danh sách các file nguồn cần thiết [cite: 265, 266]
SRCS = main.cpp Playlist.cpp

# Chuyển đổi danh sách file .cpp thành file đối tượng .o
OBJS = $(SRCS:.cpp=.o)

# Quy tắc mặc định: xây dựng chương trình
all: $(TARGET)

# Quy tắc liên kết các file đối tượng để tạo file thực thi [cite: 269]
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Quy tắc biên dịch file .cpp thành .o
# Các file này phụ thuộc vào Playlist.h và BotkifyLinkedList.h [cite: 5, 289]
%.o: %.cpp Playlist.h BotkifyLinkedList.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Lệnh dọn dẹp các file rác sau khi biên dịch [cite: 294]
clean:
	rm -f $(OBJS) $(TARGET)

# Lệnh chạy chương trình nhanh
run: all
	./$(TARGET)

.PHONY: all clean run