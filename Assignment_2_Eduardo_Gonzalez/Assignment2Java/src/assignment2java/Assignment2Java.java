package assignment2java;

/**
 * @author edu
 */

public class Assignment2Java {
    
    public static char[][] array = new char[7][7];

    public static int getThreadNum() {
        return threadNum;
    }

    public static int getFinalRowLetter() {
        return finalRowLetter;
    }

    public static int getFinalRowThread() {
        return finalRowThread;
    }

    public static int getFinalRowTimes() {
        return finalRowTimes;
    }

    public static int getFinalColLetter() {
        return finalColLetter;
    }

    public static int getFinalColThread() {
        return finalColThread;
    }

    public static int getFinalColTimes() {
        return finalColTimes;
    }
    
    public static void setThreadNum(int threadNum) {
        Assignment2Java.threadNum = threadNum;
    }

    public static void setFinalRowLetter(int finalRowLetter) {
        Assignment2Java.finalRowLetter = finalRowLetter;
    }

    public static void setFinalRowThread(int finalRowThread) {
        Assignment2Java.finalRowThread = finalRowThread;
    }

    public static void setFinalRowTimes(int finalRowTimes) {
        Assignment2Java.finalRowTimes = finalRowTimes;
    }

    public static void setFinalColLetter(int finalColLetter) {
        Assignment2Java.finalColLetter = finalColLetter;
    }

    public static void setFinalColThread(int finalColThread) {
        Assignment2Java.finalColThread = finalColThread;
    }

    public static void setFinalColTimes(int finalColTimes) {
        Assignment2Java.finalColTimes = finalColTimes;
    }

    //struct A_SIZExSIZE_ARR input;
    public static final int MAX_THREADS = 14;
    public static final int LETTERS = 90; // Z is equal to 90 so the max int we could get is a 90

    public static int threadNum = 0;

    // Final results
    
    public static int finalRowLetter = -1;
    public static int finalRowThread = -1;
    public static int finalRowTimes = -1;

    public static int finalColLetter = -1;
    public static int finalColThread = -1;
    public static int finalColTimes = -1;
     
    public static void main(String args[]) throws InterruptedException {
        
        // Print Array
        
        System.out.println("\nRandom Array: \n");
        
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                int number = (int) (Math.random() * 26) + 65;
                array[i][j] = (char) number;
                
                System.out.print(array[i][j] + " ");
            }
            System.out.println("");
        }
        
        
        for (int i=0; i<MAX_THREADS; i++) 
        { 
            Thread object = new Thread(new Assignment2Thread()); 
            object.start(); 
        }
        
        System.out.println("\n-------------\n");
        
        
        System.out.println("Row: " + finalRowThread + 
                           " Letter: " + (char) finalRowLetter + 
                           " # of Times: " + finalRowTimes);
        
        System.out.println("\nCol: " + finalColThread + 
                           " Letter: " + (char) finalColLetter + 
                           " # of Times: " + finalColTimes);
        
        System.out.println("\n-------------\n");
        
    }
    

}
