class Test:
    def __init__(self):
        self._a =1
        self.__b=2
        self.__c__=3
    def ret(self):
        return  self.__b
    def __ret(self):
        return self.__b
    def _ret(self):
        return self.__b
    
a=1
_a=1
__a=1
