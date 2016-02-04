#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <new>
#include <stdexcept>
#include <iostream>


namespace ppc {


//TODO: Add Doxygen Comments to ObjectPool
///////////////////////////////////////////////////////////////////////
/// @brief A staitc-sized container of Objects that rapidly are created 
///     and destroyed.
/// @author Daniel Luna (for CMPM 265, in case we need it)
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

    ///////////////////////////////////////////////////////////////////
    /// @brief Default Constructor
    /// @details Initializes the pool to the given size.
    ///
    /// @param poolSize The desired size of the pool.
    ///////////////////////////////////////////////////////////////////
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



    ///////////////////////////////////////////////////////////////////
    /// @brief Copy Constructor
    /// @details Creates another pool of the same size and with 
    ///     deep copy of the active particles.
    ///////////////////////////////////////////////////////////////////
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



    ///////////////////////////////////////////////////////////////////
    /// @brief Destructor
    /// @details Namely deletes the allocated pool.
    ///////////////////////////////////////////////////////////////////
    ~ObjectPool() {
        //Delete Pool
        delete[] pool_;
    };




  /////////////////////////////////////////////////////////////////////
  // Pool Management
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Changes the maximum number of Objects the pool can hold.
    ///
    /// @pre No object in the pool is in-use, and there is enough
    ///     memory for the desired size.
    /// @post size() = poolSize;
    /// @param poolSize The desired size of the pool.
    ///////////////////////////////////////////////////////////////////
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


    ///////////////////////////////////////////////////////////////////
    /// @brief Activates an object for use.
    /// @details The newly activated object's initialization is left
    ///     to the user, and thus this function returns a pointer to
    ///     the activated object. This function uses the nullptr to 
    ///     denote a failed activation.
    ///
    /// @pre (activeCount_ < poolSize_)
    /// @post activeObjects() += 1;
    /// @return Returns a pointer to the next object to activate. If
    ///     there are none reusable objects left, this function returns
    ///     nullptr.
    ///////////////////////////////////////////////////////////////////
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


    ///////////////////////////////////////////////////////////////////
    /// @brief Deactivates the object at the given index.
    /// @details Due to the way this moves around objects in the pool,
    ///     if you have to deactivate multiple objects at once, destroy
    ///     the object with the highest index first.
    ///
    /// @pre (index < activeCount_)
    /// @post activeObjects() -= 1;
    ///////////////////////////////////////////////////////////////////
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

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns the size of the pool.
    ///
    /// @return Size of the pool.
    ///////////////////////////////////////////////////////////////////
    size_t size() const { return poolSize_; };

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns the number of active objects in the pool.
    ///
    /// @return The number of active objects in the pool.
    ///////////////////////////////////////////////////////////////////
    size_t activeObjects() const { return activeCount_; };

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns a pointer to the index-th active Object.
    ///
    /// @pre (0 < index < activeCount_)
    /// @return A pointer to the index-th active Object.
    ///////////////////////////////////////////////////////////////////
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


};      //End namespace ppc


#endif  //End OBJECT_POOL_H
