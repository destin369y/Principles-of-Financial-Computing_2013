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
//			s1 =30 (%), s2 =30 (%), s3 =30 (%), rho = 40 (%), and r = 6 (%). 
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
double S,S1,S2,S3;  //stock price
double v1,v2,v3;  //volatility
double X;  //strike price
double H;  //high barrier
double yield=0;  //non-dividend
int num_path;  //number of paths
int m; //number of time points including today

double dt,R,Est,random1,random2,rho;
double Normal,Normal1,Normal2,Normal3;
double v11,v12,v21,v22,v31,v32;
double Sn1,Sn_anti1,Sn2,Sn_anti2,Sn3,Sn_anti3;
bool flag_touched,flag_touched_anti;
double result;
double correlation[4][4],P[4][4];
double SumP;

int main()
{
	cout << "stock price S1:" << endl;	
	cin >> S1;
	cout << "stock price S2:" << endl;	
	cin >> S2;
	cout << "stock price S3:" << endl;	
	cin >> S3;
	cout << "strike price X:" << endl;	
	cin >> X;
	cout << "high barrier H:" << endl;	
	cin >> H;
	cout << "year t:" << endl;	
	cin >> t;
	cout << "volatility v1:" << endl;	
	cin >> v1;
	cout << "volatility v2:" << endl;	
	cin >> v2;
	cout << "volatility v3:" << endl;	
	cin >> v3;
	cout << "correlations between any two assets rho:" << endl;	
	cin >> rho;
	cout << "interest rate r:" << endl;	
	cin >> r;
	cout << "the number of paths n:" << endl;	
	cin >> num_path;
	cout << "the number of time points including today m:" << endl;	
	cin >> m;

	r=r/100;
	v1=v1/100;
	v2=v2/100;
	v3=v3/100;
	rho=rho/100;
	dt=t/m;
	yield=yield/100;
	R=exp(r*dt);
	v11=v1*v1*dt/2;
	v12=v1*sqrt(dt);
	v21=v2*v2*dt/2;
	v22=v2*sqrt(dt);
	v31=v3*v3*dt/2;
	v32=v3*sqrt(dt);
	Est=0;

	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			P[i][j]=0;
			if(i==j)
				correlation[i][j]=1.0;
			else
				correlation[i][j]=rho;
 		}
	}

	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			if(i==j)
			{
				SumP=0;
				for(int k=1;k<=j-1;k++)
				{
					SumP=SumP+P[j][k]*P[j][k];
				}
				P[i][j]=sqrt( correlation[j][j]-SumP );
			}
			else if(i>j)
			{
				SumP=0;
				for(int k=1;k<=j-1;k++)
				{
					SumP=SumP+P[i][k]*P[j][k];
				}
				P[i][j]=( correlation[i][j]-SumP )/P[j][j];
			}
			else
				P[i][j]=0;
 		}
	}

	srand( (unsigned)time( NULL ) );

	S=S1;
	for(int j=0;j<num_path;j++)
	{
		Sn1=S1;
		Sn_anti1=S1;
		Sn2=S2;
		Sn_anti2=S2;
		Sn3=S3;
		Sn_anti3=S3;
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
			Normal1=sqrt( -2*log(random1) )*cos( 2*PI*random2 );
			
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
			Normal2=sqrt( -2*log(random1) )*cos( 2*PI*random2 );
			
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
			Normal3=sqrt( -2*log(random1) )*cos( 2*PI*random2 );
			
			//Sn=Sn*R*exp(-yield*dt)*exp(-v1+v2*Normal);
			//Sn_anti=Sn_anti*R*exp(-yield*dt)*exp(-v1-v2*Normal);
			Normal=Normal1*P[1][1];
			Sn1=Sn1*R*exp(-yield*dt)*exp(-v11+v12*Normal);
			Sn_anti1=Sn_anti1*R*exp(-yield*dt)*exp(-v11-v12*Normal);

			if (( (S<H)&&(Sn1>=H) ) || ( (S>H)&&(Sn1<=H) ))
				flag_touched=true;
			if ( ( (S<H)&&(Sn_anti1>=H) ) || ( (S>H)&&(Sn_anti1<=H) ) )
				flag_touched_anti=true;

			Normal=Normal1*P[2][1]+Normal2*P[2][2];
			Sn2=Sn2*R*exp(-yield*dt)*exp(-v21+v22*Normal);
			Sn_anti2=Sn_anti2*R*exp(-yield*dt)*exp(-v21-v22*Normal);

			Normal=Normal1*P[3][1]+Normal2*P[3][2]+Normal3*P[3][3];
			Sn3=Sn3*R*exp(-yield*dt)*exp(-v31+v32*Normal);
			Sn_anti3=Sn_anti3*R*exp(-yield*dt)*exp(-v31-v32*Normal);
	    }
		
		if(flag_touched==false)	Est+=max(X-(Sn1+Sn2+Sn3)/3,0);
		if(flag_touched_anti==false) Est+=max(X-(Sn_anti1+Sn_anti2+Sn_anti3)/3,0);
	}
	
	Est=Est/(2*num_path);
	Est=Est/exp(r*t);
	
	//cout<<Est;
	result=int((Est)*100000+0.5)/100000.0;
	cout<< "the value of result: " << result <<endl;
	
	getchar();getchar();
	return 0;
}