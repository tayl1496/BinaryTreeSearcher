#include "BinaryNodeTree.h"

template <typename ItemType>
void display(ItemType &item, int a)
{
  for(int i(0); i<=a; ++i)
  std::cout << "-";

  std::cout << item << std::endl;
}

int main()
{
  BinaryNodeTree<int> tree1;
  tree1.add(40);
  tree1.add(20);
  tree1.add(50);
  tree1.add(70);
  tree1.add(10);
  tree1.add(30);
  tree1.add(80);
  tree1.add(90);

  BinaryNodeTree<int> tree2 = tree1;
  std::cout << "tree 1 Initially:\n";
  tree1.DisplayTree(display);
  std::cout << "root data is: " << tree1.getRootData();
  std::cout << "\n";

  tree1.Mirror();
  std::cout << "\ntree1 after Mirror:\n";
  tree1.DisplayTree(display);
  std::cout << "root data is: " << tree1.getRootData();
  std::cout << "\n";

    try
      {
	std::cout << "\nTree 2 Initially:\n";
	tree2.DisplayTree(display);
	std::cout << "\n";

	std::cout << "Printing all paths from root to leaf for tree2:\n";
	tree2.printAllPathsFromRootToLeaf();

	std::cout << "\n\nTesting doesSomePathHaveSum(100)" << std::endl;
	std::cout << "Should be true, look at first line of print all paths"
		  << std::endl;
	std::cout << tree2.getSum(180);

	std::cout << "\n\nTesting doesSomePathHaveSum(400)" << std::endl;
	std::cout << tree2.getSum(400);
      }

    catch(const PrecondViolatedExcep &placeHolder)
      {
	std::cerr << "Exception thrown: " << placeHolder.what() << "\n";
      }

    BinaryNodeTree<int> tree3;
    tree3.add(10);
    tree3.add(60);
    tree3.add(50);
    tree3.add(30);
    tree3.add(70);
    tree3.add(40);
    tree3.add(90);

    std::cout << "\n\nTree 3 Initially:\n";
     tree3.DisplayTree(display);
    std::cout << std::endl;

    if(tree3.isThisaBST())
      {
	std::cout << "tree 3 is a binary search tree\n";
      }
    else
      {
	std::cout <<"tree 3 is not a binary search tree\n";
      }

      try
	{
	  std::cout << "Minimum value in tree 3: " << tree3.minValue()<<std::endl;
	  std::cout << "Maximum value in tree 3: " << tree3.maxValue()<<std::endl;

	  BinaryNodeTree<int> tree4;
	  std::cout << "Now finding minimum value in an empty tree 4:\n";
	  std::cout << tree4.minValue() << std::endl;
	}
      catch(const PrecondViolatedExcep &placeHolder)
	{
	  std::cerr << "exception thrown: " << placeHolder.what() << std::endl;
	}

      BinaryNodeTree<std::string> stringTree1;
      stringTree1.add("a");
      stringTree1.add("c");
      stringTree1.add("k");
      stringTree1.add("s");
      stringTree1.add("j");
      stringTree1.add("z");
      stringTree1.add("r");

      BinaryNodeTree<std::string> stringTree2 = stringTree1;
      BinaryNodeTree<std::string> stringTree3 = stringTree1;

      std::cout << "\n\nString tree1 Initially:\n";
      stringTree1.DisplayTree(display);
      std::cout << "root data is: " << stringTree1.getRootData();
      std::cout << "\n";

      stringTree1.Mirror();
      std::cout << "\nString tree1 after Mirror:\n";
      stringTree1.DisplayTree(display);
      std::cout << "root data is: " << stringTree1.getRootData();
      std::cout << "n";

        try
	  {
	    std::cout << "\nString tree2 Initially:\n";
	    stringTree2.DisplayTree(display);
	    std::cout << "\n";

	    std::cout << "Printing all paths from root to leaf for tree2:\n";
	    stringTree2.printAllPathsFromRootToLeaf();
	  }

	catch(const PrecondViolatedExcep &placeHolder)
	  {
	    std::cerr << "Exception thrown: " << placeHolder.what() << "\n";
	  }

	std::cout << "\n\nString Tree3 inorder:\n";
	stringTree3.DisplayTree(display);
	std::cout << std::endl;

	  try
	    {
	      std::cout << "Minimum value in stringTree3: " << stringTree3.minValue()
			<< std::endl;
	      std::cout << "Maximum value in stringTree3: " << stringTree3.maxValue()
			<< std::endl;
	      BinaryNodeTree<std::string> stringTree4;
	      std::cout << "Now finding minimum value in an empty tree4:\n";
	      std::cout << stringTree4.minValue() << std::endl;
	    }
	  catch(const PrecondViolatedExcep &placeHolder)
	    {
	      std::cerr << "exception thrown: " << placeHolder.what() << std::endl;
	    }
}
