#include <ostream>
#include <vector>
namespace ariel{
    template<typename T>
    class BinaryTree
    {
    private:
        // class Node
        // {
        // private:
        //     T data;
        // public:
        //     Node(T d):data(d){}
        // }; 
    public:

        class Iterator
        { 
        public:
            // Node current;
            Iterator(){}
            Iterator(const Iterator & oth)
            {}
            ~Iterator(){}
            bool operator!=(const Iterator & oth){return false;}
            bool operator==(const Iterator & oth){return false;}
            void operator=(const Iterator & oth){return;}
            T operator*(){return T();}
            Iterator operator++(){return *this;}
            const Iterator operator++(int dummy){return *this;}
            Iterator* operator ->(){
                return this;
            }
            int size(){
                return 0 ;
            }
        };
    private:
        Iterator i;
        
    public:
        BinaryTree():i(){}
        ~BinaryTree(){}
        BinaryTree& add_root(T data){
            return *this;
        }
        BinaryTree& add_left(T ex , T data){return *this;}
        BinaryTree& add_right(T ex , T data){return *this;}
        Iterator begin_preorder(){return i; }
        Iterator end_preorder(){return i;}
        Iterator begin_inorder(){return i; }
        Iterator end_inorder(){return i;}
        Iterator begin_postorder(){return i; }
        Iterator end_postorder(){return i;}
        Iterator begin(){return i;}
        Iterator end(){return i;}
        friend std::ostream& operator<<(std::ostream& os , const BinaryTree& b){return os;}
    };

}