#include "matrix.h"

Matrix::Matrix(int n, QWidget *parent)
    : QTableWidget(parent), m_size(n)
{
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::SingleSelection);

    setRowCount(n);
    setColumnCount(n);

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j)
        {
            QLineEdit *newItem = new QLineEdit("0",this);
            newItem->setValidator( new QIntValidator(0, n*n, this) );
            setCellWidget (i, j, newItem);
        }
    }
}

Matrix::~Matrix(){}

Matrix::Matrix(int n, const std::vector<std::vector<int>>& matrix, QWidget *parent)
    : QTableWidget(parent), m_size(n)
{

    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    setRowCount(n);
    setColumnCount(n);

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j)
        {
            QLineEdit *newItem = new QLineEdit(QString::number(matrix[i][j]), this);
            newItem->setValidator( new QIntValidator(0, n*n, this) );
            setCellWidget(i, j, newItem);
        }
    }
}

std::vector<std::vector<int>> Matrix::getMatrix() const {
    std::vector<std::vector<int>>matrix (m_size, std::vector<int> (m_size));
    for(int i = 0; i < m_size; ++i){
        for(int j = 0; j < m_size; ++j)
        {
            matrix[i][j] = dynamic_cast<QLineEdit*>(cellWidget(i, j))->text().toInt();
        }
    }

    return matrix;
}

bool Matrix::checkMatrix() const{
    std::vector<int> numbers (m_size*m_size);

    for(int i = 0; i < m_size; ++i){
        for(int j = 0; j < m_size; ++j)
        {
            if (numbers[dynamic_cast<QLineEdit*>(cellWidget(i, j))->text().toInt()]++ != 0)
                    return false;
        }
    }
    return true;
}

void Matrix::findBlankItem(int&x, int&y){
    for(int i = 0; i < m_size; ++i){
        for(int j = 0; j < m_size; ++j)
        {
            if (dynamic_cast<QLineEdit*>(cellWidget(i, j))->text().toInt() == 0)
            {
                x = i; y = j;
            }

        }
    }
}
