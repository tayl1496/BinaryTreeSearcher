/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for a node in the pointer-based implementation of the
 *  ADT binary tree.
 *
 *  Adapted from page 478 in Carrano 7e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 8 Nov 2017
 *
 *  @version 7.0 */

#ifndef BINARY_NODE_
#define BINARY_NODE_

#include <memory>

/** @class BinaryNode BinaryNode.h "BinaryNode.h"
 *
 *  Specification of the nested node type for a linked-chain based ADT
 *  binary tree. */
template <typename ItemType>
class BinaryNodeTree<ItemType>::BinaryNode {
 public:
  ItemType item;

  std::shared_ptr<BinaryNode> leftChildPtr;
  std::shared_ptr<BinaryNode> rightChildPtr;

  BinaryNode(const ItemType& anItem,
	     std::shared_ptr<BinaryNode> leftPtr = nullptr,
	     std::shared_ptr<BinaryNode> rightPtr = nullptr);

  #ifdef DTOR_TEST
  virtual ~BinaryNode();
  #else
  virtual ~BinaryNode() = default;
  #endif
};

#include "BinaryNode.cpp"

#endif
