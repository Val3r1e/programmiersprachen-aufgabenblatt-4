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
        /*if (m_node->m_next == nullptr){
            std::cout << "This is the last node";
            //return 0;
        }*/
        m_node = m_node->m_next;
        return *this;
    } 

    Self operator++(int){
        /*if (m_node->m_next == nullptr){
            std::cout << "This is the last node";
            //return 0;
        }*/
        ListIterator old(*this);
        m_node = m_node->m_next;
        return old;
        
    } 

    bool operator==(const Self& x) const{
        return m_node == x.m_node;
    } 

    bool operator!=(const Self& x) const{
        return m_node != x.m_node;
    } 

    Self next() const{
        if(m_node)
            return ListIterator(m_node->m_next);
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

//Aufg. 4.7

template <typename T>
bool operator ==(List <T> const & xs , List <T> const & ys){
    auto a = xs.begin();
    auto b = ys.begin();
    bool c = true;
    if(xs.size() != ys.size()){
        c = false;
    }
    else{
        while(a != nullptr){
            if(*a != *b){
                c = false;
            }
            ++a;
            ++b;
        }
    }
    return c;
}

template <typename T>
bool operator !=(List <T> const & xs , List <T> const & ys){
    auto a = xs.begin();
    auto b = ys.begin();
    bool c = false;
    if(xs.size() != ys.size()){
        c = true;
    }
    else{
        while(a != nullptr){
            if(*a != *b){
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

        //Dstructor

        ~List(){
            clear();
        }

        //Copy Constructor

        List(List<T> const& list):                //schon implementierte Liste
            m_first(nullptr),
            m_last(nullptr) {
                auto b = list.begin();
                while(b != nullptr){
                    push_back(*b);              //Nicht push_front
                    ++b;
                }
            }

        //Move Constructor

        List(List<T>&& list2):
            m_size(list2.m_size),
            m_first(list2.m_first),
            m_last(list2.m_last) {
                list2.m_first = nullptr;
                list2.m_last = nullptr;
                list2.m_size = 0;
            }
        


        //http://en.cppreference.com/w/cpp/container/list/empty
        bool empty() const{
            return m_size == 0;
        }
        //http://en.cppreference.com/w/cpp/container/list/size
        std::size_t size() const{
            return m_size;
        }

        //Aufg. 4.3

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

        //Aufg. 4.9

        /*void insert(const iterator& x, T const& v){         //not done
            if(x == begin()){
                push_front(v);
            }
            else if(x == end()){
                push_back(v);
            }
            else{

            }
        }*/

        //Aufg. 4.3

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

        T front(){
            if(empty()){
                std::cout << "The list is empty";
                return 0;
            }
            ListNode <T> front = *m_first;
            return front.m_value;                         //m_first->m_value     
        }

        T back(){
            if(empty()){
                std::cout << "The list is empty";
                return 0;
            }
            ListNode <T> back = *m_last;
            return back.m_value;                        //m_last->m_value 
        } 

        void clear(){
            /*m_first = nullptr;
            m_last = nullptr;
            m_size = 0;*/
            while(!empty()){
                pop_back();
            }
        }  

        //Aufg. 4.6

        ListIterator <T> begin() const{
            if(empty()){
                return ListIterator<T>();
            }
            else{
                return ListIterator<T>(m_first);
            }
        }

        ListIterator <T> end() const{
            if(empty()){
                return ListIterator<T>();
            }
            else{
                return ListIterator<T>(m_last);
            }
        } 
        
        //Aufg. 4.10

        void reverse(){                
            int s = m_size;
            auto a = begin();
            while(a != nullptr){
                push_front(*a);
                ++a;
            }
            for(int i = 1; i <= s; ++i){
                pop_back();
            }
        }


        


    private:
        std::size_t m_size = 0;
        ListNode <T>* m_first = nullptr;
        ListNode <T>* m_last = nullptr;
};

template <typename T> 
List<T> reverse(List<T> const& list){
    List<T> list2;
    auto a = list.begin();
    while(a != nullptr){
        list2.push_front(*a);
        ++a;
    }
    return list2;
}

#endif //#define BUW_LIST_HPP