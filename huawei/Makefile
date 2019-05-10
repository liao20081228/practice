#DIR自定义变量
DIR:=./debug
#EXE自定义变量
EXE:=$(DIR)/main.exe
#LIBS自定义变量
LIBS:=
CXX=gcc
#把当前目录下搜索的的.cpp文件中的.cpp文件替换为同名的.o文件
OCPP:=$(patsubst %.cpp,$(DIR)/%.o,$(wildcard *.cpp))
#把当前目录下搜索的的.c文件中的.c文件替换为同名的.co文件
OC:=$(patsubst %.c,$(DIR)/%.co,$(wildcard *.c))
#把当前目录下搜索的的.cc文件中的.cc文件替换为同名的.cco文件
OCC:=$(patsubst %.cc,$(DIR)/%.cco,$(wildcard *.cc))
OBJS:=
ifneq ($(OC),)
OBJS+=$(OC)
endif
ifneq ($(OCC),)
OBJS+=$(OCC)
endif
ifneq ($(OCPP),)
OBJS+=$(OCPP)
endif
#RM预定义变量
RM:=rm -rf
#CXXFLAGS预定义便令， c++编译器选项
CXXFLAGS:=-Wall -g -std=c99
start:mkdebug $(EXE)  
mkdebug:
#使用shell脚本或命令要加@
	@if [ ! -d $(DIR) ];then mkdir $(DIR); fi
$(EXE):$(OBJS)
	$(CXX) $(OBJS) -o $@ $(addprefix -l,$(LIBS))
$(DIR)/%.o:%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
$(DIR)/%.co:%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS)
$(DIR)/%.cco:%.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)
.PHONY:clean rebuild
clean:
	@$(RM) $(EXE) $(OBJS) 
	@$(RM) $(DIR)
rebuild: clean start
