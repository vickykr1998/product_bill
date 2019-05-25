#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <sstream>



using namespace std;

int rec_flag=0,no=0;
char rec_ind[5];
struct product
{
	char pno[20];
	char name[20];
	char price[20];
    char dis[20];
	char ind[5];
}pr[20];

struct index
{
	char ind[5];
	char pno[20];
}inp[20],temp;
//Function to sort the products in index file
void sort_index()
{
	int i,j;

	for(i=0;i<no-1;i++)
	for(j=0;j<no-i-1;j++)
	if(strcmp(inp[j].pno,inp[j+1].pno)>0)
	{
		temp=inp[j];
		inp[j]=inp[j+1];
		inp[j+1]=temp;
	}
}
//Function to Show details of particular product
void retrive_record(char *ind)
{
	for(int i=0;i<no;i++)
	{
		if(strcmp(pr[i].ind,ind)==0)
		{
			strcpy(rec_ind,ind);
			rec_flag=1;
			cout<<"Record found:\n";
            cout<<"Index\tProduct No.\tName\tPrice\tDiscount\n";
            cout<<pr[i].ind<<"\t"<<pr[i].pno<<"\t\t"<<pr[i].name<<"\t"<<pr[i].price<<"\t"<<pr[i].dis<<"\n";
			return;
		}
	}
}
//Function to display all all product details
void display_all(){
    cout<<"Index\tProduct No.\tName\tPrice\tDiscount\n";
	for(int i=0;i<no;i++)
		cout<<pr[i].ind<<"\t"<<pr[i].pno<<"\t\t"<<pr[i].name<<"\t"<<pr[i].price<<"\t"<<pr[i].dis<<"\n";
}

//Function to Search the index of the product
int search_index(char *pno)
{
	int flag=0;
	for(int i=0;i<no;i++)
	{
		if(strcmp(inp[i].pno,pno)==0)
		{
			retrive_record(inp[i].ind);
			flag=1;
		}
	}
	if(flag)
		return 1;
	else
		return -1;
}
//Function to Search the product in list
int search_id(char *pno,int j)
{
	int flag=0;
	for(int i=0;i<j;i++)
	{
		if(strcmp(pr[i].pno,pno)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag)
		return 1;
	else
		return -1;
}

//Function to Delete  product details
void delet(char *pno)
{
	rec_flag=0;
	int fr=0;
	search_index(pno);
	if(!rec_flag)
	{
		cout<<"Deletion failed.Record not found\n";
		return;

	}
	for(int i=0;i<no;i++)
	{
		if(strcmp(pr[i].ind,rec_ind)==0)
		{
			fr=i;
			break;
		}
	}
	for(int i=fr;i<no-1;i++)
	{
		pr[i]=pr[i+1];
		char str[3];
		sprintf(str,"%d",i);
		strcpy(pr[i].ind,str);
	}
	no--;
	fstream f1,f2;
    f1.open("product.txt",ios::out);
	f2.open("index.txt",ios::out);
	for(int i=0;i<no;i++)
	{
		strcpy(inp[i].pno,pr[i].pno);
		strcpy(inp[i].ind,pr[i].ind);
	}
	sort_index();
	for(int j=0;j<no;j++)
	{
	    f1<<pr[j].ind<<"|"<<pr[j].pno<<"|"<<pr[j].name<<"|"<<pr[j].price<<"|"<<pr[j].dis<<"\n";
		f2<<inp[j].pno<<"|"<<inp[j].ind<<"\n";
		
	}
	f1.close();
	f2.close();
	cout<<"Deletion successful\n";
	
}
//function to modify product details
void modify_product() 
{
    int n, found = -1;
    char pno[20];
	char name[20];
	char price[20],dis[20];
    fstream fp,f;
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Product Number of The Product";
    cin >>pno ;
    found=search_index(pno);
    if (found == -1)
        cout << "\n\n Record Not Found ";
    else
    {
    	for(int i=0;i<no;i++)
    		if(strcmp(pr[i].pno,pno)==0)
    		{
    			found=i;
    			break;
    		}
    	cout<<"enter new details\nProduct No.\n";
    	cin>>pno;
    	cout<<"Product Name\n";
    	cin>>name;
    	cout<<"Price\n";
    	cin>>price;
    	cout<<"Discount\n";
    	cin>>dis;
    	char str[3];
		sprintf(str,"%d",found);
		strcpy(pr[found].ind,str);
    	strcpy(pr[found].pno,pno);
    	strcpy(pr[found].name,name);
    	strcpy(pr[found].price,price);
    	strcpy(pr[found].dis,dis);
        for(int i=0;i<no;i++)
        {
            strcpy(inp[i].ind,pr[i].ind);
            strcpy(inp[i].pno,pr[i].pno);
        }
        sort_index();
        fp.open("product.txt",ios::out);
        f.open("index.txt",ios::out);
        for(int i=0;i<no;i++){
        	fp<<pr[i].ind<<"|"<<pr[i].pno<<"|"<<pr[i].name<<"|"<<pr[i].price<<"|"<<pr[i].dis<<"\n";
            f<<inp[i].pno<<"|"<<inp[i].ind<<"\n";
        }
    	cout<<"product details updated\n";
    	fp.close();
    }
}
//Function to Display menu of the products
void menu(){
	  cout<<"Index\tProduct No.\tName\tPrice\n";
	for(int i=0;i<no;i++)
	{
            cout<<pr[i].ind<<"\t"<<pr[i].pno<<"\t\t"<<pr[i].name<<"\t"<<pr[i].price<<"\n";
	}
}
//***************************************************************
// function to place order and generating bill for Products
//****************************************************************
void place_order() 
{
    int  quan[50], c = 0;
    float amt=0, damt=0, total = 0;
    char order_arr[50][20];
    fstream f;
    f.open("bill.txt",ios::out|ios::app);
    char ch = 'Y',na[20];
    time_t my_time = time(NULL);
    cout<<"enter customer name\n";
    cin>>na;
    f<<na<<"\t\t"<<ctime(&my_time)<<"\n\n";
    menu();
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    do 
    {
        cout << "\n\nEnter The Product No. Of The Product : ";
        cin >> order_arr[c];
        cout << "\nQuantity in number : ";
        cin >> quan[c];
        c++;
        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You For Placing The Order\n\n";
    cout << "\n\n******************************** INVOICE ************************\n";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n ";
    for (int x = 0; x <= c; x++)
    {

        for(int i=0;i<no;i++)
        {
            if (strcmp(pr[i].pno,order_arr[x])==0) 
            {
                amt = atoi(pr[i].price) * quan[x];            //type conversion from char to integer for price
                damt = amt - (amt * atoi(pr[i].dis)/ 100);   //type conversion from char to integer for discount
                cout << "\n" << order_arr[x] << "\t" << pr[i].name<<
                    "\t" << quan[x] << "\t\t" << pr[i].price << "\t" << amt << "\t\t" << damt;
                total += damt;
                f<<pr[i].pno<<"|"<<pr[i].name<<"|"<<quan[x]<<"|"<<pr[i].price<<"|"<<amt<<"|"<<damt<<"\n"; //storing details to bill.txt file
            }   
        } 
    }
    f<<"total amount = "<<total<<"\n\n";
     f.close();
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
}

//Function to enter new product
void write_product(){
	 int n;
    char pno[20];
	char name[20],ind[5];
	char price[10],dis[20];
	fstream f;
	f.open("product.txt",ios::out|ios::app);
	cout<<"enter the Number of product\n";
	cin>>n;
	for(int i=no;i<no+n;i++){
	     label: cout<<"enter "<<i+1<<" product details:\n";
	     cout<<"enter product number  :";
	     cin>>pr[i].pno;
	     cout<<"\nenter product name  :";
	     cin>>pr[i].name;
	     cout<<"\nenter product price  :";
	     cin>>pr[i].price;
	     cout<<"\nenter product discout  :";
	     cin>>pr[i].dis;
	     int q = search_id(pr[i].pno,i);
					if(q==1)
					{
						cout<<"Duplicate value\n";
						cout<<"enter again:\n";
						goto label;
					}
					f<<i<<"|"<<pr[i].pno<<"|"<<pr[i].name<<"|"<<pr[i].price<<"|"<<pr[i].dis<<"\n";

	}
	no=no+n;
	f.close();
	fstream f1,f2;
	f1.open("product.txt",ios::in);
	f2.open("index.txt",ios::out);
	for(int i=0;i<no;i++){
		f1.getline(ind,5,'|');
		f1.getline(pno,20,'|');
		f1.getline(name,20,'|');
		f1.getline(price,20,'|');
		f1.getline(dis,20,'\n');
		strcpy(pr[i].ind,ind);
		strcpy(inp[i].ind,ind);
	     strcpy(inp[i].pno,pno);
	}
	sort_index();
	for(int i=0;i<no;i++){
		f2<<inp[i].pno<<"|"<<inp[i].ind<<"\n";
	}
	f1.close();
	f2.close();

}

//***************************************************************
// ADMINSTRATOR MENU FUNCTION
//****************************************************************
void men(){
    int ch2;
    do{
        getch();
    system("CLS");
    char n[20];
    cout << "\n\n\n\tADMIN MENU";
    cout << "\n\n\t1.CREATE PRODUCT";
    cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
    cout << "\n\n\t3.QUERY ";
    cout << "\n\n\t4.MODIFY PRODUCT";
    cout << "\n\n\t5.DELETE PRODUCT";
    cout << "\n\n\t6.VIEW PRODUCT MENU";
    cout << "\n\n\t7.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-7) ";
    cin>>ch2;
    switch (ch2) 
    {
    case 1:
        write_product();
        break;
    case 2:
        display_all();
        break;
    case 3:
        char num[20];
        cout << "\n\n\tPlease Enter The Product No. ";
        cin >> num;
        search_index(num);
        break;
    case 4:
        modify_product();
        break;
    case 5:
         cout<<"enter the product number\n";
         cin>>n;
        delet(n);
        break;
    case 6:
        menu();
        break;
    case 7:
        break;
    default:
        cout << "\a";
        men();
    }
}while(ch2 !=7);
}

//***************************************************************
// THE MAIN FUNCTION OF PROGRAM
//****************************************************************
int main() 
{
    int chi;
    fstream f1,f2;
    f1.open("product.txt",ios::in);//opening file to read the data 
    f2.open("index.txt",ios::out);
    for(int i=0;i<100;i++){
        f1.getline(pr[i].ind,5,'|');
        int m=atoi(pr[i].ind);  //type conversion from char to integer
        if(i==m)
            no++;
        else
            break;
        f1.getline(pr[i].pno,20,'|');
        f1.getline(pr[i].name,20,'|');
        f1.getline(pr[i].price,10,'|');
        f1.getline(pr[i].dis,5,'\n');
        strcpy(inp[i].ind,pr[i].ind);
        strcpy(inp[i].pno,pr[i].pno);
        
    }
    sort_index();
    for(int i=0;i<no;i++)
        f2<<inp[i].pno<<"|"<<inp[i].ind<<"\n";
    f1.close();
    f2.close();
    do{
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. CUSTOMER";
        cout << "\n\n\t02. ADMINISTRATOR";
        cout << "\n\n\t03. EXIT";
        cin>>chi;
        switch (chi) 
        {
        case 1:
            place_order();
            break;
        case 2:
             men();
             break;
        case 3:
        cout<<"thanks for using the software\n";
            exit(0);
        default:
            cout << "enter valid key\n";
            break;  
    }
}while(chi<=3);
       return 0;
} 


