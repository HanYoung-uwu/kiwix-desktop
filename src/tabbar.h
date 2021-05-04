#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabBar>
#include <QStackedWidget>
#include <memory>
#include "webview.h"
#include "zimview.h"
#include "contentmanagerview.h"
#include <QMouseEvent>
#include <QWebEngineFullScreenRequest>

class TabBar : public QTabBar
{
    Q_OBJECT
    Q_PROPERTY(QString currentZimId READ currentZimId NOTIFY currentZimIdChanged)

public:
    TabBar(QWidget* parent=nullptr);
    void setStackedWidget(QStackedWidget* widget);

    void     setContentManagerView(ContentManagerView* view);
    void     setNewTabButton();
    ZimView* createNewTab(bool setCurrent);

    ZimView* currentZimView() {
        return qobject_cast<ZimView*>(mp_stackedWidget->currentWidget());
    }

    WebView* currentWebView() {
        if (ZimView *zv = currentZimView())
            return zv->getWebView();
        return nullptr;
    }

    void openUrl(const QUrl &url, bool newTab);
// Redirect call to sub-webView
    void setTitleOf(const QString& title, ZimView* tab=nullptr);
    void setIconOf(const QIcon& icon, ZimView* tab=nullptr);
    QString currentZimId();

    void triggerWebPageAction(QWebEnginePage::WebAction action, ZimView* widget=nullptr);
    QString currentArticleUrl();
    QString currentArticleTitle();
    virtual QSize tabSizeHint(int index) const;
    void openFindInPageBar();
    void closeTabsByZimId(const QString &id);

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

signals:
    void webActionEnabledChanged(QWebEnginePage::WebAction action, bool enabled);
    void libraryPageDisplayed(bool displayed);
    void currentZimIdChanged(const QString& zimId);
    void currentTitleChanged(const QString& title);

public slots:
    void closeTab(int index);
    void onCurrentChanged(int index);

private:
    QStackedWidget*     mp_stackedWidget;

    void setSelectionBehaviorOnRemove(int index);

private slots:
    void onTabMoved(int from, int to);
};

#endif // TABWIDGET_H
