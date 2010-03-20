#include "mainwindow.h"

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>

#include <core/gluon_version.h>

int main(int argc, char **argv)
{
    KAboutData aboutData("gluoncreator", NULL,
                         ki18n("Gluon Creator"), GLUON_VERSION_STRING,
                         ki18n((QString("A game creation tool.\nUsing %1 Version %2").arg(GLUON_PLATFORM_NAME).arg(GLUON_VERSION_STRING)).toUtf8()),
                         KAboutData::License_LGPL_V2,
                         ki18n("Copyright 2009-2010 by multiple contributors."),
                         KLocalizedString(),
                         "http://gluon.tuxfamily.org"
                        );
    aboutData.setProgramIconName("gluon_creator");
    aboutData.addAuthor(ki18n("Arjen Hiemstra"), ki18n("Gluon Core, Gluon Graphics, Gluon Engine, Gluon Creator"), "");
    aboutData.addAuthor(ki18n("Dan Leinir Tuthra Jensen"), ki18n("Gluon Core, Gluon Engine, Gluon Creator"), "");
    aboutData.addAuthor(ki18n("Sacha Schutz"), ki18n("Gluon Graphics,Gluon Audio,Gluon Input"), "");
    aboutData.addAuthor(ki18n("Guillaume Martres"), ki18n("Gluon Audio, Gluon Graphics"), "");
    aboutData.addAuthor(ki18n("Kim Jung Nissen"), ki18n("Gluon Input, Mac compatibility"), "");
    aboutData.addAuthor(ki18n("Rivo Laks"), ki18n("Gluon Graphics through KGLLIB"), "");

    KCmdLineArgs::init(argc, argv, &aboutData);
    KCmdLineOptions options;
    options.add("+file", ki18n("GDL file to open"));
    KCmdLineArgs::addCmdLineOptions(options);

    KApplication app;



    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    GluonCreator::MainWindow* window;
    if (args->count())
    {
        window = new GluonCreator::MainWindow(args->arg(0));
    }
    else
    {
        window = new GluonCreator::MainWindow();
    }
    window->show();

    app.exec();
}
