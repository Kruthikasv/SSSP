#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void shortest(int u,int edge_w[50][50],int vertex_w[50],int distance[],int n);
int choose_min(int distance[],int status[],int n);


int main(int argc, char *argv[])
{

  FILE *fp = fopen(argv[1], "r");
  int u = atoi(argv[2]);   //u is the starting vertex
  int i=0,j=1;
  int count;
  int num;
  int content[50];
  char *token;
  const char delimit[2] = " ";
  char str[100];
  int vertex_w[50];  //vertex_w[ ] is an array which holds weight of vertices
  int edge_w[50][50];  //edge_w[ ][ ] is an array  which holds edge weights
  int distance[50];    

  if (fp == NULL)
  {
     printf("File is not available \n");
     exit(0);
  }
 
  while(fgets(str,20,fp))
  {
      token = strtok(str, delimit);
      while( token != NULL )
      {
        num=atoi(token);
        content[i]=num;
        i++;
        token = strtok(NULL, delimit);
      }
  }
  
  int n=content[0];
  int m=content[1];
 
  for(i=1,j=3;i<=(2*n),j<=(2*n)+1;i++,j+=2)
  {
    vertex_w[i] = content[j];    
    count=j;
  }
 
  for(i=0;i<50;i++)
  {
    for(j=0;j<50;j++)
    {
       edge_w[i][j]=9999;
    }
  }
  
  for(i = count+1;i<=(3*m)+count;i+=3)
  {
      edge_w[content[i]][content[i+1]] = content[i+2];
      edge_w[content[i+1]][content[i]] = content[i+2];
  }


  for(i=1;i<=n;i++)
  {
      for(j=1;j<=n;j++)
      {
          if(i==j)
          {
              edge_w[i][j] = 0;
          }
      }
  }


  shortest(u,edge_w,vertex_w,distance,n);

  printf("\n\nThe shortest path of all vertices from starting vertex %d is :\n\n",u);
  for(j=1;j<=n;j++)
     printf("%d  ->  %d  =  %d\n",u,j,distance[j]);

   fclose(fp);
   return 0;

}



void shortest(int u,int edge_w[50][50],int vertex_w[50],int distance[],int n)
{
    int status[20];  // this variable stores the status of vertex ,ie., visited or not visited 
    int i,v,num;
    for(i=1;i<=n;i++)
    {
        status[i]=0;
        distance[i] = edge_w[u][i]+vertex_w[i]+vertex_w[u];
    }
    
    status[u] = 1;
    distance[u] = 0;
    num = 2;

    while(num <= n)
    {
        v = choose_min(distance,status,n); 
        status[v] = 1;
        num++;
        for(i=1;i<=n;i++)
        {
            if(((distance[v]+edge_w[v][i]+vertex_w[i]) < distance[i]) && (status[i]==0))
               {
                   distance[i] = distance[v]+ edge_w[v][i]+vertex_w[i];
               }
        }
    }
}


 int choose_min(int distance[],int status[],int n)
{
   int w,j=0, min=9999;
   for(w=1; w<=n;w++)
   {
      if((distance[w] < min) && (status[w]==0))
      {
         min = distance[w];
         j = w;
      }
    }
    return j;
}











