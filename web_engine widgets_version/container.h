/* container.h */

#ifndef CONTAINER_H
#define CONTAINER_H

#include <QApplication>
#include <QtWebEngineWidgets>
#include <QUrl>

class MainWindow : public QMainWindow {
    Q_OBJECT

        public slots:

    void toggleFullScreen() {
        if(isFullScreen()) {
            setWindowState(Qt::WindowNoState);
        }else {
            //qDebug() << "Hiding cursor";
            setWindowState(Qt::WindowFullScreen);
            hideCursor();
        }
    }

    void hideCursor() {
        int width = QApplication::desktop()->screenGeometry().width();
         int height = QApplication::desktop()->screenGeometry().height();

         QPoint bottomRight = QPoint(width, height);
         QCursor::setPos(bottomRight);
    }

public:
    explicit MainWindow(const QUrl &url) :
        content(std::make_unique<QWebEngineView>()),
        layout(std::make_unique<QVBoxLayout>()),
        window(std::make_unique<QWidget>())
    {
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(content.get());
        window->setLayout(layout.get());
        setCentralWidget(window.get());

        loadUrl(url);
    }

    void loadUrl(const QUrl &url) {
        if (!url.isValid()) {
            qWarning() << "invalid url: " << url;
            return;
        }
        content->setContextMenuPolicy(Qt::NoContextMenu);
        content->load(url);
        content->setFocus();
        content->show();
        connect(content.get(), &QWebEngineView::titleChanged, [this](const QString &title){
            setWindowTitle(title);
        });
    }

private:

    std::unique_ptr<QWebEngineView> content;
    std::unique_ptr<QVBoxLayout> layout;
    std::unique_ptr<QWidget> window;
    std::unique_ptr<QTimer> cursorTimer;

};

#endif // CONTAINER_H
