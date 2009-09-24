#include "kclinfowidget.h"

#include <KIcon>
#include <KMessageBox>
#include <KPushButton>
#include <KSeparator>
#include <KLocale>

#include <QGroupBox>
#include <QLabel>
#include <QProcess>
#include <QVBoxLayout>

KCLInfoWidget::KCLInfoWidget(QWidget *parent)
        : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;

    m_information = new QWidget;
    m_preview = new QWidget;
    KTabWidget *tab = new KTabWidget;
    tab->addTab(m_preview, KIcon("run-build-configure.png"), "preview");
    tab->addTab(m_information, KIcon("run-build-file.png"), "information");
    setupPreview();
    setupInformation();
    layout->addWidget(tab);
    setLayout(layout);
}

void KCLInfoWidget::setupPreview()
{
    QVBoxLayout *layout = new QVBoxLayout;

    QHBoxLayout *layoutButton = new QHBoxLayout;
    QHBoxLayout *layoutAbsolu = new QHBoxLayout;
    QHBoxLayout *layoutRelatif = new QHBoxLayout;

    KCLButton *button = new KCLButton(KCL::Key);
    KCLButton *axis = new KCLButton(KCL::AbsoluAxis);
    KCLButton *rel = new KCLButton(KCL::AbsoluAxis);

    layoutButton->addWidget(button);
    layoutAbsolu->addWidget(axis);
    layoutRelatif->addWidget(rel);

    layout->addLayout(layoutButton);
    layout->addLayout(layoutAbsolu);
    layout->addLayout(layoutRelatif);
    layout->addStretch();

    m_preview->setLayout(layout);
}

void KCLInfoWidget::setupInformation()
{
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *info = new QLabel(i18n("Some Linux distributions forbid direct access \n to the input method used by KCL(evdev) as it can causes security-related issues\n"
                                    "If you are sure, you can allow direct access by clicking here."));

    KPushButton *buttonAuthorizate = new KPushButton(KIcon("dialog-password.png"), "set permission");
    KPushButton *buttonDetect = new KPushButton(KIcon("edit-find.png"), "Detect device");

    connect(buttonAuthorizate, SIGNAL(clicked()), this, SLOT(setAuthorization()));
    connect(buttonDetect, SIGNAL(clicked()), this, SLOT(detectDevice()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(info);
    hlayout->addStretch();
    hlayout->addWidget(buttonAuthorizate);
    hlayout->addWidget(buttonDetect);

    m_model = new KCLDeviceModel;
    m_treeView = new QTreeView;
    m_treeView->setModel(m_model);
    m_treeView->setIconSize(QSize(22, 22));
    layout->addLayout(hlayout);
    layout->addWidget(m_treeView);
    m_information->setLayout(layout);
}

void KCLInfoWidget::setAuthorization()
{
    //TODO: Find a better way to do that(either via HAL, PolicyKit, or use X11 libs instead of evdev.
    if (QProcess::execute("kdesudo chmod -R a+rwx /dev/input/*")) {
        KMessageBox::information(this, i18n("authorization success..."), "success");
    } else {
        KMessageBox::error(this, i18n("authorization failed..."), "failed");
    }
}

void KCLInfoWidget::detectDevice()
{
    m_model->clear();
    m_model->setupList();
}