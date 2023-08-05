#ifndef Vec2_h
#define Vec2_h


template <class T> class myVector{
    public:
    typedef T* iterator;

    myVector(){this->create()}
    myVector(unsigned int n, const T& t = T()) {this->create(n,T)}
    myVector(const myVector& V) {copy(V)};
    myVector& operator= (const myVector& V);
    ~myVector() {delete [] data}
    T& operator[] (unsigned int i) { return data[i];}
    void push_back(const T& t);
    void push_front(const T& t);
    //erase
    iterator erase(iterator p);
    void clear();
    unsigned int size() const {return m_size;}
    void resize(unsigned int n, const T& fill_value = T());
    private:
    void create();
    void  create(unsigned int n, const T& val);
    void copy(const myVector<T>& V);
    T* data;
    unsigned int m_size;
    unsigned int m_alloc;

};



template <class T> void myVector<T>::create() {
data = NULL;
m_size = 0;
m_alloc = 0;    
}

template <class T> void myVector<T>::create(unsigned int n , const T& val) {
    data = new T[n];
    m_size = n;
    m_alloc = n;
    for (int i = 0; i < n; ++i){
        data[i] = val;

    }
    
}


template <class T> void myVector<T>::copy(const myVector<T>& V) {
 this->m_alloc = V.m_alloc;
 this->m_size = V.m_size;
 this->data = new T[this->m_alloc];
 for(int i = 0; i < this->m_size; ++i){
    this->data[i] = V.data[i];
 }    
}


template <class T> myVector& myVector<T>::operator=(const myVector<T>& V) {
    if(this != &V){
        delete [] data;
        this->copy(V);
    }
  
   

   return *this;

}

template <class T> void myVector<T>::resize(unsigned int n, const T& fill_value = T()) {
if(n <= m_size){
    m_size = n;
} else{
    if(n > m_alloc){
        m_alloc = n;
        T* tmp = new T[m_alloc];
        for(int i = 0; i < m_size; ++i){
            tmp[i] = data[i];
        }
        delete []data;
        data = tmp;
    }

    for(int i = m_size; i < m_alloc; ++i){
        data[i] = fill_value;
    }

    m_size = n;
}

}

template <class T> void myVector<T>::push_back(const T& t){
    if(m_size == m_alloc){
        if(m_alloc = 0){
            resize(1);
        } else{
        resize(m_alloc * 2);

        }
    }
    data[m_size] = t;
    ++m_size;
} 




template <class T> typename myVector<T>::iterator myVector<T>::erase(iterator p){
    for(iterator q = p; q < data + m_size - 1; ++q){
        *q = *(q + 1);
    }
    --m_size;
    return p;

}




#endif