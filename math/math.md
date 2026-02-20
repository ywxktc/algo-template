# 数学

比赛常用数学理论

## 数论

**GCD**

$$
\begin{align}
\gcd(x, y) = 
\begin{cases}
\gcd(x-y,y) & \operatorname{if} y \neq 0 \\
x & \operatorname{if} y = 0
\end{cases}
\end{align}
$$

**模运算**

$$
\begin{align}
(a+b) \bmod p &= (a \bmod p) + (b \bmod p) \\
(a \cdot b) \bmod p &= (a \bmod p) \cdot (b \bmod p)
\end{align}
$$


**同余简单结论**

$$
\begin{align}
& \space a \equiv b \pmod{p} \\ 
\Rightarrow & \space p \bigm| \left| a-b \right|
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


## 几何

**线性代数**

$$
\begin{align}

\end{align}
$$

**向量**

$$
\begin{align}

\vec{OA} &= (x_a, y_a) \\
\vec{OB} &= (x_b, y_b) \\
\vec{OC} &= (x_c, y_c) \\

\\

\vec{AB} & = \vec{AC} + \vec{CB}  \\
\vec{AB} &= - \vec{BA} \\
\vec{AB} &= \vec{OB} - \vec{OA} = (x_b-x_a,y_b-y_a) \\

\\

|\vec{AB}| &= \sqrt{(x_b-x_a)^2 + (y_b-y_a)^2} \\
\vec{OA} \cdot \vec{OB} &= x_a \, x_b + y_a \, y_b \\
\vec{OA} \times \vec{OB} &= x_a \, y_b - x_b \, y_a \\

\end{align}
$$

**三角**

$$
\begin{align}

\end{align}
$$