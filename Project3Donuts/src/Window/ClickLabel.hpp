#ifndef CLICK_LABEL_H
#define CLICK_LABEL_H

#include "global.hpp"

class ClickLabel : public QLabel
{

Q_OBJECT

public:
    explicit ClickLabel( const QPalette& color, QWidget * parent = 0 );
    ~ClickLabel();

signals:
    void clicked();

protected:
    void mousePressEvent ( QMouseEvent * event );
};


#endif
