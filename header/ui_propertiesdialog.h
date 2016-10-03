/********************************************************************************
** Form generated from reading UI file 'propertiesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTIESDIALOG_H
#define UI_PROPERTIESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PropertiesDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QDoubleSpinBox *xSpinBox;
    QSpacerItem *spacerItem;
    QLabel *label_2;
    QDoubleSpinBox *ySpinBox;
    QSpacerItem *spacerItem1;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *backgroundColorLabel;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *outlineColorLabel;
    QLabel *label_5;
    QLineEdit *textLineEdit;
    QPushButton *outlineColorButton;
    QPushButton *backgroundColorButton;
    QSpacerItem *spacerItem2;
    QDialogButtonBox *buttonBox;
    QRadioButton *radioButton;

    void setupUi(QDialog *PropertiesDialog)
    {
        if (PropertiesDialog->objectName().isEmpty())
            PropertiesDialog->setObjectName(QStringLiteral("PropertiesDialog"));
        PropertiesDialog->resize(322, 350);
        vboxLayout = new QVBoxLayout(PropertiesDialog);
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        groupBox = new QGroupBox(PropertiesDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        hboxLayout = new QHBoxLayout(groupBox);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(9, 9, 9, 9);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        hboxLayout->addWidget(label);

        xSpinBox = new QDoubleSpinBox(groupBox);
        xSpinBox->setObjectName(QStringLiteral("xSpinBox"));

        hboxLayout->addWidget(xSpinBox);

        spacerItem = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        hboxLayout->addWidget(label_2);

        ySpinBox = new QDoubleSpinBox(groupBox);
        ySpinBox->setObjectName(QStringLiteral("ySpinBox"));

        hboxLayout->addWidget(ySpinBox);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);


        vboxLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(PropertiesDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, 9);
        backgroundColorLabel = new QLabel(groupBox_2);
        backgroundColorLabel->setObjectName(QStringLiteral("backgroundColorLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(backgroundColorLabel->sizePolicy().hasHeightForWidth());
        backgroundColorLabel->setSizePolicy(sizePolicy);
        backgroundColorLabel->setFrameShape(QFrame::StyledPanel);
        backgroundColorLabel->setFrameShadow(QFrame::Raised);
        backgroundColorLabel->setScaledContents(true);

        gridLayout->addWidget(backgroundColorLabel, 2, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        outlineColorLabel = new QLabel(groupBox_2);
        outlineColorLabel->setObjectName(QStringLiteral("outlineColorLabel"));
        sizePolicy.setHeightForWidth(outlineColorLabel->sizePolicy().hasHeightForWidth());
        outlineColorLabel->setSizePolicy(sizePolicy);
        outlineColorLabel->setFrameShape(QFrame::StyledPanel);
        outlineColorLabel->setFrameShadow(QFrame::Raised);
        outlineColorLabel->setScaledContents(true);

        gridLayout->addWidget(outlineColorLabel, 1, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        textLineEdit = new QLineEdit(groupBox_2);
        textLineEdit->setObjectName(QStringLiteral("textLineEdit"));

        gridLayout->addWidget(textLineEdit, 0, 1, 1, 2);

        outlineColorButton = new QPushButton(groupBox_2);
        outlineColorButton->setObjectName(QStringLiteral("outlineColorButton"));

        gridLayout->addWidget(outlineColorButton, 1, 2, 1, 1);

        backgroundColorButton = new QPushButton(groupBox_2);
        backgroundColorButton->setObjectName(QStringLiteral("backgroundColorButton"));

        gridLayout->addWidget(backgroundColorButton, 2, 2, 1, 1);


        vboxLayout->addWidget(groupBox_2);

        spacerItem2 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem2);

        buttonBox = new QDialogButtonBox(PropertiesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);

        radioButton = new QRadioButton(PropertiesDialog);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        vboxLayout->addWidget(radioButton);

#ifndef QT_NO_SHORTCUT
        label_4->setBuddy(textLineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(PropertiesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PropertiesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PropertiesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PropertiesDialog);
    } // setupUi

    void retranslateUi(QDialog *PropertiesDialog)
    {
        PropertiesDialog->setWindowTitle(QApplication::translate("PropertiesDialog", "Edit Properties", 0));
        groupBox->setTitle(QApplication::translate("PropertiesDialog", "Position", 0));
        label->setText(QApplication::translate("PropertiesDialog", "&X:", 0));
        label_2->setText(QApplication::translate("PropertiesDialog", "&Y:", 0));
        groupBox_2->setTitle(QApplication::translate("PropertiesDialog", "Attributes", 0));
        label_7->setText(QApplication::translate("PropertiesDialog", "Background Color:", 0));
        label_4->setText(QApplication::translate("PropertiesDialog", "&Text:", 0));
        label_5->setText(QApplication::translate("PropertiesDialog", "Outline Color:", 0));
        outlineColorButton->setText(QApplication::translate("PropertiesDialog", "Choose...", 0));
        backgroundColorButton->setText(QApplication::translate("PropertiesDialog", "Choose...", 0));
        radioButton->setText(QApplication::translate("PropertiesDialog", "RadioButton", 0));
    } // retranslateUi

};

namespace Ui {
    class PropertiesDialog: public Ui_PropertiesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTIESDIALOG_H
