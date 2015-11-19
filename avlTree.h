#ifndef AVLTREE_H_
#define AVLTREE_H_
#include "exception.h"


template<class T> class Node;
template<class T> class Iterator;
template<class T> class AvlTree;

template<class T>
class Node {
	Node<T> *left;
	Node<T> *right;
	T data;
	/**
	 * Node c'tor. allocates new Node and a copy of the data object.
	 *
	 * @param object - T object to hold in this node
	 * @param left - a pointer to the left son in the tree.
	 * @param previous - a pointer to the right son in the tree.
	 * @return new Node
	 */
	Node(const T& object, Node<T> *left, Node<T> *right);
	friend class AvlTree<T> ;
	friend class Iterator<T> ;
public:
	~Node() = default;

	/**
	 * swapNodes - swap the nodes data
	 * @param - Node<T> *node - the node which data will be swapped with
	 *
	 * @return - no return value
	 */
	void swapNodes(Node<T> *node);
};

template<class T>
class Iterator {
	Node<T> *node;
	AvlTree<T> *avlTreePtr;
	/**
	 * Iterator c'tor. allocates new Iterator.
	 *
	 * @param node - a pointer to the node the iterator is pointing at.
	 * in case we want to return iterator to the end of the tree, set it as
	 * nullptr.
	 * @param avlTree - a pointer to the avlTree the iterator belongs to.
	 * @return new Node
	 */
	Iterator(Node<T> *node, List<T> *avlTree = nullptr);
	friend class AvlTree<T> ;

public:
	//default copy constructor for Iterator
	Iterator(const Iterator<T>& iter) = default;
	//default destructor for Iterator
	~Iterator() = default;
	//default operator= for Iterator
	Iterator<T>& operator=(const Iterator<T>& iter) = default;

	/**
	 * postfix iterator++ - call's when iterator++ used
	 * 						the operator proceed the iterator to next element in the tree,
	 * 						but return's the previous one. Using inorder
	 *
	 * @throw - IllegealOperationException - if current iterator points to the tree's end
	 *
	 * @return Iterator<T> - an iterator to the same element in the tree
	 */
	Iterator<T> operator++(int);

	/**
	 * postfix iterator-- - call's when iterator-- used
	 * 						the operator proceed the iterator to previous element in the tree,
	 * 						but return's the previous one.
	 *
	 * @throw - IllegealOperationException - if current iterator points to the tree's root.
	 *
	 * @return Iterator<T> - an iterator to the same element in the tree
	 */
	Iterator<T> operator--(int);
	/**
	 * operator* - used to "dereference" an iterator, returns a data of the element
	 * 			   		in the tree that is pointed by the iterator
	 * @throw - TreeExceptions::ElementNotFound - if the iterator points to tree's end
	 *
	 * @return - T& - a reference to the data stored in the current node.
	 */
	T& operator*() const;
	/**
	 * operator== - compares two iterators.
	 * @param const Iterator<T>& iter - an iterator to be compared to.
	 * @return - true if the iterators belong to the same tree , and points
	 * 			to the same node. false otherwise.
	 */
	bool operator==(const Iterator<T>& iter) const;
	/**
	 * operator!= - compares two iterators.
	 * @param const Iterator<T>& iter - an iterator to be compared to.
	 * @return - false if the iterators belong to the same tree , and points
	 * 				to the same node. true otherwise.
	 */
	bool operator!=(const Iterator<T>& iter) const;
};

template<class T>
class AvlTree {
	Node<T> *root;
public:
	AvlTree();
	
	/**
	 * copy c'tor of avlTree. copies all the elements in the tree.
	 * @param avlTree - const reference to the tree we want to create a copy of.
	 * @return
	 */
	AvlTree(AvlTree& avlTree);
	/**
	 * avlTree destructor - used to clear the tree memory.
	 */
	~AvlTree();
	
	AvlTree<T>& operator=(const AvlTree<T>& AvlTree);
	
	/**
	 * begin - return an iterator to the root of the tree.
	 * in case the tree is empty, returns an iterator to the end of the tree.
	 *
	 * @return iterator to the root.
	 */
	Iterator<T> begin();

	/**
	 * end - returns an iterator to the end of the tree. the iterator will
	 * 		 not point to the last element in the tree, but states a special
	 * 		 condition of the tree's end.
	 * @return - Iterator<T> - an iterator of type T (the type of tree).
	 *
	 */
	Iterator<T> end();
	 
	/**
	 * insert - insert new element to the tree of type T. Inserts a copy
	 * of the object. Keep the tree a search tree and legal AVL tree
	 *
	 * @param data - const reference to T object we want to insert.
	 *
	 * @return void
	 */
	void insert(const T& data);
	
	/**
	 * remove - remove an object from the tree, pointed by the iterator provided.
						 keeping the tree a legal AVL tree.
	 * @param - Iterator<T> - an iterator of the type of the tree, points
	 * 						  the element to be removed
	 * @throw - TreeExceptions::ElementNotFound -  in the following cases:
	 * 							iterator points to the end of the list
	 * 							iterator belongs to different list
	 * 							list is empty
	 * @return void - no return value
	 */
	void remove(Iterator<T> iterator);
	
	/**
	 * find - find an object in the tree according to a specific condition
	 * given in predicate.
	 *
	 * @return - if the object is in the tree, returns iterator to
	 * the first appearance of this object, otherwise, returns iterator to
	 * the end of the tree.
	 */
	template<class Predicate>
	Iterator<T> find(const Predicate& predicate);
	
};

/************** Node class Functions************/
template<class T>
Node<T>::Node(const T& object, Node<T> *left, Node<T> *right) :
		left(left), right(right), data(object) {
}

template<class T>
void Node<T>::swapNodes(Node<T> *node) {
	T temp = node->data;
	node->data = this->data;
	this->data = temp;
}

/**************End of Node class Functions************/

/************** Iterator class Functions************/
template<class T>
Iterator<T>::Iterator(Node<T> *node, AvlTree<T> *avlTree) :
		node(node), avlTree(avlTree) {
}

template<class T>
Iterator<T> Iterator<T>::operator--(int n) {
	if (this->node == nullptr) {
		throw IllegealOperationException();
	}
	Node<T> *iterNode = this->node;
	this->node = iterNode->next;
	return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator++(int n) {
	Iterator<T> iter = Iterator(*this);
	++*this; //call the prefix operator
	return iter;
}

template<class T>
T& Iterator<T>::operator*() const {
	if (this->node == nullptr) {
		throw TreeExceptions::ElementNotFound();
	}
	Node<T> *iterNode = this->node;
	return iterNode->data;
}

template<class T>
bool Iterator<T>::operator==(const Iterator<T>& iter) const {
	return (this->node == iter.node) && (this->listPtr == iter.listPtr);
}

template<class T>
bool Iterator<T>::operator!=(const Iterator<T>& iter) const {
	return !(*this == iter);
}

/**************End of Iterator class Functions************/

/************** List class Functions************/
template<class T>
AvlTree<T>::AvlTree() :
		root(nullptr) {
}

template<class T>
AvlTree<T>::AvlTree(AvlTree<T>& avlTree) {
	head = nullptr;
	Iterator<T> newListIter = this->end();
	Node<T> *nodeIter = list.head;
	while (nodeIter != nullptr) {
		this->insert(nodeIter->data, newListIter);
		newListIter = this->end();
		nodeIter = nodeIter->next;
	}
}

template<class T>
AvlTree<T>::~AvlTree() {
	Iterator<T> iter = this->begin();
	while (iter.node != nullptr) {
		this->remove(iter);
		iter = this->begin();
	}
}

template<class T>
AvlTree<T>& AvlTree<T>::operator=(const AvlTree<T>& avlTree) {
	if (this == &list) {
		return *this;
	}
	while (this->head != nullptr) {
		this->remove(this->begin());
	}
	Node<T> *nodeIter = list->head;
	while (nodeIter != nullptr) {
		this->insert(nodeIter->data, this->end());
		nodeIter = nodeIter->next;
	}
}

template<class T>
Iterator<T> AvlTree<T>::begin() {
	Iterator<T> iter(this->head, this);
	return iter;
}

template<class T>
Iterator<T> AvlTree<T>::end() {
	Iterator<T> iter(nullptr, this);
	return iter;
}

template<class T>
void AvlTree<T>::insert(const T& data, Iterator<T> iterator) {
	if (iterator.listPtr != this) {
		throw TreeExceptions::ElementNotFound();
	}
	if (iterator.node == nullptr) {
		if (this->head == nullptr) {
			this->head = new Node<T>(data, nullptr, nullptr);
			return;
		} else {
			Node<T> *nodeIter = this->head;
			while (nodeIter->next != nullptr) {
				nodeIter = nodeIter->next;
			}
			Node<T> *newNode = new Node<T>(data, nullptr, nodeIter);
			nodeIter->next = newNode;
			return;
		}
	}
	Node<T> *iteratorNode = iterator.node;
	Node<T> *iteratorPrev = iteratorNode->previous;
	Node<T> *newNode = new Node<T>(data, iteratorNode, iteratorPrev);
	iteratorNode->previous = newNode;
	if (iteratorPrev != nullptr) {
		iteratorPrev->next = newNode;
	} else {
		this->head = newNode;
	}
	return;
}

template<class T>
void AvlTree<T>::remove(Iterator<T> iterator) {

	if (head == nullptr || iterator.node == nullptr) {
		throw TreeExceptions::ElementNotFound();
	}
	if (iterator.listPtr != this || iterator.listPtr == nullptr) {
		throw TreeExceptions::ElementNotFound();
	}

	Node<T> *node = iterator.node;
	if (node->previous != nullptr) {
		Node<T> *prev = node->previous;
		prev->next = node->next;
	}
	if (node->next != nullptr) {
		Node<T> *next = node->next;
		next->previous = node->previous;
	}
	if (node->previous == nullptr) {
		this->head = node->next;
	}
	delete node;

	return;

}

template<class T>
template<class Predicate>
Iterator<T> AvlTree<T>::find(const Predicate& predicate) {
	Iterator<T> iter = this->begin();
	for (iter = this->begin(); iter != this->end(); iter++) {
		Node<T> *iterNode = iter.node;
		if (predicate(iterNode->data)) {
			return iter;
		}
	}
	return iter;
}


/**************End of List class Functions************/

#endif /* AVLTREE_H_ */
