//price a European call option on zero-coupon bonds with the binomial interest rate tree
//ddd

#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

using namespace std; 

#define max(a,b) ( ((a)>(b)) ? (a):(b) )
#define min(a,b) ( ((a)<(b)) ? (a):(b) )

int t, T; 
double *r, *v;
double x;

double *p_temp;

double Flu(double p, double ratio, double dis, int layer)
{
	double inc;
	double flu = 0;
	for(int i = 0; i <= layer; i++)
	{
		inc=p_temp[i] / (1 + p * pow(ratio, i) );
		flu += inc;
	}
	flu -= dis;
	return flu;
}

double Approximate(double a, double b, double ratio, double dis, int layer)
{
	double q0 , q1;
	q0 = Flu(a, ratio, dis, layer);
	q1 = Flu(b, ratio, dis, layer);

	double app = 0;
	for( int i = 1; i <= 300; i++ )
	{
		app = b - q1 * (b - a) / ( q1 - q0 );

		if( fabs( app - b ) < (1.0/1000000) )
			break;

		a = b;
		b = app;
		q0 = q1;
		q1 = Flu(app, ratio, dis, layer);
	}
	return app;
}

int main()
{
	cout << "input the option expiration date in years:\n";
	cin >> t;

	cout << "input the bond maturity date in years:\n";
	cin >> T;

	r = new double[T];
	for(int i = 0; i < T; i++)
	{
		cout << "input the spot rate for period " << i+1 << " in%:" << endl;
		cin >> r[i];
		r[i] = r[i]/100;
	}

	v = new double[T];
	for(int i = 0; i < T; i++)
	{
		cout << "input the volatility for period " << i+1 << " in%:" << endl;
		cin >> v[i];
		v[i] = v[i]/100;
	}

	cout << "input the strike price as % of par:" << endl;
	cin >> x;
	x=x/100;

	double k;
	double *dis;
	double *ratio;
	dis = new double[T];
	ratio = new double[T];
	for(int i = 0; i < T; i++)
	{
		k = 1;
		for(int j = 0; j <= i; j++)
		{
			k = k / (1 + r[i]);
		}
		dis[i] = k;
		ratio[i] = exp(2 * v[i]);
	}

	double **bi_r, **state; 
	bi_r=new double*[T+1];
	state=new double*[T+1];
	
	for (int i = 0; i <=T ; i++)
	{
		bi_r[i] = new double[T+1];		
		state[i] = new double[T+1];
	}
	bi_r[0][0] = r[0];
	state[0][0] = 1;
	
	p_temp = new double[T+1];

	double interest;

	for(int i = 1; i <= T; i++)
	{
		state[i][0] = state[i-1][0] / (2 * (1 + bi_r[i-1][0]));
		p_temp[0] = state[i][0];
		for(int j = 1; j < i; j++)
		{		
			state[i][j] = state[i-1][j-1] / (2 * (1 + bi_r[i-1][j-1])) 
							+ state[i-1][j] / (2 * (1 + bi_r[i-1][j]));
			p_temp[j] = state[i][j];
		}

		state[i][i] = state[i-1][i-1] / (2 * (1 + bi_r[i-1][i-1]));
		p_temp[i] = state[i][i];

		if(i != T)
		{
			interest = Approximate(0, 1, ratio[i], dis[i], i);
			for(int j = 0; j <= i; j++)
				bi_r[i][j] = interest * pow(ratio[i], j);
		}
	}

	double **tree_value;
	tree_value=new double*[T+1];
	for (int i = 0; i <=T; i++)
	{
		tree_value[i] = new double[T+1];
	}
	for(int i = 0; i <= T; i++)
	{
		tree_value[T][i] = 1;
	}
	for(int i = T-1; i >= 0; i--)
	{
		for(int j = 0; j <= i; j++)
		{
			tree_value[i][j] = (tree_value[i+1][j] + tree_value[i+1][j+1]) / (2 * (1 +  bi_r[i][j]));
			if(i == t)
			{
				tree_value[i][j] = max(tree_value[i][j] - x, 0);
			}
		}
	}

	cout << "the option value: " << tree_value[0][0] << endl;

	system("Pause");
	return 0;
}
