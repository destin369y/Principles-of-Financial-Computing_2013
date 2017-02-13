//a binomial tree program for arithmetic European Asian calls on a non-dividend-paying stock. 
//The payoff is max(average - X, 0), where average is as in the slides. 
//Inputs: S (stock price), X (strike price), t (year), n (the total number of periods), s (volatility in %), r (risk-free rate in %), 
//		k (so k+1 averages per node and their logarithms are equally spaced). 
//For example, suppose S = 95, X = 100, t = 2 (year), n = 100, s = 20 (%), r = 15 (%), and k = 100. The option price is about 10.1854.

#include <math.h>
#include <vector>
#include <iostream>
#include <iomanip> 

using namespace std;

#define max(a,b) ( ((a)>(b)) ? (a):(b) )
#define min(a,b) ( ((a)<(b)) ? (a):(b) )

double yield=0;  //non-dividend
double s;  //stock price
double x;  //strike price
double t;  //year
int n;     //the total number of periods
double v;  //volatility
double r;  //risk-free rate
int k;     //number of buckets per node

double dt,u,d,R,p,resultEuropean;

//Set up the bucket's average from min to max
vector<double> setUpAverage(vector<double> A,int j,int i) 
{
	// minimum
	A[0] = s*(1-pow(d,i+1))/(1-d) + s*pow(d,i)*u*(1-pow(u,j-i))/(1-u);
	A[0] = A[0]/(j+1);
	// maximum
	A[k] = s*(1-pow(u,j-i+1))/(1-u) + s*pow(u,j-i)*d*(1-pow(d,i))/(1-d);
	A[k] = A[k]/(j+1);
	
	for(int m=1; m<k; m++)
		//A[m]=(k-m)*A[0]/k + m*A[k]/k;
		A[m]=exp( (k-m)*log(A[0])/k + m*log(A[k])/k );	//logarithms equally spaced
	return A;
}

int main()
{
	//printf("number of spot rates n:\n");
	cout << "stock price s:" << endl;	
	//scanf("%d\n",&n);
	cin >> s;

	cout << "strike price x:" << endl;	
	cin >> x;
	cout << "year t:" << endl;	
	cin >> t;
	cout << "the total number of periods n:" << endl;	
	cin >> n;
	cout << "volatility v:" << endl;	
	cin >> v;
	cout << "interest rate r:" << endl;	
	cin >> r;
	cout << "number of buckets k:" << endl;	
	cin >> k;

	r=r/100;
	v=v/100;

	dt=t/n;
	u=exp(v*sqrt(dt));
	d=1/u;
	R=exp(r*dt);
	p=(R*exp(-yield*dt)-d)/(u-d);
	resultEuropean=0;
	
	vector< vector<double> > P( n+1, vector<double>(k+1,0) );
	vector<double> A(k+1,0);
	vector<double> AU(k+1,0);
	vector<double> AD(k+1,0);
	vector<double> D(k+1,0);
	double Au,Cu;
	double Ad,Cd;
	
	for(int i=0;i<=n;i++)
	{
		A=setUpAverage (A,n,i);
		for(int m=0;m<=k;m++)
			P[i][m]=max(0,A[m]-x);
	}
	for(int j=n-1;j>=0;j--)
	{
		for(int i=0;i<=j;i++)
		{
			A=setUpAverage (A,j,i);
			AU=setUpAverage (AU,j+1,i);
			AD=setUpAverage (AD,j+1,i+1);
			int cursorU=0;
			int cursorD=0;  
			for(int m=0;m<=k;m++)
			{
				Au=(A[m]*(j+1)+s*pow(u,j+1-i)*pow(d,i))/(j+2);
				while( (cursorU<=k) && (Au>AU[cursorU]) )
					cursorU++;
				if( (cursorU==0) || (cursorU==(k+1)) || (Au==AU[cursorU]) )  
					Cu=P[i][min(cursorU,k)];
				else
				{
					x=(Au-AU[cursorU])/(AU[cursorU-1]-AU[cursorU]);
					Cu=x*P[i][cursorU-1] +(1-x)*P[i][cursorU];
				}
				
				Ad= (A[m]*(j+1)+s*pow(u,j-i)*pow(d,i+1))/(j+2);
				while ((cursorD<=k)&&(Ad>AD[cursorD])) 
					cursorD++;
				if ((cursorD==0)||(cursorD==(k+1))||(Ad==AD[cursorD]))  
					Cd=P[i+1][min(cursorD,k)];
				else 
				{
					x=(Ad-AD[cursorD])/(AD[cursorD-1]-AD[cursorD]);
					Cd=x*P[i+1][cursorD-1] +(1-x)*P[i+1][cursorD];
				}

				D[m]=(p*Cu+(1-p)*Cd)/R;
			}
			for (int m=0; m<=k; m++) 
				P[i][m]=D[m];
		}
	}
	resultEuropean=int(P[0][0]*10000+0.5)/10000.0;

	cout<< "Option value: " << resultEuropean <<endl;

	getchar();getchar();
	return 0;
}

