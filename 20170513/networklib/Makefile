DIR:=./debug            #//DIR自定义变量
EXE:=$(DIR)/main.exe    #//EXE自定义变量
CXX:=g++                 #//CXX预定义便令
LIBS:=                   #//LIBS自定义变量
OCC:=$(patsubst %.cc,$(DIR)/%.o, $(wildcard *.cc))  #//把当前目录下搜索的的.cc文件中的.cc文件替换为同名的.cco文件
OBJS:=$(OCC) # // OBJS自定义变量，依赖对象
RM:=rm           #//RM预定义变量
CXXFLAGS:=-Wall -g -std=c++11   #// CXXFLAGS预定义便令， c++编译器选项
start:mkdebug $(EXE)  
mkdebug:
	@if [ ! -d $(DIR) ]; then mkdir $(DIR); fi
$(EXE):$(OBJS)
	$(CXX)  $(OBJS) -o $@  $(addprefix -l,$(LIBS))
$(DIR)/%.o:%.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
.PHONY:clean rebuild
clean:
	@$(RM) $(DIR)/*.exe $(DIR)/*.o 
rebuild:clean start
