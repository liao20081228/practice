import re

ret=re.compile("I Love")
re_ret=ret.search("I Love you, I Love you")
print(re_ret)
re_ret=ret.match("I Love you, I Love you")
print(re_ret)
