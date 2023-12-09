#ifndef CELLS_H
#define CELLS_H

class Cell {
   public:
    Cell();
    ~Cell();

    void setIsVisible(bool isVisible);
    bool getIsVisible();

    void setIsMine(bool isMine);
    bool isMined();

    void setFlag(bool flag);
    bool isFlagged();

    void setValue(int value);
    int getValue();

   private:
    bool isVisible;
    bool isMine;
    bool flag;
    int value;
};

#endif  // CELLS_H
