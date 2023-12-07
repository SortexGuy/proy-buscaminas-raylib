#ifndef CELLS_H
#define CELLS_H

class Cell {
   public:
    Cell();
    ~Cell();

    void setIsVisible(bool isVisible);
    bool getIsVisible();

    void setIsMine(bool isMine);
    bool getIsMine();

    void setFlag(bool flag);
    bool getFlag();

    void setValue(int value);
    int getValue();

   private:
    bool isVisible;
    bool isMine;
    bool flag;
    int value;
};

#endif  // CELLS_H
