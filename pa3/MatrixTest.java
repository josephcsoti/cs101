/*------------------------------------------------
File Name: MatrixTest.java
Desc: Tests the "Matrix" ADT
Instructions: None

Name:   Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:   10/09/18
------------------------------------------------*/

import java.util.Random;

class MatrixTest {
  public static void main(String[] args) {
    int size = 5;
    
    Matrix a = makeMatrix(size);
    Matrix b = makeMatrix(size);
    System.out.println(a);
    System.out.println(b);

    a.changeEntry(1,1,0.0);
    a.changeEntry(1,3,0.0);
    a.changeEntry(1,5,0.0);

    a.changeEntry(2,5,0.0);
    a.changeEntry(2,1,0.0);
    a.changeEntry(2,3,0.0);
    a.changeEntry(2,2,0.0);
    a.changeEntry(2,4,0.0);

    a.changeEntry(3,1,0.0);
    a.changeEntry(3,3,0.0);

    a.changeEntry(5,2,0.0);
    a.changeEntry(5,5,0.0);

    System.out.println(a.getNNZ());
    System.out.println(a);

    Matrix scale = a.scalarMult(2.0);
    Matrix add = a.add(a);
    Matrix sub = scale.sub(a);
    Matrix trans = a.transpose();
    Matrix rotate = trans.transpose().transpose().transpose();
    Matrix mult = a.mult(b);

    System.out.println(scale);
    System.out.println(add);
    System.out.println(add.equals(scale) ? "TRUE" : "FALSE");
    System.out.println(sub);
    System.out.println(trans);
    System.out.println(rotate);
    System.out.println(mult);

  }

  static Matrix makeMatrix(int size){
    Random r = new Random();
    Matrix m = new Matrix(size);
    for (int i = 1; i <= m.size; i++) {
      for (int j = 1; j <= m.size; j++) {
        double randomValue = Math.round((5.0 * r.nextDouble() + .11) * 100.00)/100.00;
        m.changeEntry(i, j, randomValue);
      }
    }
    return m;
  }

}