#include <ostream>
#include <vector>
#include <iostream>
#include<stdexcept>
#include <string>

namespace ariel
{
    enum order_type{
        in,
        pre,
        post
    };

    template <typename T>
    class BinaryTree
    {
    private:


        class Node
        {
        public:
            T data;
            Node* left;
            Node* right;
            Node(T d) : data(d), left(nullptr), right(nullptr) {}
        };

    public:



        class Iterator
        {
        private:
            size_t loc;
            // std::vector<Node*> order;
            order_type order_t;
            BinaryTree* tree;

            std::vector<Node*>& order() const {
                switch (order_t)
                {
                case order_type::in:
                    return tree->in;
                case order_type::pre:
                    return tree->pre;
                case order_type::post:
                    return tree->post;
                }
                return tree->in;
            }

        public:
            
            // Iterator(std::vector<Node*>& v) : loc(0),order(v) {}
            // Iterator(std::vector<Node*>& v , size_t l) : loc(l),order(v) {}
            Iterator(order_type o ,BinaryTree* t):order_t(o),tree(t) ,loc(0) {}
            Iterator(order_type o ,size_t l ,BinaryTree* t ):order_t(o) , loc(l) ,tree(t) {}
            // Iterator(const Iterator &oth): loc(oth.loc),order(oth.order) {}
            bool operator!=(const Iterator &oth);
            bool operator==(const Iterator &oth);
            // Iterator& operator=(const Iterator &oth);
            T& operator*();
            Iterator& operator++();
            Iterator operator++(int dummy);
            T *operator->();
        };


    private:
        Node *root;
        // std::vector<Node *> nodes;
        std::vector<Node *> in;
        std::vector<Node *> pre;
        std::vector<Node *> post;
        void inorder(Node *n);
        void preorder(Node *n);
        void postorder(Node *n);
        bool search_n_add(Node *n, const T &ex, const T &data, bool direction);
        void print(std::ostream &os,Node * n ) const ;
        void dcor(Node * n);
        void copy(Node * s , Node * d);


    public:
        
        // BinaryTree() : root(nullptr), nodes() {}
        BinaryTree() : root(nullptr), in() , pre() , post() {}
        BinaryTree(const BinaryTree& oth);
        BinaryTree(BinaryTree&& oth) noexcept;
        ~BinaryTree();
        BinaryTree& operator=(const BinaryTree& oth);
        BinaryTree<T>& operator=(BinaryTree&& oth) noexcept;
        BinaryTree &add_root(const T &data);
        BinaryTree &add_left(const T &ex, const T &data);
        BinaryTree &add_right(const T &ex, const T &data);
        Iterator begin_preorder();
        Iterator end_preorder();
        Iterator begin_inorder();
        Iterator end_inorder();
        Iterator begin_postorder();
        Iterator end_postorder();
        Iterator begin();
        Iterator end();
       
        void debug();
        void _debug(Node* n);

        template<typename E>
        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<E> &b);
    };

template <typename T>
    void BinaryTree<T>::debug(){
        _debug(root);
    }

    template <typename T>
    void BinaryTree<T>::_debug(Node * n){
        if(n == nullptr){

            //  std::cout<< "null " << endl;
            return;
        }

        std::cout <<" data : " << n->data << std::endl;
        std::cout<< " left = ";
        _debug(n->left);
        std::cout<< " right = ";
        _debug(n->right);
    }

    // copy cnor
    template <typename T>
    BinaryTree<T>::BinaryTree(const BinaryTree& oth){
        root = new Node(oth.root->data);
        copy(oth.root , root);

    }

    template <typename T>
    void BinaryTree<T>::copy(Node* s , Node* d){
        if (s->left != nullptr )
        {
            d->left = new Node(s->left->data);
            copy(s->left , d->left);
        }
        if (s->right != nullptr)
        {
            d->right = new Node(s->right->data);
            copy(s->right , d->right);
        }
    }

    template <typename T>
    BinaryTree<T>::BinaryTree(BinaryTree&& oth) noexcept{
        root = oth.root;
        in = oth.in;
        pre = oth.pre;
        post = oth.post;
        oth.root = nullptr;
    }

    // dcor
    template <typename T>
    BinaryTree<T>::~BinaryTree()
    {
        dcor(root);
    }

    template <typename T>
    void BinaryTree<T>::dcor(Node * n)
    {
        if (n == nullptr)
        {
            return;
        }
        dcor(n->left);
        dcor(n->right);
        delete n;
    }

    // = operators
    template <typename T>
    BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree&& oth) noexcept{
        dcor(root);
        root = oth.root;
        in = oth.in;
        pre = oth.pre;
        post = oth.post;
        oth.root = nullptr;
        return *this;
    }

    template <typename T>
    BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& oth){
        if (&oth == this)
        {
            return *this;
        }
        
        Node * temp = new Node(oth.root->data);
        copy(oth.root , temp);
        dcor(root);
        root = temp; 
        return *this;
    }


    // adding data 
    template <typename T>
    BinaryTree<T> &BinaryTree<T>::add_root(const T &data)
    {
        if (root == nullptr)
        {
            root = new Node(data);
        }
        root->data = data;
        return *this;
    }

    template <typename T>
    BinaryTree<T> &BinaryTree<T>::add_left(const T &ex, const T &data)
    {
        if(!search_n_add(root, ex, data, true)){
            throw std::invalid_argument("the node does not exist");
        }
        return *this;
    }

    template <typename T>
    BinaryTree<T> &BinaryTree<T>::add_right(const T &ex, const T &data)
    {
        if(!search_n_add(root, ex, data, false)){
            throw std::invalid_argument("the node does not exist");
        }
        return *this;
    }

    template <typename T>
    bool BinaryTree<T>::search_n_add(Node *n, const T &ex, const T &data, bool direction)
    {
        if (n == nullptr)
        {
            return false;
        }

        if (n->data == ex)
        {
            if (direction)
            {
                if (n->left == nullptr)
                {
                    n->left = new Node(data);
                }
                else
                {
                    n->left->data = data;
                }
            }
            else
            {
                if (n->right == nullptr)
                {
                    n->right = new Node(data);
                }
                else
                {
                    n->right->data = data;
                }
            }
            return true;
        }
        bool b = false;
        b |= search_n_add(n->left, ex, data, direction);
        b |= search_n_add(n->right, ex, data, direction);
        return b;
    }

    // order recursive function 
    template <typename T>
    void BinaryTree<T>::inorder(Node *n) 
    {
        if (n == nullptr)
        {
            return;
        }
        inorder(n->left);
        in.insert(in.end(),n);
        inorder(n->right);
    }

    template <typename T>
    void BinaryTree<T>::preorder(Node *n)
    {
        if (n == nullptr)
        {
            return;
        }
        pre.insert(pre.end(),n);
        preorder(n->left);
        preorder(n->right);
    }

    template <typename T>
    void BinaryTree<T>::postorder(Node *n)
    {
        if (n == nullptr)
        {
            return;
        }
        postorder(n->left);
        postorder(n->right);
        post.insert(post.end(),n);
    }


    // order begin  

    template <typename T>
    typename BinaryTree<T>::Iterator BinaryTree<T>::begin_inorder()
    {
        in.clear();
        inorder(root);
        return Iterator(order_type::in,this);
    }

    template <typename T>
    typename BinaryTree<T>::Iterator BinaryTree<T>::begin_preorder()
    {
        pre.clear();
        preorder(root);
        return Iterator(order_type::pre,this);
    }

    template <typename T>
    typename BinaryTree<T>::Iterator BinaryTree<T>::begin_postorder()
    {
        post.clear();
        postorder(root);
        return Iterator(order_type::post,this);
    }

    // order end 
    
    template <typename T>
    typename BinaryTree<T>::Iterator BinaryTree<T>::end_inorder(){
        begin_inorder();
        return Iterator(order_type::in , in.size(),this);
    }

    template <typename T>
    typename BinaryTree<T>::Iterator BinaryTree<T>::end_preorder(){
        begin_preorder();
        return Iterator(order_type::pre , pre.size(),this);
    }

    template <typename T>
    typename BinaryTree<T>::Iterator BinaryTree<T>::end_postorder(){
        begin_postorder();
        return Iterator(order_type::post , post.size(),this);
    }


    // regular begin and end 
    template <typename T>
    typename BinaryTree<T>::Iterator BinaryTree<T>::begin(){
        return begin_inorder();
    }

    template <typename T>
    typename BinaryTree<T>::Iterator BinaryTree<T>::end(){
        return end_inorder();
    }
    

    // ostream 
    template <typename T>
    void BinaryTree<T>::print(std::ostream &os,Node * n ) const {
        if (n == nullptr)
        {
            return;
        }
        print(os,n->left);
        os << n->data << " ";
        print(os,n->right);
    }

    template<typename E>
    std::ostream &operator<<(std::ostream &os, const BinaryTree<E> &b){
        os << "in order : ";
        b.print(os,b.root);
        return os;
    }



    //iterator
    template <typename T>
    bool BinaryTree<T>::Iterator::operator!=(const Iterator &oth)
    {
        if (oth.loc == oth.order().size() && loc == order().size())
        {
            return false;
        }
        
        if (oth.loc == oth.order().size())
        {
            return order().at(loc) != nullptr;
        }
        
        if (loc == order().size())
        {
            return oth.order().at(oth.loc) != nullptr;
        }
        
        return order().at(loc) != oth.order().at(oth.loc);
    }

    template <typename T>
    bool BinaryTree<T>::Iterator::operator==(const Iterator &oth)
    {
        if (oth.loc == oth.order().size() && loc == order().size())
        {
            return true;
        }
        
        if (oth.loc == oth.order().size())
        {
            return order().at(loc) == nullptr;
        }
        
        if (loc == order().size())
        {
            return oth.order().at(oth.loc) == nullptr;
        }
        return order().at(loc) == oth.order().at(oth.loc);
    }

    // template <typename T>
    // typename BinaryTree<T>::Iterator& BinaryTree<T>::Iterator::operator=(const Iterator &oth)
    // {
    //     order = oth.order;
    //     loc = oth.loc;
    //     return *this;
    // }

    template <typename T>
    T& BinaryTree<T>::Iterator::operator*()
    {
        return order().at(loc)->data;
    }

    template <typename T>
    typename BinaryTree<T>::Iterator& BinaryTree<T>::Iterator::operator++()
    {
        ++loc;
        return *this;
    }

    template <typename T>
    typename BinaryTree<T>::Iterator BinaryTree<T>::Iterator::operator++(int dummy)
    {
        Iterator temp = *this;
        ++loc;
        return temp;
    }

    template <typename T>
    T *BinaryTree<T>::Iterator::operator->()
    {
        return &(order().at(loc)->data);
    }
}