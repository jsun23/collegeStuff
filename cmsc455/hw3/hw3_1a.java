package hw3_1a;
/**
 * Name: Dong Sun
 * Email: dongsun1@umbc.edu
 * Class: CMSC 455 
 * Project: HW3_1a
 * Date: 6/11/2015
 */
public class hw3_1a {
	double a = 0.0;
    double b = 1.0;
    int n = 0; // 9 points
    double h = 0.0;

    hw3_1a(int n) {
	this.n = n;
	this.h = (b - a) / n;
	paint();
	
    }

    double f(double x) // "exact" function
    {
	return Math.sin(x);
    }
    
    public void paint() {
	// set up function to be approximated
	final int ns = 50; // number of samples for plotting
	final double nf = (double) n;
	double fx[] = new double[ns]; // f(x)
	final double xmin = a;
	final double xmax = b;
	double ymin = 0.0; // for automatic scaling some day
	double ymax = 1.0;
	double dx; // x step increment for plotting curve
	double xstart = a; // initial value
	double x; // stepped value xmin to xmax

	dx = (xmax - xmin) / (double) (ns - 1);
	// do NOT use x=x+dx, very inaccurate!
	for (int i = 0; i < ns; i++)
	    fx[i] = f(xstart + (double) i * dx); // get "exact" function
	ymin = fx[0];
	ymax = fx[0];
	for (int i = 1; i < ns; i++) {
	    ymin = Math.min(ymin, fx[i]);
	    ymax = Math.max(ymax, fx[i]);
	}
	// may fudge ymin and ymax for extra room for approximation
	ymin = 0.0;
	ymax = 1.0;

	// set up plot area
	final int hw = 400; // graph area height and width
	final double xsca = hw / (xmax - xmin); // x data scale 0 to 1
	final double ysca = hw / (ymax - ymin); // y data scale 0 to 1
	final int f1xOff = 25; // offsets
	final int f1yOff = 70;
	final int f1xC = f1xOff + hw / 2; // centers
	final int f1yC = f1yOff + hw / 2;

	

	// plot function
	double x1new, y1new;
	double x1old = xstart;
	double y1old = fx[0];
	
	for (int i = 1; i < ns; i++) // n-1 lines
	    {
		x1new = xstart + (double) i * dx;
		y1new = fx[i];
		
		x1old = x1new;
		y1old = y1new;
	    }

	// compute quadrature and plot areas
	// trapezoidal integration
	double aa[] = new double[n + 1]; // quadrature points
	double area = 0.0;
	double y0, x1, y1, x2, y2;
	y0 = 0.0;
	x1 = a;
	y1 = f(x1);
	
	for (int i = 1; i <= n; i++) {
	    x2 = xmin + (double) i * h;
	    y2 = f(x2);
	    area = area + (y1 + y2) / 2.0;
	    
	    x1 = x2;
	    y1 = y2;
	}
	area = ((b - a) / (double) (n)) * area; // h*area

	System.out.println("n = "+ this.n+ ", computed area=" + area + ", actual=" + (1-Math.cos(1))+ ", error=" + ((1-Math.cos(1) - area)));

	
    }



    public static void main(String[] args) {
	for (int n = 16; n <= 128; n = n * 2) {
	    new hw3_1a(n);
	}
    }

}
