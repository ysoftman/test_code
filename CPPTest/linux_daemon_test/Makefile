# CPPTest Makefile
CXX = gcc 
OUTPUT = daemon_test
INCLUDES = -I./ -I../
CFLAGS = -pg -O3 -fPIC -Wall -lpthread
SRCS = linux_daemon_test.cpp \
#	CPPTestSupport.cpp \
# 	aaa.cpp 


all:
	clear
	$(CXX) $(SRCS) $(CFLAGS) -o $(OUTPUT)

clean:
	rm -rfv $(OUTPUT)

