/********************************************************************************
** Form generated from reading UI file 'intro.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTRO_H
#define UI_INTRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Intro
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *welcomeLabel;
    QSpacerItem *verticalSpacer_4;
    QLabel *storageLabel;
    QLabel *sizeWarningLabel;
    QRadioButton *dataDirDefault;
    QRadioButton *dataDirCustom;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *dataDirectory;
    QPushButton *ellipsisButton;
    QSpacerItem *verticalSpacer_3;
    QLabel *freeSpace;
    QSpacerItem *verticalSpacer_2;
    QLabel *errorMessage;
    QLabel *lblExplanation1;
    QLabel *lblExplanation2;
    QLabel *lblExplanation3;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Intro)
    {
        if (Intro->objectName().isEmpty())
            Intro->setObjectName(QString::fromUtf8("Intro"));
        Intro->resize(674, 415);
        verticalLayout = new QVBoxLayout(Intro);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        welcomeLabel = new QLabel(Intro);
        welcomeLabel->setObjectName(QString::fromUtf8("welcomeLabel"));
        welcomeLabel->setStyleSheet(QString::fromUtf8("QLabel { font-style:italic; }"));
        welcomeLabel->setWordWrap(true);

        verticalLayout->addWidget(welcomeLabel);

        verticalSpacer_4 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_4);

        storageLabel = new QLabel(Intro);
        storageLabel->setObjectName(QString::fromUtf8("storageLabel"));
        storageLabel->setWordWrap(true);

        verticalLayout->addWidget(storageLabel);

        sizeWarningLabel = new QLabel(Intro);
        sizeWarningLabel->setObjectName(QString::fromUtf8("sizeWarningLabel"));
        sizeWarningLabel->setWordWrap(true);

        verticalLayout->addWidget(sizeWarningLabel);

        dataDirDefault = new QRadioButton(Intro);
        dataDirDefault->setObjectName(QString::fromUtf8("dataDirDefault"));

        verticalLayout->addWidget(dataDirDefault);

        dataDirCustom = new QRadioButton(Intro);
        dataDirCustom->setObjectName(QString::fromUtf8("dataDirCustom"));

        verticalLayout->addWidget(dataDirCustom);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        dataDirectory = new QLineEdit(Intro);
        dataDirectory->setObjectName(QString::fromUtf8("dataDirectory"));

        horizontalLayout_2->addWidget(dataDirectory);

        ellipsisButton = new QPushButton(Intro);
        ellipsisButton->setObjectName(QString::fromUtf8("ellipsisButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ellipsisButton->sizePolicy().hasHeightForWidth());
        ellipsisButton->setSizePolicy(sizePolicy);
        ellipsisButton->setMaximumSize(QSize(30, 16777215));
        ellipsisButton->setText(QString::fromUtf8("\342\200\246"));
        ellipsisButton->setAutoDefault(false);

        horizontalLayout_2->addWidget(ellipsisButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        freeSpace = new QLabel(Intro);
        freeSpace->setObjectName(QString::fromUtf8("freeSpace"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(freeSpace->sizePolicy().hasHeightForWidth());
        freeSpace->setSizePolicy(sizePolicy1);
        freeSpace->setWordWrap(true);

        verticalLayout_2->addWidget(freeSpace);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        errorMessage = new QLabel(Intro);
        errorMessage->setObjectName(QString::fromUtf8("errorMessage"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(errorMessage->sizePolicy().hasHeightForWidth());
        errorMessage->setSizePolicy(sizePolicy2);
        errorMessage->setTextFormat(Qt::RichText);
        errorMessage->setWordWrap(true);

        verticalLayout_2->addWidget(errorMessage);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout);

        lblExplanation1 = new QLabel(Intro);
        lblExplanation1->setObjectName(QString::fromUtf8("lblExplanation1"));
        lblExplanation1->setWordWrap(true);

        verticalLayout->addWidget(lblExplanation1);

        lblExplanation2 = new QLabel(Intro);
        lblExplanation2->setObjectName(QString::fromUtf8("lblExplanation2"));
        lblExplanation2->setWordWrap(true);

        verticalLayout->addWidget(lblExplanation2);

        lblExplanation3 = new QLabel(Intro);
        lblExplanation3->setObjectName(QString::fromUtf8("lblExplanation3"));
        lblExplanation3->setWordWrap(true);

        verticalLayout->addWidget(lblExplanation3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(Intro);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Intro);
        QObject::connect(buttonBox, SIGNAL(accepted()), Intro, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Intro, SLOT(reject()));

        QMetaObject::connectSlotsByName(Intro);
    } // setupUi

    void retranslateUi(QDialog *Intro)
    {
        Intro->setWindowTitle(QApplication::translate("Intro", "Welcome", nullptr));
        welcomeLabel->setText(QApplication::translate("Intro", "Welcome to %1.", nullptr));
        storageLabel->setText(QApplication::translate("Intro", "As this is the first time the program is launched, you can choose where %1 will store its data.", nullptr));
        dataDirDefault->setText(QApplication::translate("Intro", "Use the default data directory", nullptr));
        dataDirCustom->setText(QApplication::translate("Intro", "Use a custom data directory:", nullptr));
        freeSpace->setText(QString());
        lblExplanation1->setText(QApplication::translate("Intro", "When you click OK, %1 will begin to download and process the full %4 block chain (%2GB) starting with the earliest transactions in %3 when %4 initially launched.", nullptr));
        lblExplanation2->setText(QApplication::translate("Intro", "This initial synchronisation is very demanding, and may expose hardware problems with your computer that had previously gone unnoticed. Each time you run %1, it will continue downloading where it left off.", nullptr));
        lblExplanation3->setText(QApplication::translate("Intro", "If you have chosen to limit block chain storage (pruning), the historical data must still be downloaded and processed, but will be deleted afterward to keep your disk usage low.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Intro: public Ui_Intro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTRO_H
