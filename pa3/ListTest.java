/*------------------------------------------------
File Name: ListTest.java
Desc: Tests the List ADT
Instructions: None

Name:   Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:   10/09/18
------------------------------------------------*/

public class ListTest {
  public static void main(String[] args) {

    int size = 10;

    List<Integer> A = new List<Integer>();
    List<Integer> B = new List<Integer>();

    for (int i = 0; i < size; i++) {
      A.append(i);
      B.prepend(i);
    }

    System.out.println("A: " + A);
    System.out.println("B: " + B);

    System.out.println("A.index(): " + A.index());
    System.out.println("B.index(): " + B.index());
 
    System.out.println("A.front(): " + A.front());
    System.out.println("B.front(): " + B.front());

    System.out.println("A.back(): " + A.back());
    System.out.println("B.back(): " + B.back());

    System.out.println("A.equals(A): " + A.equals(A.copy()));
    System.out.println("A.equals(B): " + A.equals(B));

    A.deleteFront();
    B.deleteFront();
    System.out.println("A.deleteFront(): " + A);
    System.out.println("B.deleteFront(): " + B);

    A.deleteBack();
    B.deleteBack();
    System.out.println("A.deleteBack(): " + A);
    System.out.println("B.deleteBack(): " + B);

    A.moveFront();
    B.moveBack();
    for (int i = 0; i < 3; i++) {
      A.moveNext();
      B.movePrev();
    }

    System.out.println("A.get(): " + A.get());
    System.out.println("B.get(): " + B.get());

    A.clear();
    B.clear();

    System.out.println("Clearing...");
    System.out.println("A:" + A);
    System.out.println("B" + B);

    System.out.println(">>> TEST FINISHED <<<");

  }
}