CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = UserApp
SRC = main.cpp UserManager.cpp WalletManager.cpp OtpManager.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
