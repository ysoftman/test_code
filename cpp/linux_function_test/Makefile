# Makefile
CXX = gcc 
OUTPUT = function_test
INCLUDES = -I./ -I../
CFLAGS = -pg -O3 -fPIC -Wall -lpthread
SRCS = linux_function_test.cpp \
# 	aaa.cpp 


all:
	clear
	$(CXX) $(SRCS) $(CFLAGS) -o $(OUTPUT)

clean:
	rm -rfv $(OUTPUT)

