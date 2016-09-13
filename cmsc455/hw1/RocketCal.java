package rocketscience;

/**
 * Name: Dong Sun
 * Email: dongsun1@umbc.edu
 * Class: CMSC 455 
 * Project: HW1
 */



import java.math.*;
import java.text.DecimalFormat;

public class RocketCal {

	boolean start;
	/*
	 * Estes Alpha III Length 12.25 inches = 0.311 meters Diameter 0.95 inches =
	 * 0.0241 m Body area 0.785 square inches = 0.506E-3 square meters
	 * cross section Cd of body 0.45 dimensionless Fins area 7.69 square inches
	 * = 0.00496 square meters total for 3 fins Cd of fins 0.01 dimensionless
	 * Weight/mass 1.2 ounce = 0.0340 kilogram without engine Engine 0.85 ounce
	 * = 0.0242 kilogram initial engine mass Engine 0.33 ounce = 0.0094 kilogram
	 * final engine mass
	 */
	double t; // time
	double s; // height
	double v; // velocity
	double a; // acceleration
	double F; // total force not including gravity
	double m; // mass 0.0340 +0.0242
	double[] Thrust = {0.0, 6.00, 12.23, 5.35, 4.72, 4.56, 4.62, 
			4.65, 4.68, 4.61, 4.67, 4.65, 4.65, 4.57, 4.62, 
			4.62, 4.54, 4.55, 4.57, 0.0};

	double Ft;
	double dt;
	double FdBody;
	double FdFins;
	double Fg;
	double dv;
	double ds;

	public RocketCal() {
		this.start = true;
		this.t = 0.0;
		this.s = 0.0;
		this.v = 0.0;
		this.a = 0.0;
		this.F = 0.0;
		this.m = add(0.0340,0.0242);
		this.Ft = 0.0;
		this.dt = 0.1;
		this.FdBody = 0.0;
		this.FdFins = 0.0;
		this.dv = 0.0;
		this.ds = 0.0;
	

		run();
	}
	
	/*
	 * Get Ft
	 */
	private void GetFt(int i) {
		// Ft data from thrust curve
		Ft = Thrust[i];

	}

	/*
	 * Get F
	 */
	private void GetF() {
		// F = Ft - (Fd body + Fd fins + Fg) resolve forces
		F = sub(Ft, (add(FdBody, add(FdFins, Fg))));
	}

	/*
	 * Get Fg
	 */
	private void GetFg() {
		// Fg = m *g
		// g = 9.80665
		Fg = mul(m, 9.80665);
	}

	/*
	 * Get Fd
	 */
	private void GetFd() {
		// for body
		FdBody = div(
				mul(mul(mul(mul(0.45, 1.293), 0.000506), v), v), 2);
		// for fins
		FdFins = div(
				mul(mul(mul(mul(0.01, 1.293), 0.00496), v), v), 2);
	}

	/*
	 * Get mass change
	 */
	private void GetM() {
		// m = m -0.0001644*Ft
		m = sub(m, mul(0.0001644, Ft));
	}

	/*
	 * Get accelerate change
	 */
	private void GetA() {
		// a = F/m
		a = div(F, m);

	}

	/*
	 * Get dv change
	 */
	private void Getdv() {
		// dv = a*dt
		dv = mul(a, dt);

	}

	/*
	 * Get change
	 */
	private void GetV() {
		// v = v+dv
		v = add(v, dv);
	}

	/*
	 * Get ds change
	 */
	private void Getds() {
		// ds = v*dt
		ds = mul(v, dt);

	}

	/*
	 * Get s change
	 */
	private void GetS() {
		// s = s+ds
		s = add(s, ds);
	}

	private void run() {
		System.out.println("Rocket Launch");
		addTime();
	}

	private void addTime() {
		

		for (int i = 0; i < 10000000; i++) {
			// caculate and print
			if (i < 20) {
				GetFt(i);
			} else {
				Ft = 0.0;
			}

			GetM();
			GetFd();
			GetFg();
			if (i == 0) {
				F = 0.0;
			} else {

				GetF();
			}
			GetA();
			Getdv();
			GetV();
			Getds();
			GetS();

			if (i != 0) {
				if (v < 0) {
					break;
				}

			}
			dump();
			t = add(t, dt);

		}
		System.out.println("\n\t\t\t****************Reach the Highest Place******************");

	}

	private void dump() {
		DecimalFormat df1 = new DecimalFormat("#0.0000000");
		DecimalFormat df2 = new DecimalFormat("#0.00000");
		System.out.print("\nTime:  " + t + " s\t");
		System.out.print("Height: " + df1.format(s) + " m\t");
		System.out.print("V: " + df1.format(v) + " m/s\t");
		System.out.print("a: " + df1.format(a)
				+ "  m/s^2\t");
		System.out.print("Force:" + df1.format(F) + " N\t");
		System.out.print("Mass:" + df2.format(m) + " kg");

	}

	private double add(double v1, double v2) {
		BigDecimal b1 = new BigDecimal(Double.toString(v1));
		BigDecimal b2 = new BigDecimal(Double.toString(v2));
		return b1.add(b2).doubleValue();
	}

	private double sub(double v1, double v2) {
		BigDecimal b1 = new BigDecimal(Double.toString(v1));
		BigDecimal b2 = new BigDecimal(Double.toString(v2));
		return b1.subtract(b2).doubleValue();
	}

	private double mul(double v1, double v2) {
		BigDecimal b1 = new BigDecimal(Double.toString(v1));
		BigDecimal b2 = new BigDecimal(Double.toString(v2));
		return b1.multiply(b2).doubleValue();
	}

	private double div(double v1, double v2) {
		return div(v1, v2, 10);
	}

	private double div(double v1, double v2, int scale) {
		if (scale < 0) {
			throw new IllegalArgumentException(
					"Warning: scale < 0");
		}
		BigDecimal b1 = new BigDecimal(Double.toString(v1));
		BigDecimal b2 = new BigDecimal(Double.toString(v2));
		return b1.divide(b2, scale, BigDecimal.ROUND_HALF_UP).doubleValue();
	}



	

	public static void main(String[] args) {
	
		 new RocketCal();

	}
	
}