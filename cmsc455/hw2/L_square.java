package lsquare;

/**
 * Name: Dong Sun
 * Email: dongsun1@umbc.edu
 * Class: CMSC 455 
 * Project: HW2
 * Date: 6/3/2015
 */

public class L_square {
	
	    double rmserr, avgerr, maxerr;
	    int idata = 0; // reset after each use of the data set
	    double[] thrust = { 0.0, 6.00, 12.23, 5.35, 4.72, 4.56, 4.62, 
				4.65, 4.68, 4.61, 4.67, 4.65, 4.65, 4.57, 4.62, 
				4.62, 4.54, 4.55, 4.57, 0.0 };
	    double[] time = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9,
			      1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9};
	    L_square() {
		int n;

		System.out.println("L_square.java");
		for (int i = 3; i < 20; i++) {
		    n = i + 1; // need constant term and three powers 1,2,3
		    double A[][] = new double[n][n];
		    double C[] = new double[n];
		    double Y[] = new double[n];
		    System.out.println("fit data to "
				       + (n - 1) + " degree polynomial");
		    fit_pn(n, A, Y, C);
		    check_pn(n, C);
		    System.out.println("maxerr=" + maxerr + ", avgerr=" + avgerr
				       + ",rmserr=" + rmserr);
		    System.out.println(" ");
		}
	    }

	    int data_set(double yx[]) // returns 1 for data, 0 for end
	    { // sets value of y for value of x
		int k = 19; // 19
		double xx;
		double yy;

		idata++;
		if (idata > k) {
		    idata = 0;
		    return 0;
		} // ready for check
		
		xx = time[idata-1];
		yy = thrust[idata-1];
		yx[1] = xx;
		yx[0] = yy;
		return 1;
	    } // end data_set

	    void fit_pn(int n, double A[][], double Y[], double C[]) { // n is number of
		// coefficients,
		// highest
		// power-1
		int i, j, k;
		double x, y, t;
		double yx[] = new double[2];
		double pwr[] = new double[n];

		for (i = 0; i < n; i++) {
		    for (j = 0; j < n; j++) {
			A[i][j] = 0.0;
		    }
		    Y[i] = 0.0;
		}
		while (data_set(yx) == 1) {
		    y = yx[0];
		    x = yx[1];
		    pwr[0] = 1.0;
		    for (i = 1; i < n; i++)
			pwr[i] = pwr[i - 1] * x;
		    for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
			    A[i][j] = A[i][j] + pwr[i] * pwr[j];
			}
			Y[i] = Y[i] + y * pwr[i];
		    }
		}
		simeq(A, Y, C);
		for (i = 0; i < n; i++)
		System.out.println("C[" + i + "]=" + C[i]);
	    } // end fit_pn

	    void check_pn(int n, double C[]) {
		double x, y, ya, diff;
		double yx[] = new double[2];
		double sumsq = 0.0;
		double sum = 0.0;
		double maxe = 0.0;
		double xmin = 0.0;
		double xmax = 0.0;
		double ymin = 0.0;
		double ymax = 0.0;
		double xbad = 0.0;
		double ybad = 0.0;
		int i, k, imax = 0;

		k = 0;
		while (data_set(yx) == 1) {
		    y = yx[0];
		    x = yx[1];
		    if (k == 0) {
			xmin = x;
			xmax = x;
			ymin = y;
			ymax = y;
			imax = 0;
			xbad = x;
			ybad = y;
		    }
		    if (x > xmax)
			xmax = x;
		    if (x < xmin)
			xmin = x;
		    if (y > ymax)
			ymax = y;
		    if (y < ymin)
			ymin = y;
		    k++;
		    ya = C[n - 1] * x;
		    for (i = n - 2; i > 0; i--) {
			ya = (C[i] + ya) * x;
		    }
		    ya = ya + C[0];
		    diff = Math.abs(y - ya);
		    if (diff > maxe) {
			maxe = diff;
			imax = k;
			xbad = x;
			ybad = y;
		    }
		    sum = sum + diff;
		    sumsq = sumsq + diff * diff;
		}
		maxerr = maxe;
		avgerr = sum / (double) k;
		rmserr = Math.sqrt(sumsq / (double) k);
	    } 

	    void simeq(final double A[][], final double Y[], double X[]) {
		// solve real linear equations for X where Y = A * X
		// method: Gauss-Jordan elimination using maximum pivot
		// usage: simeq(A,Y,X);
		// Translated to java by : Jon Squire , 26 March 2003
		// First written by Jon Squire December 1959 for IBM 650, translated to
		// other languages e.g. Fortran converted to Ada converted to C
		// then converted to java
		int n = A.length;
		int m = n + 1;
		double B[][] = new double[n][m]; // working matrix
		int row[] = new int[n]; // row interchange indices
		int hold, I_pivot; // pivot indices
		double pivot; // pivot element value
		double abs_pivot;
		if (A[0].length != n || Y.length != n || X.length != n) {
		    System.out
			.println("Error in Matrix.solve, inconsistent array sizes.");
		}
		// build working data structure
		for (int i = 0; i < n; i++) {
		    for (int j = 0; j < n; j++) {
			B[i][j] = A[i][j];
		    }
		    B[i][n] = Y[i];
		}
		// set up row interchange vectors
		for (int k = 0; k < n; k++) {
		    row[k] = k;
		}
		// begin main reduction loop
		for (int k = 0; k < n; k++) {
		    // find largest element for pivot
		    pivot = B[row[k]][k];
		    abs_pivot = Math.abs(pivot);
		    I_pivot = k;
		    for (int i = k; i < n; i++) {
			if (Math.abs(B[row[i]][k]) > abs_pivot) {
			    I_pivot = i;
			    pivot = B[row[i]][k];
			    abs_pivot = Math.abs(pivot);
			}
		    }
		    // have pivot, interchange row indices
		    hold = row[k];
		    row[k] = row[I_pivot];
		    row[I_pivot] = hold;
		    // check for near singular
		    if (abs_pivot < 1.0E-10) {
			for (int j = k + 1; j < n + 1; j++) {
			    B[row[k]][j] = 0.0;
			}
			System.out.println("redundant row (singular) " + row[k]);
		    } // singular, delete row
		    else {
			// reduce about pivot
			for (int j = k + 1; j < n + 1; j++) {
			    B[row[k]][j] = B[row[k]][j] / B[row[k]][k];
			}
			// inner reduction loop
			for (int i = 0; i < n; i++) {
			    if (i != k) {
				for (int j = k + 1; j < n + 1; j++) {
				    B[row[i]][j] = B[row[i]][j] - B[row[i]][k]
					* B[row[k]][j];
				}
			    }
			}
		    }
		    // finished inner reduction
		}
		// end main reduction loop
		// build X for return, unscrambling rows
		for (int i = 0; i < n; i++) {
		    X[i] = B[row[i]][n];
		}
	    } // end simeq

	    public static void main(String[] args) {
		new L_square();
	    } // end main

	
}
