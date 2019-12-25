#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_result(nullptr)
{
    ui->setupUi(this);
    m_mainWidget = new QWidget(this);
    m_mainLayout = new QGridLayout(this);

    m_mainLayout->addWidget(createSizeGroupBox(), 0, 0, 1, 2);
    m_mainLayout->addWidget(createInitGroupBox(), 1, 0);
    m_mainLayout->addWidget(createFinalGroupBox(), 1, 1);
    m_mainLayout->addWidget(createResultGroupBox(), 2, 0);
    m_mainLayout->addWidget(createButtonsGroupBox(), 2, 1);

    m_mainWidget->setLayout(m_mainLayout);
    resize(1400,700);
    setWindowTitle("Пятнашки");
    setCentralWidget(m_mainWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGroupBox* MainWindow::createSizeGroupBox(){
    QGroupBox* group = new QGroupBox(this);
    QHBoxLayout* layout = new QHBoxLayout(group);

    QLabel* sizeLabel = new QLabel("Введите размер пятнашек: ", this);
    m_sizeSpinBox = new QSpinBox(this);
    m_sizeSpinBox->setRange(3, 5);
    m_sizeSpinBox->setValue(m_sizeSpinBox->maximum());
    m_sizeSpinBox->setSuffix("x" + QString::number(m_sizeSpinBox->value()));
    connect(m_sizeSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=]() {
         m_sizeSpinBox->setSuffix("x" + QString::number(m_sizeSpinBox->value()));
     });

    m_sizeButton = new QPushButton("Подвердить", this);
    connect(m_sizeButton, &QPushButton::clicked, this, &MainWindow::sizeButtonClicked);

    layout->addWidget(sizeLabel);
    layout->addWidget(m_sizeSpinBox);
    layout->addWidget(m_sizeButton);

    group->setLayout(layout);
    return group;
}

QGroupBox* MainWindow::createInitGroupBox(){
    QGroupBox* group = new QGroupBox("Начальное состояние", this);
    m_initLayout = new QVBoxLayout(group);

    m_initMatrix = new Matrix(m_sizeSpinBox->value(), this);

    QPushButton* initRandom = new QPushButton("Заполнить");
    connect(initRandom, &QPushButton::clicked, m_initMatrix, &Matrix::fillRandom);

    m_initLayout->addWidget(initRandom, Qt::AlignCenter);
    m_initLayout->addWidget(m_initMatrix, Qt::AlignCenter);
    m_initMatrix->resize(group->size());

    group->setLayout(m_initLayout);
    return group;
}

QGroupBox* MainWindow::createFinalGroupBox(){
    QGroupBox* group = new QGroupBox("Конечная цель", this);
    m_finalLayout  = new QVBoxLayout(group);

    m_finalMatrix = new Matrix(m_sizeSpinBox->value(), this);

    QPushButton* finalRandom = new QPushButton("Заполнить");
    connect(finalRandom, &QPushButton::clicked, m_finalMatrix, &Matrix::fillRandom);

    m_finalLayout->addWidget(finalRandom, Qt::AlignCenter);
    m_finalLayout->addWidget(m_finalMatrix, Qt::AlignCenter);
    m_finalMatrix->resize(group->size());

    group->setLayout(m_finalLayout);
    return group;
}

QGroupBox* MainWindow::createResultGroupBox(){
    QGroupBox* group = new QGroupBox(this);
    m_resultLayout  = new QVBoxLayout(group);

    m_resultMatrix = new Matrix(m_sizeSpinBox->value(), this);
    m_resultLayout->addWidget(m_resultMatrix);

    group->setLayout(m_resultLayout);
    return group;
}

QGroupBox* MainWindow::createButtonsGroupBox(){
    QGroupBox* group = new QGroupBox(this);
    QVBoxLayout* layout = new QVBoxLayout(group);

    m_startButton = new QPushButton("Начать", this);
    m_nextButton = new QPushButton("Следующий шаг", this);
    m_stepCount = new QLabel(this);

    m_startButton->setDisabled(false);
    m_nextButton->setDisabled(true);

    connect(m_startButton, &QPushButton::clicked, this, &MainWindow::startButtonClicked);
    connect(m_nextButton, &QPushButton::clicked, this, &MainWindow::showResultMatrix);

    layout->addWidget(m_startButton);
    layout->addWidget(m_nextButton);
    layout->addWidget(m_stepCount);

    group->setLayout(layout);
    return group;
}

void MainWindow::sizeButtonClicked()
{
   m_initMatrix->setMatrix(m_sizeSpinBox->value());
   m_finalMatrix->setMatrix(m_sizeSpinBox->value());
   m_resultMatrix->setMatrix(m_sizeSpinBox->value());
}

void MainWindow::startButtonClicked()
{
    bool check = m_initMatrix->checkMatrix() && m_finalMatrix->checkMatrix();
    if(!check)
        statusBar()->showMessage("Неверный формат ввода!");
    else {
        int x = 0, y = 0;
        m_finalMatrix->findBlankItem(x, y);
        m_count = 0;
        m_result = AStar::solve(m_finalMatrix->getMatrix(), x, y, m_initMatrix->getMatrix(), m_count);

        if(m_result == nullptr)
            m_stepCount->setText("Решения нет.");
        else {
            m_stepCount->setText("Необходимое количество шагов: " + QString::number(m_count));
            m_nextButton->setDisabled(false);
            showResultMatrix();
        }

    }
}

void MainWindow::showResultMatrix()
{
    if(m_result != nullptr){
        m_resultMatrix->setMatrix(m_result->getMatrix().size(), m_result->getMatrix());
        m_result = m_result->getParent();
    }
    else{
        m_startButton->setDisabled(false);
        m_nextButton->setDisabled(true);
    }


}
