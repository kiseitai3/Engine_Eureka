
#ifndef BST_H
#define BST_H
#include <iostream>
#include <vector>
#include <cassert>

//Prototypes
template<typename KeyTy, typename ValueTy>
void verbose(const KeyTy& key, ValueTy& value);



template<typename KeyTy, typename ValueTy>
class BinarySearchTree
{
public:
    //Typedefs
    typedef void (*TraversalFunction)(const KeyTy& key, ValueTy& value);
  //Structures
  struct TreeNode
  {
    KeyTy Key;
    ValueTy Value;
    TreeNode* pLeft;
    TreeNode* pRight;
    TreeNode(const KeyTy& key, const ValueTy& value,
             TreeNode* left = NULL, TreeNode* right = NULL);
  };

  //Methods
  BinarySearchTree();//ctor
  ~BinarySearchTree();//dtor
  //Mostly wrappers
  void insert(const KeyTy& key, const ValueTy& value);//inserts a node
  bool search(const KeyTy& key, ValueTy& value) const;//finds a node
  bool rsearch(const ValueTy& value, KeyTy& key) const;//finds the key of the node
  void remove(const KeyTy& key);// removes a node
  bool empty() const;//Returns true if empty
  size_t size() const;//Returns the size;
  size_t height() const;//Returns the height of the tree
  void clear();//Empties container
  //Getter
  std::vector<ValueTy> getContents();//Dumps all nodes into a linear structure.
  //Traveral methods
  void inorder(TraversalFunction func = verbose) const;//Order: left, root, right
  void postorder(TraversalFunction func = verbose) const;//Order: left, right, root
  void preorder(TraversalFunction func = verbose) const;//Order:root, left, right
  //Debugging
  void print() const;//Outputs the internal structure of the tree
  //Operator overloads
  ValueTy& operator [] (const KeyTy& key)//Provides [key] functionality, if defined in header it's because of template issues with compiler
  {
  /*This is a wrapper method. Check out the recursive funtions. */
  ValueTy* tmp = getValRef(Root, key);
  assert(tmp);//I can't think of another way.
  return *tmp;
  }

 private:
  //instance variables
  size_t Size;
  TreeNode* Root;//Root of the whole tree

  //Recursive methods (see wrappers)
  void insertNode(TreeNode*& root, const KeyTy& key, const ValueTy& value);
  bool searchNode(TreeNode* root, const KeyTy& key,  ValueTy& value) const;
  bool rsearchNode(TreeNode* root, const ValueTy& value,  KeyTy& key) const;
  void removeNode(TreeNode*& root, const KeyTy& key);
  void rem_swapNode(TreeNode*& root, TreeNode*& current);
  size_t computeHeight(TreeNode* root) const;
  void inorderNode(TreeNode* root, TraversalFunction& f) const;
  void preorderNode(TreeNode* root, TraversalFunction& f) const;
  void postorderNode(TreeNode* root, TraversalFunction& f) const;
  void printTree(TreeNode* root) const;
  ValueTy* getValRef(TreeNode* root, const KeyTy& key)
  {
  /*This method looks recursively for a node with the same key as key and
    returns a reference to the node's value.
  */
  if(!root)//Base case
    return NULL;

  if(root->Key == key)//We got lucky
    return &root->Value;
  else if(root->Key > key)//Otherwise, keep looking
    return getValRef(root->pLeft, key);
  else if(root->Key < key)
    return getValRef(root->pRight, key);
  return NULL;
}
  void freeTree(TreeNode* root);//Frees each node in the tree
  void dumpNode(TreeNode* root, std::vector<ValueTy>& holder);
};
//Max template function
template <class T>
  T max(const T& x, const T& y)
  {
    return x < y ? y:x;
  }

#include "BST.cc"
#endif

