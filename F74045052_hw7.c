#include <stdio.h>
#include <stdlib.h>

void early(int *ee, int n, int AOE[][n]);
void late(int *le, int *ee, int n, int AOE[][n]);
void eandl(int *e, int *l, int *ee, int *le, int n, int AOE[][n]);
void slack(int *e, int *l, int n, int *sk);
int main()
{
  int n=0, num, i=0, j=0;
  int tmp;
  FILE *fin;

  /***Read the file***/

  fin = fopen("Sample_input.txt","r");
  if(fin == NULL)
  {
    printf("File opening error!");
    exit(1);
  }
  
  fscanf(fin,"%d",&n);
  
  int AOE[n][n], ee[n], le[n];
  
  for(i=0;i<n;i++)
  {
    ee[i] = 0;
    le[i] = 0;
  }
  
  i=0; 
  
  while(fscanf(fin,"%d%*c",&tmp) != EOF)
  {
    AOE[i][j] = tmp;
    j++;
    if(tmp != 0)
    {
      num++;
    }
    if(j >=n)
    {
      i++;
      j = 0;
    }
    if(i>=n)
    {
      break;
    }
  }
  fclose(fin);

  int e[num], l[num], sk[num];

  early(ee,n,AOE);  //culculate ee
  late(le,ee,n,AOE);  //culculate le
  eandl(e,l,ee,le,n,AOE); //culculate e and l
  slack(e,l,num,sk);  //culculate l-e
 
 /*
  for(i=0;i<n;i++)
  {
    printf("ee[%d] = %d\n",i,ee[i]);
  }
  for(i=0;i<n;i++)
  {
    printf("le[%d] = %d\n",i,le[i]);
  }
  for(i=0;i<num;i++)
  {
    printf("e[%d] = %d\n",i,e[i]);
  }
  for(i=0;i<num;i++)
  {
    printf("l[%d] = %d\n",i,l[i]);
  }
  for(i=0;i<num;i++)
  {
    printf("slack[%d] = %d\n",i,sk[i]);
  }
  */


  /***print out the result***/
  printf("activity\tearly time\tlate time\tslack\n");
  printf("a[ ]\t\te\t\tl\t\tl-s\t\t\n");
  for(i=0;i<num;i++)
  {
    printf("a[%d]\t\t%d\t\t%d\t\t%d\n",i+1,e[i],l[i],sk[i]);
  }
}

/***culculate ee***/
void early(int *ee, int n,int AOE[][n])
{
  int i, j;
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    { 
      if(AOE[i][j] != 0 && ee[i]+AOE[i][j] > ee[j])
      {
        ee[j] = ee[i] + AOE[i][j];
      }
    }
  }
}

/***culculate le***/
void late(int *le, int *ee, int n, int AOE[][n])
{
  int i, j, tmp = 0;
  le[n-1] = ee[n-1];
  for(i=n-1;i>=0;i--)
  {
    for(j=n-1;j>=0;j--)
    {
      if(AOE[i][j] != 0 && AOE[i][j] - le[j] < le[i])
      {
        le[i] = le[j] - AOE[i][j];
      }
    }
  }
}

/***culculate e and l***/
void eandl(int *e, int *l, int *ee, int *le, int n, int AOE[][n])
{
  int i, j, num=0;
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
    {
      if(AOE[i][j] !=0)
      {
        e[num] = ee[i];
        l[num] = le[j] - AOE[i][j];
        num++;
      }
    }
}

/*** l - e ***/
void slack(int *e, int *l, int n, int *sk)
{
  int i;
  for(i=0;i<n;i++)
  {
    sk[i] = l[i] - e[i];
  }
}
