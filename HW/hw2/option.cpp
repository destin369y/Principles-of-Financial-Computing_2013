//a binomial tree program to calculate the prices of European and American options 

#include <math.h>
#include <vector>
#include <iostream>
#include <iomanip> 

using namespace std;

#define max(a,b) ( ((a)>(b)) ? (a):(b) )

int main()
{
	double s;
	double x1;
	double x2;
	double x3;
	double v;
	double t;
	int n;
	double yield;
	double r;

	//printf("number of spot rates n:\n");
	cout << "stock price s:" << endl;	
	//scanf("%d\n",&n);
	cin >> s;

	cout << "strike price x1:" << endl;	
	cin >> x1;
	cout << "strike price x2:" << endl;	
	cin >> x2;
	cout << "strike price x3:" << endl;	
	cin >> x3;
	cout << "volatility v:" << endl;	
	cin >> v;
	cout << "year t:" << endl;	
	cin >> t;
	cout << "the total number of periods n:" << endl;	
	cin >> n;
	cout << "continuous dividend yield d:" << endl;	
	cin >> yield;
	cout << "interest rate r:" << endl;	
	cin >> r;

	double dt=t/n;
	double u=exp(v*sqrt(dt));
	double d=1/u;
	double R=exp(r*dt);
	double p=(R*exp(-yield*dt)-d)/(u-d);
	double resultEuropean=0;
	double resultAmerican=0;
	
	vector<double> priceEuropean;
	vector<double> priceAmerican;
	
	//for(i=0;i<=n;i++)
	//	P[i]=Math.max(0,S*Math.pow(u,n-i)*Math.pow(d,i)-X);
	//for(j=n-1;j>=0;j--){
	//	for(i=0;i<=j;i++){
	//		P[i]=(p*P[i]+(1-p)*P[i+1])/R;
	//	}}
	
	for(int i=0;i<=n;i++)
	{
		//priceEuropean[i]=max( 0, s*pow(u,n-i)*pow(d,i)-x1 )-2*max( 0, s*pow(u,n-i)*pow(d,i)-x2 )+max( 0, s*pow(u,n-i)*pow(d,i)-x3 );
		priceEuropean.push_back(max( 0, s*pow(u,n-i)*pow(d,i)-x1 )-2*max( 0, s*pow(u,n-i)*pow(d,i)-x2 )+max( 0, s*pow(u,n-i)*pow(d,i)-x3 ));
		priceAmerican.push_back(max( 0, s*pow(u,n-i)*pow(d,i)-x1 )-2*max( 0, s*pow(u,n-i)*pow(d,i)-x2 )+max( 0, s*pow(u,n-i)*pow(d,i)-x3 ));
	}
	for(int j=n-1;j>=0;j--)
	{
		for(int i=0;i<=j;i++)
		{
			priceEuropean[i]=(p*priceEuropean[i]+(1-p)*priceEuropean[i+1])/R;
			priceAmerican[i]=max( (p*priceAmerican[i]+(1-p)*priceAmerican[i+1])/R,
							      max( 0, s*pow(u,j-i)*pow(d,i)-x1 )-2*max( 0, s*pow(u,j-i)*pow(d,i)-x2 )+max( 0, s*pow(u,j-i)*pow(d,i)-x3 ) 
								);
		}
	}

	resultEuropean=int(priceEuropean[0]*10000+0.5)/10000.0;
	resultAmerican=int(priceAmerican[0]*10000+0.5)/10000.0;

	cout<< "European option price: " << resultEuropean <<endl;
	cout<< "American option price: " << resultAmerican <<endl;

	getchar();getchar();
	return 0;
}