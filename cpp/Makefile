# make 없이 빌드
# g++ make_sample1.cpp make_sample2.cpp make_sample3.cpp && ./a.out
# 또는 컴파일, 링크 따로 빌드
# g++ -c make_sample1.cpp make_sample2.cpp make_sample3.cpp
# g++  make_sample1.o make_sample2.o make_sample3.o -o make_sample_exe


# Makefile 테스트
# 메뉴얼 : https://www.gnu.org/software/make/manual/make.html
# 변수 설정, 실제 사용전에 위치해야 한다.
# 사용시 ${변수} 또는 $(변수) 로 사용한다.
var1=123
# ?= 는 이전에 변수가 선언되어 사용했다면 할당하지 않는다.
# var1 은 이미 선언되어 ?= 연산으로는 100 할당할 수 없다.
var1 ?= 100
# += 값 추가 할당되어 111 222 가 된다.
# 추가된 값은 공백으로 구분된다.
var2 += 111
var2 += 222
# 변수에 열러값을 할당(확장)시 갑이 변수인 경우 참조하는데
# 이때 참조하게 자기 자신이면 recursive 하게 값을 참조하게 된다.
# = 를 사용하면 var3 할당시 자기 자신을 참조해 에러 발생한다.
# var3 = ${var3} 456
# 이런 경우 := 를 사용하면 recursive 하지 않과 심플한게 한번만 참조(확장)해 값을 설정할 수 있다.
var3 := ${var3}333


CXX = g++
OUTPUT = make_sample_exe
INCLUDES = -I./ -I../
CFLAGS = -pg -O3 -fPIC -Wall
SRCS = make_sample1.cpp \
	make_sample2.cpp \
	make_sample3.cpp
# SRC 들의 .cpp 를 .o 로 바꾸어 OBJS 변수로 설정
OBJS = $(SRCS:.cpp=.o)

# make 기본 형식
# 타겟파일을 만들기 위해선 의존성파일들이 필요하고
# 의존성파일이 준비되었으면 커맨드를 실행해서 타겟파일을 생성한다.
# target : dependency1 dependency2 ... n
# 	command
#	command 영역에 들여쓰기(tab)가 있으면 주석도 출력된다.
# command 영역에 들여쓰기(tab)가 없으면 주석처리 된다.(출력되지 않는다.)

# all. clean, build... 등 타겟은 실제 파일이 아닌데,
# 실제 all, clean, build 파일이 있다면 make 타겟 파일이 존재해서 충돌된다.
# 이를 방지하고자 .PHONY(가짜) 로 설정하면 타겟 파일 존재여부 없이 실행한다.
.PHONY: all
# make 기본 타겟은 all 이다.
# all 은 여러 타겟을 한번에 생성하기 위해 사용한다.
# clean 실행 -> $(OUTPUT) 실행
# all 을 만들기 위한 recipes 영역
all: clean $(OUTPUT)

# 방법1 - 모든 rule 을 일일히 명시한다.
# $< 현재 타겟보다 최근에 변경된 의존성 파일(첫번째 의존성 파일)을 나타내는 내장변수다.
# make_sample1.o: make_sample1.cpp
# 	g++ -c $<

# make_sample2.o: make_sample2.cpp
# 	g++ -c make_sample2.cpp

# make_sample3.o: make_sample3.cpp
# 	g++ -c make_sample3.cpp

# make_sample_exe: make_sample1.o make_sample2.o make_sample3.o
# 	g++ make_sample1.o make_sample2.o make_sample3.o -o make_sample_exe

# 방법2 - 변수를 이용해서 간략하게 하다.
# @ suppress shell command output, 명령어 화면 출력을 하지 않는다.
# $@ 는 타겟을 나타내는 내장변수다. -o $(OUTPUT) 와 같다.
# origin 은 변수가 어디서 왔는지 알려준다.
# file : makefile 에서 정의
# undefined : 정의 되지 않음
	# recipes 영역에선 탭 들여쓰기 하면 무조건 /bin/sh 로 처리된다.


$(OUTPUT):
	# output recipes
	# 탭 들여쓰기로 /bin/sh 실행
	@echo "origin var0=$(origin var0)"
	@echo "origin var1=$(origin var1)"
	@echo "var1=${var1}"
	@echo "var2=${var2}"
	@echo "var3=${var3}"


# loop 사용지 /bin/sh 전달시 $i 로 전달하려면 $$i 로 명시해야 한다.
	@for i in ${var2}; do \
		echo "for test - $$i"; \
	done

# 조건 처리 방법1
# /bin/sh 스크립트 사용시
	@if [ ${shell whoami} = "ysoftman" ]; then \
		echo "whoami cond1 - ${shell whoami}"; \
	else \
		echo "whoami cond2 - ${shell whoami}"; \
	fi

# 조건 처리 방법2
# make 자체 문법 사용
# ifeq 는 make 문법으로 /bin/sh 로 처리하면 안되기 때문에 탭 들여쓰기 하지 않는다.
ifeq ($(shell uname),Linux)
	@echo cond1 - Linux
else
	@echo cond2 - $(shell uname)
endif

	@echo "SRCS=$(SRCS)"
	@echo "OBJS=$(OBJS)"
	$(CXX) $(CFLAGS) -c $(SRCS)
	$(CXX) $(OBJS) -o $@

# clean 을 지울때 사용
.PHONY: clean
clean:
	rm -rfv $(OBJS) $(OUTPUT)
