a='for i in range(0,10):print(i)'
b=compile(a,"",'exec')
print(b)
exec(b)
