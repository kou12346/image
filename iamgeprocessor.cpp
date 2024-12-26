#include "iamgeprocessor.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>
#include "imagetransform.h"

IamgeProcessor::IamgeProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("影像處理"));
    central = new QWidget();
    QHBoxLayout *mainLayout=new QHBoxLayout(central);
    imgWin = new QLabel();
    QPixmap      *initPixmap=new QPixmap(300,200);
    gWin = new imagetransform();
    initPixmap->fill(QColor(255,255,255));
    imgWin->resize(300,200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget(central);
    createActions();
    createMenus();
    createToolBars();

    anotherWin = new QLabel();
    anotherWin->setScaledContents(true);
    anotherWin->resize(600, 400);
}

IamgeProcessor::~IamgeProcessor() {

}

void IamgeProcessor::createActions() {
    openFileAction=new QAction(QStringLiteral("開啟檔案&O"),this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("開啟影像檔案"));
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(showOpenFile()));

    exitAction=new QAction(QStringLiteral("結束&Q"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程式"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    zoombig=new QAction(QStringLiteral("放大"),this);
    zoombig->setShortcut(tr("Ctrl+B"));
    zoombig->setStatusTip(QStringLiteral("影像放大"));
    connect(zoombig,SIGNAL(triggered()),this,SLOT(big()));

    zoomsmall=new QAction(QStringLiteral("縮小"),this);
    zoomsmall->setShortcut(tr("Ctrl+S"));
    zoomsmall->setStatusTip(QStringLiteral("影像縮小"));
    connect(zoomsmall,SIGNAL(triggered()),this,SLOT(small()));

    geometryAction = new QAction(QStringLiteral("幾何轉換"),this);
    geometryAction->setShortcut(tr("Ctrl+G"));
    geometryAction->setStatusTip(QStringLiteral("影像幾何轉換"));
    connect(geometryAction,SIGNAL(triggered()),this,SLOT(showGeometryTransform()));
    connect(exitAction,SIGNAL(triggered()),gWin,SLOT(close()));

    savefileAction = new QAction(QStringLiteral("儲存檔案"),this); //
    savefileAction->setShortcut(tr("Ctrl+V"));
    savefileAction->setStatusTip(QStringLiteral("儲存影像檔案"));
    connect(savefileAction,SIGNAL(triggered()),this,SLOT(saveFile()));

}

void IamgeProcessor::big() {
    if (img.isNull()) return;
    QImage largeimg;
    largeimg=img.scaled(img.width()*2,img.height()*2);

    anotherWin->setPixmap(QPixmap::fromImage(largeimg));
    anotherWin->adjustSize();
    anotherWin->show();
}

void IamgeProcessor::small() {
    if (img.isNull()) return;
    QImage largeimg;
    largeimg=img.scaled(img.width()/2,img.height()/2);

    anotherWin->setPixmap(QPixmap::fromImage(largeimg));
    anotherWin->adjustSize();
    anotherWin->show();
}

void IamgeProcessor::createMenus() {
    fileMenu=menuBar()->addMenu(QStringLiteral("檔案&F"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(geometryAction);
    fileMenu->addAction(exitAction);
    fileMenu=menuBar()->addMenu(QStringLiteral("工具&T"));
    fileMenu->addAction(zoombig);
    fileMenu->addAction(zoomsmall);

}



void IamgeProcessor::createToolBars() {
    fileTool=addToolBar("file");
    fileTool->addAction(openFileAction);
    fileTool=addToolBar("zoom");
    fileTool->addAction(zoombig);
    fileTool->addAction(zoomsmall);
    fileTool->addAction(geometryAction);
    fileTool->addAction(savefileAction); //
}

void IamgeProcessor::loadFile(QString filename) {
    qDebug()<<QString("file name:%l").arg(filename);
    QByteArray ba=filename.toLatin1();
    printf("FN:%s\n",(char *) ba.data());
    img.load(filename);
    imgWin->setPixmap(QPixmap::fromImage(img));
}

void IamgeProcessor::showOpenFile() {
    filename=QFileDialog::getOpenFileName(this,
                          QStringLiteral("開啟影像"),tr("."),
                          "bmp(*.bmp);;png(*.png)"";;Jpeg(*.jpg)");
    if(!filename.isEmpty())
    {
        if(img.isNull())
        {
            loadFile(filename);
        }
        else
        {
            IamgeProcessor *newIPWin=new IamgeProcessor();
            newIPWin->show();
            newIPWin->loadFile(filename);
        }
    }
}
void IamgeProcessor::showGeometryTransform(){
    if(!img.isNull())
    gWin->srcImg=img;
    gWin->inWin->setPixmap(QPixmap::fromImage(gWin->srcImg));
    gWin->show();
}

void IamgeProcessor::saveFile(){ //
    QString saveFileName = QFileDialog::getSaveFileName(this,
                          QStringLiteral("儲存影像"),tr("."),
                          "bmp(*.bmp);;png(*.png)"";;Jpeg(*.jpg)");
    if(!saveFileName.isEmpty())
    {
        img.save(saveFileName);
    }
}
