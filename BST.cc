
template<typename KeyTy, typename ValueTy>
BinarySearchTree<KeyTy, ValueTy>::TreeNode::TreeNode(const KeyTy& key, const ValueTy& value,
				     TreeNode* left, TreeNode* right)
{
  //TreeNode ctor
  Key = key;
  Value = value;
  pLeft = left;
  pRight = right;
}

template<typename KeyTy, typename ValueTy>
BinarySearchTree<KeyTy, ValueTy>::BinarySearchTree()
{
  //BST ctor
  Size = 0;
  Root = NULL;
}

template<typename KeyTy, typename ValueTy>
BinarySearchTree<KeyTy, ValueTy>::~BinarySearchTree()
{
  /*BST dtor. Will deallocate the whole tree! */
  freeTree(Root);
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy, ValueTy>::insert(const KeyTy& key, const ValueTy& value)
{
 /*This is a wrapper method. Check out the recursive funtions. */
  if(Root)
    insertNode(Root, key, value);
  else
    {
      Root = new TreeNode(key, value);
      Size++;
    }
}

template<typename KeyTy, typename ValueTy>
bool BinarySearchTree<KeyTy, ValueTy>::search(const KeyTy& key, ValueTy& value) const
{
 /*This is a wrapper method. Check out the recursive funtions. */
  return searchNode(Root, key, value);
}

template<typename KeyTy, typename ValueTy>
bool BinarySearchTree<KeyTy, ValueTy>::rsearch(const ValueTy& value, KeyTy& key) const
{
 /*This is a wrapper method. Check out the recursive funtions. */
  return rsearchNode(Root, value, key);
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy, ValueTy>::remove(const KeyTy& key)
{
 /*This is a wrapper method. Check out the recursive funtions. */
  removeNode(Root, key);
}

template<typename KeyTy, typename ValueTy>
bool BinarySearchTree<KeyTy, ValueTy>::empty()const
{
 /*This is a wrapper method. Check out the recursive funtions. */
  return Size == 0;
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy, ValueTy>::clear()
{
    freeTree(Root);
}

template<typename KeyTy, typename ValueTy>
size_t BinarySearchTree<KeyTy, ValueTy>::size()const
{
 /*This is a wrapper method. Check out the recursive funtions. */
  return Size;
}

template<typename KeyTy, typename ValueTy>
size_t BinarySearchTree<KeyTy, ValueTy>::height()const
{
 /*This is a wrapper method. Check out the recursive funtions. */
  return computeHeight(Root);
}

template<typename KeyTy, typename ValueTy>
std::vector<ValueTy> BinarySearchTree<KeyTy, ValueTy>::getContents()
{
    std::vector<ValueTy> holder;
    holder.reserve(Size);//pre allocate space in order to boost performance (decreasing realloc and copy calls).
    dumpNode(Root, holder);
    return holder;
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy, ValueTy>::inorder(TraversalFunction func)const
{
 /*This is a wrapper method. Check out the recursive funtions. */
  inorderNode(Root, func);
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy, ValueTy>::postorder(TraversalFunction func)const
{
 /*This is a wrapper method. Check out the recursive funtions. */
  postorderNode(Root, func);
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy, ValueTy>::preorder(TraversalFunction func)const
{
 /*This is a wrapper method. Check out the recursive funtions. */
  preorderNode(Root, func);
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy, ValueTy>::print()const
{
 /*This is a wrapper method. Check out the recursive funtions. */
  printTree(Root);
  std::cout << std::endl;
}

/*template<typename KeyTy, typename ValueTy>
BinarySearchTree<KeyTy,ValueTy>::ValueTy& BinarySearchTree<KeyTy, ValueTy>::operator []
(const KeyTy& key)
{*/
  /*This is a wrapper method. Check out the recursive funtions. */
 /* ValueTy* tmp = getValRef(Root, key);
  if(!tmp)
    {
      insert(key, 0);
      return *(getValRef(Root, key));
    }
  else
    return *tmp;
}
*/
//Recursive methods
template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy,ValueTy>::insertNode(TreeNode*& root,
				  const KeyTy& key, const ValueTy& value)
{
  /*This method will insert a new node in the appropriate subtree.
   */
  if(!root)//Base case. We insert here!
    {
      root = new TreeNode(key, value);
      Size++;
      return;
    }

  //Search for the appropriate spot.
  if(root->Key > key)
    {
      insertNode(root->pLeft, key, value);
    }
  else if(root->Key < key)
    {
      insertNode(root->pRight, key, value);
    }
}

template<typename KeyTy, typename ValueTy>
bool BinarySearchTree<KeyTy,ValueTy>::searchNode(TreeNode* root,
				  const KeyTy& key,  ValueTy& value) const
{
  /*This method searches for a node and returns true or false if found.
    Furthermore, it returns the value of the node via the parameter value.
  */
  if(!root)//Base case
    return false;

  if(root->Key == key)//We got lucky
  {
    value = root->Value;
    return true;
  }
  else if(root->Key > key)//Keep searching
  {
    return searchNode(root->pLeft, key, value);
  }
  else if(root->Key < key)
  {
   return  searchNode(root->pRight, key, value);
  }

  return false;
}

template<typename KeyTy, typename ValueTy>
bool BinarySearchTree<KeyTy,ValueTy>::rsearchNode(TreeNode* root,
				  const ValueTy& value,  KeyTy& key) const
{
  /*This method searches for a node and returns true or false if found.
    Furthermore, it returns the key of the node via the parameter value.
  */
  if(!root)//Base case
    return false;

  if(root->Value == value)//We got lucky
  {
    key = root->Key;
    return true;
  }
  else if(root->Value > value)//Keep searching
  {
    return rsearchNode(root->pLeft, value, key);
  }
  else if(root->Value < value)
  {
   return  rsearchNode(root->pRight, value, key);
  }

  return false;
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy,ValueTy>::removeNode(TreeNode*& root, const KeyTy& key)
{
  /*This method searches for a node and "removes" it. This method makes use
    of another helper method to search for the appropriate node in the left
    subtree to swap with. The "rem" part of rem_swapNode indicates it will
    be used for removal purposes.
  */
  assert(!empty());
  if(!root)//Base case
    return;

  if(root->Key == key)//If we got lucky
  {
    if(!root->pLeft)//If no left, then I just have to change root and delete
      {              //this node.
	TreeNode* tmp = root->pRight;
	delete root;
	root = tmp;
      }
    else if(root->pLeft)//If there's a left subtree, go hunting with swapNode
      {
	rem_swapNode(root, root->pLeft);
      }
    Size--;//Decrement after deletion
    return;
  }

  //Otherwise, keep looking in the appropriate subtree!
  if(root->Key > key)
    removeNode(root->pLeft, key);
  else if(root->Key < key)
    removeNode(root->pRight, key);
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy,ValueTy>::rem_swapNode(TreeNode*& root, TreeNode*& current)
{
  /* This method searches for the rightmost node of a subtree and copies
     its nonpointer contents to the root of this subtree. Then, it modifies
     the current pointer such that the previous node is connect to the left
     subtree of this node ([A[B][C[D]]] --> [A[B][D]]).Then, it deletes
     the node. Notice the usage of & in order to allow this method to modify
     the pointer of a root directly.
  */
  if(!current->pRight)//Base case
    {
      TreeNode* tmp = current;//Hold a pointer to this node
      current = current->pLeft;//Update the current pointer to point to the
                               //left subtree.
      root->Key = tmp->Key;//Copy contents to root
      root->Value = tmp->Value;
      delete tmp;//delete the old current
      return;
    }

  rem_swapNode(root, current->pRight);
}

template<typename KeyTy, typename ValueTy>
size_t BinarySearchTree<KeyTy,ValueTy>::computeHeight(TreeNode* root) const
{
  /*This method computes the height of the tree recursively.
   */
  if(!root)
    return 0;

  return 1 + max(computeHeight(root->pLeft), computeHeight(root->pRight));
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy,ValueTy>::inorderNode(TreeNode* root, TraversalFunction& f) const
{
  /*This method will traverse the tree recursively and call the function
    provided on each node. Format: left subtree, root, right subtree.
  */
  if(!root)
    return;

  inorderNode(root->pLeft, f);
  f(root->Key, root->Value);
  inorderNode(root->pRight, f);
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy,ValueTy>::preorderNode(TreeNode* root, TraversalFunction& f) const
{
  /*This method will traverse the tree recursively and call the function
    provided on each node. Format: root, left subtree, right subtree.
  */
  if(!root)
    return;

  f(root->Key, root->Value);
  preorderNode(root->pLeft, f);
  preorderNode(root->pRight, f);
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy,ValueTy>::postorderNode(TreeNode* root, TraversalFunction& f)const
{
  /*This method will traverse the tree recursively and call the function
    provided on each node. Format: left subtree, right subtree, root.
  */
  if(!root)
    return;

  postorderNode(root->pLeft, f);
  postorderNode(root->pRight, f);
  f(root->Key, root->Value);
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy,ValueTy>::printTree(TreeNode* root) const
{
  /*This method prints recursively the root's key and value. Then,
    it prints the left and right subtrees. The format of the full output
    will mimic the internal structure of the tree!
  */
  if(!root)
    {
      std::cout << "<empty>";
      return;
    }

  std::cout << "[Key: " << root->Key << ", Value: " << root->Value
	    << ", Left: ";
  printTree(root->pLeft);
  std::cout  << ", Right: ";
  printTree(root->pRight);
  std::cout << "]";
}

/*template<typename KeyTy, typename ValueTy>
BinarySearchTree<KeyTy,ValueTy>::ValueTy* BinarySearchTree<KeyTy,ValueTy>::getValRef
(TreeNode* root, const KeyTy& key)
{
  /*This method looks recursively for a node with the same key as key and
    returns a reference to the node's value.
  */
  /*if(!root)//Base case
    return NULL;

  if(root->Key == key)//We got lucky
    return &root->Value;
  else if(root->Key > key)//Otherwise, keep looking
    return getValRef(root->pLeft, key);
  else if(root->Key < key)
    return getValRef(root->pRight, key);
  return NULL;
}*/

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy,ValueTy>::freeTree(TreeNode* root)
{
  /*This method removes recursively the left and right subtrees before removing
    the root.*/
  if(!root)
    return;

  freeTree(root->pLeft);
  freeTree(root->pRight);
  delete root;
}

template<typename KeyTy, typename ValueTy>
void verbose(const KeyTy& key, const ValueTy& value)
{
    /*This is a simple traversal function and the default function for this
    implementation! It prints out the tree but with the address of the Value
    instead of the actual value.*/
    std::cout << "[Key: " << key << ", Address of Value: " << value
	    << std::endl;
}

template<typename KeyTy, typename ValueTy>
void BinarySearchTree<KeyTy,ValueTy>::dumpNode(TreeNode* root, std::vector<ValueTy>& holder)
{
    if(!root)
        return;

    holder.push_back(root->Value);
    dumpNode(root->pLeft, holder);
    dumpNode(root->pRight, holder);
}
