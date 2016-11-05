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
      : left(nullptr), right(nullptr), key(key), value(value) {}
   ~BinarySearchTreeNode()
   {
      delete left;
      delete right;
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
                  return;
               }
               flipFlop = flipFlop->right;
            }
            else
            {
               if (flipFlop->left == nullptr)
               {
                  flipFlop->left = current;
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
      // create a pointer to the root
      // where the fake root is not a nullptr
      // if the key is greater than or equal to the current node's key
      // go right
      // if the next node's right or 
      // else (it is less than the current node's key)
      // go left

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
            if (fake_root->key == key)
               return fake_root->value;

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
            if (fake_root->key == key)
               return fake_root;

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
         recurseSomewhere(mynode->left, isLeft);
      }
      else
      {
         if (myNode->right == nullptr)
         {
            return myNode;
         }
         recurseSomewhere(myNode->right, isLeft);
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
      BinarySearchTreeNode<Key, Value> *replace;
      bool isGoingLeft = true;
      if (dead->left != nullptr)
      {
         isGoingLeft = true;
         replace = recurseSomewhere(dead->left, isGoingLeft);
         // recurse right with dead->left
         // replace = cur
         // if(dead->key < dead->parent->key)
         // dead->parent->left = replace
         // else
         // dead->parent->right = replace

      }
      else
      {
         isGoingLeft = false;
         replace = recurseSomewhere(dead->left, isGoingLeft);
         // recurse left with dead->right
         // replace = cur
         // if(dead->key < dead->parent->key)
         // dead->parent->left = replace
         // else
         // dead->parent->right = replace

      }

   }
};
