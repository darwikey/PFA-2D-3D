#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "ui_about.h"
#include "ui_notice.h"
#include "Settings.hpp"

namespace Ui {
class MainWindow;
}

//! \class MainWindow
//! \brief The MainWindow is in charge of all the windows exept the settings window and the viewer window.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! \brief Constructor, create a new window with an empty scene.
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //Pointer to the auto-generated code, which holds the properties and layout of the window.
    Ui::MainWindow *ui;

public slots:

   //! \brief Create a newscene.
   void newscene();

   //! \brief Ask for a model. Import the new model into the scene.
   void openfile();

   //! \brief Cancel the last registered action.
   void revertPreviousAction();

   //! \brief Ask for a Model. Import a new model into the scene, from  the Library path given in Settings.
   void openlibfile();

   //! \brief Ask for a path. Clear the current scene and Open a new scene from the path.
   void open();

   //! \brief Save the current scene if it has a name, call saveas otherwise.
   void save();

   //! \brief Ask for a path. Save the current scene to the path, and change the name of the scene.
   void saveas();

   //! \brief Select (in the viewer) the object selected in the list.
   void selectObject(const QModelIndex &index);

   //! \brief Delete (in both the viewer and the list) the object selected in the list.
   void deleteSelectedObject();

   //! \brief Change the color, in the viewer of the selected object.
   void changeObjectColor();

   //! \brief Invert the position of the viewer and the list.
   void invertwidgets();

   //! \brief Open the settings window.
   void editsettings();

   //! \brief Open the about window.
   void about();

   //! \brief Open the notice window.
   void notice();
   void translateCameraToZero();

   //! \brief Change the current shortcuts if they have been modified in the ini file.
   void checkSettings(int);

   //! \brief Change the TransformWidget mode to translate.
   void changeModeToTranslate();

   //! \brief Change the TransformWidget mode to rotate.
   void changeModeToRotate();

   //! \brief Change the TransformWidget mode to scale.
   void changeModeToScale();

   //! \brief Change the title of the window and the mNeedSave parameters to notify that there are unsaved changed to the scene.
   void newaction();

private:
   bool mNeedSave;
   QMainWindow * win_about;
   QMainWindow * win_notice;
   Settings * _settingsWindow;
   //Pointers to the auto-generated code, which holds the properties and layout of the windows.
   Ui::About* _about_ui;
   Ui::Notice* _notice_ui;

protected:
   //! \brief Whenever we try to end the program, check if there are unsaved changes, and ask for confirmation.
   void closeEvent(QCloseEvent *event) override;

};
#endif // MAINWINDOW_HPP
