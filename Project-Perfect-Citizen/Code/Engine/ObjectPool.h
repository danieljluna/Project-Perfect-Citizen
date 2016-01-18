#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <new>
#include <stdexcept>
#include <iostream>


namespace pcg {


//TODO: Add Doxygen Comments to ObjectPool
///////////////////////////////////////////////////////////////////////
/// @brief A staitc-sized container of Objects that rapidly are created 
///     and destroyed.
/// @details A generic templated class for managing a pool of objects.
///     This class mainly functions as a container that returns the
///     next available object to initialize. The exact initialization
///     is left to the user.
///     All N active objects are accessible using the [] operator. 
///     Attempting to access to elements beyond the Nth using the []
///     operator (i.e. when index >= activeCount_), will throw an out-
///     of-range exception.
///     ObjectPool assumes the object it pools has a Default and Copy
///     Constructor.
///
///////////////////////////////////////////////////////////////////////
template <class ObjectType>
class ObjectPool {
public:
  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    //Default Constructor
    ObjectPool(size_t poolSize = 0) {
        //Allocate memory for the pool
        if (poolSize > 0) {
            try {
                pool_ = new ObjectType[poolSize];
                poolSize_ = poolSize;
            }
            catch (std::exception& excep) {
                std::cerr << "ObjectPool::" << excep.what() << std::endl;
                pool_ = nullptr;
                poolSize_ = 0;
            }
        }
        else {
            pool_ = nullptr;
            poolSize_ = 0;
        }

        //No objects are active
        activeCount_ = 0;
    };



    //Copy Constructor
    ObjectPool(const ObjectPool<ObjectType>& other) 
            : ObjectPool<ObjectType>(other.poolSize_) {
        //Check if the pool was allocated correctly
        if (poolSize_ == other.poolSize_) {

            //Duplicate all active particles
            for (size_t i = 0; i < activeCount_; ++i) {
                pool_[i] = other.poolSize_[i];
            }
        }
    };



    //Destructor
    ~ObjectPool() {
        //Delete Pool
        delete[] pool_;
    };




  /////////////////////////////////////////////////////////////////////
  // Pool Management
  /////////////////////////////////////////////////////////////////////

    //Changes the maximum number of Objects the pool can hold.
    //Pre:  No object is in-use.
    //Post: The pool can now hold a maximum of poolSize objects.
    void resize(size_t poolSize) {

        //If no object is in use...
        if (activeCount_ == 0) {

            //Clear old memory for the pool
            if (pool_ != nullptr) {
                delete[] pool_;
            }

            //Allocate memory for the pool
            if (poolSize > 0) {
                try {
                    pool_ = new ObjectType[poolSize];
                    poolSize_ = poolSize;
                }
                catch (std::exception& excep) {
                    std::cerr << "ObjectPool::" << excep.what() << endl;
                    pool_ = nullptr;
                    poolSize_ = 0;
                }
            }
            else {
                pool_ = nullptr;
                poolSize_ = 0;
            }
        }

        //No objects are active
        activeCount_ = 0;
    };


    //Activates an object for use and returns a pointer to it for 
    //  initialization.
    //Pre:  (activeCount_ < poolSize_)
    //Ret:  Returns a pointer to the next object to activate. If there
    //      are none reusable objects left, this function returns 
    //      nullptr.
    ObjectType* createObject() const {

        //If we have more objects to activate
        if (activeCount_ < poolSize_) {
            ++activeCount_;
            return pool_ + (activeCount_ - 1);
        }
        else {
            return nullptr;
        }
    };


    //Deactivates the object at the given index.
    //Pre: (index < activeCount_)
    void destroyObject(size_t index) const {
        //If we are trying to destroy an inactive index, simply ignore it.
        //      Otherwise:
        if (index < activeCount_) {

            //If the object being destroyed is not the same as the last
            //      object in the pool.
            if (index < poolSize_) {
                //Swap the object in question with the last active object.
                pool_[index] = pool_[activeCount_ - 1];
            }

            --activeCount_;
        }
    };


  /////////////////////////////////////////////////////////////////////
  // Getters
  /////////////////////////////////////////////////////////////////////

    //Returns the size of the ObjectPool
    size_t size() const { return poolSize_; };

    //Returns the number of active Objects
    size_t activeObjects() const { return activeCount_; };

    //Returns a pointer to the index-th active Object
    //Pre:  (0 < index < activeCount_)
    ObjectType& operator[] (size_t index) const {
        //Check if we have a valid index
        if (index >= activeCount_) {
            //User is accessing ObjectPool out of range
            throw std::out_of_range("ObjectPool::Index_Out_of_Range");
        }
        else {
            //Return a reference to that Object
            return (*(pool_ + index));
        }
    };




private:
  /////////////////////////////////////////////////////////////////////
  // Private Variables
  /////////////////////////////////////////////////////////////////////

    //Pointer to the Object array
    ObjectType* pool_;

    //Stores the maximum amount of Objects the pool can hold
    size_t poolSize_;

    //Stores the current amount of active Objects
    size_t activeCount_;


};


};      //End namespace pcg


#endif  //End OBJECT_POOL_H
