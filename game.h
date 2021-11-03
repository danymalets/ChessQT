#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QTimer>
#include <vector>
#include <stack>
#include "figure.h"
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

    Ui::Game *ui;

    int level;
    Colors userColor;

    QGraphicsScene  *scene;
    stack<Board*> boards;
    Board *board;
    Figure *figures[8][8];
    vector<Move> moves;

    void start();

    QString getStatus();
    void setStatus(QString s);

    void writeMoves();

    void rivalMove(Move m);

    Move strToMove(QString s);
    QString moveToStr(Move m);

    void closeEvent(QCloseEvent *event);
    void showBoard(bool allowMovement, Move lastMove = {-1, -1, -1, -1}, bool my = false);
    void checkEnd(Move lm, bool my);
private slots:
    void slotFromPoint();
    void update();

    void on_pushButton_clicked();
};

#endif // GAME_H
