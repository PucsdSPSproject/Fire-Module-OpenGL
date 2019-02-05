int maximum(float [] ,int );
int minimum(float [] ,int );


int maximum(float x[],int len)
{
  int max=x[0],i;
  for(i=1;i<len;i++)
      if(x[i]>max)
         max=x[i];
  return max;
	  
}
int minimum(float x[],int len)
{
  int min=x[0],i;
  for(i=1;i<len;i++)
      if(x[i]<min)
         min=x[i];
  return min;
	  
}
