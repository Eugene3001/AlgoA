#ifndef MATRIX_H
#define MATRIX_H
#include <QLayout>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QTableWidget>
#include <QHeaderView>
#include <QLineEdit>
#include <QRandomGenerator>
class Matrix : public QTableWidget
{
public:
    Matrix(int n, QWidget *parent = nullptr);
    Matrix(int n, const std::vector<std::vector<int>>& matrix, QWidget *parent = nullptr);

    void setMatrix(int n);
    void setMatrix(int n, const std::vector<std::vector<int>>& matrix);
    std::vector<std::vector<int>> getMatrix() const ;

    bool checkMatrix() const;
    void findBlankItem(int&x, int&y);
    void fillRandom();

    ~Matrix();

private:
    int m_size;
    QRandomGenerator gen;
};

#endif // MATRIX_H
