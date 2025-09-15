
CXX=g++
CXXFLAGS=-std=gnu++17 -O2 -I$(CORE_DIR)

CORE_DIR?=.
CORE_SRC=$(CORE_DIR)/AccountManager.cpp $(CORE_DIR)/User.cpp $(CORE_DIR)/Wallet.cpp
MY_SRC=main.cpp AppCLI.cpp Otp.cpp BackupUtil.cpp

all: app

app: $(MY_SRC) $(CORE_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(MY_SRC) $(CORE_SRC)

clean:
	rm -f app
