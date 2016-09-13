package hw5;

//Cxfft.java    complex FFT and inverse FTT without using Complex type
//also FFT convolution
/**
 * Name: Dong Sun
 * Email: dongsun1@umbc.edu
 * Class: CMSC 455 
 * Project: HW5
 * Date: 6/23/2015
 */
public class Cxfft {
  public static double[] fft(double A[], double trans)
  // A real,imag real,imag ...
  // trans=1.0 for FFT -1.0 for IFFT
  // fill in zeros to make A.length a power of 2
  // fill in zero for imag if not available
  {
	// PURPOSE : TO PERFORM THE BASIC FFT AND INVERSE FFT COMPUTATION
	//
	// Written by : Jon Squire , 24 MAY 1983
	// JSS REVISED to ISO standard packages 26 AUGUST 1990
	// JSS Cleanup 19 October 1990
	// JSS 9 Sept 1996, Clean up generic formal parameters
	// JSS 1 April 1997, Convert to C++ then Java
	//
	double tmpr, tmpi;
	double wxr, wxi;
	double wr, wi;
	int i, js, ix, m, isp, mmax;
	double ph1;
	int n = A.length / 2;

	js = 1;
	for (ix = 1; ix < n; ix++) // reorder data
	    {
		if (js > ix) {
		    tmpr = A[2 * (js - 1)];
		    tmpi = A[2 * (js - 1) + 1];
		    A[2 * (js - 1)] = A[2 * (ix - 1)];
		    A[2 * (js - 1) + 1] = A[2 * (ix - 1) + 1];
		    A[2 * (ix - 1)] = tmpr;
		    A[2 * (ix - 1) + 1] = tmpi;
		}
		m = n / 2;
		while (m < js && m > 0) {
		    js = js - m;
		    m = m / 2;
		}
		js = js + m;
	    }
	mmax = 1;
	while (mmax < n) // compute transform
	    {
		isp = mmax + mmax;
		ph1 = Math.PI * trans / (double) mmax;
		wxr = Math.cos(ph1);
		wxi = Math.sin(ph1);
		wr = 1.0;
		wi = 0.0;
		for (m = 0; m < mmax; m++) {
		    ix = m;
		    while (ix + mmax < n) {
			js = ix + mmax;
			tmpr = wr * A[2 * js] - wi * A[2 * js + 1];
			tmpi = wr * A[2 * js + 1] + wi * A[2 * js];
			A[2 * js] = A[2 * ix] - tmpr; // BASIC BUTTERFLY
			A[2 * js + 1] = A[2 * ix + 1] - tmpi;
			A[2 * ix] = A[2 * ix] + tmpr;
			A[2 * ix + 1] = A[2 * ix + 1] + tmpi;
			ix = ix + isp;
		    }
		    tmpr = wr * wxr - wi * wxi;
		    tmpi = wr * wxi + wi * wxr;
		    wr = tmpr;
		    wi = tmpi;
		}
		mmax = isp;
	    }
	if (trans < 0.0) // only divide by n on inverse transform
	    {
		for (i = 0; i < n; i++) {
		    A[2 * i] = A[2 * i] / (double) n;
		    A[2 * i + 1] = A[2 * i + 1] / (double) n;
		}
	    }
	return A;
  } // end fft

  public static double[] fftconv(double[] a, double[] b) {
	// fft convolution
	int n = a.length;
	int m = b.length;
	if (n != m) {
	    System.out.println("fftconv n!=m");
	    System.exit(1);
	}
	double c[] = new double[n];
	double AA[] = new double[4 * n];
	double AAT[] = new double[4 * n];
	double BB[] = new double[4 * n];
	double BBT[] = new double[4 * n];
	double CC[] = new double[4 * n];
	double CCT[] = new double[4 * n];
	for (int i = 0; i < n; i++) {
	    AA[2 * i] = a[i];
	    AA[2 * i + 1] = 0.0;
	    AA[2 * (i + n)] = 0.0;
	    AA[2 * (i + n) + 1] = 0.0;
	    BB[2 * i] = b[i];
	    BB[2 * i + 1] = 0.0;
	    BB[2 * (i + n)] = 0.0;
	    BB[2 * (i + n) + 1] = 0.0;
	}
	AAT = Cxfft.fft(AA, 1.0);
	BBT = Cxfft.fft(BB, 1.0);
	for (int i = 0; i < 2 * n; i++) {
	    CCT[2 * i] = AAT[2 * i] * BBT[2 * i] - AAT[2 * i + 1]
		* BBT[2 * i + 1];
	    CCT[2 * i + 1] = AAT[2 * i] * BBT[2 * i + 1] + AAT[2 * i + 1]
		* BBT[2 * i];
	}
	CC = Cxfft.fft(CCT, -1.0);
	for (int i = 0; i < n; i++) {
	    c[i] = CC[2 * i];
	}
	return c;
  } // end fftconv

} // end class Cxfft