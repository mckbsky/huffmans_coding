#ifndef HUFFMANS_CODING_WINDOW_HPP
#define HUFFMANS_CODING_WINDOW_HPP


#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>

class Window : public QMainWindow {

private:

    QWidget *widget;
    QVBoxLayout *qvBoxLayout;

public:

    Window();

    void initWindow();

    QLayout *initLabelLayer();

    void initMainVBox();

    QLayout *initInputLayer();

    QLayout *initKeyLayer();

    QLayout *initButtonLayer();
};

#endif
