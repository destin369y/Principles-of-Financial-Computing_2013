This is a trinomial tree program to price European double-barrier knock-out calls.

The C++ code is compiled in VS2012¡C
The inputs are S (stock price), X (strike price), H (high barrier), L (low barrier), t (year), s (volatility in %), r (interest rate in %), and n (number of periods).
Assume L < S < H.
Please input the data according to the suggestive order.

Testing data:
t = 1 (year), r = 10 (%), S = 95, s = 25 (%), X = 100, L = 90, H = 140.
We can get that the option price is between 1.457 and 1.4584 when n changes.
for example,when n=2000, the result is 1.45763.
