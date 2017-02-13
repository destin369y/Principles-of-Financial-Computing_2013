This is a binomial tree program, which can be used to calculate the European Asian calls on a non-dividend-paying stock using an approximation algorithm.
The stock pays a continuous dividend yield and the payoff function is the butterfly spread.

The C++ code is compiled in VS2012¡C
The inputs are S(stock price), x(strike price), t(year), n(the total number of periods), s(volatility in %), r(risk-free rate in %) and k(so k+1 averages per node and their logarithms are equally spaced).
Please input the data according to the suggestive order.
 
Testing data:
S = 95, X = 100, t = 2 (year), n = 100, s = 20 (%), r = 15 (%), and k = 100.
We can get that the option price is about 10.1854.