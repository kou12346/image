#include "imagetransform.h"
#include <QPixmap>
#include <QFileDialog>
imagetransform::imagetransform(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    leftLayout = new QVBoxLayout(this);
    mirrorGroup = new QGroupBox(QStringLiteral("鏡射"),this);
    groupLayout = new QVBoxLayout(mirrorGroup);

    hCheckBox = new QCheckBox(QStringLiteral("水平"),mirrorGroup);
    vCheckBox = new QCheckBox(QStringLiteral("垂直"),mirrorGroup);
    mirrorButton = new QPushButton(QStringLiteral("執行"),mirrorGroup);
    savefileButton = new QPushButton(QStringLiteral("儲存"),mirrorGroup); //
    hCheckBox->setGeometry(QRect(13,28,87,19));
    vCheckBox->setGeometry(QRect(13,54,87,19));
    mirrorButton->setGeometry(QRect(13,80,93,28));
    groupLayout->addWidget(hCheckBox);
    groupLayout->addWidget(vCheckBox);
    groupLayout->addWidget(mirrorButton);
    groupLayout->addWidget(savefileButton); //
    leftLayout->addWidget(mirrorGroup);
    rotateDial = new QDial(this);
    rotateDial->setNotchesVisible(true);
    vSpacer = new QSpacerItem(20,58,QSizePolicy::Minimum,QSizePolicy::Expanding);

    leftLayout->addWidget(rotateDial);
    leftLayout->addItem(vSpacer);
    mainLayout->addLayout(leftLayout);

    inWin = new QLabel(this);
    inWin->setScaledContents(true);
    QPixmap *initPixmap = new QPixmap(300,200);
    initPixmap->fill(QColor(255,255,255));
    inWin->setPixmap(*initPixmap);
    inWin->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    if(srcImg.isNull()){
        QPixmap *initPixmap = new QPixmap(300,200);
        initPixmap->fill(QColor(255,255,255));
        inWin->setPixmap(*initPixmap);
    }
    mainLayout->addWidget(inWin);
    connect(mirrorButton,SIGNAL(clicked()),this,SLOT(mirroredImage()));
    connect(rotateDial,SIGNAL(valueChanged(int)),this,SLOT(rotatedImage()));
    connect(savefileButton,SIGNAL(clicked()),this,SLOT(saveFile())); //
}

imagetransform::~imagetransform() {}
void imagetransform::mirroredImage(){
    bool H,V;
    if(srcImg.isNull())
        return;
    H=hCheckBox->isChecked();
    V=vCheckBox->isChecked();
    dstImg = srcImg.mirrored(H,V);
    inWin->setPixmap(QPixmap::fromImage(dstImg));
    srcImg = dstImg;
}

void imagetransform::rotatedImage(){
    QTransform tran;
    int angle;
    if(srcImg.isNull())
        return;
    angle = rotateDial->value();
    tran.rotate(angle);
    dstImg = srcImg.transformed(tran);
    inWin->setPixmap(QPixmap::fromImage(dstImg));
}
void imagetransform::saveFile(){ //
    QString saveFileName = QFileDialog::getSaveFileName(this,
                          QStringLiteral("儲存影像"),tr("."),
                          "bmp(*.bmp);;png(*.png)"";;Jpeg(*.jpg)");
    if(!saveFileName.isEmpty())
    {
        dstImg.save(saveFileName);
    }
}
