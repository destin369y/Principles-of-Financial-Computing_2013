Principles of Financial Computing HW#6
R01944040 ¬h¦¨½®

This is a program to price a European call option.

The C++ code is compiled in VS2012.
The Approximation function is written for Sec-approximation.

The inputs are t (option expiration date in years), T (bond maturity date in years), r (the spot rates for period i ), s (the volatility for period i ) and X (strike price as % of par). 
Please input the data according to the suggestive order.
And the output is the option value. 

For example, suppose 
t = 2 
T = 3
r = [ 4% 4.2% 4.3% ]
s =[ 20.27% 20.27% 20.27% ]
X = 90% of par 
The call value is about 0.052438.
