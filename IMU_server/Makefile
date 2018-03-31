CC = gcc
CFLAGS = -g -Wall -std=c99 
OBJS = example.o KalmanIMU.o udp_server.o
TARGET = udp_server
#INCLUDES = ...
LIBS = -lm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	rm -f *.o
	
clean:
	rm -f $(TARGET) $(OBJS) *~ *.o
