package hw3_1b;

/**
 * Name: Dong Sun
 * Email: dongsun1@umbc.edu
 * Class: CMSC 455 
 * Project: HW3_1b
 * Date: 6/11/2015
 */
public class HW3_1b {

	public HW3_1b() {
		new gauleg();
	    }

	    public static void main(String[] args) {
		new HW3_1b();
	    }

	    // gauleg.java P145 Numerical Recipes in Fortran
	    // compute x(i) and w(i) i=1,n Legendre ordinates and weights
	    // on interval -1.0 to 1.0 (length is 2.0)
	    // use ordinates and weights for Gauss Legendre integration

	    public class gauleg {
		public gauleg() {
		    double sum, a, b;
		    double x[] = new double[17];
		    double w[] = new double[17];

		    a = 0.0;
		    b = 1.0;
		    double actul = -Math.cos(1.0) + Math.cos(0.0);
		    for (int i = 8; i <= 16; i = i * 2) {
			gaulegf(a, b, x, w, i);
			sum = 0.0;
			for (int j = 1; j <= i; j++) {
			    sum = sum + w[j] * Math.sin(x[j]);
			}
			System.out.println("n = " + i
					   + " integral (0.0,1.0) sin(x) dx = " + sum);
			System.out.println("error =" + (actul-sum));
		    }
		    System.out.println("-cos(1.0)+cos(0.0) = "
				       + actul);
		    

		} // end gauleg

		void gaulegf(double x1, double x2, double x[], double w[], int n) {

		    int m;
		    double eps = 3.0E-14;
		    double p1, p2, p3, pp, xl, xm, z, z1;
		    
		    m = (n + 1) / 2;
		    xm = 0.5 * (x2 + x1);
		    xl = 0.5 * (x2 - x1);
		    for (int i = 1; i <= m; i++) {
			z = Math.cos(3.141592654 * ((double) i - 0.25)
				     / ((double) n + 0.5));
			while (true) {
			    p1 = 1.0;
			    p2 = 0.0;
			    for (int j = 1; j <= n; j++) {
				p3 = p2;
				p2 = p1;
				p1 = ((2.0 * (double) j - 1.0) * z * p2 - ((double) j - 1.0)
				      * p3)
				    / (double) j;
			    }
			    pp = (double) n * (z * p1 - p2) / (z * z - 1.0);
			    z1 = z;
			    z = z1 - p1 / pp;
			    if (Math.abs(z - z1) <= eps)
				break;
			}
			x[i] = xm - xl * z;
			x[n + 1 - i] = xm + xl * z;
			w[i] = 2.0 * xl / ((1.0 - z * z) * pp * pp);
			w[n + 1 - i] = w[i];
		    }
		}
	    }

}
