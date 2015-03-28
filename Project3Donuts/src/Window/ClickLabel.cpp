#include "ClickLabel.hpp"

ClickLabel::ClickLabel( const QPalette& fcolor, QWidget * fparent ) :
    QLabel(fparent)
  {
	   setText("");
       setPalette(QPalette(fcolor));
       setAutoFillBackground(true);
  }

ClickLabel::~ClickLabel()
{
}

void ClickLabel::mousePressEvent ( QMouseEvent * fevent )
{
    emit clicked();
}
