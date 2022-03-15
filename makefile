CXX=g++
CC=gcc
DEBUG=-g
COMMON=-D_UNICODE
CXXFLAG=-std=c++17 $(DEBUG)
CFLAG=-std=c99 -Wpointer-to-int-cast $(DEBUG)
HASGTEST=-DGTEST_INCLUDE_GTEST_GTEST_H_
GTEST=-DGTEST_INCLUDE_GTEST_GTEST_H_ -lgtest -lgtest_main
BC=-lbenchmark

all:s2i_demo s2i_demo_gtest s2i_demo_benchmark

# 自动根据需要的文件类型编译
%.o:%.c
	$(CC) $(CFLAG) $(HASGTEST) $(COMMON) $< -c

# $^	代表的是所有依赖文件列表，使用空格分隔。如果目标是静态库文件，它所代表的只能是所有的库成员（.o 文件）名
s2i_demo:s2i_demo.c
	$(CC) $(COMMON) $< -o $@

# 如果把$(GTEST)放到前面会出现链接错误, 原因暂时未知
%_gtest:%.o %_gtest.cc
	$(CXX) $(CXXFLAG) $(COMMON) $^ -o $@ $(GTEST)

s2i_demo_benchmark:s2i_demo.o s2i_demo_benchmark.cc
	$(CXX) $(CXXFLAG) $(COMMON) $^ -o $@ $(BC)

clean:
	rm *.exe *.o
