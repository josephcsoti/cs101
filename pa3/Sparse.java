/*------------------------------------------------
File Name: Sparse.java
Desc: Client of the Matrix ADT, outputs results to a file
Instructions: None

Name:   Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:   10/09/18
------------------------------------------------*/

import java.io.*;
import java.util.Scanner;

public class Sparse {
  // checks input line
  public static void main(String args[]) throws FileNotFoundException {

    if (args.length != 2) {
      System.err.println("Usage: Sparse inputfile outputfile");
      System.exit(0);
    }
    // reads in files
    Scanner in = new Scanner(new File(args[0]));
    PrintWriter out = new PrintWriter(new File(args[1]));

    int size = in.nextInt();
    int a_nnz = in.nextInt();
    int b_nnz = in.nextInt();

    Matrix A = new Matrix(size);
    Matrix B = new Matrix(size);

    in.nextLine();

    // stores information
    for (int i = 0; i < a_nnz; i++) {
      int row = in.nextInt();
      int col = in.nextInt();
      double val = in.nextDouble();
      A.changeEntry(row, col, val);
    }

    in.nextLine();

    for (int i = 0; i < b_nnz; i++) {
      int row = in.nextInt();
      int col = in.nextInt();
      double val = in.nextDouble();
      B.changeEntry(row, col, val);
    }

    out.println("A has " + a_nnz + " non-zero entries:");
    out.println(A);

    out.println("B has " + b_nnz + " non-zero entries:");
    out.println(B);

    out.println("(1.5)*A =");
    out.println(A.scalarMult(1.5));

    out.println("A+B =");
    out.println(A.add(B));

    out.println("A+A =");
    out.println(A.add(A));

    out.println("B-A =");
    out.println(B.sub(A));

    out.println("A-A =");
    out.println(A.sub(A));

    out.println("Transpose(A) = ");
    out.println(A.transpose());

    out.println("A*B =");
    out.println(A.mult(B));

    out.println("B*B =");
    out.println(B.mult(B));

    in.close();
    out.close();
  }

}