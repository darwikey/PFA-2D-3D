#include "ClickLabel.hpp"

ClickLabel::ClickLabel( const QPalette& color, QWidget * parent ) :
    QLabel(parent)

  {
	   setText("");
       setPalette(QPalette(color));
       setAutoFillBackground(true);
  }

  ClickLabel::~ClickLabel()
  {
  }

  void ClickLabel::mousePressEvent ( QMouseEvent * event )

  {
      emit clicked();
  }
