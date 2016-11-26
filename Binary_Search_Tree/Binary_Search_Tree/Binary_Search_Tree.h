#pragma once
#include <iostream>

using namespace std;

template <typename Key, typename Value>
struct BinarySearchTreeNode {
   BinarySearchTreeNode *left, *right, *parent;
   Key key;
   Value value;

   template<typename Callable>
   void traverse(const Callable& callable) // this will allow access to key and value
   {
      if (left != nullptr)
         left->traverse(callable);
      callable(key, value);
      /* ::NOTE TO RAY
      This line of code specifies what arguments callable are allowed to take in.
      Before this, arguments are anything, and will compile with code such as
      callable(key);
      callable();
      callable(left ,right ,key ,value);
      callable(callable);
      etc.
      and will be specified as such afterwards.
      */
      if (right != nullptr)
         right->traverse(callable);
   }


   BinarySearchTreeNode(const Key& key, const Value& value)
      : left(nullptr), right(nullptr), parent(nullptr), key(key), value(value) {}
   ~BinarySearchTreeNode()
   {
   }
};

template <typename Key, typename Value>
class BinarySearchTree {
public:
   BinarySearchTreeNode<Key, Value> *root;

   BinarySearchTree() : root(nullptr) {}

   ~BinarySearchTree()
   {
   }

   Value& getRootVal()
   {
      return root->value;
   }
   // PART 1
   // Insert a value, while making sure the tree is still a binary search tree.
   // This assumes that the key does not exist in the tree.
   void insert(const Key& key, const Value& value)
   {
      BinarySearchTreeNode<Key, Value> *current = new BinarySearchTreeNode<Key, Value>(key, value);
      if (root == nullptr) //  nothing in the BS tree
      {
         // add a node and update root
         root = current;
         return;
      }
      else
      {
         BinarySearchTreeNode<Key, Value> *flipFlop = root;
         for (; flipFlop != nullptr;) // loops until the pointer is a nullptr
         {

            if (key >= flipFlop->key) // if the key is greater than the currents key
            {
               if (flipFlop->right == nullptr) // check to see if the next iteration will be a nullptr
               {
                  // set it to the new node and exit the function
                  flipFlop->right = current;
                  flipFlop->right->parent = flipFlop;
                  return;
               }
               flipFlop = flipFlop->right;
            }
            else
            {
               if (flipFlop->left == nullptr)
               {
                  flipFlop->left = current;
                  flipFlop->left->parent = flipFlop;
                  return;
               }
               flipFlop = flipFlop->left;
            }


         }
         // cout << "current node: " << flipFlop << " value: " << flipFlop->value << "\nleft: " << flipFlop->left << " right: << flipFlop->right << "\n";
      }
   }

   // PART 1
   // Given a key, find the corresponding value.
   // This assumes that the key exists.
   Value& get(const Key& key) const
   {
      BinarySearchTreeNode<Key, Value> *fake_root = root; // preserves the root
      for (BinarySearchTreeNode<Key, Value> *flipFlop = root; fake_root != nullptr; fake_root = flipFlop) // creates a switch that either goes left or right depending on the code
      {
         if (key >= fake_root->key) // key is greater than or equal to root->key
         {
            if (fake_root->key == key)
               return fake_root->value;

            flipFlop = fake_root->right;
         }
         else
         {
            flipFlop = fake_root->left;
         }
      }
   }

   // PART 1
   // Given a callable, that takes a Key and Value, call that callable
   // for every key/value pair in the tree in sorted order.
   // e.g. callable(Key(), Value()) // IN ORDER
   template <typename Callable>
   void for_each_key_val(const Callable& callable)
   {
      if (root != nullptr)
         return root->traverse(callable);
   }

   BinarySearchTreeNode<Key, Value> *findNode(const Key& key)
   {
      BinarySearchTreeNode<Key, Value> *fake_root = root; // preserves the root
      for (BinarySearchTreeNode<Key, Value> *flipFlop = root; fake_root != nullptr; fake_root = flipFlop) // creates a switch that either goes left or right depending on the code
      {
         if (key >= fake_root->key) // key is greater than or equal to root->key
         {
            if (fake_root->key == key)
               return fake_root;

            flipFlop = fake_root->right;
         }
         else
         { 
            flipFlop = fake_root->left;
         }
      }
   }

   BinarySearchTreeNode<Key, Value> *recurseSomewhere(BinarySearchTreeNode<Key, Value> *myNode, bool isLeft)
   {
      if (isLeft)
      {
         // recurse left
         if (myNode->left == nullptr)
         {
            return myNode;
         }
         return recurseSomewhere(myNode->left, isLeft);
      }
      else
      {
         if (myNode->right == nullptr)
         {
            return myNode;
         }
         return recurseSomewhere(myNode->right, isLeft);
         
         //recurse right
      }

   }

   // PART 2
   // Remove the value associated with key,
   // while making sure the tree is still a binary search tree.
   // This assumes that the key exists.
   void remove(const Key& key)
   {
      BinarySearchTreeNode<Key, Value> *dead = findNode(key);
      BinarySearchTreeNode<Key, Value> *replace = nullptr;
      bool isGoingLeft = true;

      // handles cases of left and right subtrees, and left subtrees
      if (dead->left != nullptr)
      {        

         isGoingLeft = false;
         replace = recurseSomewhere(dead->left, isGoingLeft); // goes to the left one, then goes right until it finds null.
         // handle case of the root being removed
         if (dead == root)
         {
            if (dead->right != nullptr)
            {
               replace->right = dead->right;
               dead->right->parent = replace;
            }
            root = dead->left;
            delete dead;
            return;
         }
         // if the node is less than it's parent
         if (dead->key < dead->parent->key)
         {
            dead->parent->left = dead->left;
            dead->left->parent = dead->parent;
         }
         else
         {
            dead->parent->right = dead->left;
            dead->left->parent = dead->parent;
         }
         if (dead->right != nullptr)
         {
            replace->right = dead->right;
            dead->right->parent = replace;
         }
        delete dead;
      }
      // handles cases of right subtrees
      else if(dead->right != nullptr)  // if it has children at all
      {
         // handle the case of the BS tree only having right sub-trees

         isGoingLeft = true;
         replace = recurseSomewhere(dead->right, isGoingLeft);
         if (dead == root)
         {
            root = dead->right;
            delete dead;
            return;
         }

         if (dead->key < dead->parent->key)
         {
            dead->parent->left = dead->right;
            dead->right->parent = dead->parent;
         }
         else
         {
            dead->parent->right = dead->right;
            dead->right->parent = dead->parent;
         }
         delete dead;
      }
      // handles case of one nothing connected to the node's subtrees
      else
      {
         if (dead != root)
         {
            if (dead->key < dead->parent->key)
               dead->parent->left = nullptr;
            else
               dead->parent->right = nullptr;
         }
         else
            root = nullptr;
        delete dead;
      }
   }
};
