// Lynn T. Aung
// 10-17-2023
// Doubly Linked List

import java.util.AbstractList;

public class DLinkedList<E> extends AbstractList<E>{

	private DNode<E> head;
	private DNode<E> tail;
	private int size;

	public DLinkedList(){
		head = new DNode<E>();
		tail = head;
		size = 0;
	}
    
    //Helper method to make sure the index doesn't go out of bounds
    private boolean isValidIndex(int i){
		return i >= 0 && i < size;
	}
    
    //Helper method to traverse the linked list with index
    private DNode<E> getNode(int index){
		if (!isValidIndex(index)){
			throw new IndexOutOfBoundsException();
		}
		DNode<E> current = head;
		for (int i=0; i<index; i++ ) {
			current = current.next;
		}
		return current;
	}

	/* appends element to end of the list */
	public boolean add(E e){
        DNode<E> node = new DNode<>(e);
		if (size == 0)
        {
            head = node;
            tail = node;
            size++;
            return true;
        }
        
        tail.next = node;
        node.prev = tail;
        tail = node;
        // Node.next is already null since it was instantiated above
        size++;
		return true;
	}

	/* insert element at the given index 
	if the index is out of bounds throw an IndexOutOfBoundsException */
	public void add(int index, E e){
        DNode<E> node = new DNode<>(e);
		if (index == 0)
        {
            // Set new node to be the head node
            head.prev = node;
            node.next = head;
            head = node;
            // Head node.prev is already null since instantiated above
            size++;
        }
        else if (index == size)
        {
            add(e);
        }
        else 
        {
            DNode<E> prev = getNode(index - 1); //Get node from before
            // The new node points to the original node's next 
            node.next = prev.next;
            // Now, the next node won't be gone, the next pointer of the prev node can be changed
            prev.next = node; 
            node.prev = prev; // point back to the node before the new node
            // change the pointer of the next node to the new node
            node.next.prev = node; 
            size++;
        }
	}
	public void clear(){
		head.next = null;
        head = null;
		tail = head;
		size = 0;
	}

	/* get the data from the node at the given index 
		if the index does not exist throw an IndexOutOfBoundsException */
	public E get(int index){
		DNode<E> current = getNode(index); // checks for exception
		return current.data;
	}

	/* remove the node at the given index from the list and return its data 
		if the index does not exist throw an IndexOutOfBoundsException */
	public E remove(int index){
		if (size == 0) 
            throw new IndexOutOfBoundsException(); 
        if (index == 0) 
        {
            E content = head.data;
            head = head.next; //Replace head
            //Change so that the head isn't pointing anything back
            head.prev = null; 
            size--;
            return content;
        } 
        if (index == size)
        {
            DNode<E> node = tail;
            E content = node.data;
            tail = node.prev; //Replace tail node
            tail.next = null; 
            size--;
            return content;
        }
        DNode<E> prev = getNode(index - 1);
        E content = prev.next.data;
        prev.next = prev.next.next; //Skip the original node
        size--;
        return content;
	}

	/* replace the contents at the given index with the data given
		return the data that was previously at that index 
		if the index does not exist throw an IndexOutOfBoundsException */
	public E set(int index, E element){
		if (size == 0)
            throw new IndexOutOfBoundsException();
        DNode<E> current = getNode(index);
        E content = current.data;
        current.data = element;
        return content;
	}

	public int size(){
		return size;
	}

	public String toString(){
		String list = "{";
		DNode<E> current = head;
		while (current != null){
			list += current.data.toString() + ", ";
			current = current.next;
		}
		return list + "}";
	}

	// internal class for single linking nodes
	class DNode<E> {
		E data;
		DNode<E> next;
		DNode<E> prev;

		public DNode(){
			this(null);
		}

		public DNode(E data){
			this.data = data;
			next = null;
			prev = null;
		}

		public DNode(E data, DNode<E> prev, DNode<E> next){
			this.data = data;
			this.prev = prev;
			this.next = next;
		}
	}
	
}