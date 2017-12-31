CC = g++  
# 可执行文件  
TARGET = app  
# C文件  
SRCS = *.cpp  
# 目标文件  
OBJS = $(SRCS:.cpp=.o)  
# 库文件  
DLIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui  
# 链接为可执行文件  
$(TARGET):$(OBJS)  
	$(CC) -o $@ $^ $(DLIBS)  
clean:  
	rm -rf $(TARGET) $(OBJS)  
# 编译规则 $@代表目标文件 $< 代表第一个依赖文件  
%.o:%.cpp  
	$(CC) -o $@ -c $<  
