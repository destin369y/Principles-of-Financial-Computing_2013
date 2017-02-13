Principles of Financial Computing HW#5
R01944040 柳成蔭

This is a Monte Carlo Simulation program to price a 3-asset single-barrier European knock-out put.

The C++ code is compiled in VS2012。
使用了原始的Monte Carlo方法和Brownian Bridge改進的方法。
輸入是 S1, S2, S3, X, H (barrier on S1), t (year), v1 (volatility of 1st asset in %), v2 (volatility of 2nd asset in %), v3 (volatility of 3rd asset in %), rho (the correlations between any two assets in %), r (interest rate in %), n (number of paths), and m (number of time points including today, not needed if the Brownian bridge method is used)。And the terminal payoff is max(X - (S1 + S2 + S3)/3, 0).
按提示順序輸入數據來獲得結果，其中最後可以選擇輸入1看使用Brownian Bridge的結果，或輸入0不使用Brownian Bridge。

對於Variance Reduction。
Monte Carlo方法用多條path重複計算來實現收斂，次數越多平均值就越接近實際價格。為了減小誤差，這個程式中我使用了antithetic variables，利用Var((Y1+Y2)/2)，Y1跟Y2是同樣的分佈(在這次作業中是Normal distribution)，而Y2為負的Y1，這樣就降低了1/2的variance。

對於Brownian Bridge的速度提高。
利用Brownian Bridge的特性去預估路徑是否曾碰觸到barrier。我認為利用此方式來評估價值，最大的好處是同樣的replication數(N)時，不需要在每個小片段都模擬出一個股價，因此計算速度較快，時間複雜度為O(N)。而原始方法把時間切割成幾期的期數M至少要到30左右或更大才會比較準確，因此Brownian Bridge的方法可以很大的提高運算速度。

Testing data:
S1 = 50, S2 = 50, S3 = 50, X = 50, H = 80, t = 1 (year), v1 =30 (%), v2 =30 (%), v3 =30 (%), rho = 40 (%), and r = 6 (%).
測試中選擇number of time points為m=50，發現不使用Brownian Bridge的方法計算時間會是使用Brownian Bridge的50倍左右。當path數n較大時可以明顯感覺出Brownian Bridge對速度的提高。
path數n越大越收斂, 當n為100時，price的值在2.9 ~ 3.4左右，當n為1000時，price的值在3.0 ~ 3.3左右
Brownian Bridge的結果當n為100時已經收斂到3.0~3.3左右，可見使用Brownian Bridg調整的Monte Carlo Simulation能更快速地收斂至實際價格。
當n更大時兩種方法都已收斂到較小的範圍，比如當n為10000時，price的值在3.14 ~ 3.22左右，當n為50000時，price的值在3.16 ~ 3.2左右。
