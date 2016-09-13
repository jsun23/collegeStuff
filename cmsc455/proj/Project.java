package finalproject;


/**
 * Name: Dong Sun
 * Email: dongsun1@umbc.edu
 * Class: CMSC 455 
 * Project: Project
 * Date: 7/2/2015
 */
import java.math.BigDecimal;
import java.math.RoundingMode;
//define
public class Project {
	
    private double dt = 0.001;
    private double dx = 2.00;// init with a bad value
    private double dy = 2.00;// init with a bad value
    private double xrangeMin = -1.00;
    private double xrangeMax = 1.00;
    private double yrangeMin = -1.00;
    private double yrangeMax = 1.00;
    private double zmin = 999.9;// init with a bad value
    private double z = 999.9;
    private double zmin2 = 999.9;
    private double x = -0.024;
    private double y = 0.209;
    private double dx2 = 2.00;
    private double dy2 = 2.00;
    public Project() {
	

    	BigDecimal ii = new BigDecimal(x);
    	ii.setScale(200, BigDecimal.ROUND_DOWN);
		BigDecimal jj = new BigDecimal(y);
		jj.setScale(200, BigDecimal.ROUND_DOWN);
    	
	
		for(BigDecimal ix = new BigDecimal(Double.toString(xrangeMax));ix.doubleValue()>=this.xrangeMin;
				ix=ix.subtract(new BigDecimal(Double.toString(this.dt)))){
			for(BigDecimal iy = new BigDecimal(Double.toString(yrangeMax));iy.doubleValue()>=this.yrangeMin;
					iy=iy.subtract(new BigDecimal(Double.toString(this.dt)))){
		
	/*	for (BigDecimal i = new BigDecimal(Double.toString(xrangeMin)); i
				 .doubleValue() <= this.xrangeMax; i = i.add(new BigDecimal(Double
										 .toString(this.dt)))) {
	   for (BigDecimal j = new BigDecimal(Double.toString(yrangeMin)); j
		    .doubleValue() <= this.yrangeMax; j = j.add(new BigDecimal(Double
								     .toString(this.dt)))) {*/
		   double tempZ= f2(ix.doubleValue(), iy.doubleValue()).doubleValue();
		   if(tempZ < zmin2){
			    zmin2 = tempZ;
			    this.dx2 = ix.doubleValue();
			    this.dy2 = iy.doubleValue();
			    z = opt(ix.doubleValue(), iy.doubleValue());
			}
	   }}
	   
	for (BigDecimal i = new BigDecimal(Double.toString(xrangeMin)); i
				 .doubleValue() <= this.xrangeMax; i = i.add(new BigDecimal(Double
										 .toString(this.dt/2)))) {
	   for (BigDecimal j = new BigDecimal(Double.toString(yrangeMin)); j
		    .doubleValue() <= this.yrangeMax; j = j.add(new BigDecimal(Double
								     .toString(this.dt/2)))) {
		  //this.dt = dt/2;
		  
		   /*	if(i.doubleValue()>ix.doubleValue() && j.doubleValue()>iy.doubleValue())
	    	{
	    		i=ix;
	    		j=iy;
	    	}*/
	    	//BigDecimal ii = i.setScale(200);
	    	//BigDecimal jj = j.setScale(200);
	    	//double y[] = {j.doubleValue(),j.doubleValue()};
	    	//double ymin[]={-1,-1};
	    	//double ymax[]={1,1};
	    	//double dt1[] = new double[2];
	    	
	    	//dy = OPT.optmn(2, y, -1000.0, 8, dt, dt1, ymin, ymax);
		double tempZ= f2(i.doubleValue(), j.doubleValue()).doubleValue();
		
		//z = f2(ii.doubleValue(),jj.doubleValue());
		
		//zmin = Math.min(zmin, tempZ);
		
		if(tempZ < zmin){
		    zmin = tempZ;
		    this.dx = i.doubleValue();
		    this.dy = j.doubleValue();
		    //z = opt(ix.doubleValue(), iy.doubleValue());
		}
		
		
	    }}// end loop
	System.out.println("xmin"+xrangeMin);
	System.out.println("ymin"+yrangeMin);
	BigDecimal xx = new BigDecimal(dx);
	//BigDecimal xxx = xx.setScale(100);
	BigDecimal yy = new BigDecimal(dy);
	//BigDecimal yyy = yy.setScale(100);
    BigDecimal zz = new BigDecimal(zmin);
    BigDecimal zzz = new BigDecimal(z);
    BigDecimal zzzz = new BigDecimal(zmin2);
    System.out.println("Globle Search");
	System.out.println("zmin: "+ /*zmin);*/zzzz.toString());
	System.out.println("x: "+dx2);//xxx.toString());
	System.out.println("y: "+dy2);//yyy.toString());
	System.out.println("\nafter first dt/2");
	System.out.println("zmin2: "+ zz.toString()/*zmin);*/);
	System.out.println("x: "+ xx);//xxx.toString());
	System.out.println("y: "+ yy);//yyy.toString());
	System.out.println("\nFinal");
	System.out.println("Final zmin: "+ zzz.toString());
	System.out.println("x: "+ii.toString());//xxx.toString());
	System.out.println("y: "+jj.toString());//yyy.toString());
    }

    public BigDecimal f2(double x, double y) {
    BigDecimal i =new BigDecimal ( Math.exp(Math.sin(60.0 *(x))) + Math.sin(50.0 * Math.exp(y))
	    + Math.sin(70.0 * Math.sin(x)) + Math.sin(Math.sin(80.0 * y))
	    - Math.sin(10.0 * (x + y)) + (x * x + y * y) / 4.0);
    	return i;
    }

    public BigDecimal function(double x, double y) {
	BigDecimal x1 = new BigDecimal(Double.toString(x));
	BigDecimal y1 = new BigDecimal(Double.toString(y));
	BigDecimal ans;
	BigDecimal aa = x1.multiply(new BigDecimal(Double.toString(50.0)));
	double f1 = Math.exp(Math.sin(aa.doubleValue()));

	System.out.println(x1);
	System.out.println(y1);

	return x1;

    }
    public double opt(double xbest,double ybest) {
    	
    	double[] x = new double[10];
    	double z;
    	z = f2(xbest, ybest).doubleValue();
    	do
    	{
    	BigDecimal xx = new BigDecimal(xbest);
    	BigDecimal dxx = new BigDecimal(dt);
    	BigDecimal xs = xx.subtract(dxx);
    	BigDecimal xa = xx.add(dxx);
    	BigDecimal yy = new BigDecimal(ybest);
    	BigDecimal dyy = new BigDecimal(dt);
    	BigDecimal ys = yy.subtract(dyy);
    	BigDecimal ya = yy.add(dyy);
    	
    	
    		x[0]=f2(xs.doubleValue(), ybest).doubleValue();
    		x[1]=f2(xbest, ys.doubleValue()).doubleValue();
    		x[2]=f2(xs.doubleValue(), ys.doubleValue()).doubleValue();
    		x[3]=f2(xbest, ybest).doubleValue();
    		x[4]=f2(xbest, ya.doubleValue()).doubleValue();
    		x[5]=f2(xs.doubleValue(),ya.doubleValue()).doubleValue();
    		x[6]=f2(xa.doubleValue(), ybest).doubleValue();
    		x[7]=f2(xa.doubleValue(), ys.doubleValue()).doubleValue();
    		x[8]=f2(xs.doubleValue(), ya.doubleValue()).doubleValue();
    		x[9]=f2(xa.doubleValue(), ya.doubleValue()).doubleValue();
    		dt =dt/2;
    		
    	}while(dt > 10E-100 );
    	for(int i=0;i < (x.length-1);i++)
    	{
    		if(x[i]<x[i+1])
    			z = x[i];
    		
    	}
    	return z;
    }


    public static void main(String[] args) {
	 new Project();

    }
}
