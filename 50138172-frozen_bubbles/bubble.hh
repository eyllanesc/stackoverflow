#ifndef BUBBLE_HH
#define BUBBLE_HH

enum Color {RED, GREEN, BLUE, COLOR_COUNT};

class Bubble
{
public:
    Bubble(int x, int y, Color color);

    int getX() const;
    int getY() const;
    Color getColor() const;

private:
    int x_;
    int y_;
    Color color_;
};

#endif // BUBBLE_HH
