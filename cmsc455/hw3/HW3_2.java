package hw3_2;

/**
 * Name: Dong Sun
 * Email: dongsun1@umbc.edu
 * Class: CMSC 455 
 * Project: HW3_2
 * Date: 6/3112015
 */
import java.text.DecimalFormat;
public class HW3_2 {
	public void check(){
	
		DecimalFormat df = new java.text.DecimalFormat( "0.0000");
		double gridList[] = {1.0,0.1,0.01,0.001,0.0001};
		for(int n =0;n<gridList.length;n++){
		    int counter = 0;
		    for(double i = -5; i<=5;){
			for(double j = -5;j<= 5;){
			    // to check X Y is in the area on not
			    if(checkArea(i, j)){
				counter++;
			    }
			    String result2=df.format(j+gridList[n]);
			    j = Double.parseDouble(result2);
			}
			String result=df.format(i+gridList[n]);
			i = Double.parseDouble(result);
		    }
		    System.out.println("when grid = "+gridList[n] + ", dot in area = "+counter+", area = "+ calArea(counter, gridList[n]));
		}
		
		
	    }
	    public double calArea(int counter,double grid){
		return counter*grid*grid;
	    }
	    
	    public boolean checkArea(double x,double y){
		// check c1 need outside c1
		// c1 (x-2)^2+(y-2)^2 > 1^2 
		if(((x-2)*(x-2) + (y-2)*(y-2))>1){
		    // check inside c2
		    // c2 x^2+(y-2)^2 < 2^2
		    if((x*x + (y-2)*(y-2))<4){
			// check inside c3
			// c3 x^2+y^2 < 3^2
			if((x*x +y*y)<9){
			    return true;
			}
		    }
		}
		return false;
	    }
	    public HW3_2() {
		// count area 
		// c = r*r*pi
		//double c1 = 1*1*Math.PI;
		//double c2 = 2*2*Math.PI;
		//double c3 = 3*3*Math.PI;
		check();
		
		//double area = 
		
		//new point_in_poly();
		
		
	    }

	    public static void main(String[] args) {

		new HW3_2();
	    }

}
