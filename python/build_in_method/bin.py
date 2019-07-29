class test:
    def __init__(self,x):
        self.x=x
    def __int__(self):
        return self.x

a=test(10)
print(bin(a))
