/** BST.h - Templated Binary Search Tree
 * Peter Turner - Spring 2012
 */

#include "stdafx.h"
#include "ErrorManager.h"
#include <iostream>
#include <Windows.h>

/** class BSTNode - Node for the binary search tree.
 */

template <typename T> class BST;

template <typename T> class BSTNode {
public:
   BSTNode<T> (T *d, BSTNode<T> *p) : data(d), parent(p), left(NULL), right(NULL) {}

private:
   friend class BST<T>;
   
   BSTNode<T> *left;
   BSTNode<T> *right;
   BSTNode<T> *parent;
   T *data;   
};

   /* BST -- Binary Search Tree
   Maintains a blank dummy node.  Both of its children are the root.

   --- Interface ---
   T *Find(UINT id) --> Returns the node containing the specified data element -- O(log n)
   void Insert(T) --> Inserts the data element into a NEW node -- O(log n)
   void BInsert(T) --> Inserts the data element into a NEW node
                        Additionally, it balances the entire tree. -- O(n log n)   
   void Balance() --> Balances the tree -- O(n log n)
   void Clear() --> Deletes all nodes in the tree with the exception of the dummy (root's root). --> O(n)
   bool Erase (T) --> Deletes and removes the specified data node from the tree. Returns true on success. --> O(n log n) ?
   UINT NodeCount() --> Returns the number of nodes in the tree -- O(n)
   */

template <typename T>
class BST { 
   friend class BSTNode<T>;
   
   BSTNode<T>* dummy;
   BSTNode<T>* root;
public:
   explicit BST<T> () : dummy (new BSTNode<T>(new T(), NULL)), 
            root(NULL) {
      dummy->left = root;
      dummy->right = root;
   }
   explicit BST<T> (const T& r) : dummy (new BSTNode<T>(T(), NULL)), 
            root(new BSTNode<T>(r, dummy)) {
      dummy->left = root;
      dummy->right = root;
   }
   ~BST<T>() {
      Clear();
      delete dummy;   
   } 
  
   //----------------------------------------------------------------------------
   // Custom for Asset Manager
   // Finds the node holding a particular data by ID. 
   // Returns NULL if the item does not exist. 
   T *Find (UINT input) {
      BSTNode<T> *current = root;
      if (root == NULL) {
         return NULL;
      }
      bool found = false;
       
      while (1) {
         if (*(current->data) == input) {
            return current->data; // found
         }
         if (*(current->data) < input) {
            if (current->right != NULL) {
               current = current->right;
            } else {
               return NULL;
            }
         } else { // input.data < current->data
            if (current->left != NULL) {
               current = current->left;
            } else {
               return NULL;
            }
         }     
      } 
   }
   
   //----------------------------------------------------------------------------
  
   // Inserts the data into a newly allocated node.
   void Insert(T *input) {
      BSTNode<T> *newParent = NULL;
      
      newParent = findParent (input); // Find the future parent of our new addition
      if (newParent == dummy) {
         root = new BSTNode<T> (input, dummy);
         dummy->left = root;
         dummy->right = root;
         root->parent = dummy;        
         return;
      }
      if (newParent == NULL) { // duplicate      
         return;
      }    
      if (*input < *(newParent->data)) {
         newParent->left = new BSTNode<T> (input, newParent);
         return;            
      }
      else {
         newParent->right = new BSTNode<T> (input, newParent);
         return;        
      }
       
   }

   //----------------------------------------------------------------------------
   // Inserts the new element and then balances the whole tree.
   void BInsert(const T& input) {
     insert(input);
     balance();     
   }
   
   //----------------------------------------------------------------------------
   // Deletes all elements from the tree recursively. This includes the root.
   // Kills all external pointers to nodes.    
   void Clear() {
      if (root != NULL) {
         recursiveDelete(root);
      }
   }
   
   //----------------------------------------------------------------------------
   // Erases element with data value item from the tree    
   bool Erase (const T& item) {
      BSTNode<T> *current = find (item);
      BSTNode<T> *link = NULL;
      BSTNode<T> *smallest = NULL;
      bool rootFlag = false;
      
      if (current == root) {
         rootFlag = true;
      }

      if (current == NULL) {
         return false; // not found.
      }
      
      if (noChild(current)) { // leaf         
         if (current->parent->left == current) {
            current->parent->left = NULL;
         } else if (current->parent->right == current) {
            current->parent->right = NULL;
         }
         delete current;
         
         if (rootFlag) {
            root = NULL;
            dummy->left = NULL;
            dummy->right = NULL;
         }
         return true;
      } else if (singleChild(current)) { // 1 child    
         if (current->left != NULL) {
            link = current->left;
         } else if (current->right != NULL) {
            link = current->right;
         }    
         
         if (current->parent->left == current) {
            current->parent->left = link;
         } else if (current->parent->right == current) {
            current->parent->right = link;
         }
         link->parent = current->parent;
            delete current;
    
         if (rootFlag) {
            root = link;
            dummy->left = root;
            dummy->right = root;
         }                
         return true;
      } else { // 2 children. not actually splicing out node. just altering data
              // and then deleting a leaf.
         smallest = current->right;
         while (smallest->left != NULL) { // find smallest in right subtree
            smallest = smallest->left;
         }
         *(current->data) = *(smallest->data);
         
         if (smallest == current->right) { // direct child is the smallest
             if (noChild(smallest)) {
                current->right = NULL;
             } else {
                current->right = smallest->right;
                current->right->parent = current;  
            }
         } else {
            smallest->parent->left = NULL;
         }
         delete smallest;
      }   
   }   

   //----------------------------------------------------------------------------
   // Counts and returns the number of nodes    
   UINT NodeCount() {
      return recursiveCountNodes(root);
   }
   
   //----------------------------------------------------------------------------
      
   // Balance the tree. Return the new depth.
   // !Warning: Destroys external pointers to nodes!
   void Balance() {
      // Rebuild tree by first sorting, then adding them in the proper order.
      UINT nodeCount = recursiveCountNodes(root);
      T *nodeArray = new T[nodeCount]; // temporary array

      for (int i = 0; i < nodeCount; i++) {
         T smallest = findSmallest(root);
         nodeArray[i] = smallest;         
         erase(smallest);  // right now it erases based on T.  should add function to erase based on *node
      }      
      clear();
      recursiveInsert(nodeArray, 0, nodeCount);      
      delete nodeArray;
   }


private:
   // Count nodes from parameter. Recursive.    
   UINT recursiveCountNodes(BSTNode<T> *current) {
      static UINT number = 0;

      if (current == root) { // Reset if we're starting fresh
         number = 0;
      }
      ++number;
      
      if (current->left != NULL) {
         recursiveCountNodes(current->left);  
      }
      if (current->right != NULL) {
         recursiveCountNodes(current->right);
      }
      return number;
   }
   
   //----------------------------------------------------------------------------
   // Returns value of smallest element    
   T* findSmallest(BSTNode<T> *current) {      
      while (1) {
         if (current->left != NULL) {
            current = current->left;
         } else {
            return current->data;
         }
      }
   }

   //----------------------------------------------------------------------------
   
   // does the node have any children?    
   bool noChild (BSTNode<T> *p) {
      return (p->left == NULL && p->right == NULL);
   }
   
   //----------------------------------------------------------------------------
   
   // does the node have only one child?    
   bool singleChild (BSTNode<T> *p) {
      if (noChild(p)) {
         return false;
      }
      return (p->left == NULL || p->right == NULL);
   }
	
   //----------------------------------------------------------------------------
   
   void recursiveDelete(BSTNode<T> *current) {
      if (current == NULL) {
         return;
      }
      if (current == root) {
         if (current->left == NULL && current->right == NULL) {
            dummy->left = dummy->right = NULL;
            return;
         }
      }
      if (current->left != NULL) {
         recursiveDelete(current->left);
      }
      if (current->right != NULL) {
         recursiveDelete(current->right);
      }
      
      if (current->parent->left == current) {
         current->parent->left = NULL;
      }
      if (current->parent->right == current) {
         current->parent->right = NULL;
      }
      if (current == root) {
         if (current->left == NULL && current->right == NULL) {
            dummy->left = dummy->right = NULL;
            delete current; // Boom      
            return;
         }
      }
      
   }

   //----------------------------------------------------------------------------
   // Used to recursively insert elements from an array for balancing.
   void recursiveInsert(T *dataArray, UINT low, UINT high) {
      UINT range = high-low;
      if (range == 0) {
         return;
      }
      UINT middle = low + range/2;
      insert(dataArray[middle]);
      if (range == 1) {
         return;
      }
      recursiveInsert(dataArray, low, middle);
      recursiveInsert(dataArray, middle+1, high);
   }

   //----------------------------------------------------------------------------
   // Finds the future parent of a new addition. Returns NULL if the new item already exists.
   // Otherwise returns the parent of new child.   
   BSTNode<T> *findParent (T *input) {
      if (root == NULL || dummy->left == NULL) {
         return dummy;
      } 
      BSTNode<T> *current = root;      
       
      while (1) {
         if (*input == *(current->data)) {
            return NULL; // duplicate
         }

         if (*input > *(current->data)) {
            if (current->right != NULL) {
               current = current->right;
            }
            else { // Right child is target, so return current (parent)
               return current;
            }
         } else { // input < current->Data
            if (current->left != NULL) {
               current = current->left;
            } else { // Left child is target, so return current (parent)
               return current;
            }
         }         
      } 
   }
   
   //----------------------------------------------------------------------------

   // Finds the node holding a particular data. Returns NULL if the item does not exist.   
   BSTNode<T> *find (const T &input) {
      BSTNode<T> *current = root;
      bool found = false;
        if (root == NULL) {
         return NULL;
      }
      while (1) {
         if (input == current->data) {
            return current; // found
         }
         if (input > current->data) {
            if (current->right != NULL) {
               current = current->right;
            } else {
               return NULL;
            }
         } else { // input.data < current->data
            if (current->left != NULL) {
               current = current->left;
            } else {
               return NULL;
            }
         }     
      } 
   }
   
   //--------- Debugging Tools ---------

public:
   // Interactive tree manipulation. 
   void walk () { 
      BSTNode<T> *current = root;
      BSTNode<T> *kill = current;
      size_t input = 1;
      while (input != 0) {
         if (current == dummy) current = root;
         std::cout << "Your Data: " << current->data<< std::endl;
         
         if (current == root) std::cout << "[ROOT] " << std::endl;
         else
            std::cout << " | [1] Parent: " << current->parent->data << std::endl;
         if (current->left == NULL)
            std::cout << " | Left: NULL"<< std::endl;
         else
            std::cout << " | [2] Left: " << current->left->data << std::endl;
         if (current->right == NULL)
            std::cout << " | Right: NULL"<< std::endl;
         else
            std::cout << " | [3] Right: " << current->right->data << std::endl;
         std::cout << " | [4] Erase " << std::endl;   
         std::cout << " | [0] Exit " << std::endl;
         std::cin >> input;
         switch (input) {
         case 1: 
            if (current != root)
               current = current->parent;
            break;
         case 2:
            if (current->left != NULL)
               current = current->left;
            break;
         case 3:
            if (current->right != NULL)
               current = current->right;
            break;
         case 4:
            kill = current;
            current = current->parent;
            erase (kill->data);
            break;
         default:
            break;
         }
      }   
   }
   
   //---------------------------------------------------------------------------- 

   void display () {
      traverse (root);        
   }
   	
   //----------------------------------------------------------------------------

   UINT countNodes() {
      return countNodes(root);
   }
   	
   //----------------------------------------------------------------------------
   
   void traverse (BSTNode<T> *b) { // displays Data of tree, beginning at root
      std:: cout << " Data: " <<  b->data;            
      if (b->left == NULL) {
         std:: cout << " Left: NULL ";
      }
      else {
         std:: cout << " Left: " << b->left->data;
      }
      if (b->right == NULL) {
         std:: cout << " Right: NULL ";
      }
      else {
         std:: cout << " Right: " << b->right->data;
      }
      std::cout<<std::endl;

      if (b->left != NULL) {
         traverse(b->left);  
      }
      if (b->right != NULL) {
         traverse(b->right);
      }
      return;
   }       
};
//----------------------------------------------------------------------------