package hw5;


/**
 * Name: Dong Sun
 * Email: dongsun1@umbc.edu
 * Class: CMSC 455 
 * Project: HW5
 * Date: 6/23/2015
 */
import java.util.ArrayList;


public class HW5 {
  public HW5(String file_in, String file_out) {
	double amin, amax, aavg;
	int m; // next power of 2

	read_wav R = new read_wav(file_in, file_out, false);
	// wav_read(file_in); done by constructor
	int n = R.outix; // number of sound samples
	for (m = 64; m < 2500000; m *= 2)
	    if (m > 2 * n)
		break;
	System.out.println("power of 2 m=" + m);
	
	System.out.println("have " + n + " points for FFT");
	double A[] = new double[m];
	double B[] = new double[m];
	for (int i = 0; i < 2 * n; i += 2)
	    A[i] = (double) R.A[i / 2]; // real
	for (int i = 1; i < 2 * n; i += 2)
	    A[i] = 0.0; // imag
	amin = A[0];
	amax = A[0];
	aavg = 0.0;
	for (int i = 0; i < 2 * n; i += 2) {
	    amin = Math.min(amin, A[i]);
	    amax = Math.max(amax, A[i]);
	    aavg += A[i];
	}
	aavg = aavg / (double) n;
	System.out.println("input min=" + amin + ", max=" + amax + ", avg="
			   + aavg);
	for (int i = 2 * n; i < m; i++)
	    A[i] = 0.0; // zero to power of 2

	B = Cxfft.fft(A, 1.0);

	// change frequency bins, some B[i], put code here for HW5
	// not just add/sub/mul/div all bins

	A = Cxfft.fft(B, -1.0);
	amin = A[0];
	amax = A[0];
	aavg = 0.0;
	for (int i = 0; i < 2 * n; i += 2) {
	    amin = Math.min(amin, A[i]);
	    amax = Math.max(amax, A[i]);
	    //aavg += A[i];
	}
	
	// delete high and low frequency bins
	ArrayList < Double > list = new ArrayList < Double > ( );
	
	for (int i = 0; i < A.length; i ++) {
	    if(amin == A[i] || amax == A[i]){
		// delete high and low frequency
	    }else{
		list.add(amax);
		
	    }
	}
	System.out.println("\nbefore delete high and low frequency bins "+A.length);
	int temp = A.length;
	A = new double[list.size()];
	for(int i =0; i<list.size();i++){
	    A[i] = list.get(i);
	}
	
	System.out.print("after delete high and low frequency bins ");
	System.out.println(A.length);
	System.out.println();
	double newmin = 0.0;
	double newmax = 0.0;
	
	for (int i = 0; i < 2 * n; i += 2) {
	    newmin = Math.min(amin, A[i]);
	    newmax = Math.max(amax, A[i]);
	    aavg += A[i];
	}
	aavg = aavg / (double) n;
	System.out.println("output min=" + newmin + ", max=" + newmax + ", avg="
			   + aavg);
	// should normalize

	for (int i = 0; i < 2 * n; i += 2)
	    R.A[i / 2] = (int) (0.99 * A[i]);
	for (int i = 0; i < n; i++) {
	    if (R.A[i] > 127)
		R.A[i] = 127;
	    if (R.A[i] < -127)
		R.A[i] = -127;
	}
	R.wav_write(file_out);
  }
  
  public static void main(String[] args) {
	String file_in = "cat.wav";
	if (args.length > 0) {
	    file_in = args[0];
	}
	String file_out = "cleared.wav";
	if (args.length > 1) {
	    file_out = args[1];
	}
	new HW5(file_in, file_out);
  } // end main
} // end class fft_wav of fft_wav.java
