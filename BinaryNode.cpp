

template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNode::BinaryNode(const ItemType& anItem,
						 std::shared_ptr<BinaryNode>
						 leftptr,
						 std::shared_ptr<BinaryNode>
						 rightptr)
{
  this->item = anItem;
  this->leftChildPtr = leftptr;
  this->rightChildPtr = rightptr;
}
