/* A project to store record of Bus, their Fee and to generate bill
	BY- NAMAN MITTAL
	XII-A
*/
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<dos.h>
#include<graphics.h>

  int pur[100];
  int n;
  inline void clear();

  class maintain
  {
	public:
	int busno;
	char source[30];
	float fare;
	char dest[30];
	int noseats;
	char date[15];
	void getdata()
	{
		clear();
		cout<<"\n\nENTER THE BUS NO : ";
		cin>>busno;
		cout<<"\n\nENTER THE SOURCE : ";
		gets(source);
		cout<<"\n\nENTER DESTINATION : ";
		gets(dest);
		cout<<"\n\nENTER TICKET FARE : " ;
		cin>>fare;
		cout<<"\n\nENTER THE NUMBER OF SEATS : ";
		cin>>noseats;
		cout<<"\n\nENTER THE DATE OF DEPARTURE(dd/mm/yy) : ";
		gets(date);
	}
	void dispdata()
	{
		 clear();
		 cout<<"\n\n BUS NO : "<<busno;
		 cout<<"\n\n SOURCE : "<<source;
		 cout<<"\n\n DESTINATION : "<<dest;
		 cout<<"\n\n FARE : "<<fare;
		 cout<<"\n\n NUMBER OF SEATS : "<<noseats;
		 cout<<"\n\n DATE OF DEPARTURE(dd/mm/yy) : "<<date;
	}
	int retbusno()
	{
		return busno;
	}
	char* retdate()
	{
		return date;
	}
  };


  class passenger
  {
	   public:
	   int registrationno;
	   char name[30];
	   char address[40];
	   struct date dep_date;
	   char creditcardno[20];
	   void getdata()
	   {
		 clear();
		 cout<<"\n\n\nEnter Customer's Registration Number : ";
		 cin>>registrationno;
		 cout<<"\n\nEnter Customer's Name : ";
		 gets(name);
		 cout<<"\n\nEnter Customer's Address : ";
		 gets(address);
		 cout<<"\n\nEnter Customer's CREDIT CARD Number(10 digits) : ";
		 gets(creditcardno);
	   }
	   void dispdata()
	   {
		clear();
		cout<<"\n\nRegistration Number : "<<registrationno;
		cout<<"\n\nName : "<<name;
		cout<<"\n\nAddress : "<<address;
		cout<<"\n\nCREDIT CARD Number : "<<creditcardno;
	   }
	   char* retname()
	   {
		return name;
	   }
	   int retregno()
	   {
		return registrationno;
	   }
  };

  // Function to create passenger record
  void pcreate()
  {
	 clear();
	 passenger p;
	 char rep;
	 ofstream fout("pass.dat",ios::app|ios::binary);
	 do
	 {
		 clear();
		 p.getdata();
		 fout.write((char*)&p,sizeof(p));
		 cout<<"\n\nWant to write more records ? (y/n) : ";
		 rep=getche();
	 }while(rep=='y'||rep=='Y');
	 fout.close();
  }

// Function to modify passenger record
  void pmodify()
  {
	clear();
	passenger p;
	char con;
	int no,found;
	ifstream fin("pass.dat",ios::in|ios::binary);
	cout<<"\n\nEnter the Customer's Registration Number for modifications : ";
	cin>>no;
	ofstream fout("newpass.dat",ios::out|ios::binary);
	while(fin.read((char*)&p,sizeof(p)))
	{
	      if(p.retregno()==no)
	      {
		    clrscr();
		    p.dispdata();
		    cout<<"\n\nAre you sure you want to modify ? (y/n) : ";
		    cin>>con;
		    if(con=='y')
		    {
			  clrscr();
			  p.getdata();
			  found=1;
		    }
		    else
			  found=0;
	      }
	      fout.write((char*)&p,sizeof(p));
	}
	if(found==1)
		cout<<"\n\nRECORD MODIFIED";
	else if(found==0)
		cout<<"\n\nMODIFICATION CANCELLED";
	else
		cout<<"\n\nNO RECORD FOUND";
	getch();
	fin.close();
	fout.close();
	remove("pass.dat");
	rename("newpass.dat","pass.dat");
  }

  // Function to delete passenger record
  void pdel()
  {
	clear();
	passenger p;
	char con;
	int no,found;
	ifstream fin("pass.dat",ios::in|ios::binary);
	cout<<"\n\n\nEnter the Registration Number for deletion : ";
	cin>>no;
	ofstream fout("newpass.dat",ios::out|ios::binary);
	while(fin.read((char *)&p,sizeof(p)))
	{
	     if(p.retregno()==no)
	     {
		  p.dispdata();
		  cout<<"\n\nAre you sure you want to delete ? (y/n) : ";
		  cin>>con;
		  if(con=='n')
		  {	fout.write((char *)&p,sizeof(p));
			found=0;
		  }
		  else
			found=1;
	     }
	     else
	     {
		  fout.write((char *)&p,sizeof(p));
	     }
	}
	if(found==1)
		cout<<"\n\nRECORD DELETED";
	else if(found==0)
		cout<<"\n\nDELETION CANCELLED";
	else
		cout<<"\n\nNO RECORD FOUND";
	getch();
	fin.close();
	fout.close();
	remove("pass.dat");
	rename("newpass.dat","pass.dat");
  }

// Function to display passenger record
  void pdisplay()
  {
	  clear();
	  passenger p;
	  char ans;
	  clrscr();
	  ifstream fin("pass.dat",ios::in|ios::binary);
	  do
	  {
		clrscr();
		fin.read((char*)&p,sizeof(p));
		p.dispdata();
		cout<<"\n\nWant to read more records ? (y/n) : ";
		ans=getche();
	  }
	  while (ans=='y'||ans=='Y');
	  fin.close();
  }

// Function to search passenger record by name
  void pqueryname()
  {
	 clear();
	 char nam[30];
	 passenger p;
	 int found;
	 cout<<"\nEnter the Name of passenger to search : ";
	 gets(nam);
	 ifstream fin("pass.dat",ios::in|ios::binary);
	 while(fin.read((char *)&p,sizeof(p)))
	 {
		   if(strcmp(p.retname(),nam)==0)
		   {
			 p.dispdata();
			 found=0;
		   }
		   else
			 found=1;
	 }
	 if (found==1)
		cout<<"\n\nNO RECORD FOUND";
	 else
		cout<<"\n\nPress Enter to continue";
	 getch();
	 fin.close();
  }

// Function to search passenger record by registration number
  void pqueryregno()
  {
	clear();
	passenger p;
	int regno,found;
	cout<<"\nEnter the Passenger registration no. to search : ";
	cin>>regno;
	ifstream fin("pass.dat",ios::in|ios::binary);
	while(fin.read((char*)&p,sizeof(p)))
	{
		   if(p.retregno()==regno)
		   {
			  p.dispdata();
			  found=0;
		   }
		   else
			  found=1;
	}
	if(found==1)
		cout<<"\n\nNO RECORD FOUND";
	else
		cout<<"\n\nPress Enter to continue";
	getch();
	fin.close();
  }


// Function to create bus record
  void mcreate()
  {
	clear();
	maintain m;
	char rep;
	ofstream fout("bus.dat",ios::app|ios::binary);
	do
	{
		clrscr();
		m.getdata();
		fout.write((char*)&m,sizeof(m));
		cout<<"\n\nWANT TO WRITE MORE RECORDS ? (y/n) : ";
		rep=getche();
	}while (rep=='y'||rep=='Y');
	fout.close();
  }

// Function to modify bus record
  void mmodify()
  {
	clear();
	int no;
	char con;
	maintain m;
	int found;
	ifstream fin("bus.dat",ios::in|ios::binary);
	cout<<"\n\nENTER THE BUS NO.FOR MODIFICATIONS : ";
	cin>>no;
	ofstream fout("temp.dat",ios::out|ios::binary);
	while(fin.read((char*)&m,sizeof(m)))
	{
	      if(m.retbusno()==no)
	      {
		  clrscr();
		  m.dispdata();
		  cout<<"\n\nAre you sure you want to modify ? (y/n) : ";
		  cin>>con;
		  if(con=='y')
		  {
			clrscr();
			m.getdata();
			found=1;
		  }
		  else
			found=0;
	      }
	      fout.write((char*)&m,sizeof(m));
	}
	if(found==1)
		cout<<"\n\nRECORD MODIFIED";
	else if(found==0)
		cout<<"\n\nMODIFICATION CANCELLED";
	else
		cout<<"\n\nNO RECORD FOUND";
	getch();
	fin.close();
	fout.close();
	remove("bus.dat");
	rename("temp.dat","bus.dat");
  }


// Function to update number of seats in bus record
  void mupdate()
  {
	clear();
	maintain m;
	ifstream fin;
	int no;
	fin.open("bus.dat",ios::in|ios::binary);
	cout<<"\n\nENTER THE BUS NO. FOR  UPDATION : ";
	ofstream fout;
	cin>>no;
	fout.open("temp.dat",ios::out|ios::binary);
	int qty;
	fin.read((char*)&m,sizeof(m));
	do
	{
		if(no!=m.busno)
			fout.write((char*)&m,sizeof(m));
		else
		{
			int l;
			cout<<"\n\nENTER NUMBER OF SEATS FOR UPDATION : ";
			cin>>qty;
			cout<<"\n\nDO YOU WANT TO:\n1.ADD\n2.DELETE";
			cout<<"\n\nENTER YOUR CHOICE : ";
			cin>>l;
			if(l==1)
			{
				m.noseats+=qty;
				fout.write((char*)&m,sizeof(m));
			}
			else if(l==2)
			{
				m.noseats-=qty;
				fout.write((char*)&m,sizeof(m));
			}
			else
				cout<<"\n\nINVALID CHOICE";
		}
		fin.read((char*)&m,sizeof(m));
	}
	while(fin);
	cout<<"\n\n RECORD MODIFIED";
	cout<<"\n\n Press ENTER to continue";
	getch();
	fin.close();
	fout.close();
	remove("bus.dat");
	rename("temp.dat","bus.dat");
  }

// Function to delete bus record
  void mdel()
  {
	clear();
	maintain m;
	char con;
	ifstream fin;
	int no,found;
	fin.open("bus.dat",ios::in|ios::binary);
	cout<<"\n\nENTER THE BUS NUMBER TO DELETE : ";
	ofstream fout;
	cin>>no;
	fout.open("temp.dat",ios::out|ios::binary);
	while(fin.read((char*)&m,sizeof(m)))
	{
	     if(m.retbusno()==no)
	     {
		  m.dispdata();
		  cout<<"\n\nAre you sure you want to delete ? (y/n) : ";
		  cin>>con;
		  if(con=='n')
		  {	fout.write((char*)&m,sizeof(m));
				found=0;
		  }
		  else
			found=1;
	     }
	     else
	     {
		  fout.write((char*)&m,sizeof(m));
	     }
	}
	if(found==1)
		cout<<"\n\nRECORD DELETED";
	else if(found==0)
		cout<<"\n\nDELETION CANCELLED";
	else
		cout<<"\n\nNO RECORD FOUND";
	getch();
	fin.close();
	fout.close();
	remove("bus.dat");
	rename("temp.dat","bus.dat");
  }

// Function to display bus record
  void mdisplay()
  {
	clear();
	maintain m;
	char ans;
	clrscr();
	ifstream fin("bus.dat",ios::in|ios::binary);
	do
	{
		 clrscr();
		 fin.read((char*)&m,sizeof(m));
		 m.dispdata();
		 cout<<"\n\nWANT TO READ MORE RECORDS ? (y/n) : ";
		 ans=getche();
	}
	while(ans=='y'||ans=='Y');
	fin.close();
  }

// Function to search bus record by bus number
  void mquerybus()
  {
	clear();
	maintain m;
	int busnumber,found;
	cout<<"\n\nEnter the Bus no. to search : ";
	cin>>busnumber;
	ifstream fin("bus.dat",ios::in|ios::binary);
	while(fin.read((char*)&m,sizeof(m)))
	{
		   if(m.retbusno()==busnumber)
		   {	   m.dispdata();
			   found=0;
		   }
		   else
			found=1;
	}
	if(found==1)
		cout<<"\n\nNO RECORD FOUND";
	else
		cout<<"\n\nPress Enter to continue";
	getch();
	fin.close();
  }

// Function to search bus record by departure date
  void mquerydate()
  {
	clear();
	maintain m;
	char date[15];
	int found;
	cout<<"\n\nEnter the Departure Date to search : ";
	gets(date);
	ifstream fin("bus.dat",ios::in|ios::binary);
	while(fin.read((char*)&m,sizeof(m)))
	{
		   if(strcmp(m.retdate(),date)==0)
		   {	   m.dispdata();
			   found=0;
		   }
		   else
			found=1;
	}
	if(found==1)
		cout<<"\n\nNO RECORD FOUND";
	else
		cout<<"\n\nPress Enter to continue";
	getch();
	fin.close();
  }

// Function for clearing the graphics screen
  inline void clear()
  {
	 clrscr();
	 setbkcolor(LIGHTBLUE);
	 cleardevice();
  }

// Function to display menu of Maintenance of bus record
  void maintenance()
  {
	int n;
	do
	{
		clear();
		cout<<"\n\n\t\t\tWELCOME TO MAINTENANCE OF BUS RECORDS";
		cout<<"\n\n\n 1.CREATE A NEW BUS RECORD";
		delay(75);
		cout<<"\n\n 2.MODIFY A RECORD";
		delay(75);
		cout<<"\n\n 3.DELETE A RECORD";
		delay(75);
		cout<<"\n\n 4.DISPLAY THE BUS RECORD";
		delay(75);
		cout<<"\n\n 5.UPDATE NO. OF SEATS";
		delay(75);
		cout<<"\n\n 6.QUERY ON BASIS OF BUS NO.";
		delay(75);
		cout<<"\n\n 7.QUERY ON BASIS OF DEPARTURE DATE";
		delay(75);
		cout<<"\n\n Press ESCAPE to return to previous menu";
		delay(75);
		cout<<"\n\n ENTER YOUR CHOICE : ";
		n=getche();
		delay(350);
		if(n==27)
			return;
		switch(n)
		{
			case '1': mcreate();
				  break;
			case '2': mmodify();
				  break;
			case '3': mdel();
				  break;
			case '4': mdisplay();
				  break;
			case '5': mupdate();
				  break;
			case '6': mquerybus();
				  break;
			case '7': mquerydate();
				  break;
			default : cout<<"\n\nInvalid Choice";
		}
	}while(1);
  }

// Function for booking ticket
  void ticketbooking()
  {
	clear();
	int reg;
	passenger p;
	ifstream fin("pass.dat",ios::in|ios::binary);
	cout<<"\n\n ENTER REGISTRATION NUMBER : ";
	cin>>reg;
	int f=0;
	while(fin.read((char*)&p,sizeof(p)))
	{
	       if(p.retregno()==reg)
		{
			 f=1;
			 p.dispdata();
			 cout<<"\n\nPRESS ENTER TO CONTINUE";
			 getch();
		}
	}
	fin.close();
	if (f==0)
	{
		cout<<"\n\n REGISTRATION NO. NOT FOUND ...";
		char rep;
		cout<<"\n\n DO YOU WANT TO REGISTER ? (y/n) : ";
		cin>>rep;
		if (rep=='y')
		{
			pcreate();
			getch();
		}
		else
			return;
	}
	ifstream f1;
	maintain m;
	f1.open("bus.dat",ios::in|ios::binary);
	clear();
	gotoxy(1,1);
	cout<<"BUS NO.";
	gotoxy(9,1);
	cout<<"SOURCE";
	gotoxy(20,1);
	cout<<"DESTINATION";
	gotoxy(40,1);
	cout<<"DATE";
	gotoxy(50,1);
	cout<<"FARE";
	gotoxy(60,1);
	cout<<"SEATS AVAILABLE";
	int x=3;
	while(f1.read((char*)&m,sizeof(m)))
	{
			 gotoxy(1,x);
			 cout<<m.busno;
			 gotoxy(9,x);
			 cout<<m.source;
			 gotoxy(20,x);
			 cout<<m.dest;
			 gotoxy(40,x);
			 cout<<m.date;
			 gotoxy(50,x);
			 cout<<m.fare;
			 gotoxy(60,x);
			 cout<<m.noseats;
			 x++;
	}
	char ans;
	for(int i=0;i<100;i++)
		pur[i]=NULL;
	gotoxy(10,20);
	cout<<"ENTER THE BUS NO. : ";
	cin>>n;
	pur[n-1]=n;
	cout<<"\n\n\t\t\tPRESS ENTER TO CONTINUE";
	getch();
	f1.close();
  }

// Function to create bill after booking ticket
  void bill()
  {
	clear();
	maintain m;
	float tot=0, price;
	gotoxy(1,1);
	cout<<"BUS NO.";
	gotoxy(9,1);
	cout<<"SOURCE";
	gotoxy(20,1);
	cout<<"DESTINATION";
	gotoxy(40,1);
	cout<<"DATE";
	gotoxy(50,1);
	cout<<"FARE";
	gotoxy(60,1);
	cout<<"SEATS BOOKED";
	gotoxy(73,1);
	cout<<"PRICE";
	for(int i=0;i<=n;i++)
	{
		long offset=0;
		fstream f("bus.dat",ios::in|ios::out|ios::binary);
		f.read((char*)&m,sizeof(m));
		int qty;
		do
		{
			 if(pur[i]==m.retbusno())
			 {
				 gotoxy(1,4);
				 cout<<m.busno;
				 gotoxy(9,4);
				 cout<<m.source;
				 gotoxy(20,4);
				 cout<<m.dest;
				 gotoxy(39,4);
				 cout<<m.date;
				 gotoxy(50,4);
				 cout<<m.fare;
				 if(m.noseats<=0)
				 {
					 gotoxy(60,4);
					 cout<<"NO SEATS";
					 cout<<"\nPRESS ENTER TO CONTINUE";
					 ticketbooking();
				 }
				 else
				 {
					 gotoxy(1,7);
					 cout<<"\nEnter no. of seats to book : ";
					 cin>>qty;
					 gotoxy(60,4);
					 cout<<qty;
					 price=m.fare*qty;
					 gotoxy(73,4);
					 cout<<price;
					 tot=tot+price;
					 m.noseats-=qty;
					 f.seekp(offset,ios::beg);
					 f.write((char*)&m,sizeof(m));
				 }
			 }
			 offset+=sizeof(m);
			 f.read((char*)&m,sizeof(m));
		}while(f);
		f.close();
	}
	gotoxy(2,15);
	cout<<"TOTAL AMOUNT                                          "<<tot;
	getch();
  }

// Function for registration of name
  void registername()
  {
	int n;
	clrscr();
	do
	{
		clear();
		cout<<"\n\n\t\t\t\tWELCOME TO PASSENGER RESERVATION";
		cout<<"\n\n 1.CREATE A NEW RECORD";
		delay(75);
		cout<<"\n\n 2.MODIFY A RECORD";
		delay(75);
		cout<<"\n\n 3.DELETE A RECORD";
		delay(75);
		cout<<"\n\n 4.DISPLAY THE DATA";
		delay(75);
		cout<<"\n\n 5.QUERY ON BASIS OF NAME";
		delay(75);
		cout<<"\n\n 6:QUERY ON BASIS OF REGISTRATION NUMBER";
		delay(75);
		cout<<"\n\n Press ESCAPE key to return to previous menu";
		delay(75);
		cout<<"\n\n ENTER YOUR CHOICE : ";
		n=getche();
		delay(350);
		if(n==27)
			return;
		switch(n)
		{
			case '1': pcreate();
				  break;
			case '2': pmodify();
				  break;
			case '3': pdel();
				  break;
			case '4': pdisplay();
				  break;
			case '5': pqueryname();
				  break;
			case '6': pqueryregno();
				  break;
			default:  cout<<"\n\nInvalid Choice";
		}
	}while(1);
  }

// Function to display menu of customer service
  void customer()
  {
	int n;
	clrscr();
	do
	{
		clear();
		cout<<"\n\n\t\t\t\t WELCOME TO BUS RESERVATION ";
		cout<<"\n\n\n\n1.REGISTER YOUR NAME";
		delay(100);
		cout<<"\n\n2.BOOK TICKET";
		delay(100);
		cout<<"\n\nPress ESCAPE key to return to previous menu";
		delay(100);
		cout<<"\n\nENTER THE CHOICE : ";
		n=getche();
		delay(350);
		if(n==27)
			return;
		switch(n)
		{
			case '1': registername();
				  break;
			case '2': ticketbooking();
				  bill();
				  break;
			default:  cout<<"\nInvalid Choice";
		}
	}while(1);
  }

// Function for password in the project
  int lock()
  {
	setbkcolor(CYAN);
	char key[30],ch;
	int i=-1;
	cleardevice();
	settextstyle(0,0,2);
	outtextxy(100,180,"Enter Password : ");
	do
	{
		ch=getch();
		if (ch==13)
		break;
		if(ch==8)
		{
			if(i>=0)
				i--;
		}
		else
		key[++i]=ch;
		cleardevice();
		settextstyle(0,0,2);
		outtextxy(100,180,"Enter Password : ");
		moveto(400,180);
		for(int x=0;x<=i;x++)
		      {	settextstyle(0,0,2);
		       outtext("*");      }
	}while(1);
	key[++i]='\0';
	if(strcmp(key,"khms")==0)
		 return 2;
	else
		 return 0;
  }

// Function to initialize the graphics
  void setgraph()
  {
	int graphdriver = DETECT, graphmode, error_code;
	initgraph(&graphdriver, &graphmode, ".\\bgi");
	error_code = graphresult();
	if (error_code != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(error_code));
		printf("Press any key to halt:");
		getch();
		exit(1);
	}
  }

// Function for loading process in the project
  void loading()
  {
	int left, top, right, bottom;
	int left1,top1,right1,bottom1;
	setbkcolor(CYAN);
	settextstyle(0,0,2);
	outtextxy(70,180,"LOADING");
	left = 563;
	top =  177;
	right = 197;
	bottom = 203;
	for(int i=200;i<=560;i+=20)
	{
		left1=i;
		top1= 180;
		right1= 200;
		bottom1= 200;
		setcolor(WHITE);
		setfillstyle(1,YELLOW);
		rectangle(left,top,right,bottom);
		delay(40);
		bar(left1,top1,right1,bottom1);
	}
	delay(100);
	outtextxy(90,280,"PRESS ENTER TO CONTINUE");
	getch();
  }

// Function for welcome screen
  void mainscreen()
  {
	setbkcolor(CYAN);
	settextstyle(0,0,8);
	outtextxy(120,180,"WELCOME");
	delay(5000);
  }

// Function for exit screen
  void quit()
  {
	setbkcolor(CYAN);
	settextstyle(0,0,6);
	outtextxy(150,180,"GOODBYE");
	delay(5000);
	exit(0);
  }


  void main()
  {
	setgraph();
	mainscreen();
	cleardevice();
	int unlock;
	setbkcolor(CYAN);
	cleardevice();
	unlock=lock();
	if(unlock==2)
	{
		settextstyle(0,0,2);
		outtextxy(120,300,"CORRECT PASSWORD");
		delay(600);
		cleardevice();
		loading();
		cleardevice();
		setbkcolor(CYAN);
		gotoxy(10,10);
		cout<<"NOTE : PLEASE DO NOT PRESS ENTER AFTER CHOOSING THE OPTIONS IN MENU";
		delay(3900);
		do
		{
			cleardevice();
			setbkcolor(LIGHTBLUE);
			setcolor(YELLOW);
			settextstyle(0,0,3);
			outtextxy(50,60,"BUS MANAGEMENT SOFTWARE");
			setcolor(WHITE);
			settextstyle(0,0,2);
			outtextxy(100,180,"1.MAINTENANCE OF BUS RECORDS");
			delay(100);
			outtextxy(100,240,"2.CUSTOMER SERVICE");
			delay(100);
			outtextxy(100,300,"3.EXIT");
			delay(100);
			setcolor(YELLOW);
			outtextxy(50,180,"-->");
			int x1=180,ch1=1;
			char ch;
			while(1)
			{
				ch=getch();
				setcolor(BLACK);
				outtextxy(50,x1,"-->");
				if(ch==72 && ch1==1)
				{
					ch1=3;
					x1=300;
				}
				else if(ch==72 && ch1!=1)
				{
					ch1--;
					x1-=60;
				}
				else if (ch==80 && ch1==3)
				{
					ch1=1;
					x1=180;
				}
				else if (ch==80 && ch1!=3)
				{
					ch1++;
					x1+=60;
				}
				else if (ch==13)
					break;
				setcolor(YELLOW);
				outtextxy(50,x1,"-->");
			}
			switch(ch1)
			{
				case 1: maintenance();
					break;
				case 2: customer();
					break;
				case 3: cleardevice();
					setcolor(WHITE);
					quit();
				default: cout<<"\nInvalid Choice";
			}
		}while(1);
	  }
	else
	{
		setbkcolor(CYAN);
		settextstyle(0,0,2);
		delay(100);
		outtextxy(120,300,"INCORRECT PASSWORD");
		delay(200);
		outtextxy(120,400,"PRESS ENTER TO CONTINUE");
		getch();
		cleardevice();
		quit();
	}
	closegraph();
  }
