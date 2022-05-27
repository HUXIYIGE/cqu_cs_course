import urllib  
# 如要更新代码，可以运行这个爬虫
#https://ita.skanev.com/
# 也是很好的参考网页，不过只有1-11章
  
for i in range(1, 36):  
    url = r"http://sites.math.rutgers.edu/~ajl213/CLRS/Ch" + str(i) + ".pdf"  
    path = r"./"+str(i)+".pdf"  
    data = urllib.urlopen(url).read()  
    f = file(path,"wb")  
    f.write(data)  
    f.close()  
    print "finish download " + url + "!"  