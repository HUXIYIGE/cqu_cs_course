# 编译原理实验一BUG记录

## BUG1

### 错误原因

在语句推导的时候，在测试平台上语句列有可能是全空，也有可能是有内容（文法定义不是全空，至少有一个分号）在代码中需要分情况讨论

### 解决方法

只需要在代码中分类即可

```c++
else if(curtok=="LBRACE"){
    if(seek(1)=="RBRACE"){
        fout << "<语句列>" << endl;
        nexttoken();
    }
    else{
        nexttoken();
        statement_column();
        nexttoken();
    }
}
```

## BUG2

## 错误原因

在函数声明头部的时候，错把token类别码记录了，没有记录单词值，因此在有函数调用语句的时候就会出错

### 解决方法

把值换成val[curindex-1]

```c++
has_retval.insert(pair<string,bool>(val[curindex-1],true));
```

## BUG3

## 错误原因

有一些函数调用时忘记添加对应的语法分析输出，导致平台无法通过

### 解决方法

添加对应的语法分析输出语句即可，例如

```c++
fout << "<声明头部>" << endl;
```

## BUG4

## 错误原因

最开始在变量定义的时候未考虑二维数组，测试平台上无法识别

### 解决方法

在变量定义函数中增加对应的识别逻辑，如果是二维数组的话，后面的第七个token一定是]，第八个是=

```c++
if(seek(2)=="ASSIGN"||(seek(4)=="RBRACK"&&seek(5)=="ASSIGN")||(seek(4)=="RBRACK"&&seek(7)=="RBRACK"&&seek(8)=="ASSIGN")){
```

## BUG5

## 错误原因

最开始的时候直接定义各个函数，因为存在互相调用的关系，编译器会报错，没有声明函数

### 解决方法

后面将语法分析整个定义为类，然后把递归调用的函数都写为类内函数，如下

```c++
class yufafenxi{
private:
	string curtok="";
	string unregonized="";
	int toknum=0;
	int curindex=0;
	unordered_map<string, bool> has_retval;
	ofstream fout;
public:
	void nexttoken(){}
    void unsigned_integer(){}

```

## 