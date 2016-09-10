//This is a predefined algorithm.
//We have made use of previously written code.
//(Minimum) Assignment Problem by Hungarian Algorithm
//taken from Knuth's Stanford Graphbase
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF (0x7FFFFFFF)

#define verbose (1)
int n;
double **new_matrix;
char **Result;  // used as boolean

void hungarian()
{
int i,j;
int false=0,true=1;

unsigned int m=n;
int k;
int l;
double s;
int col_mate[n];
memset(col_mate,0,sizeof(col_mate));
int row_mate[n];
memset(row_mate,0,sizeof(row_mate));
int parent_row[n];
memset(parent_row,0,sizeof(parent_row));
int unchosen_row[n];
memset(unchosen_row,0,sizeof(unchosen_row));
int t;
int q;
double row_dec[n];
memset(row_dec,0,sizeof(row_dec));
double col_inc[n];
memset(col_inc,0,sizeof(col_inc));
double slack[n];
memset(slack,0,sizeof(slack));
int slack_row[n];
memset(slack_row,0,sizeof(slack_row));
int unmatched;
double cost=0;
int row, col;

for (i=0;i<n;++i)
  for (j=0;j<n;++j)
    Result[i][j]=false;

// Begin subtract column minima in order to start with lots of zeroes 12
// printf("Using heuristic\n");
for (l=0;l<n;l++)
{
  s=new_matrix[0][l];
  for (k=1;k<n;k++)
    if (new_matrix[k][l]<s)
      s=new_matrix[k][l];
  cost+=s;
  if (s!=0)
    for (k=0;k<n;k++)
      new_matrix[k][l]-=s;
}
// End subtract column minima in order to start with lots of zeroes 12

// Begin initial state 16
t=0;
for (l=0;l<n;l++)
{
  row_mate[l]= -1;
  parent_row[l]= -1;
  col_inc[l]=0;
  slack[l]=INF;
}
for (k=0;k<m;k++)
{
  s=new_matrix[k][0];
  for (l=1;l<n;l++)
    if (new_matrix[k][l]<s)
      s=new_matrix[k][l];
  row_dec[k]=s;
  for (l=0;l<n;l++)
    if (s==new_matrix[k][l] && row_mate[l]<0)
    {
      col_mate[k]=l;
      row_mate[l]=k;
      // if (verbose)
      //   // printf("matching col %d==row %d\n",l,k);
      goto row_done;
    }
  col_mate[k]= -1;
  // if (verbose)
  //   // printf("node %d: unmatched row %d\n",t,k);
  unchosen_row[t++]=k;
row_done:
  ;
}

// End initial state 16
 
// Begin Hungarian algorithm 18
if (t==0)
  goto done;
unmatched=t;
while (1)
{
  // if (verbose)
  //  // printf("Matched %d rows.\n",m-t);
  q=0;
  while (1)
  {
    while (q<t)
    {
      // Begin explore node q of the forest 19
      {
        k=unchosen_row[q];
        s=row_dec[k];

        for (l=0;l<n;l++)
          if (slack[l])
          {
            double del;
            del=new_matrix[k][l]-s+col_inc[l];
            if (del<slack[l])
            {
              if (del==0)
              {
                if (row_mate[l]<0)
                  goto breakthru;
                slack[l]=0;
                parent_row[l]=k;
                // if (verbose)
                //   // printf("node %d,%d: row %d==col %d--row %d\n",q,
                //     // t,row_mate[l],l,k);
                unchosen_row[t++]=row_mate[l];
              }
              else
              {
                slack[l]=del;
                slack_row[l]=k;
              }
          }
        }
      }
      // End explore node q of the forest 19
      q++;
    }
 
    // Begin introduce a new zero into the matrix 21
    s=INF;
    for (l=0;l<n;l++)
      if (slack[l] && slack[l]<s)
        s=slack[l];
    for (q=0;q<t;q++)
      row_dec[unchosen_row[q]]+=s;
    for (l=0;l<n;l++)
      if (slack[l])
      {
        slack[l]-=s;
        if (slack[l]==0)
        {
          // Begin look at a new zero 22
          k=slack_row[l];
          // if (verbose)
          //   // printf(
          //   //  "Decreasing uncovered elements by %f produces zero at [%d,%d]\n",
          //   //   s,k,l);
          if (row_mate[l]<0)
          {
            for (j=l+1;j<n;j++)
              if (slack[j]==0)
                col_inc[j]+=s;
            goto breakthru;
          }
          else
          {
            parent_row[l]=k;
            // if (verbose)
            //  // printf("node %d: row %d==col %d--row %d\n",t,row_mate[l],l,k);
            unchosen_row[t++]=row_mate[l];
          }
          // End look at a new zero 22
        }
      }
      else
        col_inc[l]+=s;
    // End introduce a new zero into the matrix 21
  }
breakthru:
  // Begin update the matching 20
  // if (verbose)
  //  // printf("Breakthrough at node %d of %d!\n",q,t);
  while (1)
  {
    j=col_mate[k];
    col_mate[k]=l;
    row_mate[l]=k;
    // if (verbose)
    //  // printf("rematching col %d==row %d\n",l,k);
    if (j<0)
      break;
    k=parent_row[j];
    l=j;
  }
  // End update the matching 20
  if (--unmatched==0)
    goto done;
  // Begin get ready for another stage 17
  t=0;
  for (l=0;l<n;l++)
  {
    parent_row[l]= -1;
    slack[l]=INF;
  }
  for (k=0;k<m;k++)
    if (col_mate[k]<0)
    {
      // if (verbose)
      //  // printf("node %d: unmatched row %d\n",t,k);
      unchosen_row[t++]=k;
    }
  // End get ready for another stage 17
}
done:

// // Begin doublecheck the solution 23
// for (k=0;k<m;k++)
//   for (l=0;l<n;l++)
//     if (new_matrix[k][l]<row_dec[k]-col_inc[l])
//       exit(0);
// for (k=0;k<m;k++)
// {
//   l=col_mate[k];
//   if (l<0 || new_matrix[k][l]!=row_dec[k]-col_inc[l])
//     exit(0);
// }
// k=0;
// for (l=0;l<n;l++)
//   if (col_inc[l])
//     k++;
// if (k>m)
//   exit(0);
// End doublecheck the solution 23
// End Hungarian algorithm 18

for (i=0;i<m;++i)
{
  Result[i][col_mate[i]]=true;
}
for (k=0;k<m;++k)
{
  for (l=0;l<n;++l)
  {
    new_matrix[k][l]=new_matrix[k][l]-row_dec[k]+col_inc[l];
  }
}
for (i=0;i<m;i++)
  cost+=row_dec[i];
for (i=0;i<n;i++)
  cost-=col_inc[i];
printf("Hungarian Cost is : %f\n",cost);
}

void main()
{
int y,x,i;

scanf("%d\n",&n);
new_matrix=(double**)malloc(n*sizeof(double*));
for(x=0;x<n;x++)
  new_matrix[x]=(double*)malloc(n*sizeof(double));
Result=(char**)malloc(n*sizeof(char*));
for(x=0;x<n;x++)
  Result[x]=(char*)malloc(n*sizeof(char));
double orig_matrix[n][n];
double temp;
for(x=0;x<n;x++)
{
   for(y=0;y<n;y++)
   {
      scanf("%lf ",&temp);
      new_matrix[x][y]=temp;
      orig_matrix[x][y]=temp;
   }
}

hungarian();

for (y=0;y<n;++y)
  for (x=0;x<n;++x)
    if (Result[y][x])
      printf("<R%d,T%d,%lf>\n",y+1,x+1,orig_matrix[y][x]);
}