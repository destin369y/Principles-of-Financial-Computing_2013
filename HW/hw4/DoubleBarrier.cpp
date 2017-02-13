//a trinomial tree program to price European double-barrier knock-out calls. 
//Inputs: S (stock price), X (strike price), H (high barrier), L (low barrier), t (year), s (volatility in %), 
//		r (interest rate in %), and n (number of periods). 
//		Assume L < S < H. 
//For example, the price is about 1.457-1.4584 when t = 1 (year), r = 10 (%), S = 95, s = 25 (%), X = 100, L = 90, H = 140. 

#include <math.h>
#include <vector>
#include <iostream>
#include <iomanip> 

using namespace std;

#define max(a,b) ( ((a)>(b)) ? (a):(b) )
#define min(a,b) ( ((a)<(b)) ? (a):(b) )

double S;  //stock price
double X;  //strike price
double t;  //year
double v;  //volatility
double r;  //interest rate
double H;  //high barrier
double L;  //low barrier
double rebate=0;  //no rebate

int n;  //the total number of partitions
double dt,h,l,lambda,gamma,R,pu,pd,pm,u,d,a,b,pu_L,pd_L,pm_L,result;

int main()
{
	//printf("number of spot rates n:\n");
	cout << "stock price S:" << endl;	
	//scanf("%d\n",&n);
	cin >> S;

	cout << "strike price X:" << endl;	
	cin >> X;
	cout << "high barrier H:" << endl;	
	cin >> H;
	cout << "low barrier L:" << endl;	
	cin >> L;
	cout << "year t:" << endl;	
	cin >> t;
	cout << "volatility s:" << endl;	
	cin >> v;
	cout << "interest rate r:" << endl;	
	cin >> r;
	cout << "the total number of periods n:" << endl;	
	cin >> n;

	r=r/100;
	v=v/100;
	dt=t/n;
	
	if(L>H) 
	{
		cout << "low barrier higher than high barrier " << endl;
		return 0;
	}
	if(L>S) 
	{
		cout << "stock price lower than low barrier " << endl;
		return 0;
	}
	if(S>H) 
	{
		cout << "stock price higher than high barrier " << endl;
		return 0;
	}

	// try to hit high barrier 
	// h steps to high barrier
	h=floor( log(H/S) / ( v*sqrt(dt) ) );  
	if(abs(h)<1) 
	{	
		cout << "Increase the number of partitions, suggest at least " << ceil( v*v*(t) / pow( log(H/S),2 ) ) << endl;
		return 0;
	}
	if(abs(h)>n) 
	{
		cout << "Increase the number of partitions, suggest at least " << ceil( pow( log(H/S),2 ) / (v*v *(t)) ) << endl;
		return 0;
	}

	lambda=log(H/S)/(h*v*sqrt(dt));
	R=exp(r*dt);
	pu=1/(2*lambda*lambda)+(r-v*v/2.0)*sqrt(dt)/(2*lambda*v);
	pd=1/(2*lambda*lambda)-(r-v*v/2.0)*sqrt(dt)/(2*lambda*v);
	pm=1.0-pu-pd;
	u=exp(lambda*v*sqrt(dt));
	d=1/u;

	// low barrier must be more than one layer below S
	if(S*d<= L)  
	{ 
		cout << "Increase the number of partitions "  << endl;
		return 0;
	}
	// l steps to right above low barrier
	l=floor(log(S/L)/(v*lambda*sqrt(dt)));
	gamma=-log(L/(S*pow(d,l-1)))/(lambda*v*sqrt(dt)); // extra stretch for layer l to coincide with low barrier

	// branching probabilities for layer right above low barrier
	a=(r-v*v/2.0)*sqrt(dt)/(lambda*v);
	b=1/(lambda*lambda);
	pu_L=(b+a*gamma)/(1+gamma);
	pd_L=(b-a)/(gamma+gamma*gamma);
	pm_L=1.0-pu_L-pd_L;
	if (pu_L<0 || pm_L <0 || pd_L<0) 
	{
		cout << "Increase the number of partitions "  << endl;
		return 0;
	}

	vector<double> Q(2*n+1,0);
	for(int i=0;i<=2*n;i++)
	{
		Q[i]= max(0,S*pow(d,n-i)-X);
	}
	Q[n+h]=rebate; 
	Q[n-l]=rebate;
	for(int j=n-1;j>=0;j--)
	{
		for(int i=0;i<=2*j;i++)
		{
			if(i == (j-l+1)) // layer l-1
			{ 
				Q[i]=(pd_L*Q[i]+pm_L*Q[i+1]+pu_L*Q[i+2])/R;
			} 
			else 
			{
				Q[i]=(pd*Q[i]+pm*Q[i+1]+pu*Q[i+2])/R;
			}
		}
		if ((h+j)<=2*j) 
		{ // high barrier
			Q[h+j]=rebate;
		}
		if ((j-l)>=0) 
		{ // low barrier
			Q[j-l]=rebate;
		}
	}
	result=int((Q[0])*100000+0.5)/100000.0;

	cout<< "Option value: " << result <<endl;

	getchar();getchar();
	return 0;
}	