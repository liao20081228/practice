class test:
    count=0
    sex=1
print(dir(test))    
delattr(test,"count")
print(dir(test))
