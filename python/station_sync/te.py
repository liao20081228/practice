import re

ret=re.compile("a+(b+)")
re_ret=ret.search("I Love you, aaaa aaabb")
print(re_ret.group())
print(re_ret.group(1))
print(re_ret.group(2))
