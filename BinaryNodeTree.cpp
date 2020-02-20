/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Implementation file for a pointer-based implementation of the ADT binary
 *  tree.
 *
 *  Adapted from pages 482-491 in Carrano 7e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 8 Nov 2017
 *
 *  @version 7.0 */

#include <algorithm>
#include <iostream>
#include <memory>
#include <new>

#include "PrecondViolatedExcep.h"
#include "NotFoundException.h"

//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////
template <typename ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(BinaryNodePtr subTreePtr) const
{
  int height(0);

  if (subTreePtr != nullptr) {
    height = 1 + std::max(getHeightHelper(subTreePtr->leftChildPtr),
			  getHeightHelper(subTreePtr->rightChildPtr) );
  }

  return height;
}

template <typename ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNodePtr subTreePtr) const {

  int numNodes(0);

  if (subTreePtr != nullptr) {
          numNodes = 1 +
	    getNumberOfNodesHelper(subTreePtr->leftChildPtr) +
	    getNumberOfNodesHelper(subTreePtr->rightChildPtr);
  }

  return numNodes;
}

template <typename ItemType>
std::shared_ptr<typename BinaryNodeTree<ItemType>::BinaryNode>
BinaryNodeTree<ItemType>::balancedAdd(BinaryNodePtr subTreePtr,
				      BinaryNodePtr newNodePtr) {

  auto returnPtr(newNodePtr);

  if (subTreePtr != nullptr) {
    auto leftPtr(subTreePtr->leftChildPtr);
    auto rightPtr(subTreePtr->rightChildPtr);

    if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr) ) {
      subTreePtr->rightChildPtr = balancedAdd(rightPtr, newNodePtr);
    }
    else {
      subTreePtr->leftChildPtr = balancedAdd(leftPtr, newNodePtr);
    }

    returnPtr = subTreePtr;
  }

  return returnPtr;
}

template <typename ItemType>
std::shared_ptr<typename BinaryNodeTree<ItemType>::BinaryNode>
BinaryNodeTree<ItemType>::moveValuesUpTree(BinaryNodePtr subTreePtr) {

  BinaryNodePtr returnPtr;

  if (isLeaf(subTreePtr) ) {
    subTreePtr.reset();
  }
  else {
    auto leftPtr(subTreePtr->leftChildPtr);
    auto rightPtr(subTreePtr->rightChildPtr);

    if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr) ) {
      subTreePtr->item =  leftPtr->item;
      subTreePtr->leftChildPtr = moveValuesUpTree(leftPtr);
    }
    else {
      subTreePtr->item = rightPtr->item;
      subTreePtr->rightChildPtr = moveValuesUpTree(rightPtr);
    }

    returnPtr = subTreePtr;
  }

  return returnPtr;
}

/** Depth-first search of tree for item.
 *
 *  @param subTreePtr The tree to search.
 *
 *  @param target The target item to find.
 *
 *  @param success Communicate to client whether we found the target.
 *
 *  @return A pointer to the node containing the target. */
template <typename ItemType>
std::shared_ptr<typename BinaryNodeTree<ItemType>::BinaryNode>
BinaryNodeTree<ItemType>::removeValue(BinaryNodePtr subTreePtr,
				      const ItemType& target,
				      bool& success) {

  BinaryNodePtr returnPtr;

  if(subTreePtr != nullptr) {
    if (subTreePtr->item == target) {
      subTreePtr = moveValuesUpTree(subTreePtr);
      success = true;
    }
    else {
      subTreePtr->leftChildPtr = removeValue(subTreePtr->leftChildPtr,
					     target,
					     success);
      if (!success) {
	subTreePtr->rightChildPtr = removeValue(subTreePtr->rightChildPtr,
						target,
						success);
      }
    }

    returnPtr = subTreePtr;
  }

  return returnPtr;
}

template <typename ItemType>
std::shared_ptr<typename BinaryNodeTree<ItemType>::BinaryNode>
BinaryNodeTree<ItemType>::findNode(BinaryNodePtr subTreePtr,
				   const ItemType& target) const {

  BinaryNodePtr returnPtr;

  if (subTreePtr != nullptr) {
    if (subTreePtr->item == target) {
      returnPtr = subTreePtr;
    }
    else {
      returnPtr = findNode(subTreePtr->leftChildPtr,
			   target);
      if (returnPtr == nullptr) {
	returnPtr = findNode(subTreePtr->rightChildPtr,
			     target);
      }
    }
  }

  return returnPtr;
}

template <typename ItemType>
std::shared_ptr<typename BinaryNodeTree<ItemType>::BinaryNode>
BinaryNodeTree<ItemType>::copyTree(const BinaryNodePtr& subTreePtr) const {

  BinaryNodePtr newTreePtr;

  // Copy tree nodes using a preorder traversal
  if (subTreePtr != nullptr) {
    newTreePtr = std::make_shared<BinaryNode>(subTreePtr->item,
					      copyTree(subTreePtr->leftChildPtr),
					      copyTree(subTreePtr->rightChildPtr) );
  }

  return newTreePtr;
}

//////////////////////////////////////////////////////////////
//      Protected Tree Traversal Sub-Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&),
					BinaryNodePtr subTreePtr) {

  if (subTreePtr != nullptr) {
    visit(subTreePtr->item);

    preorder(visit, subTreePtr->leftChildPtr);
    preorder(visit, subTreePtr->rightChildPtr);
  }
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&),
				       BinaryNodePtr subTreePtr) {

  if (subTreePtr != nullptr) {
    inorder(visit, subTreePtr->leftChildPtr);

    visit(subTreePtr->item);

    inorder(visit, subTreePtr->rightChildPtr);
  }
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&),
					 BinaryNodePtr subTreePtr) {

  if (subTreePtr != nullptr) {
    postorder(visit, subTreePtr->leftChildPtr);
    postorder(visit, subTreePtr->rightChildPtr);

    visit(subTreePtr->item);
  }
}

//////////////////////////////////////////////////////////////
//      Protected Node Access Sub-Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
bool BinaryNodeTree<ItemType>::isLeaf(BinaryNodePtr nodePtr) const {

     return nodePtr->leftChildPtr == nullptr &&
       nodePtr->rightChildPtr == nullptr;
}

template <typename ItemType>
std::shared_ptr<typename BinaryNodeTree<ItemType>::BinaryNode>
BinaryNodeTree<ItemType>::getRootPtr() const {

  return rootPtr;
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::setRootPtr(BinaryNodePtr newRootPtr) {

  rootPtr = newRootPtr;
}

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
  : rootPtr(std::make_shared<BinaryNode>(rootItem) ) {
}

template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
					 const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
					 const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr)
  : rootPtr(std::make_shared<BinaryNode>(rootItem,
					 copyTree(leftTreePtr->rootPtr),
					 copyTree(rightTreePtr->rootPtr)) ) {
}

template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr) {

  try {
    rootPtr = copyTree(treePtr.rootPtr);
  }
  catch (const std::bad_alloc&) {
    clear();
    throw;
  }
}

//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const {

  return rootPtr == nullptr;
}

template <typename ItemType>
int BinaryNodeTree<ItemType>::getHeight() const {

  return getHeightHelper(rootPtr);
}

template <typename ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const {

  return getNumberOfNodesHelper(rootPtr);
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::clear() {

  rootPtr.reset();
}

template <typename ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const {

  if (isEmpty() ) {
    std::string message("BinaryNodeTree::getRootData: called ");
    message += "on an empty tree.";

    throw PrecondViolatedExcep(message);
  }

  return rootPtr->item;
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newItem) {

  if (isEmpty() ) {
    try {
      rootPtr = std::make_shared<BinaryNode>(newItem);
    }
    catch (const std::bad_alloc&) {
      // What should we do with this? Return something? Throw a
      // different type of exception? Crash?
    }
  }
  else {
    rootPtr->item = newItem;
  }
}

template <typename ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData) {

  bool canAdd(true);

  try {
    auto newNodePtr(std::make_shared<BinaryNode>(newData) );

    rootPtr = balancedAdd(rootPtr, newNodePtr);
  }
  catch (const std::bad_alloc&) {
    canAdd = false;
  }

  return canAdd;
}

template <typename ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& target) {

  bool isSuccessful(false);

  rootPtr = removeValue(rootPtr, target, isSuccessful);

  return isSuccessful;
}

template <typename ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const {

  auto binaryNodePtr(findNode(rootPtr, anEntry) );

  if (binaryNodePtr == nullptr) {
    std::string message("BinaryNodeTree::getEntry: Entry ");
    message += "not found in this tree.";

    throw NotFoundException(message);
  }

  return binaryNodePtr->item;
}

template <typename ItemType>
bool BinaryNodeTree<ItemType>:: contains(const ItemType& anEntry) const {

  return findNode(rootPtr, anEntry) != nullptr;
}

//////////////////////////////////////////////////////////////
//      Public Traversals Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&) ) {

  preorder(visit, rootPtr);
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&) ) {

  inorder(visit, rootPtr);
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&) ) {

  postorder(visit, rootPtr);
}

//////////////////////////////////////////////////////////////
//      Overloaded Operator
//////////////////////////////////////////////////////////////

template <typename ItemType>
BinaryNodeTree<ItemType>&
BinaryNodeTree<ItemType>::operator=(const BinaryNodeTree<ItemType>& rhs) {

  auto oldTreePtr(rootPtr);

  if (this != &rhs) {
    try {
      rootPtr = copyTree(rhs.rootPtr);
      oldTreePtr.reset();
    }
    catch (const std::bad_alloc&) {
      rootPtr.reset();
      rootPtr = oldTreePtr;
      throw;
    }
  }

  return *this;
}

///////////////////////////////////////////////////////////////
//   My methods that solve simple problems with binary trees
///////////////////////////////////////////////////////////////
//private:
//Unitly Method for DisplayTree method.
template <typename ItemType>
void BinaryNodeTree<ItemType>::DisplayOrder(void visit(ItemType&, int),
					    BinaryNodePtr subTreePtr, int a) {

  if (subTreePtr != nullptr) {
    DisplayOrder(visit, subTreePtr->rightChildPtr, a+1);
    visit(subTreePtr->item, a);
    DisplayOrder(visit, subTreePtr->leftChildPtr, a+1);
   
  }
}

//public:
/** This diplay method displays the tree as required in the assignment
 * @pre: None
 *
 * @post: Tree is displayed. */
template <typename ItemType>
void BinaryNodeTree<ItemType>::DisplayTree(void visit(ItemType&, int) ) {

  DisplayOrder(visit, rootPtr, 0);
}

/** The accessor method that calls the recursive method to flip the tree.
 *
 * @post Flips the tree if successful. */
template <typename ItemType>
void BinaryNodeTree<ItemType>::Mirror()
{
  MirrorHelper(rootPtr);
}

/** The recursive method that flip the nodes in a tree left-to-right.
 *
 * @param The tree to be flipped.
 *
 * @post Flips the tree. */
template <typename ItemType>
void BinaryNodeTree<ItemType>::MirrorHelper(BinaryNodePtr treePtr)
{
  if(treePtr == nullptr)
    {
      return;
    }
  else
    {
      MirrorHelper(treePtr->leftChildPtr);
      MirrorHelper(treePtr->rightChildPtr);
      std::swap(treePtr->leftChildPtr, treePtr->rightChildPtr);
    }
}

/** An accesor method that calls the actual recursive method to check if BST.
 *
 * @return True if it is a BST, or false if not. */

template <typename ItemType>
bool BinaryNodeTree<ItemType>::isThisaBST()
{
  return isThisaBSTHelper(rootPtr, INT_MIN, INT_MAX);
}

/** A recursive method that sees if the tree contains a binary search tree
 *
 * @param The tree to be searched, and the min and max values.
 *
 * @return True if it is a BST, or false if not. */

template <typename ItemType>
bool BinaryNodeTree<ItemType>::isThisaBSTHelper(BinaryNodePtr treePtr,
						int min,
						int max)
{
  // An empty tree is a BST
  if(treePtr == nullptr)
    {
      return true;
    }

  //If this is true, not a BST
  if(treePtr->item < min || treePtr-> item > max)
    {
      return false;
    }
  //Checks the subtrees recursively
  return isThisaBSTHelper(treePtr->leftChildPtr, min, treePtr->item)
    && isThisaBSTHelper(treePtr->rightChildPtr, treePtr->item, max);
}

/** The accessor method that calls the recursive method to print all the paths
 * from root to leaf in the tree.
 *
 * @post Prints the paths. */
template <typename ItemType>
void BinaryNodeTree<ItemType>::printAllPathsFromRootToLeaf()
{
  if(rootPtr == nullptr)
    {
      std::string message("BinaryNodeTree::printAllPathsFromRootToLeaf: ");
      message += "not found in this tree.";

      throw PrecondViolatedExcep(message);
    }
  int height = getHeight();
  ItemType pathArray[height];
  printAllPathsFromRootToLeafHelper(rootPtr, pathArray, 0);
}

/** The recursive method that prints all the paths from root to leaf in a tree.
 *
 * @param treePtr (the tree), pathArray[] (an array that stores the values of 
 * the nodes in the current path, index (an integer that is the number of nodes
 * in the current path)
 *
 * @post Prints the root to leaf paths */
template <typename ItemType>
void BinaryNodeTree<ItemType>::printAllPathsFromRootToLeafHelper(BinaryNodePtr treePtr,
								 ItemType pathArray[], int index)
{
  pathArray[index] = treePtr->item;
  index++;
  if(treePtr->leftChildPtr == nullptr && treePtr->rightChildPtr == nullptr)
    {
      printArray(pathArray,index);
      return;
    }
  if(treePtr->leftChildPtr != nullptr)
    {
      printAllPathsFromRootToLeafHelper(treePtr->leftChildPtr, pathArray, index);
    }
  if(treePtr->rightChildPtr != nullptr)
    {
      printAllPathsFromRootToLeafHelper(treePtr->rightChildPtr, pathArray, index);
    }
}

/** Prints each node of a path from root to leaf.
 *
 * @param pathArray[] (the array that holds the values of the nodes along the
 * current path, length (an integer that stores the length of it)
 *
 * @post Prints each node of a path from root to leaf. */
template <typename ItemType>
void BinaryNodeTree<ItemType>::printArray(ItemType pathArray[], int length)
{
  for(int i = 0; i < length; i++)
    {
      // std::cout << pathArray[i] << " ";
      if(pathArray[i] == rootPtr->item)
	{
	  std::cout << "\n";
	}
      std::cout << pathArray[i] << " ";

    }
}

/** An accessor method that returns the maximum value of the tree by calling
 * the actual recursive method
 *
 * @return ItemType The maximum value in the tree */
template <typename ItemType>
ItemType BinaryNodeTree<ItemType>::maxValue()
{
  if(rootPtr == nullptr)
    {
      std::string message("BST is empty");
      throw PrecondViolatedExcep(message);
    }
  return maxValueHelper(rootPtr, rootPtr->item);
}

/** The recursive method that returns the maximum value of the tree.
 *
 * @param The tree to be searched, ItemType currentMax (the maximum value)
 *
 * @return ItemType The maximum value inside the tree. */
template <typename ItemType>
ItemType BinaryNodeTree<ItemType>::maxValueHelper(BinaryNodePtr treePtr,
						  ItemType currentMax)
{
  if(treePtr == NULL)
    {
      return currentMax;
    }
  currentMax = currentMax > treePtr->item ? currentMax : treePtr->item;

  ItemType leftMax = maxValueHelper(treePtr->leftChildPtr, currentMax);
  ItemType rightMax = maxValueHelper(treePtr->rightChildPtr, currentMax);

  return leftMax > rightMax ? leftMax : rightMax;
}

/** An accessor method that returns the minimum value inside the tree by
 * calling the actual recursive method that does the work.
 *
 * @return ItemType The minimum value inside the tree. */
template <typename ItemType>
ItemType BinaryNodeTree<ItemType>::minValue()
{
  if(rootPtr == nullptr)
    {
      std::string message("BST is empty");
      throw PrecondViolatedExcep(message);
    }
  return minValueHelper(rootPtr, rootPtr->item);
}

/** The recursive method that returns the minimum value of the tree.           
 *                                                                             
 * @param The tree to be searched, ItemType currentMin 
 * (the minimum value)          
 *                                                                             
 * @return ItemType The minimum value inside the tree. */
template <typename ItemType>
ItemType BinaryNodeTree<ItemType>::minValueHelper(BinaryNodePtr treePtr,
						  ItemType currentMin)
{
  if(treePtr == NULL)
    {
      return currentMin;
    }

  currentMin = currentMin < treePtr->item ? currentMin : treePtr->item;

  ItemType leftMin = minValueHelper(treePtr->leftChildPtr, currentMin);
  ItemType rightMin = minValueHelper(treePtr->rightChildPtr, currentMin);

  return leftMin < rightMin ? leftMin : rightMin;
}

/** Bool method that returns true if there is a path from the root down
 * to a leaf, such that adding up all the value along the path equals the
 * given sum (done recursively).
 *
 * @param The tree to be searched, and the sum that is to be added (which is
 * passed by value from another method for safety measures)
 *
 * @return True if the sum equals a path from root to a leaf when added,
 * or false if not. */
template <typename ItemType>
bool BinaryNodeTree<ItemType>::doesSomePathHaveSum(BinaryNodePtr treePtr,
						   int sum)
{
  if(treePtr == NULL)
    {
      return sum == 0;
    }

  else
    {
      bool ans = 0;

      //check both sub trees
      int subtreeSum = sum - treePtr->item;

      //If the leaf node and sum is 0, return true
      if(subtreeSum == 0 && treePtr->leftChildPtr == NULL
	 && treePtr->rightChildPtr == NULL)
	{
	  return 1;
	}

      if(treePtr->leftChildPtr)
	{
	  ans = ans || doesSomePathHaveSum(treePtr->leftChildPtr,
					   subtreeSum);
	}
      if(treePtr->rightChildPtr)
	{
	  ans = ans || doesSomePathHaveSum(treePtr->rightChildPtr,
					   subtreeSum);
	}
      return ans;
    }
}

/** An accessor method that calls the actual recursive method to check if
 * the sum of root to leaf is added to be the total of the sum passed as an
 * argument here.
 *
 * @param sum An integer value that is supposed to be the sum of the values
 * from root to leaf.
 *
 * @return True if it is the correct sum for a path, or false if not. */
template <typename ItemType>
bool BinaryNodeTree<ItemType>::getSum(int sum)
{
  if(rootPtr == nullptr)
    {
      std::string message("BT is empty");
      throw PrecondViolatedExcep(message);
    }
  return doesSomePathHaveSum(rootPtr, sum);
}
