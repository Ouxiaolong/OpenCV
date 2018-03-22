CXX = g++ #编译工具
INCLUDE = $(shell pkg-config --cflags opencv) #头文件
LIBS = $(shell pkg-config --libs opencv)#库文件
SOURCES = *.cpp #资源文件
OBJECTS = $(SOURCES:.cpp=.o)#目标文件 
TARGET = app #可执行文件 

$(TARGET):$(OBJECTS)  
	$(CXX) -o $(TARGET) $(OBJECTS) -I $(INCLUDE) $(LIBS)  
$(OBJECTS):$(SOURCES)  
	$(CXX) -c $(SOURCES)  
 
# 编译规则 $@代表目标文件 $< 代表第一个依赖文件  
%.o:%.cpp  
	$(CXX) -I $(INCLUDE) -o $@ -c $<  
#清除编译过程中产生的文件
clean:  
	$(RM) $(OBJECTS) $(TARGET) 