#include<iostream>
#include<cmath>

using namespace std;


bool convert_bool (int num , int pos)
{
	bool arr[100]; 
	int i=0;
	while(num>0)
	{
		arr[i] = !(num%2 == 0);
		num /= 2;
		i++;
	}
	bool flag = false;
	if(pos<i)
		if(arr[pos] == true)
			flag = true;
	return flag;
}

int cal_r(int n)
{
	int counter = 0;
	int i = 0;
	while(i<=n)
	{
		if(ceil(log2(i)) == floor(log2(i)))
			counter++;
		i++;
	}
	return --counter;
}

void create_msg()
{
	int n;
	bool msg[100];
	cout<<"How many bits are there in the hamming code by receiver : ";
	cin>>n;
	cout<<"Enter a "<<n<<" bit binary code by receiver (add space in between) : ";
	for(int i=0 ; i<n ; i++)
		cin>>msg[i];
	int r = cal_r(n);
	int count = 0;
	bool temp[100];
	for(int i=1 ; i<=n ; i++)
		if(ceil(log2(i)) == floor(log2(i)))
		{
			int c=0;
			int power = ceil(log2(i));
			for(int j=1 ; j<=n ; j++)
				if(!(ceil(log2(j)) == floor(log2(j))))
					if(convert_bool(j,power))
						if(msg[j-1] == true)
							c++;
			temp[power] = (c%2 != 0);
		}
	int c = 0;
	for(int i=1 ; i<=n ; i++)
		if(ceil(log2(i)) == floor(log2(i)))
			if(temp[(int)ceil(log2(i))]!=msg[i-1])
				c += i;
	if(c!=0)
		msg[c-1] = !msg[c-1];
	cout<<"correct hamming code : ";
	for(int i=0 ; i<n ; i++)
		cout<<msg[i];
}

int main()
{	
	create_msg();
	return 0;
}
