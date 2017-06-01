# ifndef BUW_LIST_HPP
# define BUW_LIST_HPP
# include <cstddef>
#include "iostream"

//List.hpp
template <typename T>
struct List;

template <typename T>
struct ListNode{
    ListNode(): 
        m_value(),
        m_prev(nullptr),
        m_next(nullptr) {}

    ListNode(T const & v, ListNode* prev , ListNode* next): 
        m_value(v), 
        m_prev(prev), 
        m_next(next) {}

    T m_value;
    ListNode* m_prev;
    ListNode* m_next;
};

template <typename T>
struct ListIterator{

    typedef ListIterator <T> Self;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;
    friend class List <T>;

    ListIterator():
        m_node(0) {}
    
    ListIterator (ListNode <T>* n):
        m_node(n) {}
    
    reference operator*() const{
        return m_node->m_value;
    } 

    pointer operator->() const{
        return &(m_node->m_value);
    } 

    Self& operator++(){
        m_node = m_node->m_next;
        return *this;
    } 

    Self operator++(int){
        ListIterator old(*this);
        m_node = m_node->m_next;
        return old;
        
    } 

    //compares the pointers, wether they are pointing to the same Element 
    bool operator==(const Self& x) const{
        return m_node == x.m_node;
    } 

    //or not
    bool operator!=(const Self& x) const{
        return m_node != x.m_node;
    } 

    Self next() const{
        if(m_node)
            return ListIterator(m_node->m_next);
        else
            return ListIterator(nullptr);
    }

    Self prev() const{
        if(m_node)
            return ListIterator(m_node->m_prev);
        else
            return ListIterator(nullptr);
    }

    private:
        //The Node the iterator is pointing to
        ListNode <T>* m_node = nullptr;
};

template <typename T>
struct ListConstIterator{
    friend class List <T>;
    public:
        // not implemented yet
    private:
        ListNode <T>* m_node = nullptr;
};

//Aufg. 4.7, operators == and !=

template <typename T>
bool operator ==(List <T> const& xs , List <T> const& ys){
    auto a = xs.begin();
    auto b = ys.begin();
    bool c = true;
    if(xs.size() != ys.size()){         //if not the same size, can't be ==
        c = false;
    }
    else{
        while(a != nullptr){
            if(*a != *b){              //if one element not the same, not ==
                c = false;
            }
            ++a;
            ++b;
        }
    }
    return c;
}

template <typename T>
bool operator !=(List <T> const& xs , List <T> const& ys){
    auto a = xs.begin();
    auto b = ys.begin();
    bool c = false;
    if(xs.size() != ys.size()){       //if not the same size, can't be == has to be !=
        c = true;
    }
    else{
        while(a != nullptr){
            if(*a != *b){            //if one element not the same, not == has to be !=
                c = true;
            }
            ++a;
            ++b;
        }
    }
    return c;
}

template <typename T>
class List{

    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef ListIterator <T> iterator;
        typedef ListConstIterator <T> const_iterator;
        friend class ListIterator <T>;
        friend class ListConstIterator <T>;

        //Aufg. 4.2

        //Default Constructor
        List():
            m_size (0),
            m_first (nullptr),
            m_last (nullptr) {}

        
        bool empty() const{
            return m_size == 0;
        }
        
        std::size_t size() const{
            return m_size;
        }

        //Destructor
        ~List(){
            clear();
        }

        //Copy Constructor, creates new list out of already existing list

        List(List<T> const& list):                //already implemented list
            m_first(nullptr),                     //set *this on nullptr
            m_last(nullptr) {
                auto b = list.begin();            //iterate through list
                while(b != nullptr){
                    push_back(*b);                //push all elements into *this
                    ++b;
                }
            }

        //Move Constructor, moves elements from one list to the other, "steals them"

        List(List<T>&& list2):                    
            m_size(list2.m_size),                 
            m_first(list2.m_first),
            m_last(list2.m_last) {
                list2.m_first = nullptr;
                list2.m_last = nullptr;
                list2.m_size = 0;
            }


        //Aufg. 4.12, Zuweisungsoperator

        List<T> operator= (List<T> list){
            swap(list);
            return *this;
        }

        //Aufg. 4.3, push_front and pop_front

        void push_front(T const& v){
            if(empty()){
                m_first = new ListNode<T>(v,nullptr,nullptr);  
                m_last = m_first;
                ++ m_size;
            }
            else{
                m_first = new ListNode<T>(v,nullptr,m_first);
                (*(*m_first).m_next).m_prev = m_first;
                ++ m_size;
            }
        }

        void push_back(T const& v){
            if(empty()){
                m_first = new ListNode<T>(v,nullptr,nullptr);  
                m_last = m_first;
                ++ m_size;
            }
            else{
                m_last = new ListNode<T>(v,m_last,nullptr);
                (*(*m_last).m_prev).m_next = m_last;
                ++ m_size;
            }
        }

        //Aufg. 4.9, insert at certain position

        void insert(iterator p, T const& v){         
            if(p == begin()){
                push_front(v);
            }
            else if(p == bend()){
                push_back(v);
            }
            else{
                ListNode <T>* newNode = new ListNode<T>(v, p.prev().m_node, p.m_node);
                p.m_node->m_prev = newNode;
                newNode->m_prev->m_next = newNode;
                ++ m_size;
            }
        }

        //Aufg. 4.3, pop_front, pop_back, front, back

        void pop_front(){
            if(empty()){
                std::cout << "The list is empty";
            }
            if(size() == 1){
                m_first = nullptr;
                m_last = nullptr;
                -- m_size;
            }
            else{
                m_first = &*(*m_first).m_next;
                (*m_first).m_prev = nullptr;
                -- m_size;
            }
        }

        void pop_back(){
            if(empty()){
                std::cout << "The list is empty";
            }
            if(size() == 1){
                m_first = nullptr;
                m_last = nullptr;
                -- m_size;
            }
            else{
                m_last = &*(*m_last).m_prev;
                (*m_last).m_next = nullptr;
                -- m_size;
            }
        }

        //gets value of the first element
        T front(){                                         
            if(empty()){
                std::cout << "The list is empty";
                return 0;
            }                       
            return m_first->m_value;     
        }

        //gets value of the last element
        T back(){
            if(empty()){
                std::cout << "The list is empty";
                return 0;
            }                       
            return m_last->m_value; 
        } 

        //Aufg. 4.4, clear, deletes all elements 

        void clear(){
            while(!empty()){
                pop_back();
            }
        }  

        //Aufg. 4.6

        //iterator points to first element
        ListIterator <T> begin() const{         
            if(empty()){
                return ListIterator<T>();
            }
            else{
                return ListIterator<T>(m_first);
            }
        }

        //iterator points to last element
        ListIterator <T> end() const{           
            if(empty()){
                return ListIterator<T>();
            }
            else{
                return ListIterator<T>(m_last);
            }
        }

        //iterator points to element behind last element
        ListIterator <T> bend() const{        
            return ListIterator<T>();
        } 
        
        //Aufg. 4.10, turns list around

        void reverse(){                
            int s = m_size;             //remember the size
            auto a = begin();
            while(a != nullptr){        //Add all the elements (reversed) at the front
                push_front(*a);
                ++a;
            }
            for(int i = 1; i <= s; ++i){        //Delete the old ones at the back
                pop_back();
            }
        }

        //Aufg. 4.12, swaps the elements of two lists

        void swap(List<T>& list){
            std::swap(m_size, list.m_size);
            std::swap(m_first, list.m_first);
            std::swap(m_last, list.m_last);
        }
        


    private:
        std::size_t m_size = 0;
        ListNode <T>* m_first = nullptr;
        ListNode <T>* m_last = nullptr;
};

//Aufg. 4.10, free reverse function 

template <typename T> 
List<T> reverse(List<T> const& list){
    List<T> list2;
    auto a = list.begin();
    while(a != nullptr){
        list2.push_front(*a);           //push elements of list reversed into list2
        ++a;
    }
    return list2;
}

#endif //#define BUW_LIST_HPP