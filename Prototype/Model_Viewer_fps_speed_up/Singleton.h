#ifndef SINGLETON_H
#define SINGLETON_H


template <typename T>

class Singleton {

 protected:
  // Constructeur/destructeur
  Singleton() { }
  ~Singleton() { }

 public:
  // Interface publique
  static T* getInstance() {
    if (nullptr == mSingleton) {

      mSingleton = new T;
    }

    return mSingleton;
  }

  static void destroy() {
    if (nullptr != mSingleton) {
      delete mSingleton;
      mSingleton = nullptr;
    }
  }

 private:
  // Unique instance
  static T* mSingleton;
};

template <typename T>

T* Singleton<T>::mSingleton = nullptr;

#endif
