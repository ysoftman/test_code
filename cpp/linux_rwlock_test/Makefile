# Makefile
CXX = gcc 
OUTPUT = rwlock_test
INCLUDES = -I./ -I../
CFLAGS = -pg -O3 -fPIC -Wall -lpthread
SRCS = linux_rwlock_test.cpp \
# 	aaa.cpp 


all:
	clear
	$(CXX) $(SRCS) $(CFLAGS) -o $(OUTPUT)

clean:
	rm -rfv $(OUTPUT)

