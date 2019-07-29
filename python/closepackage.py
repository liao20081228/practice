class pepole(object):
    count=0

class boy:
    age=0

class girl(boy,pepole):
    pass

print(hasattr(pepole,"__name__"))
