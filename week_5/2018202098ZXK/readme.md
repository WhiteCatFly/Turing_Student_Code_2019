# BigInt
## INTRO

A naive BigInt class
author: ZXK  

模板类的声明实现应该在同一个头文件，所以只有一个头文件  

Feature
+  use Template
+  can work with built-in type
+  add divide

## Usage
```
make
./prog
```



## BigInt Interface  
+ BigNum<typename T, T, unsigned>  
利用模板构造，T是需要采用的“承载”的base,  第二个T为进制（整10）， 第三个是该进制的长度  
default: long long , 10000000, 7  
例如BigNum<int, 1000, 3>  myNum(19260817)  
为了避免减法过程中产生溢出的bug, 推荐采用有符号的数字作base
+ BigNum(string num)  
BigNum<> myNum("20190504")
+ BigNum(T x)  
BigNum<> myNum(100000007)

+ BigNum abs()  
abs(Num)
+ unsigned length()  
return length of num  
100 -> 2; -119 -> 3;

+ opeartor T()  
explicit type_cast:   
 int him = (int) BigNum(19260817);  
long long him = (long long) BigNum(10260817)

+ ...  
加减乘除，比较大小



### To Do 
+  add FFT


### 设计思路
感谢查寒天，让我知道乘法采用FFT 的思路  
感谢杨铭基，给我用模板做类型转化的思路
