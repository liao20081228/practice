class person:
    "这是一个基类" #文档字符串
    count=0 #类属性，所有类对象和实例对象共享，可被类对象和实例对象访问，但会被同名实例对象覆盖
    __count=0 #私有类属性，类外不可访问，不可继承
    def __init__(self,name,age):
        self.name=name
        self.__age=age
        count+=1
        __count+=1
    #普通方法，可被类对象和实例对象调用，但使用实例对象调用时会转为实例方法，此时至少要有一个参数
    def nomal_method():
        print("nomal method,person.count：",person.count)

    #静态方法，可被类对象和实例对象调用，不可访问实例属性和方法
    @staticmethod
    def static_method():
        print("static method,person.count：",person.count)

    #类方法，可被类对象和实例对象调用，不可访问实例属性和方法
    @classmethod
    def class_method(cls):
        print("class method,cls.count：",cls.count,"person.count：",person.count)

    #实例方法，只可被实例对象调用，类对象调用需要传入实例对象。可以访问类和实例的属性和方法
    def instance_method(self):
        print("instance method,self.count：",self.count,"person.count：",
        person.count,"self.name:",self.name,"self.__age:",self.__age)

    #私有方法，不可访问，不可继承
    def __private_method(self):
        print("private method,self.count：",self.count,"person.count：",person.count,
        "self.name:",self.name,"self.__age:",self.__age)	
