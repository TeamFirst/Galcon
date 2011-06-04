#pragma once

#include <QWidget>
#include "message/MessageStepPlayer.h"

namespace GUI
{
   class CGUIView;

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
       void wheelEvent(QWheelEvent *);

       void mouseClick();

       CGUIView* GetView();

       void SetPlayerId(unsigned int id);

   signals:
       void SendStepPlayer(Message::CMessageStepPlayerPtr mess);
   private:
       CGUIView* m_view;
       unsigned int m_playerId;

       bool m_mouseSelection;
       bool m_mouseActive;
       int m_mousePressedX;
       int m_mousePressedY;
       int m_mouseCurrentX;
       int m_mouseCurrentY;
   };
} // Namespace GUI
