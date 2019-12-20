#ifndef MATRIX_H
#define MATRIX_H
#include <QLayout>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QTableWidget>
#include <QHeaderView>
#include <QLineEdit>

class Matrix : public QTableWidget
{
public:
    Matrix(int n, QWidget *parent = nullptr);
    Matrix(int n, const std::vector<std::vector<int>>& matrix, QWidget *parent = nullptr);
    std::vector<std::vector<int>> getMatrix() const ;
    bool checkMatrix() const;
    void findBlankItem(int&x, int&y);
    ~Matrix();

private:
    int m_size;
};

#endif // MATRIX_H
