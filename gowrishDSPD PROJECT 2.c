#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char vehicle_type[100];
	char maker[100];
	int year_of_manufacture;
	char engine_no[100];
	char registration_no[100];
	unsigned int vehicle_price;
	int owners_ID;
}vehicle;

typedef struct{
	int owner_ID;
	char name[100];
	char fathername[100];
	char address[1000];
	int date_of_purchase[1000];
	int month_of_purchase[1000];
	int year_of_purchase[1000];
	double purchase_amount;
	vehicle own[1000];
	int vehicles,cars_count;
}Owner;
//initialize vehicle
void initialize_vehicle(vehicle *v)
{
	int i;
	for(i=0;i<1000;i++)
	{
		v[i].owners_ID=-1;
		strcpy(v[i].maker,"");
		v[i].year_of_manufacture=-1;
		strcpy(v[i].registration_no,"");
		strcpy(v[i].vehicle_type,"");
		v[i].vehicle_price=0;
		strcpy(v[i].engine_no,"");
	}
}
//initialize owner
void initialize_owner(Owner *p)
{
	int i,j;
	for(i=0;i<1000;i++)
	{
		p[i].owner_ID=-1;
		strcpy(p[i].name,"");
		strcpy(p[i].fathername,"");
		strcpy(p[i].address,"");
		p[i].purchase_amount=0;
		p[i].vehicles=0;
		p[i].cars_count=0;
		initialize_vehicle(p[i].own);
		for(j=0;j<1000;j++)
		{
			p[i].date_of_purchase[j]=-1;
			p[i].month_of_purchase[j]=-1;
			p[i].year_of_purchase[j]=-1;
		}
	}
}
//question no -1
int add(Owner *d,int index)
{
	Owner p;
	printf("Enter the owner ID :");
	scanf("%d",&p.owner_ID);
	printf("Enter the Owner name :");
	scanf("%s",p.name);
	printf("Enter the father's name :");
	scanf("%s",p.fathername);
	printf("Enter the address :");
	scanf("%s",p.address);
	int N=index,i,found=0;
	for(i=0;i<N&&found==0;i++)
	{
		if(d[i].owner_ID==p.owner_ID)
		{
			found=1;
		}	
	}
	if(found==1)
	{
		printf("The owner already exists \nTry again!\n");
	}
	else
	{
		d[N]=p;
		index=index+1;
		printf("The new owner details are added successfully.\n");
	}
	return index;
}
//question no -2
void add_new_car_to_owner(Owner *d,int index,int select)
{
	Owner p;
	int N=index;
	printf("Enter the ID of the owner who purchases new car : ");
	scanf("%d",&p.owner_ID);
	int i,found=0;
	for(i=0;i<N&&found==0;i++)
	{
		if(d[i].owner_ID==p.owner_ID)
		{
			found=1;
		}
	}
	if(found==1)
	{
		if(d[i].vehicles<5)
		{
			
			if(select==0)
			{
				printf("Enter the type of the vehicle based on number of wheels \n for example : \n if there are 5 wheeles enter 5wheeler : ");
				scanf("%s",d[i].own[d[i].vehicles+1].vehicle_type);
			}
			else
			{
				strcpy(d[i].own[d[i].vehicles+1].vehicle_type,"4wheeler");
			}
			printf("Enter the name of the maker ");
			scanf("%s",d[i].own[d[i].vehicles+1].maker);
			printf("Enter the name of the engine :");
			scanf("%s",d[i].own[d[i].vehicles+1].engine_no);
			printf("Enter the registration number :");
			scanf("%s",d[i].own[d[i].vehicles+1].registration_no);
			printf("Enter the year of manufacture : ");
			scanf("%d",&d[i].own[d[i].vehicles+1].year_of_manufacture);
			printf("Enter the price of the car : ");
			scanf("%d",&d[i].own[d[i].vehicles+1].vehicle_price);
			printf("Enter the date of purchase :");
			scanf("%d",&d[i].date_of_purchase[d[i].vehicles+1]);
			printf("Enter the month of purchase :");
			scanf("%d",&d[i].month_of_purchase[d[i].vehicles+1]);
			printf("Enter the year of purchase :");
			scanf("%d",&d[i].year_of_purchase[d[i].vehicles+1]);
			d[i].own[d[i].vehicles+1].owners_ID=d[i].owner_ID;
			d[i].purchase_amount+=d[i].own[d[i].vehicles+1].vehicle_price;
			d[i].vehicles+=1;
			if(strcmp(d[i].own[d[i].vehicles+1].vehicle_type,"4wheeler"))
			{
				d[i].cars_count+=1;
			}
		}
		else
		{
			printf("The owner already has 5 vehicles.\n");
		}
	}
	else
	{
		printf("The owner with ID %d doesn't exist please create his profile first\n",p.owner_ID);
	}
}
//question no -3
int delete_car(Owner *d,int index)
{
	int i,N=index,found=0,owner_index;
	vehicle input;
	printf("Enter the ID of the owner : ");
	scanf("%d",&input.owners_ID);
	for(i=0;i<N&&found==0;i++)
	{
		if(d[i].owner_ID==input.owners_ID)
		{
			found=1;
		}
	}
	if(found==1)
	{
		owner_index=i;
		printf("Enter the registration number of car : ");
		scanf("%s",input.registration_no);
		int flag=0;
		for(i=0;i<d[owner_index].vehicles&&flag==0;i++)
		{
			if(strcmp(input.registration_no,d[owner_index].own[i].registration_no)==0)
			{
				d[owner_index].purchase_amount-=d[owner_index].own[d[owner_index].vehicles-1].vehicle_price;
				d[owner_index].own[i]=d[owner_index].own[d[owner_index].vehicles-1];
				d[owner_index].date_of_purchase[i]=d[owner_index].date_of_purchase[d[owner_index].vehicles-1];
				d[owner_index].month_of_purchase[i]=d[owner_index].month_of_purchase[d[owner_index].vehicles-1];
				d[owner_index].year_of_purchase[i]=d[owner_index].year_of_purchase[d[owner_index].vehicles-1];
				strcpy(d[owner_index].own[d[owner_index].vehicles-1].engine_no,"");
				strcpy(d[owner_index].own[d[owner_index].vehicles-1].maker,"");
				strcpy(d[owner_index].own[d[owner_index].vehicles-1].registration_no,"");
				strcpy(d[owner_index].own[d[owner_index].vehicles-1].vehicle_type,"");
				d[owner_index].own[d[owner_index].vehicles-1].owners_ID=-1;
				d[owner_index].own[d[owner_index].vehicles-1].vehicle_price=0;
				d[owner_index].own[d[owner_index].vehicles-1].year_of_manufacture=0;
				d[owner_index].date_of_purchase[d[owner_index].vehicles-1]=-1;
				d[owner_index].month_of_purchase[d[owner_index].vehicles-1]=-1;
				d[owner_index].year_of_purchase[d[owner_index].vehicles-1]=-1;
				flag=1;
				d[owner_index].vehicles-=1;
				d[owner_index].cars_count-=1;
			}
		}
		if(flag==0)
		{
			printf("The car with given registration number doesn't exist with this owner\n");
		}
		else
		{
			if(d[owner_index].cars_count==0)
			{
				d[owner_index]=d[N-1];
				int j;
				for(j=0;j<d[N-1].vehicles;j++)
				{
					d[N-1].date_of_purchase[j]=-1;
					d[N-1].month_of_purchase[j]=-1;
					d[N-1].year_of_purchase[j]=-1;
				}
				d[N-1].owner_ID=-1;
				d[N-1].purchase_amount=0;
				d[N-1].cars_count=0;
				d[N-1].vehicles=0;
				strcpy(d[N-1].address,"");
				strcpy(d[N-1].name,"");
				strcpy(d[N-1].fathername,"");
				initialize_vehicle(d[N-1].own);
				index-=1;
				printf("The Owner is removed as 0 number of cars are present\n");	
			}
			else
			{
				printf("The car details only removed\n");
			}
		}
	}
	else
	{
		printf("The owner with given ID is not existing \n");
	}
	return index;
}
//question number -4
void list_cars(Owner *d,int index)
{
	Owner p;
	int N=index,j,i,k;
	vehicle v[100];
	printf("Enter the owner ID : ");
	scanf("%d",&p.owner_ID);
	int found=0;
	for(i=0;i<N&&found==0;i++)
	{
		if(d[i].owner_ID==p.owner_ID)
		{
			found=1;
		}
	}
	if(found==1)
	{
		k=0;
		for(j=0;j<d[i].vehicles;j++)
		{
			if(strcmp(d[i].own[j].vehicle_type,"4wheeler")==0)
			{
				v[k]=d[i].own[j];
				k++;
			}
		}
		int car_size=k;
		int p,q;
		for(p=0;p=car_size-1;p++)
		{
			for(q=0;q<car_size-1-p;q++)
			{
				if(v[q].year_of_manufacture>v[q+1].year_of_manufacture)
				{
					vehicle temp=v[q];
					v[q]=v[q+1];
					v[q+1]=temp;
				}
			}
		}
		for(p=0;p<car_size;p++)
		{
			printf("The year of manufature of car = %d\n",v[p].year_of_manufacture);
			printf("The maker of the car is %s\n",v[p].maker);
			printf("The engine number is %s\n",v[p].engine_no);
			printf("The registration number of the car is %s\n",v[p].registration_no);
			printf("The vehicle prize is %d\n",v[p].vehicle_price);
		}
	}
	else
	{
		printf("Please enter the existing owner ID\n");
	}
}
//question no -5
int rem_before_1990(Owner *d,int index)
{
	int n=index,i,j,count=0;
	for(i=0;i<index;i++)
	{
		int p=d[i].vehicles-1,rem=0;
		for(j=0;j<d[i].vehicles;j++)
		{
			if(strcmp(d[i].own[j].vehicle_type,"4wheeler")==0 && d[i].own[j].year_of_manufacture<1990)
			{
				d[i].purchase_amount-=d[i].own[j].vehicle_price;
				d[i].own[j]=d[i].own[p];
				d[i].date_of_purchase[i]=d[i].date_of_purchase[p];
				d[i].month_of_purchase[i]=d[i].month_of_purchase[p];
				d[i].year_of_purchase[i]=d[i].year_of_purchase[p];
				d[i].own[p].owners_ID=-1;
				d[i].own[p].vehicle_price=0;
				d[i].own[p].year_of_manufacture=-1;
				d[i].date_of_purchase[p]=-1;
				d[i].month_of_purchase[p]=-1;
				d[i].year_of_purchase[p]=-1;
				strcpy(d[i].own[p].engine_no,"");
				strcpy(d[i].own[p].maker,"");
				strcpy(d[i].own[p].registration_no,"");
				strcpy(d[i].own[p].vehicle_type,"");
				p=p-1;
				rem+=1;
				j=j-1;
			}
		}
		d[i].vehicles-=rem;
		d[i].cars_count-=rem;
		if(d[i].cars_count==0)
		{
			d[i]=d[n-1];
			int j;
			for(j=0;j<d[n-1].vehicles;j++)
			{
				d[n-1].date_of_purchase[j]=-1;
				d[n-1].month_of_purchase[j]=-1;
				d[n-1].year_of_purchase[j]=-1;
			}
			d[n-1].owner_ID=-1;
			d[n-1].purchase_amount=0;
			d[n-1].cars_count=0;
			d[n-1].vehicles=0;
			strcpy(d[n-1].address,"");
			strcpy(d[n-1].name,"");
			strcpy(d[n-1].fathername,"");
			initialize_vehicle(d[n-1].own);
			n=n-1;
			i=i-1;
		}
	}
	index=n;
	printf("Removed all cars whose year of manufacture is before 1990\n");
	return index;
}
//question no -6
void find_maximum(Owner *d,int index)
{
	int max1=0,max2=-1,n=index,i;
	for(i=0;i<index;i++)
	{
		if(max1<d[i].vehicles)
		{
			max2=max1;
			max1=d[i].vehicles;
		}
		else if(max1>d[i].vehicles && max2<d[i].vehicles)
		{
			max2=d[i].vehicles;
		}
	}
	printf("The max number of vehicles are possed by the owner/owners is/are %d \nThe list of the owner /owners : \n",max1);
	for(i=0;i<index;i++)
	{
		if(d[i].vehicles==max1)
		{
			printf("The owner ID : %d and Name : %s\n",d[i].owner_ID,d[i].name);
		}
	}
	printf("The second max number of vehicles are possed by the owner/owners is/are %d \nThe list of the owner /owners : \n",max2);
	for(i=0;i<index;i++)
	{
		if(d[i].vehicles==max2)
		{
			printf("The owner ID : %d and Name : %s\n",d[i].owner_ID,d[i].name);
		}
	}
}
//question no -7
void owners_purchased_more_than_1_2wheeler(Owner *d,int index)
{
	int i,j;
	int count,flag=0;
	for(i=0;i<index;i++)
	{
		int k=0,l;
		count=0;
		for(j=0;j<d[i].vehicles&&count==0;j++)
		{
			if((strcmp(d[i].own[j].vehicle_type,"2wheeler")==0))
			{
				for(l=0;l<j&&count==0;l++)
				{
					if(d[i].year_of_purchase[j]==d[i].year_of_purchase[l] && strcmp(d[i].own[l].vehicle_type,"2wheeler")==0)
					{
						count=count+1;
						flag=1;
					}
				}
			}
		}
		if(count==1)
		{
			printf("The owner with ID : %d purchased more than 1 2wheeler vehicles in same year\n",d[i].owner_ID);
		}
	}
	if(flag==0)
	{
		printf("No owner purchased more than 1 2wheeler vehicles in same year\n");
	}
}
//question no -8
void costilest_vehicle(Owner *d,int index)
{
	int max_cost=0,i,n,flag=0,j;
	printf("Enter the Owner ID :");
	scanf("%d",&n);
	for(i=0;i<index&&flag==0;i++)
	{
		if(n==d[i].owner_ID)
		{
			flag=1;
		}
	}
	if(flag==0)
	{
		printf("The owner ID doesn't exist \n");
	}
	else
	{
		for(j=0;j<d[i].vehicles;j++)
		{
			if(max_cost<d[i].own[j].vehicle_price)
			{
				max_cost=d[i].own[j].vehicle_price;
			}
		}
		printf("The cost of the costliest vehicle by the owner with ID : %d is %d",d[i].owner_ID,max_cost);
	}
}
//question -9
void list_owner_more_than_1_of_same_brand(Owner *d,int index)
{
	char brand[100];
	int i,j,flag=0;
	printf("Enter the name of the brand :");
	scanf("%s",brand);
	for(i=0;i<index;i++)
	{
		int count=0;
		for(j=0;j<d[i].vehicles;j++)
		{
			if(strcmp(d[i].own[j].maker,brand)==0)
			{
				count=count+1;
			}
		}
		if(count>=2)
		{
			printf("The owner with ID : %d have more than 1 vehicle of the brand given\n",d[i].owner_ID);
			flag=1;
		}
	}
	if(flag==0)
	{
		printf("No owner posses more than 1 vehicle of the given brand");
	}
}
//question no -10
void list_of_owners_in_particular_year(Owner *d,int index)
{
	int year;
	printf("Enter the year : ");
	scanf("%d",&year);
	int flag=0,i,j;
	for(i=0;i<index;i++)
	{
		for(j=0;j<d[i].vehicles;j++)
		{
			if((strcmp(d[i].own[j].vehicle_type,"3wheeler")==0)&&(d[i].year_of_purchase[j]==year))
			{
				printf("The owner with owner ID :%d\n",d[i].owner_ID);
				flag=1;
			}
		}
	}
	if(flag==0)
	{
		printf("No one purchased the 3wheeler in the year %d",year);
	}
}

int main()
{
	int select,status=0,add_index=0;
	Owner *details,p;
	details = (Owner*)malloc(sizeof(Owner)*1000);
	
	do
	{
		printf("Press 0:To add new vehicle to the owners\n");
		printf("Press 1:To add new owner\n");
		printf("Press 2:To add new car to the owners\n");
		printf("Press 3:To add delete car to the owner\n");
		printf("Press 4:To list cars of a particular owner in ascending order\n");
		printf("Press 5:To delete all cars that are manufactured before 1990\n");
		printf("Press 6:To Find the maximum and 2nd maximum number of vehicles\n");
		printf("Press 7:To Find the owners who purchased more than 1 2wheeler vehicles\n");
		printf("Press 8:To Find the costiest vehicle with a particular owner\n");
		printf("Press 9:To Find the more than one vehicle of particular brand\n");
		printf("Press 10:To Find the owners who purchased 3wheeler in a particular year\n");
		printf("Press -1:To exit from the code\n");
		printf("Please always enter the data in small letters and without gaps for the names and addresses\n");
		scanf("%d",&select);
		if(select==-1)
		{
			printf("You asked to exit from the program\n");
			status=1;
		}
		else if(select==0)
		{
			if(add_index==0)
			{
				printf("No data of owner is stored please enter data of owner\n");
			}
			else
			{
				add_new_car_to_owner(details,add_index,select);
			}
		}
		else if(select==1)
		{
			if(add_index==0)
			{
				printf("No data of owner is stored please enter data of owner\n");
			}
			else
			{
				add_index = add(details,add_index);
			}
		}
		else if(select==2)
		{
			if(add_index==0)
			{
				printf("No data of owner is stored please enter data of owner\n");
			}
			else
			{
				add_new_car_to_owner(details,add_index,select);
			}
		}
		else if(select==3)
		{
			if(add_index==0)
			{
				printf("No data of owner is stored please enter data of owner\n");
			}
			else
			{
				add_index=delete_car(details,add_index);
			}
		}
		else if(select==4)
		{
			if(add_index==0)
			{
				printf("No data of owner is stored please enter data of owner\n");
			}
			else
			{
				list_cars(details,add_index);
			}
		}
		else if(select==5)
		{
			if(add_index==0)
			{
				printf("No data of owner is stored please enter data of owner\n");
			}
			else
			{
				add_index=rem_before_1990(details,add_index);
			}
		}
		else if(select==6)
		{
			if(add_index==0)
			{
				printf("No data of owner is stored please enter data of owner\n");
			}
			else
			{
				find_maximum(details,add_index);
			}
		}
		else if(select==7)
		{
			if(add_index==0)
			{
				printf("No data of owner is stored please enter data of owner\n");
			}
			else
			{
				owners_purchased_more_than_1_2wheeler(details,add_index);
			}
		}
		else if(select==8)
		{
			if(add_index==0)
			{
				printf("No data of owner is stored please enter data of owner\n");
			}
			else
			{
				costilest_vehicle(details,add_index);
			}
		}
		else if(select==9)
		{
			if(add_index==0)
			{
				printf("No data of owner is stored please enter data of owner\n");
			}
			else
			{
				list_owner_more_than_1_of_same_brand(details,add_index);
			}
		}
		else if(select==10)
		{
			if(add_index==0)
			{
				printf("No data of owner is stored please enter data of owner\n");
			}
			else
			{
				list_of_owners_in_particular_year(details,add_index);
			}
		}
		else
		{
			printf("Please select the number from 0 to 10 only\n");
		}
	}while(status==0);
	free(details);
	details = NULL;
}
