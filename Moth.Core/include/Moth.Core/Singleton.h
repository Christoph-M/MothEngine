#pragma once

/*!
* @brief   This class represents, manages and deletes a singleton_
*/
template<typename T>
class Singleton {
#define SINGLETONCLASS(T) friend class Singleton<T>; protected: T();
public:

    /*!
    * @brief   This method creates a singleton_ for the child class
    */
    static void CreateInstance(void) { if (!singleton_) singleton_ = new T(); }

    /*!
    * @brief   This method generates a singleton_ pointer to the child class if none exists
    * @return  The pointer to the child class as singleton_
    */
    static T* InstancePtr(void) {
		CreateInstance();
        return singleton_;
    }

    /*!
    * @brief   This method generates a reference to the child class if none exists
    * @return  The reference to the child class as singleton_
    */
    static T& Instance(void) { return *InstancePtr(); }

    /*!
    * @brief   This method resets the instance of the singleton_ class
    */
    static void ResetInstance(void) {
        if (singleton_) {
            delete singleton_;
            singleton_ = nullptr;
        }
    }

private:
    static T* singleton_;

    Singleton(const Singleton<T>&) { }

protected:
    Singleton(void) { }
};

template<typename T> T* Singleton<T>::singleton_ = nullptr;