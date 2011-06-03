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
    CGUIView* GetView();
private:
    CGUIView* m_view;
};

#endif // PLAYWINDOW_H
