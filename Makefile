CC := g++
CFLAGS := -g -Wall -std=c++17
BUILD_DIR := build

#TARGET Executables
TARGETS := client serverM serverEE serverCE
TARGETS_BUILD := $(addprefix $(BUILD_DIR)/,$(TARGETS))

# Default Target
all: $(TARGETS_BUILD)

# Compile client
$(BUILD_DIR)/client: src/client.cpp
	$(CC) $(CFLAGS) src/client.cpp -o $(BUILD_DIR)/client

# Compile Main Server
$(BUILD_DIR)/serverM: src/serverM.cpp src/helperFuncs.h
	$(CC) $(CFLAGS) src/serverM.cpp -o $(BUILD_DIR)/serverM

# Compile EE Backend
$(BUILD_DIR)/serverEE: src/serverEE.cpp src/helperFuncs.h
	$(CC) $(CFLAGS) src/serverEE.cpp -o $(BUILD_DIR)/serverEE

# Compile CE Backend
$(BUILD_DIR)/serverCE: src/serverCE.cpp src/helperFuncs.h
	$(CC) $(CFLAGS) src/serverCE.cpp -o $(BUILD_DIR)/serverCE

# Clean generated
clean: 
	rm -f $(TARGETS_BUILD)
