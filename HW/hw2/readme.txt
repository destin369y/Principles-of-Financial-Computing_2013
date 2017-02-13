This is a binomial tree program, which can be used to calculate the prices of European and American options.
The stock pays a continuous dividend yield and the payoff function is the butterfly spread.

用C++在VS2010環境下編寫。
Inputs are S (stock price), X1 (strike price 1), X2 (strike price 2), X3 (strike price 3), σ (volatility), t (year), n (the total number of periods), δ (continuous dividend yield), and r (interest rate).
輸入時按提示順序輸入即可。
 
測試數據
S = 80, X1 = 100, X2 = 120, X3 = 140, σ = 0.4, t = 1, n = 100, δ = 0.02, and r = 0.06.
We can get that the European option price is about 1.7518 and the American option price is about 5.6296.