/*------------------------------------------------
File Name: Matrix.java
Desc: "Matrix" data type using an array of linked lists
Instructions: None

Name:   Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:   10/09/18
------------------------------------------------*/

class Matrix {
  int size;
  int nnz;
  List<Entry>[] rows;

  // Constructor
  // Makes a new n x n zero Matrix. pre: n>=1
  Matrix(int n) {
    if (n < 1)
      throw new RuntimeException("Matrix.java: Matrix() - Cant create a matrix of size < 1");

    this.size = n;
    this.nnz = 0;
    this.rows = new List[n];

    for (int i = 0; i < size; i++)
      rows[i] = new List<Entry>();
  }

  // -------- Access functions --------------- //

  // Returns n, the number of rows and columns of this Matrix
  int getSize() {
    return size;
  }

  // Returns the number of non-zero entries in this Matrix
  int getNNZ() {
    return nnz;
  }

  // overrides Object's equals() method
  public boolean equals(Object x) {

    if (!(x instanceof Matrix))
      return false;

    Matrix M = (Matrix) x;

    if (M.getSize() == size && M.getNNZ() == nnz) {
      for (int i = 0; i < size; i++) {
        if (!rows[i].equals(M.rows[i]))
          return false;
      }
      return true;
    } else
      return false;
  }

  // --------- Manipulation procedures ------------ //

  // Set Matrix to zero state
  void makeZero() {
    for (int i = 0; i < size; i++)
      rows[i].clear();

    nnz = 0;
  }

  // Returns a new Matrix having the same entries as this Matrix
  Matrix copy() {
    Matrix res = new Matrix(size);
    for (int i = 0; i < size; i++) {
      List<Entry> list = rows[i];
      for (list.moveTo(0); list.index() != -1; list.moveNext()) {
        Entry entry = list.get();
        // System.out.println("Append");
        res.rows[i].append(entry);
        res.nnz++;
      }
    }
    res.nnz = getNNZ();
    return res;
  }

  // changes ith row, jth column of this Matrix to x
  // pre: 1<=i<=getSize(), 1<=j<=getSize()
  void changeEntry(int i, int j, double x) throws RuntimeException {

    if (!(i >= 0 && i <= getSize()) && !(j >= 0 && j <= getSize())) {
      throw new RuntimeException("Matrix.java: changeEntry() - index invalid");
    }

    List<Entry> list = rows[i - 1];
    Entry entry = new Entry(i, j, x);

    // find index
    int index = this.getEntryIndex(i, j);

    // Entry does not exist
    if (index == -1) {

      // If doesnt exist but wants "delete" somehow
      if (x == 0.0)
        return;

      // Is the row empty
      if (list.length() == 0) {
        list.append(entry);
        nnz++;
        return;
      }

      // row does exist, find closest element
      list.moveFront();
      for (list.index(); list.index() != -1; list.moveNext()) {
        Entry e = list.get();
        if (e.column > j) {
          list.insertBefore(entry);
          nnz++;
          return;
        } else if (list.index() == list.length() - 1) {
          list.append(entry); // End of list, appending
          nnz++;
          return;
        }

      }
    }
    // Entry exists
    else {
      // "remove" a entry
      if (x == 0.0) {
        list.moveTo(index);
        list.delete();
        nnz--;
        return;
      }

      // Change value of index
      list.moveTo(index);
      if (list.get().value != x) {
        list.insertBefore(entry);
        list.delete();
      }
    }

  }

  // Returns a new Matrix that is the scalar product of this Matrix with x
  Matrix scalarMult(double x) {

    Matrix res = new Matrix(size);

    for (int i = 1; i <= size; i++) {
      List<Entry> list = rows[i - 1];
      list.moveFront();
      for (int j = 1; j <= list.length(); j++) {
        Entry entry = list.get();
        res.changeEntry(entry.row, entry.column, entry.value * x);
        list.moveNext();
      }
    }

    return res;
  }

  // returns a new Matrix that is the sum of this Matrix with M
  // pre: getSize()==M.getSize()
  Matrix add(Matrix M) throws RuntimeException {

    if (getSize() != M.getSize())
      throw new RuntimeException("Matrix.java: add() - matrices are different sizes");

    if (this.equals(M))
      return this.scalarMult(2);

    Matrix res = M.copy();

    for (int i = 0; i < rows.length; i++) {
      res.rows[i] = addRow(1, i + 1, this.rows[i], res.rows[i]);
    }

    return res;
  }

  // returns a new Matrix that is the difference of this Matrix with M
  // pre: getSize()==M.getSize()
  Matrix sub(Matrix M) throws RuntimeException {

    if (getSize() != M.getSize())
      throw new RuntimeException("Matrix.java: sub() - matrices are different sizes");

    Matrix res = M.copy();

    for (int i = 0; i < rows.length; i++) {
      List<Entry> a = rows[i];
      List<Entry> b = res.rows[i];
      a.moveFront();
      b.moveFront();
      for (a.moveTo(0); a.index() != -1; a.moveNext()) {
        Entry e = a.get();
        int col = e.column;
        double diff = e.value;
        int index = res.getEntryIndex(i + 1, col);
        if (index != -1) {
          b.moveTo(index);
          Entry temp = b.get();

          if(temp.value < 0)
            diff = temp.value;
          else
            diff -= temp.value;
          }
          res.changeEntry(i + 1, col, diff);
        }
        
    }

    return res;
      }

  // Returns a new Matrix that is the transpose of this Matrix
  Matrix transpose() {

    Matrix res = new Matrix(size);

    for (int i = 0; i < size; i++) {
      List<Entry> a = rows[i];
      for (a.moveTo(0); a.index() != -1; a.moveNext()) {
        Entry e = a.get();
        int currCol = e.column;
        res.changeEntry(currCol, i + 1, e.value);
      }
    }
    return res;
  }

  // returns a new Matrix that is the product of this Matrix with M
  // pre: getSize()==M.getSize()
  Matrix mult(Matrix M) throws RuntimeException {

    if (getSize() != M.getSize())
      throw new RuntimeException("Matrix.java: mult() - matrices are different sizes");

    M = M.transpose();

    Matrix res = new Matrix(size);

    for (int i = 0; i < size; i++) {
      if (rows[i].length() != size)
        continue;
      else {
        for (int j = 0; j < size; j++)
          res.changeEntry(i, j, dot(this.rows[i], M.rows[i]));
      }
    }
    return res;
  }

  // ------- Other functions -----------

  // Overrides Object's toString() method, prints nnz rows
  public String toString() {

    String res = "";

    for (int i = 0; i < rows.length; i++) {
      if (rows[i].length() == 0)
        continue;
      else if (i == rows.length - 1)
        res += (i + 1) + ": " + rows[i].toString();
      else
        res += (i + 1) + ": " + rows[i].toString() + "\n";
    }

    return res;
  }

  // Return the dot product of 2 Lists
  private static double dot(List<Entry> P, List<Entry> Q) {

    double dot = 0;

    for (P.moveTo(0); P.index() != -1; P.moveNext()) {
      Entry pp = (Entry) P.get();
      for (Q.moveTo(0); Q.index() != -1; Q.moveNext()) {
        Entry qq = (Entry) Q.get();
        if (pp.column == qq.column) {
          dot += pp.value * qq.value;
          break;
        }
      }
    }
    return dot;
  }

  // Finds entry position in the matrix, returns -1 if DNE
  int getEntryIndex(int row, int column) {

    List<Entry> list = rows[row - 1];

    if (list.length() != 0) {
      list.moveFront();
      Entry entry;
      for (list.index(); list.index() != -1; list.moveNext()) {
        entry = list.get();
        if (entry.column == column)
          return list.index();
      }
    }

    return -1;
  }

  // Helper Function to simplify adding rows together
  List<Entry> addRow(int isneg, int row, List<Entry> P, List<Entry> Q) {
    List<Entry> PQ = new List();

    P.moveFront();
    Q.moveFront();

    for (int i = 0; i < Math.max(P.length(), Q.length()); i++) {

      // If running off list
      // P DNE
      if (i > P.length() - 1) {
        Entry e = Q.get();
        double val = e.value;
        e = new Entry(row, i + 1, val);
        PQ.append(e);
        Q.moveNext();
        continue;
      }

      // Q DNE
      if (i > Q.length() - 1) {
        Entry e = P.get();
        double val = e.value;
        e = new Entry(row, i + 1, val);
        PQ.append(e);
        P.moveNext();
        continue;
      }

      // Both P and Q exist at this point "middle"
      Entry a = P.get();
      Entry b = Q.get();

      // Lines up
      if (a.column == b.column) {
        double total = a.value + (isneg * b.value);
        // Only create and entry when value exists
        if (total != 0) {
          Entry e = new Entry(row, a.column, total);
          PQ.append(e);
        }
        P.moveNext();
        Q.moveNext();
        continue;
      } else if (a.column < b.column) { // A is before
        Entry e = new Entry(row, a.column, a.value);
        PQ.append(e);
        P.moveNext();
        continue;
      } else if (a.column > b.column) { // B is before
        Entry e = new Entry(row, b.column, isneg * b.value);
        PQ.append(e);
        Q.moveNext();
        continue;
      }
    }

    return PQ;
  }

  // Data type to store row, col, val in the Lists
  private class Entry {
    int row;
    int column;
    double value;

    Entry(int row, int column, double value) {
      this.row = row;
      this.column = column;
      this.value = value;
    }

    // Overrides equals()
    public boolean equals(Object obj) {
      if (obj instanceof Entry) {
        Entry other = (Entry) obj;
        return (this.row == other.row) && (this.column == other.column) && (this.value == other.value);
      } else
        return false;
    }

    // Prints entry data really pretty
    public String toString() {
      return "(" + column + ", " + value + ")";
    }
  }
}