CC := g++
CFLAGS := -g -Wall -std=c++17
BUILD_DIR := build

#TARGET Executables
TARGETS := client serverM serverEE serverCE
TARGETS_BUILD := $(TARGETS)

# Default Target
all: $(TARGETS_BUILD)

# Compile client
client: client.cpp
	$(CC) $(CFLAGS) client.cpp -o client

# Compile Main Server
serverM: serverM.cpp helperFuncs.h
	$(CC) $(CFLAGS) serverM.cpp -o serverM

# Compile EE Backend
serverEE: serverEE.cpp helperFuncs.h
	$(CC) $(CFLAGS) serverEE.cpp -o serverEE

# Compile CE Backend
serverCE: serverCE.cpp helperFuncs.h
	$(CC) $(CFLAGS) serverCE.cpp -o serverCE

# Clean generated
clean: 
	rm -f $(TARGETS_BUILD)
