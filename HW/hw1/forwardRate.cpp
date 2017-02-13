#include <math.h>
#include <vector>
#include <iostream>
#include <iomanip> 

using namespace std;

int main()
{
	int n;
	vector<double> spotRate;
	vector<int> maturity;

	//printf("number of spot rates n:\n");
	cout << "number of spot rates n:" << endl;	
	//scanf("%d\n",&n);
	cin >> n;
	
	vector<double> forwardRate(n,0);
	vector<double> s(n,0);

	cout << "spot rates spotRate:" << endl;
	for(int i=0;i<n;i++)
	{
		double j;
		cin >> j;
		spotRate.push_back(j/100);
	}

	cout << "maturities N:" << endl;
	for(int i=0;i<n;i++)
	{
		int j;
		cin >> j;
		maturity.push_back(j);
	}

// 	for(int i=0;i<n;i++){
// 		cout << maturity[i] << " ";
// 	}
// 	cout << endl;
// 	
// 	for(int i=0;i<n;i++){
// 		cout << spotRate[i] << " ";
// 	}
// 	cout << endl;

	forwardRate[0]=spotRate[0]*100;

	for(int k=1;k<n;k++)
	{
		if(spotRate.empty()!=true && maturity.empty()!=true)			
		{			
			s[k]=pow(1+spotRate[k],1.0*maturity[k]);
		    s[k-1]=pow(1+spotRate[k-1],1.0*maturity[k-1]);
			forwardRate[k]=(pow(s[k]/s[k-1],1.0/(maturity[k]-maturity[k-1]))-1)*100;
		}
	}

	for(int i=0;i<n;i++)
	{
		cout<<fixed << setprecision(4) << forwardRate[i]<<"% ";
	}

	getchar();getchar();
	return 0;
}