#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QPushButton>
#include <QWidget>
#include "matrix.h"
#include "node.h"
#include "astar.h"
#include "QSpinBox"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sizeButtonClicked();
    void startButtonClicked();
    void showResultMatrix();

private:
    Ui::MainWindow *ui;

    QWidget* m_mainWidget;
    QGridLayout* m_mainLayout;

    QPushButton* m_sizeButton;
    QSpinBox* m_sizeSpinBox;

    Matrix* m_initMatrix;
    QVBoxLayout* m_initLayout;

    Matrix* m_finalMatrix;
    QVBoxLayout* m_finalLayout;

    Matrix* m_resultMatrix;
    QVBoxLayout* m_resultLayout;
    QLabel* m_stepCount;

    QPushButton* m_startButton;
    QPushButton* m_nextButton;

    Node* m_result;
    int m_count;

    QGroupBox* createSizeGroupBox();
    QGroupBox* createInitGroupBox();
    QGroupBox* createFinalGroupBox();
    QGroupBox* createResultGroupBox();
    QGroupBox* createButtonsGroupBox();


};
#endif // MAINWINDOW_H
