# 数学

比赛常用数学理论

## 数论

**模运算**

$$
\begin{align}
(a+b) \bmod p &= (a \bmod p) + (b \bmod p) \\
(a \cdot b) \bmod p &= (a \bmod p) \cdot (b \bmod p)
\end{align}
$$




## 组合数

**组合数定义**

$$
\begin{align}
\binom{n}{m} = \frac{n!}{m! (n - m)!} = \frac{(n-m+1)(n-m+2)\cdots n}{m!} 
\end{align}
$$

**组合数DP**

$$
\begin{align}
\binom{n}{m} &= \binom{n-1}{m-1} + \binom{n-1}{m}
\end{align}
$$

**组合数&阶乘**

$$
\begin{align}
\binom{(c_1+c_2+\cdots+c_n)!}{c_1c_2\cdots c_n} &= \binom{c_1}{c_1} \binom{c_1 + c_2}{c_2} \cdots \binom{c_1 + c_2 + \cdots + c_n}{c_n}
\end{align}
$$
