#include<iostream>
#include<stdlib.h>
#include<sstream>
#include<time.h>

using namespace std;

struct frame
{
	int data;
	int error;
	int frame_no;
};

struct timer
{
	int sf;
	int error;
	string s;
	timer()
	{
		error = 0;
	}
};

void *resend(void *p)
{
	timer *ptr = static_cast<timer *>(p);
	if(ptr->error == 1)
		cout<<ptr->s;
	else
	{
		for(int i=0 ; i<200000000 ; i++);
		cout<<ptr->s;
	}
}

class receiver
{
	private:
		int n;
		int *frames;
	public:
		receiver()
		{
			n = 0;
			frames = new int[100];
		}
		int receive(frame f,timer &t)
		{
			ostringstream str;
			str<<n+1;
			if(f.error == 0 && n+1 == f.frame_no)
			{
				frames[n++] = f.data;
				return n-1;
			}
			if(f.error == 1)
				t.s = "Errror in transfer of frame"+str.str()+"!!\n";
			else
				t.s = "Timer out error in frame"+str.str()+"!!\n";
			return -1;
		}
};

class sender
{
	private:
		int n;
		int *frames;
		int sn;
		int sf;
		int winsn;
	public:
		sender()
		{
			n = sn = sf = 0;
			frames = new int[100];
		}
		void input()
		{
			cout<<"How many frames are there : ";
			cin>>n;
			for(int i=0 ; i<n ;)
			{
				cout<<"Enter data of frame "<<i+1<<"(in integers) : ";
				cin>>frames[i++];
			}
		}
		void send(receiver r)
		{
			timer t;
			srand(time(0));
			bool cansend = true;
			int i = 0;
			winsn = 0;
			frame f;
			pthread_t tid1,tid2;
			pthread_attr_t attr1,attr2;
			while(i<n)
			{
				int error = rand() % 3;
				int chance = rand() % 2;
				f.data = frames[sn];
				t.error = f.error = error;
				t.sf = sf;
				f.frame_no = sn+1;
				sender *s = this;
				if(sn < n && winsn < 7)
				{
					cout<<"Frame : "<<sn+1<<" sent!!"<<endl;
					sn++;
					winsn++;
				}
				if(r.receive(f,t) != -1)
				{
					cout<<"Data received : "<<f.data<<" : "<<"Frame : "<<sn<<" received successfully!!"<<endl;
					if(sf < n-1)
						sf++;
					winsn--;
					i++;
				}
				else if(chance == 1)
				{
					cansend = false;
					pthread_attr_init(&attr1);
					pthread_create(&tid1,&attr1,resend,&t);
					pthread_join(tid1,NULL);
					sn = sf;
					winsn = 0;
					cansend = true;
				}
			}
		}	
};

int main()
{
	receiver r;
	sender s;
	s.input();
	s.send(r);
	return 0;
}
