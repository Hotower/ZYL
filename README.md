# ZYL
ZYong,a simple programming language
# Introduction(English Edition)
	Hello,this is Hotower,I'm going to introduce you a interesting programme:ZYong.
	The code of ZYong should be written in "code.zyl" and run "ZYL_Interpreter.exe" to compile it.
	This is a simple programming language but (in my opinion) not a simple work.
	here are the functions supported in the language:

## A.out()

the function "out" can be used to output sth in `result.txt`,you can check the answer in the txt after compiling.

	out("string")

The code above is going to output "string" (exclude quotation marks) in `result.txt`.

	out(a)

The code above is going to output the value of variable "a" in `result.txt`.

## B.def()

the function "def" can be used to define a new variable.

	def(a)

The code above is going to define a variable "a" whose value will be "0".

	def(a,123)

The code above is going to define a variable "a" whose value will be "123".

## C.in()

the function "in" can be used to input sth from `input.txt`,you should type the data in the txt before the programme is compiled.

	in(a,b,...)

The code above is going to read the value of variable "a","b",etc from `input.txt`.

## D.when()

the function "when" can be used to judge if the Boolean expression in the brackets.If it is true,the following codes will be done and stop at "end".

	when(1)
	    out(1)
	end

The code above is going to output "1"(exclude quotation marks) if 1 is true

## E.when()repeat

the function "when<>repeat" can be used to repeat to do the following codes stop at "end" until the Boolean expression in the brackets is false.

	def(i,1)
	when(i<=10)repeat
	    out(i,"@e")
	    i=i+1
	end

The code above is going to output the value of i and increase i by 1 until i<=10 is false.

<br> <br>  <hr>  <br>
# 简介（简体中文版）
	大家好，我是热力天蝎。我将在此介绍一个有趣的程序：中庸。
	中庸的代码需要写在"code.zyl"中，然后运行"ZYL_Interpreter.exe"来编译。
	这是一门简单的编程语言，但写起来（在我看来）并不简单。
	接下来我将介绍已有的函数：
## 一、out()

out函数可以在`result.txt`当中输出一些东西，你可以编译后在这个文档中找到你输出的结果。

	out("string")

上述代码可以在`result.txt`当中输出“string”（不包括引号）。

	out(a)

上述代码可以在`result.txt`当中输出变量a的值。

## 二、def()

def函数可以用来定义变量。

	def(a)

上述代码可以用来定义一个值为“0”的变量a。

	def(a,123)

上述代码可以用来定义一个值为“123”的变量a。

## 三、in()

in函数可以用来在`input.txt`中读入一个或多个变量的值。

	in(a,b,...)

上述代码可以在`input.txt`中读入变量a，b等等的值。

## 四、when()

when函数在判断括号内内容为真之后将执行后来的命令。一个when函数会停止在"end"处。

	when(1)
	    out(1)
	end

上述代码可以在1为真时输出“1”（不包括引号）

## 五、when()repeat

when<>repeat函数在判断括号内内容为真之后将重复执行后来的命令。一个when<>repeat函数会停止在"end"处。

	def(i,1)
	when(i<=10)repeat
	    out(i,"@e")
	    i=i+1
	end
上述代码可以在i<=10时输出i的值并将i增加1
