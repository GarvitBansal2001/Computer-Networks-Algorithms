#include<iostream>

using namespace std;

void input (bool arr[] , int n , bool gx[] , int r)
{
	cout<<"Enter a "<<n<<" bit binary code(add space in between) : ";
	for(int i=0 ; i<n ; i++)
		cin>>arr[i];
	for(int i=0 ; i<r ; i++)
		arr[n+i] = false;
}

void display (bool arr[] , int n , bool gx[] , int r)
{
	cout<<"Code : ";
	for(int i=0 ; i<n+r ; i++)
		cout<<arr[i];
}

void shift (bool arr[] , int r)
{
	for(int i=0 ; i<r ; i++)
		arr[i] = arr[i+1];
}

void sender (bool arr[] , int n , bool gx[] , int r)
{
	bool result[4];
	for(int i=0 ; i<=r ;i++)
		result[i] = arr[i];
	for(int i=r+1 ; i<n+r ; i++)
	{
		while(result[0] == false && i<n+3)
		{
			shift(result,r);
			result[3] = arr[i];
			i++;
		}
		if(result[0] != false)
		{
			for(int xo=0 ; xo<=r ; xo++)
			{
				result[xo] = result[xo]^gx[xo];
			}
			i--;
		}
	}
	for(int xo=0 ; xo<r ; xo++)
		arr[n+r-1-xo] = result[r-xo];
	display(arr,n,gx,r);
	
}

int main ()
{
	int n;
	int r;
	cout<<"degree of g(x) : ";
	cin>>r;
	int *temp = new int[r+1];
	bool *gx = new bool[r+1];
	for(int i=0 ; i<=r ; i++)
	{
		cout<<"enter coefficient of x^"<<i<<" : ";
		cin>>temp[i];
		if(temp[i] == 0)
			gx[r-i] = false;
		else
			gx[r-i] = true;
	}
	cout<<"Enter the length of message : ";
	cin>>n;
	bool *arr = new bool[n+r];
	input(arr,n,gx,r);
	sender(arr,n,gx,r);
	return 0;
}
