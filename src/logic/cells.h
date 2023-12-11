#ifndef CELLS_H
#define CELLS_H

class Cell {
   public:
    Cell();
    ~Cell();

    void setVisible(bool visible);
    bool isVisible();

    void setHasMine(bool isMine);
    bool isMined();

    void setFlag(bool flag);
    bool isFlagged();

    void setValue(int value);
    int getValue();

    void toggleFlag();

   private:
    bool visible = false;
    bool hasMine = false;
    bool flag = false;
    int value = 0;
};

#endif  // CELLS_H
