這是一個計算forward rates的程式。用C++在VS2010環境下編寫。
Input是number of spot rates n、spot rates和maturities。
輸入時按提示順序輸入即可。其中spot rates只需輸入百分率數字，如2.5%per period，只需輸入2.5。
Output是計算得到的對應的forward rates，用百分率表示。
 
測試數據
spot rates n=5
spot rates are [2.0%, 2.5%, 3.0%, 3.5%, 4.0%]
corresponding maturities are [1, 2, 3, 5, 8]
forward rates are f(0,1) = 2.0000%, f(1,2) = 3.0025%, f(2,3) = 4.0073%, f(3,5) = 4.2546%, f(5,8) = 4.8387%