CC := g++
CFLAGS := -std=c++11 -Wall

#TARGET Executables
TARGETS := client serverM serverEE serverCE

# Default Target
all: $(TARGETS)

# Compile client
client: client.cpp
	$(CC) $(CFLAGS) client.cpp -o client

# Compile Main Server
serverM: serverM.cpp
	$(CC) $(CFLAGS) serverM.cpp -o serverM

# Compile EE Backend
serverEE: serverEE.cpp
	$(CC) $(CFLAGS) serverEE.cpp -o serverEE

# Compile CE Backend
serverCE: serverCE.cpp
	$(CC) $(CFLAGS) serverCE.cpp -o serverCE

# Clean generated
clean: 
	rm -f $(TARGETS)
