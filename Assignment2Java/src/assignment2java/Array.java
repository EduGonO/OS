package assignment2java;

/**
 * @author edu
 */
public class Array {

    public static void main(String args[]) {
        
        char[][] array = new char[7][7];
        
        for (int i = 0; i < 7; i++) {
            
            for (int j = 0; j < 7; j++) {
                
                int number = (int) (Math.random() * 26) + 65;
                array[i][j] = (char) number;
                
                System.out.print(array[i][j] + " ");
            }
            System.out.println("");
        }
    }

}
