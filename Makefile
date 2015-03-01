CXX=g++
CXXFLAGS=-W -Wall
LDFLAGS=-lpcap
EXEC=arppoisonning

all: $(EXEC)

arppoisonning: Arp.o ArpSpoofing.o Ethernet.o NetworkUtilities.o Packet.o
	$(CXX) -o arppoisonning Arp.o ArpSpoofing.o Ethernet.o NetworkUtilities.o Packet.o main.cpp $(LDFLAGS)

Arp.o: Arp.cpp
	$(CXX) -o Arp.o -c Arp.cpp $(CXXFLAGS) $(LDFLAGS)

ArpSpoofing.o: ArpSpoofing.cpp
	$(CXX) -o ArpSpoofing.o -c ArpSpoofing.cpp $(CXXFLAGS) $(LDFLAGS)

Ethernet.o: Ethernet.cpp
	$(CXX) -o Ethernet.o -c Ethernet.cpp $(CXXFLAGS) $(LDFLAGS)

NetworkUtilities.o: NetworkUtilities.cpp
	$(CXX) -o NetworkUtilities.o -c NetworkUtilities.cpp $(CXXFLAGS) $(LDFLAGS)

Packet.o: Packet.cpp
	$(CXX) -o Packet.o -c Packet.cpp $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
