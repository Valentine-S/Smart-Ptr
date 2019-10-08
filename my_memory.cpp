//Valentine Shidlovskiy
//CSCI - 335 - Home Project 1

template <typename T>
my_unique_ptr<T>::my_unique_ptr(){//Default Constuctor, NO Paramaters
  p = nullptr;
}

template <typename T>
my_unique_ptr<T>::my_unique_ptr(T* nptr){//Construcor, Takes a PTR parameter
  p = nptr;
}

template <typename T>
my_unique_ptr<T>::my_unique_ptr(my_unique_ptr && uptr){//Move Construcor
  if(this != &uptr){
    p = std::move(uptr.p);
    uptr.p = nullptr;
  }
}

template <typename T>
my_unique_ptr<T>& my_unique_ptr<T>::operator=(my_unique_ptr<T> && uptr){//Move Assignment
   if(this != &uptr){
     if(uptr.p != nullptr){
       delete p;
       p = std::move(uptr.p);
       uptr.p = nullptr;
     }
     else{
       delete p;
       p = nullptr;
     }
  }
   return *this;
}

template <typename T>
bool my_unique_ptr<T>::isNullptr(){
  if (p == nullptr){
    return true;
  }
  else{
    return false;
  }
}

template <typename T>
my_unique_ptr<T>::~my_unique_ptr(){//Destructor
  delete p;
}

template <typename T>
T& my_unique_ptr<T>::operator*(){
  return *p;
}

template <typename T>
T* my_unique_ptr<T>::operator->(){
  return p;
}

//Shared PTR - =====================================================================

template <typename T>
my_shared_ptr<T>::my_shared_ptr(){//Default Constuctor, NO Paramaters
  p = nullptr;
  count = nullptr;
}

template <typename T>
my_shared_ptr<T>::my_shared_ptr(T* nptr){//Construcor, Takes a PTR parameter
  if(nptr != nullptr){
    p = nptr;
    count = new int;
    *count = 1;
  }
  else{
    p = nullptr;
    count = nullptr;
  }
}

template <typename T>
my_shared_ptr<T>::my_shared_ptr(my_shared_ptr && uptr){ // Move Constructor
  if(this != &uptr){//Checks if main is attempting to move something onto it self
    if(uptr.p != nullptr){
      p = std::move(uptr.p); //Move p and count and set uptr to nullptr, prevents memory leaks
      uptr.p = nullptr;
      count = std::move(uptr.count);
      uptr.count = nullptr;
    }
    else{
      p = nullptr;
      count = nullptr;
    }
  }
}

template <typename T>
my_shared_ptr<T>::my_shared_ptr(const my_shared_ptr & uptr){ // Copy Constructor
  p = nullptr;
  count = nullptr;
  if(uptr.p != nullptr){ //copy where uptr is pointing to p and count. Increase count by 1
    p = uptr.p;
    count = uptr.count;
    (*count)++;
  }
}

template <typename T>
my_shared_ptr<T>& my_shared_ptr<T>::operator=(my_shared_ptr && uptr){ //Move assignment operator
  if (uptr.p  == p) {
    return *this;
  }

  T* tempPtr = p; //Create a temporary ptr to keep track of the P
  int* tempCount = count;//create a temporart ptr to keep track of the count

  p = uptr.p; //make THIS point to the next ptr and next count
  count = uptr.count;
  uptr.p = nullptr; 
  uptr.count = nullptr;
  if(tempCount){ 
    (*tempCount)--;
    if(*tempCount == 0){ //subtract one from temp count and check if it is equal to 0, 
      delete tempPtr;
      delete tempCount;
    }
  }
  return *this;
}



template <typename T>
my_shared_ptr<T>& my_shared_ptr<T>::operator=(const my_shared_ptr & uptr){ //Copy assignment operator
  if(this != &uptr){
    my_shared_ptr<T> temp{uptr};//create a temp shared ptr that will make sure there is no lost memory if uptr points to another shared ptr
    
    if(uptr.p != nullptr){
      if(count != nullptr){
	(*count)--;
	if(*count == 0){ //decrease count by 1 and check if it is equal to 0
	  if(p != nullptr){
	    delete p;	    
	    delete count;	    
	  }
	  else{
	    delete count;
	  }
	}
      }
      p = std::move(temp.p); //use the temp to get the information we were holding for later
      temp.p = nullptr;
      count = std::move(temp.count);
      temp.count = nullptr; //set temp to nullptr
    }
    else{
      if(p != nullptr){
	delete p;
	p = nullptr;
      }
      if(count != nullptr){
	delete count;
	count = nullptr;
      }
    }
  }
  return *this;
}

template <typename T>
bool my_shared_ptr<T>::isNullptr(){
  if (p == nullptr){
    return true;
  }
  else{
    return false;
  }
}

template <typename T>
T& my_shared_ptr<T>::operator*(){
  return *p;
}

template <typename T>
T* my_shared_ptr<T>::operator->(){
  return p;
}

template <typename T>
my_shared_ptr<T>::~my_shared_ptr(){
  if(p != nullptr){//Check if p and count are nullptr
    if(count != nullptr){
      (*count)--;
      if((*count) == 0){//decrease count and check if it is == 0.
	delete p;
	delete count;
      }
    }
  }
}

