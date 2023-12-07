#ifndef CEILS_H
#define CEILS_H

class Ceil {
   public:
    Ceil();
    ~Ceil();

    void setIsVisible( bool isVisible );
    bool getIsVisible( );

    void setIsMine( bool isMine );
    bool getIsMine( );

    void setFlag( bool flag );
    bool getFlag( );

    void setValue( int value );
    int getValue( );
    
   private:
    bool isVisible;
    bool isMine;
    bool flag;
    int value;
  
};

#endif // CEILS_H


