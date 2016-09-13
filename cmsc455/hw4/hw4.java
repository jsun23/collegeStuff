package hw4;
/**
 * Name: Dong Sun
 * Email: dongsun1@umbc.edu
 * Class: CMSC 455 
 * Project: HW4
 * Date: 6/22/2015
 */
import java.math.BigDecimal;
public class hw4 {

    public static void main(String[] args) {
	new hw4();
    }

    private Integer n;
    private Integer m;
    public hw4() {
	this.n = 52;
	this.m = 7;

	fct();
	
	
    }

    private void fct() {
	// n! / ((n-m)! m!)
	System.out.println("n is 52 card");
	System.out.println("m is picked up 7 card ");
	BigDecimal nfac = factorial(new BigDecimal(Integer.toString(this.n)));
	BigDecimal mfac = factorial(new BigDecimal(Integer.toString(this.m)));
	System.out.println("n! = "+ nfac);
	System.out.println("m! = "+ mfac);

	Integer temp = n-m;
	
	BigDecimal result = nfac.divide(mfac.multiply(factorial(new BigDecimal(Integer.toString(temp)))));
	System.out.println("n! / ((n-m)! m!) = "+ result);
    }
    
    private BigDecimal factorial(BigDecimal n) {
	if (n.compareTo(new BigDecimal("1")) <= 0)
	    return new BigDecimal("1");
	return n.multiply(factorial(n.subtract(new BigDecimal("1"))));
    }
    
}

