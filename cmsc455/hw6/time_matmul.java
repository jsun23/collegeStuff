package hw6;

//time_matmul.java  fine how large matrix multiple can be 
//check that time increases order n^3   
//doubling N takes 8 times as long      
//can be days for 10,000 by 10,000      

public class time_matmul
{
public time_matmul()
{
double t1, t2;

for(int N=100; N<=1600; N=N*2) // N<=3200 is OK, takes minutes 
{
System.out.println("multiply N by N matrices, N="+N);
double a[] = new double[N*N];
double b[] = new double[N*N];
double c[] = new double[N*N];
for(int i=0; i<N; i++)
{
for(int j=0; j<N; j++)
{
a[i*N+j] = (double)i;
b[i*N+j] = (double)j;
}
}
System.out.println("initialized");
t1 = System.currentTimeMillis();

for(int i=0; i<N; i++)
{
for(int j=0; j<N; j++)
{
c[i*N+j] = 0.0;
for(int k=0; k<N; k++)
c[i*N+j] = c[i*N+j] + a[i*N+k]*b[k*N+j]; // most time spent here! 
}
}
t2 = System.currentTimeMillis();
System.out.println("N="+N+", c="+c[5]+", raw time="+
    ((t2-t1)/1000.0)+" seconds");
t2 = 1.0e3*(t2-t1)/((double)N*(double)N*(double)N);
System.out.println("order N^3 normalized time="+t2);
System.out.println(" ");
}
} // end time_matmul constructor

public static void main (String[] args)
{
new time_matmul();
}
} // end time_matmul.java