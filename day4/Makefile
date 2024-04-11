SRC=${wildcard ./*.cpp}#wildcard查找指定目录下指定类型的文件
OBJS=${patsubst %.cpp,%.o,${SRC}}#patsubst把SRC变量中所有后缀为.cpp的文件名替换为.o
.PHONY:clean#避免当前目录下存在与命令同名文件

#$@生成目标 $^所有依赖 $<第一个依赖
main:${OBJS}
	@g++ $^ -o $@

#%.o:%.c表示所有的.o依赖于对应名字的.c
%.o:%.cpp
	-g++ -c $< -o $@

clean:
	@rm -f ${OBJS} main
