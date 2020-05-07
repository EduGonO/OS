package assignment2java;

import static java.lang.Thread.sleep;

/**
 * @author edu
 */
public class Assignment2Thread implements Runnable {
    
    public static int finalRowLetter = -1;
    public static int finalRowThread = -1;
    public static int finalRowTimes = -1;

    public static int finalColLetter = -1;
    public static int finalColThread = -1;
    public static int finalColTimes = -1;

    @Override
    public void run() {
        try {
            int num = Assignment2Java.threadNum++;


            //System.out.printf("\nThread #" + (num+1));
            int[] results = new int[95];

            int frequency = -1;
            int letter = -1;

            if (num<7) {
                

                for (int i = 0; i < 7; i++) {
                    char res = Assignment2Java.array[i][num];
                    results[res]++;
                }

                for (int i = 0; i < Assignment2Java.LETTERS; i++) {
                    if (results[i] > frequency) {
                        frequency = results[i];
                        letter = i;
                    }
                }
                
                //System.out.printf("\nMost Frequent Letter: " + (char)letter + " Times: " + frequency + " (Thread " + (num+1) + ")\n");

                if (frequency > Assignment2Java.getFinalColTimes()) {
                    Assignment2Java.setFinalColLetter((char) letter);

                    if (num == 0) {
                        Assignment2Java.setFinalColThread(0);
                    } else {
                        Assignment2Java.setFinalColThread(num);
                    }

                    Assignment2Java.setFinalColTimes(frequency);
                }

            } else {
                    
                
                for (int i = 0; i < 7; i++) {
                    char res = Assignment2Java.array[num % 7][i];
                    results[res]++;
                }

                for (int i = 0; i < Assignment2Java.LETTERS; i++) {
                    if (results[i] > frequency) {
                        frequency = results[i];
                        letter = i;
                    }
                }
                
                //System.out.printf("\nMost Frequent Letter: " + (char)letter + " Times: " + frequency + " (Thread " + (num+1) + ")\n");
                
                if (frequency > Assignment2Java.getFinalRowTimes()) {
                    Assignment2Java.setFinalRowLetter((char) letter);
                    Assignment2Java.setFinalRowThread(num%7);
                    Assignment2Java.setFinalRowTimes(frequency);
                }
            }
        } catch (Exception e) {
            // Throwing an exception 
            System.out.printf("Exception");
        }
    }

}
