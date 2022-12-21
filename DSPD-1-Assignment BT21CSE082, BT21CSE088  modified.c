#include <stdio.h>
#include <math.h>
#include <string.h>

#define STATION_LEN 10
#define LEN 100

typedef struct
{
      float sky_view_factor;
      float vegetation_density_ratio[LEN];
      float population_density;
      int pervious_surface_fraction;
      int impervious_surface_fraction;
      char station_status[STATION_LEN];
      int distance[LEN];
}urban_parameters;
urban_parameters Urban_parameters [LEN];

typedef struct 
{
      float air_temperature[LEN];
      float relative_humidity[LEN];
}weather_parameters;
weather_parameters Weather_parameters [LEN];

int n;
void initiaze( urban_parameters Urban_parameters [], weather_parameters Weather_parameters[],int n)
{
	int i,j,k;
	
      for (  i = 0; i < n; i++)
      {
            Urban_parameters[i].sky_view_factor = 0;
            Urban_parameters[i].population_density = 0;
            Urban_parameters[i].pervious_surface_fraction = 0;
            Urban_parameters[i].impervious_surface_fraction = 0;
            Urban_parameters[i].station_status[0] = '\0';
      }
      for ( j = 0; j < n; j++)
      {
            for ( k = 0; k < 30; k++)
            {
                  Urban_parameters[j].vegetation_density_ratio[k] = 0;
                  Urban_parameters[j].distance[k] = 0;
                  Weather_parameters[j].air_temperature[k] = 0;
                  Weather_parameters[j].relative_humidity[k] = 0;
            }
      }
}
int insert_update( urban_parameters Urban_parameters [],  weather_parameters Weather_parameters[],int n)
{
	int i,k,j;
      for ( i = 0; i < n; i++)
      {
            printf("Enter the urban parameters of station-%d", i);
            scanf("%d", &Urban_parameters[i].sky_view_factor);
            scanf("%d", &Urban_parameters[i].population_density);
            scanf("%d", &Urban_parameters[i].pervious_surface_fraction);
            scanf("%d", &Urban_parameters[i].impervious_surface_fraction);
            scanf("%s", &Urban_parameters[i].station_status[STATION_LEN]);
            scanf("%d", &Urban_parameters[i].distance[LEN]);
            for( k=0; k<30; k++)
            {
                  scanf("%d", &Urban_parameters[j].distance[k]);
                  scanf("%d", &Urban_parameters[j].vegetation_density_ratio[k]);
            }
      }

      for ( j = 0; j < n; j++)

      {
            printf("Enter the weather parameters for a month of station-%d", j);
            for ( k = 0; k < 30; k++)
            {
                  scanf("%d", &Weather_parameters[j].air_temperature[k]);
                  scanf("%d", &Weather_parameters[j].relative_humidity[k]);
            }
      }
}
// question 1
int  count[LEN], max = 0,p,j,k;
    float avg_temp[LEN],tot_avg_temp;
void question1( weather_parameters Weather_parameters1[],int n)
{
	
	for (p=0; p<n; p++)
	{
      count[p] = 0;
      avg_temp[p] = 0;
	}
      // finding highest heat degree days
      for ( j = 0; j < n; j++)
      {
            for ( k = 0; k < 30; k++)
            {
                  avg_temp[j] = avg_temp[j] + (Weather_parameters1[j].air_temperature[k]) / 30;//finding avg temp for each station
            }
            tot_avg_temp = tot_avg_temp + (avg_temp[j]) / n;//finding avg city temp
      }
      for ( j = 0; j < n; j++)
      {
            for ( k = 0; k < 30; k++)
            {
                  if (Weather_parameters1[j].air_temperature[k] > tot_avg_temp)
                  {
                        count[j]++;//finding no.of days with temp higher than avg city temp
                  }
            }
            if (count[j] > max)
            {
                  max = count[j];
            }
      }
      printf("stations with highest heat degree days are- ");
      for ( j = 0; j < n; j++)
      {
            if (max == count[j])
            {
                  printf("station-%d, ", j);
            }
      }
}

// question 2


void question2( weather_parameters Weather_parameters2 [],  urban_parameters Urban_parameters2[], int x)
{
	int  rur_loc,  count1,j,p;
	float min_temp = 100.0,min = 1000.0;
	char name1[20]="urban";
	char name2[20]="rural";
      if (strcmp(Urban_parameters2[x].station_status ,name1 )==0)//checking whether station is urban
      {
            for ( j = 0;j!=x && j < n; j++)
            {
                  if (strcmp(Urban_parameters2[j].station_status , name2)==0)//checking whether station is rural
                  {
                        if (min > Urban_parameters2[x].distance[j])//finding nearby rural station
                        {
                              min = Urban_parameters2[x].distance[j];
                              rur_loc = j;
                        }
                        // finding the difference between temparatures of station_x and station_rur_loc
                        for ( p = 0; p < 30; p++)
                        {
                              if (min_temp > abs(Weather_parameters2[x].air_temperature[p] - Weather_parameters2[rur_loc].air_temperature[p]))
                              {
                                    min_temp = Weather_parameters2[x].air_temperature[p] - Weather_parameters2[rur_loc].air_temperature[p];
                                    count1 = 1;
                              }
                              else if (min_temp == abs(Weather_parameters2[x].air_temperature[p] - Weather_parameters2[rur_loc].air_temperature[p]))
                              {
                                    count1++;//counting the total thermally comfortable days 
                              }
                        }
                  }
            }
            printf("the thermally comfortable days of station-%d are %d", x, count1);
      }
      else
      {
            printf("entered station is rural");
      }
}

// question 3
int  date[LEN], s[LEN],i,j,k,l;
float ratio[LEN];
void question3( weather_parameters Weather_parameters3[],  urban_parameters Urban_parameters3[],int n)
{

      for ( i = 0; i < n; i++)
      {
            s[i] = 0;//finding the count at perticular station
      }
      for ( j = 0; j < n; j++)
      {
            //picking up dates air temp > avg city temp
            for ( k = 0; k < 30; k++)
            {
                  if (Weather_parameters3[j].air_temperature[k] > tot_avg_temp)
                  {
                        ratio[i] = Urban_parameters3[j].vegetation_density_ratio[k];
                        date[s[j]] = k;
                        s[j]++;
                  }
            }
      }

      int sorted = 0, tem, tem1;
      //sorting the picked dates acc to vegetation density ratio
      for (j = 0; j < n; j++)
      {
            for ( k = 0; k < s[j] - 1; k++)
            {
                  sorted = 1;
                  for ( l = 0; l < s[j] - k - 1 && sorted == 1; l++)
                  {
                        if (ratio[l] < ratio[l + 1])
                        {
                              tem = ratio[l];
                              ratio[l] = ratio[l + 1];
                              ratio[l + 1] = tem;
                              tem1 = date[l];
                              date[l] = date[l + 1];
                              date[l + 1] = tem1;
                              sorted = 0;
                        }
                  }
            }
      }
      for ( j = 0; j < n; j++)
      {
            printf("the dates of station-%d are", j);
            for ( k = 0; k < s[j]; k++)
            {
                  printf("%d", date[k]);
            }
      }
}

// question 4
int min1, loc, m = 0,i;
//finding the max temp of particular station
float max_temp(int y)
{
      int max = 0;
      for ( i = 0; i < 30; i++)
      {
            if (Weather_parameters[y].air_temperature[i] > max)
            {
                  max = Weather_parameters[y].air_temperature[i];
            }
      }
      return max;
}

void question4 (urban_parameters Urban_parameters5[],  weather_parameters Weather_parameters5[], int k)
{
      int tem, loc[LEN],q,j,p,Loc=0,loc1,r;
      for ( q = 0; q < n; q++)
      {
            loc[q] = q;
      }
      //finding out the first k population density stations in dcreasing order
      //by using sorting
      for ( j = 0; j < k; j++)
      {
            min1 = Urban_parameters5[j].population_density;
            Loc = j;
            for ( p = j + 1; p < n; p++)
            {
                  if (min1 > Urban_parameters5[p].population_density)
                  {
                        min1 = Urban_parameters5[p].population_density;
                        Loc = p;
                        tem = loc[j];
                        loc[j] = loc[p];
                        loc[p] = tem;
                  }
                  else if (min1 == Urban_parameters5[p].population_density)
                  {
                        if (max_temp(j) < max_temp(p))
                        {
                              tem = loc[j];
                              loc[j] = loc[p];
                              loc[p] = tem;
                        }
                  }
                  Urban_parameters5[Loc].population_density = Urban_parameters5[j].population_density;
                  Urban_parameters5[j].population_density = min1;
            }
      }
      printf("Top %d stations with minimum population density with highest maximum temperature are ", k);
      for ( r = 0; r < k; r++)
      {
            printf("station-%d\n", loc[r]);
      }
}

//question 5
int rural_loc,j,i;
float heat_island_intensity,mini=1000.0;
void question5( urban_parameters Urban_parameters6[], weather_parameters Weather_parameters6[])
{
	char name3[20]="urban";
	char name4[20]="rural";
      for( i=0;i<n;i++)
      {
      	
            if(strcmp(Urban_parameters6[i].station_status ,name3 )==0)
            {
                  for(j=0;j!=i && j<n;j++)
                  {
                        if(strcmp(Urban_parameters6[i].station_status ,name4 )==0)
                        {    
                              if (mini > Urban_parameters6[i].distance[j])
                              {
                                    mini = Urban_parameters6[i].distance[j];
                                    rural_loc = j;
                              } 
                              else if(mini == Urban_parameters6[i].distance[j])//checking whether station has 2 nearby ruaral stations
                              {
                                    if(Urban_parameters6[j].pervious_surface_fraction>Urban_parameters6[rural_loc].pervious_surface_fraction)
                                    {
                                          rural_loc=j;
                                    }
                              }
                        }
                  }
                  heat_island_intensity = avg_temp[i]-avg_temp[rural_loc];
            }
            printf("The heat island intensity of station-%d is %f",i,heat_island_intensity);
      }
}

int main()
{
      int x,k;
      printf("enter the value of n ");
      scanf("%d",&n);
      initiaze(  Urban_parameters,   Weather_parameters, n);
      insert_update(  Urban_parameters,   Weather_parameters, n);
      question1(  Weather_parameters, n);
      printf("enter the value of x");
      scanf("%d",&x);
      question2(  Weather_parameters,   Urban_parameters, x);
      question3(  Weather_parameters,   Urban_parameters, n);
      printf("enter the value of k");
      scanf("%d",&k);
      question4(  Urban_parameters,  Weather_parameters, k);
      question5(  Urban_parameters,   Weather_parameters);

}
