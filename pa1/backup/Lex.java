/*------------------------------------------------
File Name: lex.java
Name:   Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:   10/09/18
------------------------------------------------*/

import java.io.*;
import java.util.Scanner;

public class Lex {
  public static void main(String[] args) throws IOException {

    // Coorect Lex arg usage
    if (args.length != 2) {
      System.err.println("Usage: Lex inputfile outputfile");
      System.exit(1);
    }

    // Open files and writer
    Scanner scan = new Scanner(new File(args[0]));
    PrintWriter print = new PrintWriter(new FileWriter(args[1]));

    // Get line count
    int len = 0;
    while (scan.hasNextLine()) {
      len++;
      scan.nextLine();
    }

    // Close scanner (gonna reopen later)
    scan.close();
    scan = null;

    // Create emptyarr
    String[] arr = new String[len];

    // Reset scanner
    scan = new Scanner(new File(args[0]));

    // Insert lines from file into array
    int i = 0;
    while (scan.hasNextLine()) {
      arr[i] = scan.nextLine();
      i++;
    }

    // Creaet instance of list ADT and add the first element
    List list = new List();
    list.append(0); // oth element is always "sorted"

    // "Insertion Sort"
    for(int j = 1; j < arr.length; j++) {
      // Get line
      String str = arr[j];
      int k = j;
      
      // Move cursor to front
      list.moveFront();
      
      // Compare current string t0 next one
      // If "b" is still larger than "a"
      // Move cursor to next element and compare
      while(k > 0 && str.compareTo(arr[list.get()]) >= 0) {
        list.moveNext();
        k--;
      }
      // Insert item at given index after search
      if(list.index() >= 0)
        list.insertBefore(j);
      else
        list.append(j); // No more elements to compare, so it must be the largest, thus we append
    }

    // Reset index to the front of the List
    list.moveFront();
    // Loop through List to print out all lines in the correct order
    while(list.index() >= 0) {
      print.println(arr[list.get()]);
      list.moveNext();
    }

    // Clean up
    scan.close();
    print.close();
  }
}