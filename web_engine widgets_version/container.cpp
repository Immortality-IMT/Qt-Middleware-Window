#include "container.h"

int main(int argc, char **argv) {

        QApplication app(argc, argv);
        //MainWindow window(QUrl("http://127.0.0.1/axx/"))
        MainWindow window(QUrl::fromLocalFile("/home/user/Download/Qt-Middleware-Container/build-Qt_Container-Desktop-Debug/vid.html"));
        window.showMaximized();
        QShortcut* fullscreenShortcut = new QShortcut(QKeySequence(Qt::Key_F), &window);
        QObject::connect(fullscreenShortcut, &QShortcut::activated, &window, &MainWindow::toggleFullScreen);
        return app.exec();
}
