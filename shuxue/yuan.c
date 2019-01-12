#include<math.h>
#include<stdio.h>

void get_circle(double x1, double y1, double x2, double y2, double x3, double y3)
{

double r,  x0, y0,m;
double Xmove=x1;  
double Ymove=y1;  
x2=x2-x1;  
y2=y2-y1;  
x3=x3-x1;  
y3=y3-y1;  
m=2.0*(x2*y3-y2*x3);  
x0=(x2*x2*y3-x3*x3*y2+y2*y3*(y2-y3))/m;  
y0=(x2*x3*(x3-x2)-y2*y2*x3+x2*y3*y3)/m;  
 r = sqrt(x0*x0 + y0*y0);
x0+=Xmove;  
y0+=Ymove; 

printf("(%f,%f) %f\n",x0,y0,r);
 return;
}



void main(int argc,char** argv){
	get_circle(1,0,2.4,1.2,0,1.2);	
}
