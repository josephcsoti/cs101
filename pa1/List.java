/*------------------------------------------------
File Name: List.java
Name:   Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:   10/09/18
------------------------------------------------*/

class List {

  Node head;
  Node tail;
  Node cur;

  class Node {

    Node prev;
    Node next;
    int val;

    Node(int val) {
      this.val = val;
      this.next = null;
      this.prev = null;
    }

  }

  // Constructor
  List() {
    head = null;
    tail = null;
    cur = null;
  }

  // Returns the number of elements in this List.
  int length() {
    if (head == null)
      return 0;

    int len = 0;
    Node cur = head;

    while (cur != null) {
      len++;
      cur = cur.next;
    }

    return len;
  }

  // If cursor is defined, returns the index of the cursor element,
  // otherwise returns -1.
  int index() {
    if (this.cur == null)
      return -1;

    int len = 0;
    Node cur = head;

    while (cur != null) {
      if (this.cur == cur)
        return len;
      cur = cur.next;
      len++;
    }

    return len;
  }

  // Returns front element. Pre: length()>0
  int front() throws RuntimeException {
    if (length() <= 0)
      throw new RuntimeException("List.java: front() - List is empty");

    return head.val;
  }

  // Returns back element. Pre: length()>0
  int back() throws RuntimeException {
    if (length() <= 0)
      throw new RuntimeException("List.java: back() - List is empty");

    return tail.val;
  }

  // Returns cursor element. Pre: length()>0, index()>=0
  int get() throws RuntimeException {
    if (length() <= 0)
      throw new RuntimeException("List.java: get() - List is empty");
    if (index() < 0)
      throw new RuntimeException("List.java: get() - Invalid index");

    return cur.val;
  }

  // Returns true if and only if this List and L are the same
  // integer sequence. The states of the cursors in the two Lists
  // are not used in determining equality.
  boolean equals(List L) {

    // check size
    if (this.length() == L.length()) {

      Node cur_a = this.head;
      Node cur_b = L.head;
      // check items
      while (cur_a != null || cur_b != null) {
        if (cur_a.val != cur_b.val)
          return false; // Value @ curr is different
        cur_a = cur_a.next;
        cur_b = cur_b.next;
      }
      return true; // All items are equal

    } else
      return false; // Size is diff

  }

  // Resets this List to its original empty state.
  void clear() {
    head = null;
    tail = null;
    cur = null;
  }

  // If List is non-empty, places the cursor under the front element,
  // otherwise does nothing.
  void moveFront() {
    if (length() > 0)
      cur = head;
  }

  // If List is non-empty, places the cursor under the back element,
  // otherwise does nothing.
  void moveBack() {
    if (length() > 0)
      cur = tail;
  }

  // If cursor is defined and not at front, moves cursor one step toward
  // front of this List, if cursor is defined and at front, cursor becomes
  // undefined, if cursor is undefined does nothing.
  void movePrev() {
    if (cur == null)
      return;

    if (cur == head) {
      cur = null;
      return;
    }

    if (cur != head) {
      cur = cur.prev;
      return;
    }
  }

  // If cursor is defined and not at back, moves cursor one step toward
  // back of this List, if cursor is defined and at back, cursor becomes
  // undefined, if cursor is undefined does nothing.
  void moveNext() {
    if (cur == null)
      return;

    if (cur == tail) {
      cur = null;
      return;
    }

    if (cur != tail) {
      cur = cur.next;
      return;
    }

  }

  // Insert new element into this List. If List is non-empty,
  // insertion takes place before front element.
  void prepend(int data) {
    Node node = new Node(data);

    // First node
    if (head == null) {
      head = node;
      tail = node;
      return;
    }

    // nth node
    head.prev = node;
    node.next = head;
    head = node;

  }

  // Insert new element into this List. If List is non-empty,
  // insertion takes place after back element.
  void append(int data) {
    Node node = new Node(data);

    // First node
    if (head == null) {
      head = node;
      tail = node;
      return;
    }

    // nth node
    node.prev = tail;
    tail.next = node;
    tail = node;

  }

  // Insert new element before cursor.
  // Pre: length()>0, index()>=0
  void insertBefore(int data) throws RuntimeException {
    if (length() <= 0)
      throw new RuntimeException("List.java: insertBefore() - List is empty");
    if (index() < 0)
      throw new RuntimeException("List.java: insertBefore() - Invalid index");

    // Equivalent to prepending
    if (cur == head) {
      prepend(data);
      return;
    }

    // prepare node
    Node node = new Node(data);
    node.prev = cur.prev;
    node.next = cur;

    // Insert at cur
    cur.prev.next = node;
    cur.prev = node;

  }

  // Inserts new element after cursor.
  // Pre: length()>0, index()>=0
  void insertAfter(int data) throws RuntimeException {
    if (length() <= 0)
      throw new RuntimeException("List.java: insertAfter() - List is empty");
    if (index() < 0)
      throw new RuntimeException("List.java: insertAfter() - Invalid index");

    // Equivalent to appending
    if (cur == tail) {
      append(data);
      return;
    }

    // Prepare node
    Node node = new Node(data);
    node.prev = cur;
    node.next = cur.next;

    // Insert node
    cur.next = node;
    cur.next.prev = node;
  }

  // Deletes the front element. Pre: length()>0
  void deleteFront() throws RuntimeException {
    if (length() <= 0)
      throw new RuntimeException("List.java: deleteFront() - List is empty");

    removeNode(head);
  }

  // Deletes the back element. Pre: length()>0
  void deleteBack() throws RuntimeException {
    if (length() <= 0)
      throw new RuntimeException("List.java: deleteBack() - List is empty");

    removeNode(tail);
  }

  // Deletes cursor element, making cursor undefined.
  // Pre: length()>0, index()>=0
  // Other methods
  void delete() throws RuntimeException {
    if (length() <= 0)
      throw new RuntimeException("List.java: delete() - List is empty");
    if (index() < 0)
      throw new RuntimeException("List.java: delete() - Invalid index");

    removeNode(cur);
  }

  // Overrides Object's toString method. Returns a String
  // representation of this List consisting of a space
  // separated sequence of integers, with front on left.
  public String toString() {
    String res = "";

    Node cur = head;
    while (cur != null) {
      res += cur.val + " ";
      cur = cur.next;
    }

    return res;
  }

  // Returns a new List representing the same integer sequence as this
  // List. The cursor in the new list is undefined, regardless of the
  // state of the cursor in this List. This List is unchanged.
  List copy() {

    List copy = new List();
    Node cur = head;

    while (cur != null) {
      copy.append(cur.val);
      cur = cur.next;
    }

    return copy;
  }

  // Generic helper function to help remove an given node
  void removeNode(Node node) {

    // Node n is cursor so set cur to (-1)
    if (cur == node)
      this.cur = null;

    // Only one node in the list
    if (length() <= 1) {
      head = null;
      tail = null;
      return;
    }

    // Remove head
    if (node == head) {
      head.next.prev = null;
      head = head.next;
      return;
    }

    // Remove tail
    if (node == tail) {
      tail.prev.next = null;
      tail = tail.prev;
      return;
    }

    // Remove body
    Node cur = head;
    while (cur.next != null) {
      if (cur == node) {
        cur.prev.next = cur.next;
        cur.next.prev = cur.prev;
        return;
      }
      cur = cur.next;
    }

  }

}