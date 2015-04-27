#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Quadtree/Tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTests
{
	TEST_CLASS(VisitNodes)
	{
		TEST_METHOD(Add)
		{
			Tree<char> myTree('1');

			treeNode <char>* dos = myTree.Add('2');
			treeNode <char>* tres = myTree.Add('3');
			treeNode <char>* quatre = myTree.Add('4');

			Assert::IsTrue(dos->data == '2');
			Assert::IsTrue(tres->data == '3');
			Assert::IsTrue(quatre->data == '4');

			treeNode <char>* cinc = myTree.Add('5', dos);
			treeNode <char>* sis = myTree.Add('6', dos);

			Assert::IsTrue(dos->children.GetPointer(0)->atr->data == '5');
			Assert::IsTrue(dos->children.GetPointer(1)->atr->data == '6');
		}

		TEST_METHOD(Clear)
		{
			Tree<char> myTree('1');

			treeNode <char>* dos = myTree.Add('2');
			treeNode <char>* tres = myTree.Add('3');
			treeNode <char>* quatre = myTree.Add('4');

			Assert::IsTrue(dos->data == '2');
			Assert::IsTrue(tres->data == '3');
			Assert::IsTrue(quatre->data == '4');

			myTree.Clear();

			Assert::IsTrue(dos->data != '2');
			Assert::IsTrue(tres->data != '3');
			Assert::IsTrue(quatre->data != '4');
		}

		TEST_METHOD(Preorder_Recursive)
		{
			Tree<char> myTree('1');

			treeNode <char>* two = myTree.Add('2');
			treeNode <char>* three = myTree.Add('3');
			treeNode <char>* four = myTree.Add('4');

			myTree.Add('5', two);
			myTree.Add('6', two);

			myTree.Add('7', three);

			myTree.Add('8', four);
			myTree.Add('9', four);
			myTree.Add('a', four);

			DList<char>* myList = new DList<char>;
			myTree.PreorderRecursive(myList);


			Assert::AreEqual(myList->GetPointer(0)->atr, '1');
			Assert::AreEqual(myList->GetPointer(1)->atr, '2');
			Assert::AreEqual(myList->GetPointer(2)->atr, '5');
			Assert::AreEqual(myList->GetPointer(3)->atr, '6');
			Assert::AreEqual(myList->GetPointer(4)->atr, '3');
			Assert::AreEqual(myList->GetPointer(5)->atr, '7');
			Assert::AreEqual(myList->GetPointer(6)->atr, '4');
			Assert::AreEqual(myList->GetPointer(7)->atr, '8');
			Assert::AreEqual(myList->GetPointer(8)->atr, '9');
			Assert::AreEqual(myList->GetPointer(9)->atr, 'a');
		}

		TEST_METHOD(Preorder_Iterative)
		{
			Tree<char> myTree('1');

			treeNode <char>* two = myTree.Add('2');
			treeNode <char>* three = myTree.Add('3');
			treeNode <char>* four = myTree.Add('4');

			myTree.Add('5', two);
			myTree.Add('6', two);

			myTree.Add('7', three);

			myTree.Add('8', four);
			myTree.Add('9', four);
			myTree.Add('a', four);

			DList<char>* myList = new DList<char>;
			myTree.PreorderIterative(myList);


			Assert::AreEqual(myList->GetPointer(0)->atr, '1');
			Assert::AreEqual(myList->GetPointer(1)->atr, '2');
			Assert::AreEqual(myList->GetPointer(2)->atr, '5');
			Assert::AreEqual(myList->GetPointer(3)->atr, '6');
			Assert::AreEqual(myList->GetPointer(4)->atr, '3');
			Assert::AreEqual(myList->GetPointer(5)->atr, '7');
			Assert::AreEqual(myList->GetPointer(6)->atr, '4');
			Assert::AreEqual(myList->GetPointer(7)->atr, '8');
			Assert::AreEqual(myList->GetPointer(8)->atr, '9');
			Assert::AreEqual(myList->GetPointer(9)->atr, 'a');
		}

		TEST_METHOD(Inorder_Recursive)
		{
			Tree<char> myTree('1');

			treeNode <char>* two = myTree.Add('2');
			treeNode <char>* three = myTree.Add('3');
			treeNode <char>* four = myTree.Add('4');

			myTree.Add('5', two);
			myTree.Add('6', two);

			myTree.Add('7', three);

			myTree.Add('8', four);
			myTree.Add('9', four);
			myTree.Add('a', four);

			DList<char>* myList = new DList<char>;
			myTree.InorderRecursive(myList);

			Assert::AreEqual(myList->GetPointer(0)->atr, '5');
			Assert::AreEqual(myList->GetPointer(1)->atr, '2');
			Assert::AreEqual(myList->GetPointer(2)->atr, '6');
			Assert::AreEqual(myList->GetPointer(3)->atr, '1');
			Assert::AreEqual(myList->GetPointer(4)->atr, '3');
			Assert::AreEqual(myList->GetPointer(5)->atr, '7');
			Assert::AreEqual(myList->GetPointer(6)->atr, '8');
			Assert::AreEqual(myList->GetPointer(7)->atr, '4');
			Assert::AreEqual(myList->GetPointer(8)->atr, '9');
			Assert::AreEqual(myList->GetPointer(9)->atr, 'a');
		}

		TEST_METHOD(Inorder_Iterative)
		{
			Tree<char> myTree('1');

			treeNode <char>* two = myTree.Add('2');
			treeNode <char>* three = myTree.Add('3');
			treeNode <char>* four = myTree.Add('4');

			myTree.Add('5', two);
			myTree.Add('6', two);

			myTree.Add('7', three);

			myTree.Add('8', four);
			myTree.Add('9', four);
			myTree.Add('a', four);

			DList<char>* myList = new DList<char>;
			myTree.InorderIterative(myList);

			Assert::AreEqual(myList->GetPointer(0)->atr, '5');
			Assert::AreEqual(myList->GetPointer(1)->atr, '2');
			Assert::AreEqual(myList->GetPointer(2)->atr, '6');
			Assert::AreEqual(myList->GetPointer(3)->atr, '1');
			Assert::AreEqual(myList->GetPointer(4)->atr, '3');
			Assert::AreEqual(myList->GetPointer(5)->atr, '7');
			Assert::AreEqual(myList->GetPointer(6)->atr, '8');
			Assert::AreEqual(myList->GetPointer(7)->atr, '4');
			Assert::AreEqual(myList->GetPointer(8)->atr, '9');
			Assert::AreEqual(myList->GetPointer(9)->atr, 'a');
		}

		TEST_METHOD(Postorder_Recursive)
		{
			Tree<char> myTree('1');

			treeNode <char>* two = myTree.Add('2');
			treeNode <char>* three = myTree.Add('3');
			treeNode <char>* four = myTree.Add('4');

			myTree.Add('5', two);
			myTree.Add('6', two);

			myTree.Add('7', three);

			myTree.Add('8', four);
			myTree.Add('9', four);
			myTree.Add('a', four);

			DList<char>* myList = new DList<char>;
			myTree.PostorderRecursive(myList);

			Assert::AreEqual(myList->GetPointer(0)->atr, '5');
			Assert::AreEqual(myList->GetPointer(1)->atr, '6');
			Assert::AreEqual(myList->GetPointer(2)->atr, '2');
			Assert::AreEqual(myList->GetPointer(3)->atr, '7');
			Assert::AreEqual(myList->GetPointer(4)->atr, '3');
			Assert::AreEqual(myList->GetPointer(5)->atr, '8');
			Assert::AreEqual(myList->GetPointer(6)->atr, '9');
			Assert::AreEqual(myList->GetPointer(7)->atr, 'a');
			Assert::AreEqual(myList->GetPointer(8)->atr, '4');
			Assert::AreEqual(myList->GetPointer(9)->atr, '1');
		}

		TEST_METHOD(Postorder_Iterative)
		{
			Tree<char> myTree('1');

			treeNode <char>* two = myTree.Add('2');
			treeNode <char>* three = myTree.Add('3');
			treeNode <char>* four = myTree.Add('4');

			myTree.Add('5', two);
			myTree.Add('6', two);

			myTree.Add('7', three);

			myTree.Add('8', four);
			myTree.Add('9', four);
			myTree.Add('a', four);

			DList<char>* myList = new DList<char>;
			myTree.PostorderIterative(myList);

			Assert::AreEqual(myList->GetPointer(0)->atr, '5');
			Assert::AreEqual(myList->GetPointer(1)->atr, '6');
			Assert::AreEqual(myList->GetPointer(2)->atr, '2');
			Assert::AreEqual(myList->GetPointer(3)->atr, '7');
			Assert::AreEqual(myList->GetPointer(4)->atr, '3');
			Assert::AreEqual(myList->GetPointer(5)->atr, '8');
			Assert::AreEqual(myList->GetPointer(6)->atr, '9');
			Assert::AreEqual(myList->GetPointer(7)->atr, 'a');
			Assert::AreEqual(myList->GetPointer(8)->atr, '4');
			Assert::AreEqual(myList->GetPointer(9)->atr, '1');
		}

	};

}