CXXFLAGS =	-O2 -g -std=c++11 -Wall -fmessage-length=0

OBJS =		main.o

LIBS =

TARGET =	a

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)