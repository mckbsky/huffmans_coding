#ifndef HUFFMANS_CODING_WINDOW_HPP
#define HUFFMANS_CODING_WINDOW_HPP


#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>

class Window : public QMainWindow {

private:

    QWidget *widget;
    QVBoxLayout *qvBoxLayout;

    void showAuthorsPopup();

    void showAboutPopup();

    void exportAction();

    void importAction();

public:

    Window();

    void initWindow();

    QLayout *initLabelLayer();

    void initMainVBox();

    QLayout *initInputLayer();

    QLayout *initKeyLayer();

    QLayout *initButtonLayer();

    void initMenu();

    void initFileMenu(QMenuBar *pBar);

    void initHelpMenu(QMenuBar *pBar);
};

#endif
