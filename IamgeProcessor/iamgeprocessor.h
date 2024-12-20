#ifndef IAMGEPROCESSOR_H
#define IAMGEPROCESSOR_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>

class IamgeProcessor : public QMainWindow
{
    Q_OBJECT

public:
    IamgeProcessor(QWidget *parent = nullptr);
    ~IamgeProcessor();
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);
private slots:
    void showOpenFile();
    void big();
    void small();

private:
    QWidget *central;
    QMenu   *fileMenu;
    QToolBar   *fileTool;
    QImage   img;
    QString   filename;
    QLabel   *imgWin;
    QLabel   *anotherWin;
    QAction   *openFileAction;
    QAction   *exitAction;
    QAction   *zoombig;
    QAction   *zoomsmall;

};
#endif // IAMGEPROCESSOR_H
