#ifndef GUISPACE_H
#define GUISPACE_H

#include <QPainter>

class CGUISpace
{
public:
    CGUISpace(){}
    CGUISpace(unsigned int x, unsigned int y);

    void Draw(QPainter*);
private:
    unsigned int m_width;
    unsigned int m_height;
};

#endif // GUISPACE_H
