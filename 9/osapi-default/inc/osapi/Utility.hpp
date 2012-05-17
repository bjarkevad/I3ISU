#ifndef OSAPI_UTILITY_HPP
#define OSAPI_UTILITY_HPP


namespace osapi
{
  class Notcopyable
  {
  protected:
    Notcopyable() { }
    ~Notcopyable() { }
    
  private:
    Notcopyable(const Notcopyable&);
    const Notcopyable& operator=(const Notcopyable&);
  };


  
  void sleep(unsigned long msecs);
}



#endif
