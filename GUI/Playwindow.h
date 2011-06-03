#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H
#include "Guiview.h"

class CPlayWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CPlayWindow(QWidget* parent  = 0);

    void CreateWindow();
    void DestroyWindow();
    void ShowWindow();

    void paintEvent(QPaintEvent *);

    void setView(CGUIView* view);
private:
    CGUIView* m_view;
};

#endif // PLAYWINDOW_H
