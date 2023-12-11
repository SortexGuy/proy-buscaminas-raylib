#ifndef CELLS_H
#define CELLS_H

class Cell {
   public:
    Cell();
    ~Cell();

    void setVisible(bool visible);
    bool isVisible();

    void setMined(bool isMine);
    bool isMined();

    void setFlag(bool flag);
    bool isFlagged();

    void setValue(int value);
    int getValue();

    void toggleFlag();

   private:
    bool visible;
    bool isMine;
    bool flag;
    int value;
};

#endif  // CELLS_H
