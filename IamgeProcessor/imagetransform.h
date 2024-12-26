﻿#ifndef IMAGETRANSFORM_H
#define IMAGETRANSFORM_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QDial>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
class imagetransform : public QWidget
{
    Q_OBJECT

public:
    imagetransform(QWidget *parent = nullptr);
    ~imagetransform();
    QLabel    *inWin;
    QGroupBox *mirrorGroup;
    QCheckBox *hCheckBox;
    QCheckBox *vCheckBox;
    QPushButton *mirrorButton;
    QDial *rotateDial;
    QSpacerItem *vSpacer;
    QHBoxLayout *mainLayout;
    QVBoxLayout *groupLayout;
    QVBoxLayout *leftLayout;
    QImage srcImg;
    QImage dstImg;
    QAction *savefileAction;
    QPushButton *savefileButton;
private slots:
    void mirroredImage();
    void rotatedImage();
    void saveFile(); //
};
#endif // IMAGETRANSFORM_H
