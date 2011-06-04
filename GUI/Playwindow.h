#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H
#include "Guiview.h"

class CPlayWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CPlayWindow(QWidget* parent  = 0);

    void CreateWindow(const unsigned int x, const unsigned int y);
    void DestroyWindow();
    void ShowWindow();

    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    CGUIView* GetView();

    void SetPlayerId(unsigned int id);
private:
    CGUIView* m_view;
    unsigned int m_playerId;

    bool m_mouseSelection;
    bool m_mouseActive;
    unsigned int m_mousePressedX;
    unsigned int m_mousePressedY;
    unsigned int m_mouseCurrentX;
    unsigned int m_mouseCurrentY;
};

#endif // PLAYWINDOW_H
