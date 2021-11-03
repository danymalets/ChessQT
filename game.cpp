#include "game.h"
#include "ui_game.h"
#include <QFile>
#include <QProcess>
#include<iostream>

#include <QCloseEvent>

QString CONNECT_1 = "cnct1";
QString CONNECT_2 = "cnct2";
QString WAITM = "waitm";
QString END =       "endgm";
QString APP_PATH = "//Users//danielmalec//Desktop//sp//build-chess-Qt_6_1_3_for_macOS-Release//chess.app";
QString STATUS_PATH = "//Users//danielmalec//Desktop//sp//ChessQT//game//status.txt";


Game::Game(QWidget *parent): QMainWindow(parent), ui(new Ui::Game)
{
    ui->setupUi(this);
    setWindowTitle("Шахматы");
    scene = new QGraphicsScene();
    scene->setSceneRect(-400, -400, 800, 800);
    ui->textEdit->setReadOnly(true);
    ui->radioButton->click();
    ui->graphicsView->setScene(scene);
    userColor = white;

    start();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);
}

void Game::start()
{
    moves.clear();
    while (!boards.empty()) boards.pop();
    board = new Board();

    QString status = getStatus();
    if (status == END){
        userColor = white;
        setStatus(CONNECT_1);
    }
    else if (status == CONNECT_1){
        userColor = black;
        ui->label_5->setText("Ход соперника");
        setStatus(CONNECT_2);
    }
    else{
        QApplication::quit();
    }
    showBoard(false);
    Board *nBoard = new Board();
    nBoard->copy(board);
    boards.push(nBoard);
}


void Game::update()
{
    QString status = getStatus();
    if (userColor == white){
        if (status == END){
            QApplication::quit();
        }
        else if (status == CONNECT_1){
            // wait
        }
        else if (status == CONNECT_2){
            ui->label_5->setText("Ваш ход");
            setStatus(WAITM);
            showBoard(true);
        }
        else if (status == WAITM){
            // wait
        }
        else{
            if (status[4] == 'b'){
                rivalMove(strToMove(status));
            }
            //ui->pushButton->setText("w" + QString::number(rand() % 10)  + "|" + status + "|" + QString::number(status.length()));
        }
    }
    else{
        if (status == END){
            QApplication::quit();
        }
        else if (status == CONNECT_1){
            // error
        }
        else if (status == CONNECT_2){
            // wait
        }
        else if (status == WAITM){
            // wait
        }
        else{
            if (status[4] == 'w'){
                rivalMove(strToMove(status));
            }
            //ui->pushButton->setText("b" +QString::number(rand() % 10)  + "|" + status + "|" + QString::number(status.length()));
        }
    }
}

void Game::slotFromPoint(){
    Move m;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (figures[i][j]->wasMove) {
                m = figures[i][j]->move;
            }
        }
    }

    showBoard(false, m, true);
    moves.push_back(m);
    writeMoves();
    setStatus(moveToStr(m) + (userColor == white ? QString("w") : QString("b")));
    ui->label_5->setText("Ход соперника");
    checkEnd(m, true);
}

void Game::rivalMove(Move m)
{
    moves.push_back(m);
    writeMoves();
    if (userColor == black) m = {m.x1, 7 - m.y1, m.x2, 7 - m.y2};
    board->move(m);
    showBoard(true, m, false);
    setStatus(WAITM);
    ui->label_5->setText("Ваш ход");
    checkEnd(m, false);
}

void Game::checkEnd(Move lm, bool my)
{
    if (board->isMate(black)){
        showBoard(false, lm, my);
        ui->label_5->setText("Мат. Вы победили!");
        return;
    }
    if (board->isStalemate(black)){
        showBoard(false, lm, my);
        ui->label_5->setText("Пат. Ничья.");
        return;
    }
    if (board->isMate(white)){
        showBoard(false, lm, my);
        ui->label_5->setText("Мат. Вы проиграли.");
        return;
    }
    if (board->isStalemate(white)){
        showBoard(false, lm);
        ui->label_5->setText("Пат. Ничья.");
        return;
    }
}

void Game::showBoard(bool allowMovement, Move lastMove, bool my)
{
    scene->clear();
    scene->addRect(-430, -430, 860, 860, QPen(Qt::NoPen), QBrush(QColor("#634936")));
    QGraphicsTextItem *text;
    if (userColor == white){
        for (int i = 0; i < 8; i++){
            text = scene->addText(QString(char(i + 'a')), QFont("Calibri", 18));
            text->setDefaultTextColor(QColor(214, 198, 174));
            text->setPos(-360 + i * 100, 400);
        }
        for (int i = 0; i < 8; i++){
            text = scene->addText(QString::number(i + 1), QFont("Calibri", 18));
            text->setDefaultTextColor(QColor(214, 198, 174));
            text->setPos(-421, 335 - i * 100);
        }
    }
    else{
        for (int i = 0; i < 8; i++){
            text = scene->addText(QString(char((7 - i) + 'a')), QFont("Calibri", 18));
            text->setDefaultTextColor(QColor(214, 198, 174));
            text->setPos(-360 + i * 100, 400);
        }
        for (int i = 0; i < 8; i++){
            text = scene->addText(QString::number(8 - i), QFont("Calibri", 18));
            text->setDefaultTextColor(QColor(214, 198, 174));
            text->setPos(-421, 335 - i * 100);
        }
    }

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if ((i + j) % 2 == 0){
                scene->addRect(-400 + i * 100, -400 + j * 100, 100, 100, QPen(Qt::NoPen), QBrush(Qt::gray));
            }
            else{
                scene->addRect(-400 + i * 100, -400 + j * 100, 100, 100, QPen(Qt::NoPen), QBrush(Qt::darkGray));
            }

    Move m = lastMove;
    if (m.x1 != -1){
        if (userColor == black) m = {7 - m.x1, m.y1, 7 - m.x2, m.y2};
        if (userColor == black && my) m = { m.x1,7 -m.y1,  m.x2, 7 -m.y2};
        if ((m.x1 + m.y1) % 2 == 0)
            scene->addRect(-400 + m.x1 * 100, -400 + m.y1 * 100, 100, 100,
                           QPen(Qt::red), QBrush(Qt::gray));
        else
            scene->addRect(-400 + m.x1 * 100, -400 + m.y1 * 100, 100, 100,
                           QPen(Qt::red), QBrush(Qt::darkGray));

        if ((m.x2 + m.y2) % 2 == 0)
            scene->addRect(-400 + m.x2 * 100, -400 + m.y2 * 100, 100, 100,
                           QPen(Qt::red), QBrush(Qt::gray));
        else
            scene->addRect(-400 + m.x2 * 100, -400 + m.y2 * 100, 100, 100,
                           QPen(Qt::red), QBrush(Qt::darkGray));
    }
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            figures[i][j] = new Figure(board, i, j, allowMovement, userColor);
            scene->addItem(figures[i][j]);
            connect(figures[i][j], SIGNAL(moveSignal()), this, SLOT(slotFromPoint()));
        }
    }
}

void Game::writeMoves()
{
    ui->textEdit->setText("");
    for (int i = 0; i < (int)moves.size(); i += 2){
        if (i + 1 == (int)moves.size())
            ui->textEdit->append(QString::number(i/2+1) + ".   " + moveToStr(moves[i]));
        else
            ui->textEdit->append(QString::number(i/2+1) + ".   " + moveToStr(moves[i]) + "    " + moveToStr(moves[i + 1]));
    }
}

Game::~Game()
{
    delete ui;
}

void Game::on_pushButton_clicked()
{
    QProcess *process = new QProcess(this);
    process->start(APP_PATH);
}


QString Game::getStatus()
{
    QFile file(STATUS_PATH);
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream(&file);
        return stream.readLine();
    }
    return "error";
}

void Game::setStatus(QString s){
    QFile file(STATUS_PATH);
    if ( file.open(QFile::WriteOnly | QFile::Truncate) )
    {
        QTextStream stream(&file);
        stream << s;
        stream.flush();
    }
}

void Game::closeEvent (QCloseEvent *event)
{
    setStatus(END);
    event->accept();
}


Move Game::strToMove(QString s)
{
    return {s[0].unicode() - 'a',
            (8 - (s[1].unicode() - '0')),
            s[2].unicode() - 'a',
            (8 - (s[3].unicode() - '0'))};
}

QString Game::moveToStr(Move m)
{
    return QString("") +
           QChar(m.x1+ 'a') +
           QChar(8 - m.y1 + '0') +
           QChar(m.x2 + 'a') +
           QChar(8 - m.y2 + '0');
}





