//a Monte Carlo Simulation program 
//3-asset single-barrier European knock-out put where the barrier is on the first asset S1. 
//Inputs: S1, S2, S3, X, H (barrier on S1), t (year), 
//		s1 (volatility of 1st asset in %), s2 (volatility of 2nd asset in %), s3 (volatility of 3rd asset in %), 
//		rho (the correlations between any two assets in %), r (interest rate in %), n (number of paths),
//		and m (number of time points including today, not needed if the Brownian bridge method is used). 
//The terminal payoff is max(X - (S1 + S2 + S3)/3, 0). 
//Assume H > S1. 
//The option will be knocked out if the first asset hits the barrier H. 
//For example, the price is about 3.15 ~ 3.2, 
//			when S1 = 50, S2 = 50, S3 = 50, X = 50, H = 80, t = 1 (year), 
//			s1 =30 (%), s2 =30 (%), s3 =30 (%), row = 40 (%), and r = 6 (%). 
//It is suggested that you apply antithetic variables. 
//You earn extra credits for doing the Brownian bridge method and compare convergence speeds.

#include <math.h>
#include <vector>
#include <iostream>
#include <iomanip> 
#include <time.h>

using namespace std;

#define max(a,b) ( ((a)>(b)) ? (a):(b) )
#define min(a,b) ( ((a)<(b)) ? (a):(b) )
#define PI double( acos(-1.0) )

double t;  //year
double r;  //interest rate
double S;  //stock price
double v;  //volatility
double X;  //strike price
double H;  //high barrier
double yield=0;  //non-dividend

int num_path;  //number of paths
int m; //number of time points including today

double dt,R,Est,Normal,v1,v2,random1,random2,rho;
double Sn,Sn_anti;
bool flag_touched,flag_touched_anti;
double result;
double correlation[4][4];

int main()
{
	cout << "stock price S:" << endl;	
	cin >> S;
	cout << "strike price X:" << endl;	
	cin >> X;
	cout << "high barrier H:" << endl;	
	cin >> H;
	cout << "year t:" << endl;	
	cin >> t;
	cout << "volatility v:" << endl;	
	cin >> v;
	cout << "correlations between any two assets rho:" << endl;	
	cin >> rho;
	cout << "interest rate r:" << endl;	
	cin >> r;
	cout << "the number of paths n:" << endl;	
	cin >> num_path;
	cout << "the number of time points including today m:" << endl;	
	cin >> m;

	r=r/100;
	v=v/100;
	rho=rho/100;
	dt=t/m;
	yield=yield/100;
	R=exp(r*dt);
	v1=v*v*dt/2;
	v2=v*sqrt(dt);
	Est=0;

	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			if(i==j)
				correlation[i][j]=1.0;
			else
				correlation[i][j]=rho;
 		}
	}

	srand( (unsigned)time( NULL ) );
	for(int j=0;j<num_path;j++)
	{
		Sn=S;
		Sn_anti=S;
		flag_touched=false;
		flag_touched_anti=false;

		if (S == H) 
		{
			flag_touched=true;
			flag_touched_anti=true;
		}

		for(int i=0;i<m;i++)
		{
			random1=(double)rand()/(RAND_MAX);
          	while(random1==0)
			{
				random1=(double)rand()/(RAND_MAX);
			}
			random2=(double)rand()/(RAND_MAX);
			while(random1==0)
			{
				random2=(double)rand()/(RAND_MAX);
			}
			Normal=sqrt( -2*log(random1) )*cos( 2*PI*random2 );
			
			Sn=Sn*R*exp(-yield*dt)*exp(-v1+v2*Normal);
			Sn_anti=Sn_anti*R*exp(-yield*dt)*exp(-v1-v2*Normal);
			if (( (S<H)&&(Sn>=H) ) || ( (S>H)&&(Sn<=H) ))
				flag_touched=true;
			if ( ( (S<H)&&(Sn_anti>=H) ) || ( (S>H)&&(Sn_anti<=H) ) )
				flag_touched_anti=true;
	    }
		
		if(flag_touched==false)	Est+=max(X-Sn,0);
		if(flag_touched_anti==false) Est+=max(X-Sn_anti,0);
	}
	
	Est=Est/(2*num_path);
	Est=Est/exp(r*t);
	
	//cout<<Est;
	result=int((Est)*100000+0.5)/100000.0;
	cout<< "the value of result: " << result <<endl;
	
	getchar();getchar();
	return 0;
}