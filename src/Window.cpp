#include <Window.hpp>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>
#include <QtCore/QCoreApplication>
#include <QtWidgets/QFileDialog>
#include <iostream>
#include <headers/Huffman.hpp>

Window::Window() {
    initWindow();
    initMainVBox();
    initMenu();
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
    this->widget = new QWidget();
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
    inTextEdit = new QTextEdit();
    outTextEdit = new QTextEdit();
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
    connect(encodeButton, &QPushButton::released, this, &Window::encodeAction);
    auto decodeButton = new QPushButton();
    decodeButton->setText("Dekodowanie");
    auto boxLayout = new QHBoxLayout();
    boxLayout->addWidget(encodeButton);
    boxLayout->addWidget(decodeButton);
    return boxLayout;
}

void Window::initMenu() {
    auto mainMenu = menuBar();
    initFileMenu(mainMenu);
    initHelpMenu(mainMenu);
}

void Window::initFileMenu(QMenuBar *mainMenu) {
    auto fileMenu = mainMenu->addMenu("Plik");
    auto importAction = fileMenu->addAction("Import");
    connect(importAction, &QAction::triggered, this, &Window::importAction);
    auto exportAction = fileMenu->addAction("Export");
    connect(exportAction, &QAction::triggered, this, &Window::exportAction);
    auto exitAction = fileMenu->addAction("Wyjście");
    connect(exitAction, &QAction::triggered, this, &QCoreApplication::exit);
}

void Window::initHelpMenu(QMenuBar *mainMenu) {
    auto helpMenu = mainMenu->addMenu("Pomoc");
    auto aboutAction = helpMenu->addAction("O programie");
    connect(aboutAction, &QAction::triggered, this, &Window::showAboutPopup);
    auto authorsAction = helpMenu->addAction("Autorzy");
    connect(authorsAction, &QAction::triggered, this, &Window::showAuthorsPopup);
}

void Window::showAuthorsPopup() {
    QMessageBox::about(this, "Autorzy", "Maciej Brzęczkowski");
}

void Window::showAboutPopup() {
    QMessageBox::about(this, "O programie", "Kodowanie Huffmana\n Projekt z przedmiotu 'Wstęp do komunikacji "
                                            "człowiek-komputer\n 2018");
}

void Window::exportAction() {
    QString filename = QFileDialog::getSaveFileName(this, QFileDialog::tr("Eksport"), "");
}

void Window::importAction() {
    QString filename = QFileDialog::getOpenFileName(this, QFileDialog::tr("Import"), "");
}

void Window::encodeAction() {
    auto inputText = inTextEdit->toPlainText().toLatin1().data();
    Huffman huffman;
    auto encodedChars = huffman.doEncode(inputText, "out.txt", Argument::STRING);
    std::string encodedString(encodedChars.begin(), encodedChars.end());
    outTextEdit->setPlainText(QString(encodedString.c_str()));
}
