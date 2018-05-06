#include <Window.hpp>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

Window::Window() {
    this->widget = new QWidget();
    initWindow();
    initMainVBox();
}

void Window::initMainVBox() {
    qvBoxLayout = new QVBoxLayout();
    qvBoxLayout->addLayout(initLabelLayer());
    qvBoxLayout->addLayout(initInputLayer());
    qvBoxLayout->addLayout(initKeyLayer());
    qvBoxLayout->addLayout(initButtonLayer());
    widget->setLayout(qvBoxLayout);
}

void Window::initWindow() {
    setCentralWidget(widget);
    setWindowTitle("Kodowanie Huffmana");
    resize(800, 600);
    move(100, 100);
}

QLayout *Window::initLabelLayer() {
    auto inLabel = new QLabel();
    inLabel->setText(QString("Wejscie"));
    auto outLabel = new QLabel();
    outLabel->setText(QString("Wyjscie"));
    auto boxLayout = new QHBoxLayout();
    boxLayout->addWidget(inLabel);
    boxLayout->addWidget(outLabel);
    return boxLayout;
}

QLayout *Window::initInputLayer() {
    auto boxLayout = new QHBoxLayout();
    auto inTextEdit = new QTextEdit();
    auto outTextEdit = new QTextEdit();
    boxLayout->addWidget(inTextEdit);
    boxLayout->addWidget(outTextEdit);
    return boxLayout;
}

QLayout *Window::initKeyLayer() {
    auto keyLabel = new QLabel();
    keyLabel->setText(QString("Klucz: "));
    auto keyInput = new QLineEdit();
    auto boxLayout = new QHBoxLayout();
    boxLayout->addWidget(keyLabel);
    boxLayout->addWidget(keyInput);
    return boxLayout;
}

QLayout *Window::initButtonLayer() {
    auto encodeButton = new QPushButton();
    encodeButton->setText("Kodowanie");
    auto decodeButton = new QPushButton();
    decodeButton->setText("Dekodowanie");
    auto boxLayout = new QHBoxLayout();
    boxLayout->addWidget(encodeButton);
    boxLayout->addWidget(decodeButton);
    return boxLayout;
}
