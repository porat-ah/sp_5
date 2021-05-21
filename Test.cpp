#include "doctest.h"
#include "sources/BinaryTree.hpp"
using namespace ariel;
TEST_CASE("all functons"){
    BinaryTree<int> tree;
    tree.add_root(1).add_left(1,2)
    .add_left(2,4).add_right(2,5)
    .add_right(1,3).add_left(3,6)
    .add_right(3,7);
    int inorder[]{4,2,5,1,6,3,7};
    int preorder[]{1,2,4,5,3,6,7};
    int postorder[]{4,5,2,6,7,3,1};
    int j = 0;
    for (int i: tree)
    {
        CHECK_EQ(i,inorder[j++]);
    }
    j = 0;
    for (auto it=tree.begin_preorder(); it!=tree.end_preorder(); ++it) {
         CHECK_EQ(*it,preorder[j++]);
    }
    j = 0;
    for (auto it=tree.begin_inorder(); it!=tree.end_inorder(); ++it) {
         CHECK_EQ(*it,inorder[j++]);
    }
    j = 0;
    for (auto it=tree.begin_postorder(); it!=tree.end_postorder(); ++it) {
         CHECK_EQ(*it,postorder[j++]);
    }
    CHECK_THROWS(tree.add_right(10,9));
   {
        auto it = tree.begin_inorder();
        for (int i : inorder)
        {
            CHECK_EQ(i,*it);
            it++;
        }
   }
    {
        auto it = tree.begin_preorder();
        for (int i : preorder)
        {
            CHECK_EQ(i,*it);
            it++;
        }
   }
    {
        auto it = tree.begin_postorder();
        for (int i : postorder)
        {
            CHECK_EQ(i,*it);
            it++;
        }
   }
    

}