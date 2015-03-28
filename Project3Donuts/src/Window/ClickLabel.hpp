#ifndef CLICK_LABEL_H
#define CLICK_LABEL_H

#include "global.hpp"

//! \class ClickLabel
//! \brief A new kind of button to chose colors (preview enable)
class ClickLabel : public QLabel
{

Q_OBJECT

public:
    //! \brief Constructor, create a new label with no text and the given color
    explicit ClickLabel( const QPalette& fcolor, QWidget * fparent = 0 );
    ~ClickLabel();

signals:
    void clicked();

protected:
    //! \brief Whenever the mouse is pressed while being above the label, send the clicked() signal.
    void mousePressEvent ( QMouseEvent * fevent ) override;
};


#endif
